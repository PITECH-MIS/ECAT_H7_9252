#ifndef _WS2812_H
#define _WS2812_H

#include "global_include.h"

#define LIGHT_COUNT 1 // Currently does not support specifying light count(related to buffer size) at runtime
#define DMA_BUF_OFFSET_HEAD 30
#define DMA_BUF_LEN ((2 * (DMA_BUF_OFFSET_HEAD)) + ((LIGHT_COUNT) * 24) + 1)
#define BIT0_HIGH_TIME (0.295f * 1e-6f) // 0.295us
#define BIT1_HIGH_TIME (0.595f * 1e-6f) // 0.595us

class WS2812LightStrip
{
public:
    WS2812LightStrip(TIM_TypeDef *_htim, uint32_t _channel, DMA_TypeDef *_hdma, uint32_t _dma_ch)
    : htim(_htim), channel(_channel), hdma(_hdma), dma_channel(_dma_ch) {};
    void Init(float _brightness);
    void Update();
    void SetColor(uint32_t index, uint8_t r, uint8_t g, uint8_t b);
    void SetBrightness(float _brightness);
private:
    void SetDMABuf32(uint32_t index);
    float brightness = 1.0f;
    uint8_t rgb_buffer[LIGHT_COUNT][3] = {0};
    TIM_TypeDef *htim;
    uint32_t channel = 0;
    DMA_TypeDef *hdma;
    uint32_t dma_channel = 0;
    uint32_t bit_1 = 0;
    uint32_t bit_0 = 0;
    uint32_t CCR_address = 0;
    uint32_t dma_buffer[DMA_BUF_LEN] = {0};
};

void GetColorWheel(uint8_t pos, uint8_t *r, uint8_t *g, uint8_t *b);

#endif