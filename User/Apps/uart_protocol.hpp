#ifndef _UART_PROTOCOL_HPP
#define _UART_PROTOCOL_HPP

#include <cstdint>
#include "utils.h"
#include "string.h"
#include "sys/param.h"

class motor_state_t
{
public:
    uint8_t IsAlive = 0;
    uint8_t Enable = 0;
    uint8_t NodeID = 0;
    uint8_t Mode = 0;
    uint8_t MotorTemp = 0;
    uint8_t MCUTemp = 0;
    uint8_t LimiterState = 0;
    uint16_t ErrorCode = 0;
    uint32_t SN = 0;
    float IqReal = 0.0f;
    float IdReal = 0.0f;
    float Vbus = 0.0f;
    float Ibus = 0.0f;
    float EstimateSpeed = 0.0f;
    float EstimateRawAngle = 0.0f;
    float CurrentLimit = 0.0f;
    bool operator==(const motor_state_t& rhs) const
    {
        return  (IqReal == rhs.IqReal) &&
                (IdReal == rhs.IdReal) &&
                (Vbus == rhs.Vbus) &&
                (Ibus == rhs.Ibus) &&
                (EstimateSpeed == rhs.EstimateSpeed) &&
                (EstimateRawAngle == rhs.EstimateRawAngle) &&
                (CurrentLimit == rhs.CurrentLimit) &&
                (IsAlive == rhs.IsAlive) &&
                (Enable == rhs.Enable) &&
                (Mode == rhs.Mode) &&
                (MotorTemp == rhs.MotorTemp) &&
                (MCUTemp == rhs.MCUTemp) &&
                (LimiterState == rhs.LimiterState) &&
                (ErrorCode == rhs.ErrorCode) &&
                (NodeID == rhs.NodeID) &&
                (SN == rhs.SN);
    }
};

class motor_set_t
{
public:
    uint8_t Enable = 0;
    uint8_t Mode = 0;
    float IqSet = 0.0f;
    float SetSpeed = 0.0f;
    float SetRawAngle = 0.0f;
    float SetTrajectoryAngle = 0.0f;
    float SetCurrentLimit = 0.0f;
    bool operator==(const motor_set_t& rhs) const // optimized short-circuit condition
    {
        return  (Enable == rhs.Enable) &&
                (SetTrajectoryAngle == rhs.SetTrajectoryAngle) &&
                (Mode == rhs.Mode) &&
                (SetSpeed == rhs.SetSpeed) &&
                (SetRawAngle == rhs.SetRawAngle) &&
                (SetCurrentLimit == rhs.SetCurrentLimit);
    }
};

#define PDO_PAYLOAD_LEN 42

// #pragma pack(push, 1)

template<class T>
class uart_buffer_t
{
public:
    enum class Type : uint8_t
    {
        MOTOR = sizeof(T) % 0x11,
        PAYLOAD = sizeof(T) % 0x13,
    };
    Type header = Type::MOTOR;
    char payload[MAX(sizeof(T), PDO_PAYLOAD_LEN)];
    uint8_t crc16_msb = 0;
    uint8_t crc16_lsb = 0;
    bool operator==(const uart_buffer_t<T>& rhs) const
    {
        if(header != rhs.header) return false;
        return memcmp(payload, rhs.payload, sizeof(uart_buffer_t<T>) - 1) == 0;
    }
    bool operator!=(const uart_buffer_t<T>& rhs) const
    {
        return !(*this == rhs);
    }
    bool isValid()
    {
        if(header != Type::MOTOR && header != Type::PAYLOAD) return false;
        uint16_t crc16 = (crc16_msb << 8) | crc16_lsb;
        if(crc16 == getCRC16((uint8_t*)&header, sizeof(uart_buffer_t<T>) - 2)) return true;
        return false;
    }
    void prepare(Type type, uint32_t _sn)
    {
        header = type;
        uint16_t crc16 = getCRC16((uint8_t*)&header, sizeof(uart_buffer_t<T>) - 2);
        crc16_msb = (uint8_t)(crc16 >> 8);
        crc16_lsb = (uint8_t)crc16;
    }
    T* getPayload()
    {
        return (T*)payload;
    }
};

template<>
class uart_buffer_t<motor_set_t>
{
public:
    enum class Type : uint8_t
    {
        MOTOR = sizeof(motor_set_t) % 0x11,
        PAYLOAD = sizeof(motor_set_t) % 0x13,
    };
    Type header = Type::MOTOR;
    uint32_t SN = 0;
    char payload[MAX(sizeof(motor_set_t), PDO_PAYLOAD_LEN)];
    uint8_t crc16_msb = 0;
    uint8_t crc16_lsb = 0;
    bool operator==(const uart_buffer_t<motor_set_t>& rhs) const
    {
        if(header != rhs.header || SN != rhs.SN) return false;
        return memcmp(payload, rhs.payload, sizeof(uart_buffer_t<motor_set_t>) - 5) == 0;
    }
    bool operator!=(const uart_buffer_t<motor_set_t>& rhs) const
    {
        return !(*this == rhs);
    }
    bool isValid()
    {
        if(header != Type::MOTOR && header != Type::PAYLOAD) return false;
        uint16_t crc16 = (crc16_msb << 8) | crc16_lsb;
        if(crc16 == getCRC16((uint8_t*)&header, sizeof(uart_buffer_t<motor_set_t>) - 2)) return true;
        return false;
    }
    void prepare(Type type, uint32_t _sn)
    {
        header = type;
        SN = _sn;
        uint16_t crc16 = getCRC16((uint8_t*)&header, sizeof(uart_buffer_t<motor_set_t>) - 2);
        crc16_msb = (uint8_t)(crc16 >> 8);
        crc16_lsb = (uint8_t)crc16;
    }
    motor_set_t* getPayload()
    {
        return (motor_set_t*)payload;
    }
};

