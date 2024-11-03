#ifndef _GLOBAL_INCLUDE_H
#define _GLOBAL_INCLUDE_H

#ifdef __cplusplus
extern "C" {
#endif
/* ---------------- C Scope --------------- */ // For executed by C file
#include "stdint-gcc.h"
#include "main.h"
#include "iwdg.h"
#include "crc.h"
#include "usart.h"
#include "i2c.h"
#include "spi.h"
#include "fdcan.h"
#include "adc.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "utypes.h"
#include "ecat_slv.h"
#include "ecat_options.h"
#include "bsp_isr.h"
void app_main();
void esc_update_irq();
void esc_pdi_irq();
void esc_sync0_irq();
void esc_sync1_irq();
void usb_rx_callback(uint8_t* Buf, uint32_t Len);
#ifdef __cplusplus
}
/* --------------- C++ Scope -------------- */

#endif
#endif