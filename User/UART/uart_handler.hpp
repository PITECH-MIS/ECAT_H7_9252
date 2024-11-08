#ifndef _UART_HANDLER_HPP
#define _UART_HANDLER_HPP

#ifdef __cplusplus
extern "C" {
#endif
#include "kfifo.h"
#include "printf.h"
#include "utils.h"
#ifdef __cplusplus
}
#endif

#include "parser.h"
#include "global_include.h"

#define RX_BUFFER_SIZE 256
#define TX_BUFFER_SIZE 256

typedef void (*uart_rx_cb)(uint16_t Size);

class UART
{
public:
    UART(UART_HandleTypeDef *_huart) : huart(_huart) {};
    UART(UART_HandleTypeDef *_huart, uint16_t _stack_size) : huart(_huart), rx_stack_size(_stack_size)
    {
        // static_assert(_stack_size <= BUFFER_SIZE, "");
    };
    void Init();
    bool OnIdleIRQ(UART_HandleTypeDef *_huart, uint16_t Size);
    // uint32_t GetRxLen() {return kfifo_used_s(&rx_fifo);};
    void PutTxFifo(char *src, uint32_t len);
    uint32_t GetTxFifoLen()
    {
        return kfifo_used_s(&tx_fifo);
    }
    void FlushTxFifo()
    {
        kfifo_flush_s(&tx_fifo);
    }
    void GetRxFifo(char *dst, uint32_t len);
    void Transmit(); // DMA transmit from tx_fifo
    void TransmitBlocking(uint8_t *buf, uint32_t len);
    // void Transmit(char *src, uint32_t len); // DMA transmit from buffer
    void print(uint8_t transmit, const char *fmt, ...);
    void RegisterCallback(uart_rx_cb func) {rx_cb = func;};
    bool ProcessCmd();
    // Parser parser;
    char tx_buffer[TX_BUFFER_SIZE];
    uint8_t rx_buffer[RX_BUFFER_SIZE];
    // kfifo_static_t rx_fifo;
    UART_HandleTypeDef *huart;
private:
    
    kfifo_static_t tx_fifo;
    uint16_t rx_stack_size = RX_BUFFER_SIZE;
    // uint16_t rx_buf_pos = 0;
    // uint16_t rx_length = 0;
    // uint8_t rx_finished_sem = 0; // 0 indicates no income message is unhandled
    // char cmd_buffer[16];
    // float arg_buffer[16];
    // uint8_t arg_len = 0;
    uart_rx_cb rx_cb = nullptr;
};

void UART::print(uint8_t transmit, const char *fmt, ...)
{
    char buffer[TX_BUFFER_SIZE];
    va_list args;
    va_start(args, fmt);
    uint16_t buffer_len = (uint16_t)vsnprintf(buffer, TX_BUFFER_SIZE, fmt, args);
    // PutTxFifo(buffer, buffer_len);
    if(transmit) Transmit();
}

