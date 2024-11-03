#include "ws2812.h"
void WS2812LightStrip::Init(float _brightness)
{
    LL_RCC_ClocksTypeDef clock_freqs;
    LL_RCC_GetSystemClocksFreq(&clock_freqs);
    float pwm_freq_hz = clock_freqs.HCLK_Frequency / ((LL_TIM_GetPrescaler(htim) + 1) * (LL_TIM_GetAutoReload(htim) + 1));
    // T = 1/f
    bit_1 = (uint32_t)(BIT1_HIGH_TIME * pwm_freq_hz * (float)(LL_TIM_GetAutoReload(htim) + 1));
    bit_0 = (uint32_t)(BIT0_HIGH_TIME * pwm_freq_hz * (float)(LL_TIM_GetAutoReload(htim) + 1));
    CCR_address = (uint32_t)(&htim->CCR1);
    switch(channel)
    {
        case LL_TIM_CHANNEL_CH2: CCR_address = (uint32_t)(&htim->CCR2); break;
        case LL_TIM_CHANNEL_CH3: CCR_address = (uint32_t)(&htim->CCR3); break;
        case LL_TIM_CHANNEL_CH4: CCR_address = (uint32_t)(&htim->CCR4); break;
        case LL_TIM_CHANNEL_CH5: CCR_address = (uint32_t)(&htim->CCR5); break;
        case LL_TIM_CHANNEL_CH6: CCR_address = (uint32_t)(&htim->CCR6); break;
        default: break;
    }
    SetBrightness(_brightness);
    Update();
}
void WS2812LightStrip::Update()
{
    for(uint32_t i = 0; i < LIGHT_COUNT; i++) SetDMABuf32(i);
    LL_DMA_DisableStream(hdma, dma_channel);
    LL_DMA_SetMemoryAddress(hdma, dma_channel, (uint32_t)((uint32_t*)dma_buffer));
    LL_DMA_SetPeriphAddress(hdma, dma_channel, (uint32_t)CCR_address);
    LL_DMA_SetDataLength(hdma, dma_channel, DMA_BUF_LEN);
    LL_DMA_EnableStream(hdma, dma_channel);
    LL_TIM_EnableDMAReq_CC1(htim);
    LL_TIM_CC_EnableChannel(htim, channel);
    LL_TIM_EnableAllOutputs(htim);
    LL_TIM_EnableCounter(htim);
}
void WS2812LightStrip::SetBrightness(float _brightness)
{
    if(_brightness > 1.0f) _brightness = 1.0f;
    else if(_brightness < 0.0f) _brightness = 0.0f;
    brightness = _brightness;
}
void WS2812LightStrip::SetDMABuf32(uint32_t index)
{
    if(index > LIGHT_COUNT - 1) index = LIGHT_COUNT - 1;
    for(uint8_t i = 0; i < 8; i++)
    {
        *(dma_buffer + DMA_BUF_OFFSET_HEAD + 24 * index + i) = (rgb_buffer[index][0] & (0x80 >> i)) ? bit_1 : bit_0;
        *(dma_buffer + DMA_BUF_OFFSET_HEAD + 24 * index + i + 8) = (rgb_buffer[index][1] & (0x80 >> i)) ? bit_1 : bit_0;
        *(dma_buffer + DMA_BUF_OFFSET_HEAD + 24 * index + i + 16) = (rgb_buffer[index][2] & (0x80 >> i)) ? bit_1 : bit_0;
    }
}
void WS2812LightStrip::SetColor(uint32_t index, uint8_t r, uint8_t g, uint8_t b)
{
    if(index > LIGHT_COUNT - 1) index = LIGHT_COUNT - 1;
    rgb_buffer[index][0] = (uint8_t)((float)g * brightness);
    rgb_buffer[index][1] = (uint8_t)((float)r * brightness);
    rgb_buffer[index][2] = (uint8_t)((float)b * brightness);
}

void GetColorWheel(uint8_t pos, uint8_t *r, uint8_t *g, uint8_t *b)
{
    if(pos < 85)
    {
        *r = pos * 3;
        *g = 255 - *r;
        *b = 0;
        return;
    }
    if(pos < 170)
    {
        pos -= 85;
        *g = 0;
        *b = pos * 3;
        *r = 255 - *b;
        return;
    }
    pos -= 170;
    *r = 0;
    *g = pos * 3;
    *b = 255 - *g;
}