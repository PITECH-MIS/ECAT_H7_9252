#ifndef _PDO_SLAVE_PROTOCOL_HPP
#define _PDO_SLAVE_PROTOCOL_HPP

#include <cstdint>
#include "utils.h"
#include <cstring>
#include "kfifo.h"
#include "ethercat_wrapper.hpp"

#define BUFFER_LEN 48
#define PACKET_HEADER 0x52

class pdo_protocol_buf_t
{
public:
    uint8_t header = 0;
    uint8_t packet_id = 0;
    uint8_t sender_id = 0;
    uint8_t receiver_id = 0;
    char payload[BUFFER_LEN - 6];
    uint8_t crc16_msb = 0;
    uint8_t crc16_lsb = 0;
    bool operator==(const pdo_protocol_buf_t& rhs) const
    {
        if(header != rhs.header || packet_id != rhs.packet_id) return false;
        return memcmp(&sender_id, &rhs.sender_id, sizeof(pdo_protocol_buf_t) - 2) == 0;
    }
    bool operator!=(const pdo_protocol_buf_t& rhs) const
    {
        return !(*this == rhs);
    }
    bool isValid()
    {
        if(header != PACKET_HEADER) return false;
        uint16_t crc16 = (crc16_msb << 8) | crc16_lsb;
        if(crc16 == getCRC16(&header, sizeof(pdo_protocol_buf_t) - 2)) return true;
        return false;
    }
    void prepare()
    {
        header = PACKET_HEADER;
        uint16_t crc16 = getCRC16(&header, sizeof(pdo_protocol_buf_t) - 2);
        crc16_msb = (uint8_t)(crc16 >> 8);
        crc16_lsb = (uint8_t)crc16;
    }
};

typedef void (*payload_result_cb)(char *payload, uint8_t len);

class PDOSlaveProtocol
{
public:
    PDOSlaveProtocol()
    {
        kfifo_init_s(&tx_fifo, KFIFO_STATIC_BUF_SIZE);
    };
    void onPDOLoop();
    bool SendPayload(char *payload, uint8_t len);
    void RegisterRxPayloadCallback(payload_result_cb cb) { _new_payload_cb = cb; };
    void Reset();
    bool print(const char *fmt, ...);
private:
    pdo_protocol_buf_t tx_buf;
    pdo_protocol_buf_t rx_buf;
    kfifo_static_t tx_fifo;
    payload_result_cb _new_payload_cb = nullptr;
};

void PDOSlaveProtocol::onPDOLoop()
{
    auto *ptr = (pdo_protocol_buf_t*)Obj.TxBuf;
    auto fifo_len = kfifo_used_s(&tx_fifo);
    if(fifo_len > 0)
    {
        if(fifo_len > sizeof(tx_buf.payload)) fifo_len = sizeof(tx_buf.payload);
        char buffer[sizeof(tx_buf.payload)];
        kfifo_get_s(&tx_fifo, buffer, fifo_len);
        tx_buf.packet_id++;
        memset(tx_buf.payload, 0, sizeof(tx_buf.payload));
        memcpy(tx_buf.payload, buffer, fifo_len);
        tx_buf.prepare();
        memcpy(Obj.TxBuf, &tx_buf, sizeof(tx_buf));
    }
    // if(*ptr != tx_buf && tx_buf.isValid())
    // {
    //     // printf("Sending Tx Payload\n");
    //     memcpy(Obj.TxBuf, &tx_buf, sizeof(tx_buf));
    // }
    ptr = (pdo_protocol_buf_t*)Obj.RxBuf;
    if(*ptr != rx_buf && (*ptr).isValid())
    {
        memcpy(&rx_buf, Obj.RxBuf, sizeof(rx_buf));
        // printf("Received Rx payload\n");
        if(_new_payload_cb) _new_payload_cb(rx_buf.payload, sizeof(rx_buf.payload));
    }
}

bool PDOSlaveProtocol::SendPayload(char *payload, uint8_t len)
{
    // auto *ptr = (pdo_protocol_buf_t*)Obj.TxBuf;
    // if(*ptr != tx_buf && tx_buf.isValid()) return false; // THERE IS ONGOING PAYLOAD THAT HASN'T BEEN TRANSMITTED
    // if(len > sizeof(tx_buf.payload)) len = sizeof(tx_buf.payload);
    // tx_buf.packet_id++;
    // memset(tx_buf.payload, 0, sizeof(tx_buf.payload));
    // memcpy(tx_buf.payload, payload, len);
    // tx_buf.prepare();
    kfifo_put_s(&tx_fifo, payload, strlen(payload));
    return true;
}

void PDOSlaveProtocol::Reset()
{
    memset(&tx_buf, 0, sizeof(tx_buf));
    memset(&rx_buf, 0, sizeof(rx_buf));
    memset(Obj.TxBuf, 0, sizeof(Obj.TxBuf));
    memset(Obj.RxBuf, 0, sizeof(Obj.RxBuf));
}

bool PDOSlaveProtocol::print(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char buffer[sizeof(tx_buf.payload)];
    auto buffer_len = (uint8_t)vsnprintf(buffer, sizeof(buffer), fmt, args);
    return SendPayload(buffer, buffer_len);
}

#endif