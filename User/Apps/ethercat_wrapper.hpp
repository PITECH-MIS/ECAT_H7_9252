#ifndef _ETHERCAT_WRAPPER_HPP
#define _ETHERCAT_WRAPPER_HPP

#include "global_include.h"
#include <cstring>
#include "platform.hpp"

_Objects Obj;
uint16_t _adc_1_value __section(".ram_d1_area") = 0;
uint16_t _adc_3_value[2] __section(".ram_d3_area") = {0};
#define Vrefint_raw _adc_3_value[1]
#define Tmcu_raw _adc_3_value[0]
#define KEEPALIVE_TICKS 500

void master_set_cb();
void master_get_cb();
void ecat_app_cb();
void state_change_cb(uint8_t *as, uint8_t *an);
uint16_t dc_checker(void);
void user_failsafe();
void user_enterop();

// uint32_t user_pre_sdo_dl_hook(uint16_t index,
//       uint8_t subindex,
//       void * data,
//       size_t size,
//       uint16_t flags);
// uint32_t user_post_sdo_dl_hook(uint16_t index,
//          uint8_t subindex,
//          uint16_t flags);
// uint32_t user_pre_sdo_up_hook(uint16_t index,
//          uint8_t subindex,
//          void * data,
//          size_t *size,
//          uint16_t flags);
// uint32_t user_post_sdo_up_hook(uint16_t index,
//          uint8_t subindex,
//          uint16_t flags);

class ECATWrapper
{
public:
    void Init();
    void Update();
    volatile float uptime_sec = 0;
    volatile uint32_t fps = 0;
    volatile uint32_t frame_counter = 0;
    uint32_t last_rec_tick = 0;
    bool isOP = false;
    bool isLineAlive = false;
    bool isSafeToRun = false;
    bool checkFailSafe();
private:
    esc_cfg_t ecat_esc_cfg = 
    {
        .user_arg = NULL,
        .use_interrupt = 1,
        .watchdog_cnt = 100,
        .set_defaults_hook = NULL,
        .pre_state_change_hook = NULL,
        .post_state_change_hook = state_change_cb,
        .application_hook = ecat_app_cb,
        .safeoutput_override = NULL,
        .pre_object_download_hook = NULL,
        .post_object_download_hook = NULL,
        .pre_object_upload_hook = NULL,
        .post_object_upload_hook = NULL,
        .rxpdo_override = NULL,
        .txpdo_override = NULL,
        .esc_hw_interrupt_enable = ESC_interrupt_enable,
        .esc_hw_interrupt_disable = ESC_interrupt_disable,
        .esc_hw_eep_handler = NULL,
        .esc_check_dc_handler = dc_checker,
    };
};
ECATWrapper ethercat;

void cb_set_outputs() // MASTER sets output to SLAVE
{
    ethercat.frame_counter++;
    ethercat.last_rec_tick = HAL_GetTick();
    master_set_cb();
}

void cb_get_inputs() // MASTER gets input from SLAVE
{
    master_get_cb();
}

void state_change_cb(uint8_t *as, uint8_t *an)
{
    if(*as == SAFEOP_TO_OP)
    {
        ESC_ALeventmaskwrite(ESC_ALeventmaskread() | ESCREG_ALEVENT_WD);
    }
    else if(*as == PREOP_TO_SAFEOP)
    {
        DIG_process(DIG_PROCESS_INPUTS_FLAG);
    }
    if(*as == INIT_TO_OP || *as == SAFEOP_TO_OP || *as == PREOP_TO_OP || *as == BOOT_TO_OP || *as == OP_TO_OP) 
    {
        ethercat.isOP = true;
    }
    else 
    {
        ethercat.isOP = false;
    }
    switch(*as)
    {
        case INIT_TO_INIT:
            printf("INIT_TO_INIT\n");
            break;
        case INIT_TO_PREOP:
            printf("INIT_TO_PREOP\n");
            break;
        case INIT_TO_BOOT:
            printf("INIT_TO_BOOT\n");
            break;
        case INIT_TO_SAFEOP:
            printf("INIT_TO_SAFEOP\n");
            break;
        case INIT_TO_OP:
            printf("INIT_TO_OP\n");
            break;
        case PREOP_TO_INIT:
            printf("PREOP_TO_INIT\n");
            break;
        case PREOP_TO_PREOP:
            printf("PREOP_TO_PREOP\n");
            break;
        case PREOP_TO_BOOT:
            printf("PREOP_TO_BOOT\n");
            break;
        case PREOP_TO_SAFEOP:
            printf("PREOP_TO_SAFEOP\n");
            break;
        case PREOP_TO_OP:
            printf("PREOP_TO_OP\n");
            break;
        case BOOT_TO_INIT:
            printf("BOOT_TO_INIT\n");
            break;
        case BOOT_TO_PREOP:
            printf("BOOT_TO_PREOP\n");
            break;
        case BOOT_TO_BOOT:
            printf("BOOT_TO_BOOT\n");
            break;
        case BOOT_TO_SAFEOP:
            printf("BOOT_TO_SAFEOP\n");
            break;
        case BOOT_TO_OP:
            printf("BOOT_TO_OP\n");
            break;
        case SAFEOP_TO_INIT:
            printf("SAFEOP_TO_INIT\n");
            break;
        case SAFEOP_TO_PREOP:
            printf("SAFEOP_TO_PREOP\n");
            break;
        case SAFEOP_TO_BOOT:
            printf("SAFEOP_TO_BOOT\n");
            break;
        case SAFEOP_TO_SAFEOP:
            printf("SAFEOP_TO_SAFEOP\n");
            break;
        case SAFEOP_TO_OP:
            printf("SAFEOP_TO_OP\n");
            break;
        case OP_TO_INIT:
            printf("OP_TO_INIT\n");
            break;
        case OP_TO_PREOP:
            printf("OP_TO_PREOP\n");
            break;
        case OP_TO_BOOT:
            printf("OP_TO_BOOT\n");
            break;
        case OP_TO_SAFEOP:
            printf("OP_TO_SAFEOP\n");
            break;
        case OP_TO_OP:
            printf("OP_TO_OP\n");
            break;
        default: break;
    }
}

