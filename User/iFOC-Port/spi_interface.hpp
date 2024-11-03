#ifndef _SPI_INTERFACE_H
#define _SPI_INTERFACE_H

#include "global_include.h"
#include "spi_base.h"

class SPI : public SPIBase
{
public:
    SPI(SPI_HandleTypeDef *_hspi, GPIO_TypeDef *cs_port, uint32_t cs_pin) : hspi(_hspi), CS_Port(cs_port), CS_Pin(cs_pin) {};
    void SetCS() override { LL_GPIO_ResetOutputPin(CS_Port, CS_Pin); };
    void ResetCS() override { LL_GPIO_SetOutputPin(CS_Port, CS_Pin); };
    uint8_t WriteBytes(uint8_t *data, uint16_t len) override;
    uint8_t ReadBytes(uint8_t *ret, uint16_t len) override;
    uint8_t ReadWriteBytes(uint8_t *data, uint8_t *ret, uint16_t len) override;
private:
    SPI_HandleTypeDef *hspi;
    GPIO_TypeDef *CS_Port;
    uint32_t CS_Pin;
};

uint8_t SPI::WriteBytes(uint8_t *data, uint16_t len)
{
    return HAL_SPI_Transmit(hspi, data, len, HAL_MAX_DELAY);
}

uint8_t SPI::ReadBytes(uint8_t *ret, uint16_t len)
{
    return HAL_SPI_Receive(hspi, ret, len, HAL_MAX_DELAY);
}

uint8_t SPI::ReadWriteBytes(uint8_t *data, uint8_t *ret, uint16_t len)
{
    return HAL_SPI_TransmitReceive(hspi, data, ret, len, HAL_MAX_DELAY);
}

#endif