void UART::Init()
{
    // kfifo_init_s(&rx_fifo, KFIFO_STATIC_BUF_SIZE);
    kfifo_init_s(&tx_fifo, KFIFO_STATIC_BUF_SIZE);
    HAL_UART_AbortReceive(huart);
    // HAL_UARTEx_ReceiveToIdle_DMA(huart, rx_buffer, rx_stack_size);

    WRITE_REG(((DMA_Stream_TypeDef*)huart->hdmarx->Instance)->PAR, (uint32_t)&(huart->Instance->RDR));
    // LL_DMA_SetPeriphAddress(DMA1, huart->hdmarx->Init.Channel, (uint32_t)&(huart->Instance->RDR));
    WRITE_REG(((DMA_Stream_TypeDef*)huart->hdmarx->Instance)->M0AR, (uint32_t)rx_buffer);
    // LL_DMA_SetMemoryAddress(DMA1, huart->hdmarx->Init.Channel, (uint32_t)rx_buffer);
    MODIFY_REG(((DMA_Stream_TypeDef*)huart->hdmarx->Instance)->NDTR, DMA_SxNDT, rx_stack_size);
    // LL_DMA_SetDataLength(DMA1, huart->hdmarx->Init.Channel, rx_stack_size);
    // SET_BIT(huart->hdmarx->Instance->CR, DMA_SxCR_HTIE);
    // LL_DMA_EnableIT_HT(DMA1, huart->hdmarx->Init.Channel);
    // SET_BIT(huart->hdmarx->Instance->CR, DMA_SxCR_TCIE);
    // LL_DMA_EnableIT_TC(DMA1, huart->hdmarx->Init.Channel);
    ATOMIC_SET_BIT(huart->Instance->CR3, USART_CR3_DMAR);
    SET_BIT(((DMA_Stream_TypeDef*)huart->hdmarx->Instance)->CR, DMA_SxCR_EN);
    huart->pRxBuffPtr = rx_buffer;
    huart->RxXferSize = rx_stack_size;
    huart->ReceptionType = HAL_UART_RECEPTION_TOIDLE;
    huart->RxEventType = HAL_UART_RXEVENT_TC;
    __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
    __HAL_UART_ENABLE(huart);
}

bool UART::OnIdleIRQ(UART_HandleTypeDef *_huart, uint16_t Size)
{
    if(_huart == huart)
    {
        // rx_length = Size - rx_buf_pos;
        // kfifo_put_s(&rx_fifo, (char*)rx_buffer, rx_length);
        // rx_buf_pos += rx_length;
        // if(rx_buf_pos >= RX_BUFFER_SIZE) rx_buf_pos = 0;
        // if(_huart->RxEventType == HAL_UART_RXEVENT_IDLE) rx_finished_sem++;
        CLEAR_BIT(((DMA_Stream_TypeDef*)huart->hdmarx->Instance)->CR, DMA_SxCR_EN);
        // kfifo_put_s(&rx_fifo, (char*)rx_buffer, Size);
        if(rx_cb != nullptr) rx_cb(Size);
        MODIFY_REG(((DMA_Stream_TypeDef*)huart->hdmarx->Instance)->NDTR, DMA_SxNDT, rx_stack_size);
        SET_BIT(((DMA_Stream_TypeDef*)huart->hdmarx->Instance)->CR, DMA_SxCR_EN);
        // rx_finished_sem++;
        return true;
    }
    return false;
}

bool UART::ProcessCmd()
{
    // if(rx_finished_sem == 0) return false;
    // uint16_t len = kfifo_used_s(&rx_fifo);
    // char temp[RX_BUFFER_SIZE];
    // kfifo_get_s(&rx_fifo, temp, len);
    // getCommand(temp, len, cmd_buffer);
    // splitData_f(temp, len, arg_buffer, &arg_len, ' ');
    // parser.Parse(cmd_buffer, arg_buffer, arg_len);
    // rx_finished_sem--;
    return true;
}

void UART::PutTxFifo(char *src, uint32_t len)
{
    kfifo_put_s(&tx_fifo, src, len);
}

void UART::GetRxFifo(char *dst, uint32_t len)
{
    // kfifo_get_s(&rx_fifo, dst, len);
}

void UART::Transmit()
{
    // while(huart->hdmatx->State == HAL_DMA_STATE_BUSY);
    uint16_t len = kfifo_used_s(&tx_fifo);
    kfifo_get_s(&tx_fifo, tx_buffer, len);
    // uint16_t len = tx_len;
    // HAL_DMA_Abort(huart->hdmatx);
    HAL_UART_DMAStop(huart);
    HAL_UART_Transmit_DMA(huart, (const uint8_t*)tx_buffer, len);
    // for(uint16_t i = 0; i < len; i++)
    // {
    //     HAL_UART_Transmit(huart, (const uint8_t *)(tx_buffer + i), 1, 0x00FF);
    // }
}

void UART::TransmitBlocking(uint8_t *buf, uint32_t len)
{
    HAL_UART_Transmit(huart, (const uint8_t *)buf, len, 0x00FF);
}

#endif