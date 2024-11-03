#ifndef _BSP_ISR_H
#define _BSP_ISR_H

#include "spi.h"

#define ESC_SPI &hspi1

#define ESC_CS_Port SPI1_CS_GPIO_Port
#define ESC_CS_Pin  SPI1_CS_Pin

#define spi_select(dummy) LL_GPIO_ResetOutputPin(ESC_CS_Port, ESC_CS_Pin)
#define spi_unselect(dummy) LL_GPIO_SetOutputPin(ESC_CS_Port, ESC_CS_Pin)
#define write(dummy, data, size) HAL_SPI_Transmit(ESC_SPI, data, size, 0xFFF)
#define read(dummy, result, size) HAL_SPI_Receive(ESC_SPI, result, size, 0xFFF)
#define spi_bidirectionally_transfer(dummy, result, data, size) HAL_SPI_TransmitReceive(ESC_SPI, data, result, size, 0xFFF)
#define spi_setup() spi_unselect(0)

#endif