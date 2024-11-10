#ifndef _BSP_ISR_H
#define _BSP_ISR_H

#include "spi.h"

#define ESC_SPI &hspi1

#define ESC_CS_Port SPI1_CS_GPIO_Port
#define ESC_CS_Pin  SPI1_CS_Pin

// extern uint32_t m_cnt_error;
// extern uint32_t m_cnt_busy;
// extern uint32_t m_cnt_timeout;
// extern uint32_t m_cnt_ok;
//
// __STATIC_INLINE void PROBE(HAL_StatusTypeDef status)
// {
//     if(status == HAL_ERROR) m_cnt_error++;
//     else if(status == HAL_BUSY) m_cnt_busy++;
//     else if(status == HAL_TIMEOUT) m_cnt_timeout++;
//     else m_cnt_ok++;
// }

#define spi_select() LL_GPIO_ResetOutputPin(ESC_CS_Port, ESC_CS_Pin)
#define spi_unselect() LL_GPIO_SetOutputPin(ESC_CS_Port, ESC_CS_Pin)
#define disable_irq() __disable_irq()
#define enable_irq() __enable_irq()
// #define write(dummy, data, size) PROBE(HAL_SPI_Transmit(ESC_SPI, data, size, 0xFFF))
// #define read(dummy, result, size) PROBE(HAL_SPI_Receive(ESC_SPI, result, size, 0xFFF))
#define write(dummy, data, size) HAL_SPI_Transmit(ESC_SPI, data, size, 0xFFF)
#define read(dummy, result, size) HAL_SPI_Receive(ESC_SPI, result, size, 0xFFF)
#define spi_bidirectionally_transfer(dummy, result, data, size) HAL_SPI_TransmitReceive(ESC_SPI, data, result, size, 0xFFF)
#define spi_setup() spi_unselect()

#endif