uint16_t dc_checker(void)
{
    printf("Requested DC Checker");
    ESCvar.dcsync = 1;
    return 0;
}

float getVoltage(uint16_t raw) // mV
{
    return (float)((float)raw * (float)__LL_ADC_CALC_VREFANALOG_VOLTAGE(Vrefint_raw, LL_ADC_RESOLUTION_16B) / 65535.0f);
}

float getMCUTemperature()
{
    return __LL_ADC_CALC_TEMPERATURE(__LL_ADC_CALC_VREFANALOG_VOLTAGE(Vrefint_raw, LL_ADC_RESOLUTION_16B), Tmcu_raw, LL_ADC_RESOLUTION_16B);
}

bool ECATWrapper::checkFailSafe()
{
    if(HAL_GetTick() - last_rec_tick >= KEEPALIVE_TICKS) isLineAlive = false;
    else isLineAlive = true;
    bool temp = isOP && isLineAlive;
    if(temp != isSafeToRun)
    {
        if(temp) user_enterop();
        else user_failsafe();
        isSafeToRun = temp;
    }
    return isSafeToRun;
}

void ECATWrapper::Init()
{
    HAL_NVIC_EnableIRQ(ESC_PDI_IRQn);
    HAL_NVIC_DisableIRQ(ESC_SYNC0_IRQn);
    HAL_NVIC_DisableIRQ(ESC_SYNC1_IRQn);

    HAL_ADCEx_Calibration_Start(&hadc3, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);
    HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);
    HAL_ADC_Start_DMA(&hadc3, (uint32_t *)_adc_3_value, 2);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&_adc_1_value, 1);

    LL_GPIO_ResetOutputPin(LAN_RST_GPIO_Port, LAN_RST_Pin);
    delay_ms(300);
    LL_GPIO_SetOutputPin(LAN_RST_GPIO_Port, LAN_RST_Pin);
    delay_ms(100);
    user_failsafe(); // recover from uninit state
    ecat_slv_init(&ecat_esc_cfg);
    Obj.serial = (uint32_t)GetSerialNumber();
}

// https://github.com/glowbuzzer/gblan9252_soes

void ECATWrapper::Update() // called every 2ms
{
    static uint16_t profile_counter = 0;
    static float last_time = (float)HAL_GetTick() * 0.001f;
    DIG_process(DIG_PROCESS_WD_FLAG);
    ecat_slv_poll();
    checkFailSafe();
    if(profile_counter++ >= 500)
    {
        fps = frame_counter;
        frame_counter = 0;
        profile_counter = 0;
    }
    float temp = (float)HAL_GetTick() * 0.001f;
    uptime_sec += temp - last_time;
    last_time = temp;
}

// Interrupt Priority: Update = PDI > SYNC0 > SYNC1

void esc_update_irq()
{
    LL_TIM_ClearFlag_UPDATE(TIM17);
    // LL_GPIO_SetOutputPin(TEST_GPIO_Port, TEST_Pin);
    ethercat.Update();
    HAL_IWDG_Refresh(&hiwdg1);
    // LL_GPIO_ResetOutputPin(TEST_GPIO_Port, TEST_Pin);
}

void esc_pdi_irq()
{
    // printf("ESC PDI IRQ\n");
    pdi_isr();
}

void esc_sync0_irq()
{
    // printf("ESC SYNC0 IRQ\n");
    sync0_isr();
}

void esc_sync1_irq()
{
    // printf("ESC SYNC1 IRQ\n");
}

#endif