// #pragma pack(pop)

#define DEAD_TIMEOUT_TICKS 500
#define UART_KEEPALIVE_TICKS 100

#define MASTER_ROLE 1
#define SLAVE_ROLE  2

#define ROLE MASTER_ROLE

#if ROLE == MASTER_ROLE  // Tx set buffer, Rx state buffer, automatically parse rx state
#define TX_FUNC_NAME SendTxSet
#define TX_STRUCT_NAME motor_set_t
#define RX_STRUCT_NAME motor_state_t
#elif ROLE == SLAVE_ROLE // Tx state buffer, Rx set buffer, automatically parse rx set
#define TX_FUNC_NAME SendTxState
#define TX_STRUCT_NAME motor_state_t
#define RX_STRUCT_NAME motor_set_t
#endif

typedef void (*rx_payload_cb)(char *payload, uint8_t len);

class UARTProtocol
{
public:
    UARTProtocol(uint32_t _sn = 0) : target_sn(_sn) {};
    uint32_t target_sn = 0;
    bool IsRemoteAlive();
    bool OnRxBuffer(char *buffer, uint16_t max_len);
    bool SendTxPayload(char *payload, uint8_t len); 
    void RegisterRxPayloadCallback(rx_payload_cb cb) { _rx_payload_cb = cb; };
    bool requestedTx = false; // if requestedTx, then serialize tx_buffer to char array
    uart_buffer_t<TX_STRUCT_NAME> tx_buffer; // readonly outside
    uart_buffer_t<RX_STRUCT_NAME> rx_buffer; // writeonly in OnRxBuffer, then parse directly to target_rx_ptr
    bool TX_FUNC_NAME(TX_STRUCT_NAME *data); // will be called periodically, if not, then this device is dead.
    RX_STRUCT_NAME *target_rx_ptr = nullptr;
private:
    rx_payload_cb _rx_payload_cb = nullptr;
    uint32_t last_tx_tick = 0;
    uint32_t last_rx_tick = 0;
};

bool UARTProtocol::IsRemoteAlive()
{
    if(HAL_GetTick() - last_rx_tick >= DEAD_TIMEOUT_TICKS) return false;
    return true;
}

bool UARTProtocol::OnRxBuffer(char *buffer, uint16_t max_len)
{
    if(max_len < sizeof(decltype(rx_buffer))) return false;
    auto *rx_struct = (decltype(rx_buffer)*)buffer;
#if ROLE == SLAVE_ROLE // check for condition that one buffer contains multiple struct.
    do
    {
        if((*rx_struct).isValid()) break;
        buffer++;
        rx_struct = (decltype(rx_buffer)*)buffer;
    }while(max_len--);
    if(max_len == 0) return false;
    // if((*rx_struct).)
#endif
    // if ROLE == MASTER_ROLE, the validness is ensured by UARTArbiter
    // Received valid buffer.
    if((*rx_struct) != rx_buffer)
    {
        if((*rx_struct).header == uart_buffer_t<RX_STRUCT_NAME>::Type::MOTOR)
        {
            if(target_rx_ptr) memcpy(target_rx_ptr, (*rx_struct).payload, sizeof(RX_STRUCT_NAME));
        }
        else
        {
            if(_rx_payload_cb) _rx_payload_cb((*rx_struct).payload, sizeof((*rx_struct).payload));
        }
        memcpy(&rx_buffer, rx_struct, sizeof(decltype(rx_buffer)));
    }
    last_rx_tick = HAL_GetTick();
    return true;
}

bool UARTProtocol::SendTxPayload(char *payload, uint8_t len)
{
    if(target_sn == 0)
    {
        requestedTx = false;
        return false;
    }
    if(requestedTx) return false; // previous Tx process not over
    if(len > sizeof(tx_buffer.payload)) len = sizeof(tx_buffer.payload);
    memcpy(tx_buffer.payload, payload, len);
    tx_buffer.prepare(uart_buffer_t<TX_STRUCT_NAME>::Type::PAYLOAD, target_sn);
    last_tx_tick = HAL_GetTick();
    requestedTx = true;
    return true;
}

bool UARTProtocol::TX_FUNC_NAME(TX_STRUCT_NAME *data)
{
    if(target_sn == 0)
    {
        requestedTx = false;
        return false;
    }
    if(requestedTx) return false; // previous Tx process not over
    if(HAL_GetTick() - last_tx_tick < UART_KEEPALIVE_TICKS) // within keepalive period
    {
        if(*(data) == *((TX_STRUCT_NAME*)tx_buffer.payload)) return false; // the same
    }
    memcpy(tx_buffer.payload, data, sizeof(TX_STRUCT_NAME));
    tx_buffer.prepare(uart_buffer_t<TX_STRUCT_NAME>::Type::MOTOR, target_sn);
    last_tx_tick = HAL_GetTick(); // update timer
    requestedTx = true;
    return true;
}

#endif