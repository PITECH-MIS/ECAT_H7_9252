#ifndef _BSP_ISR_H
#define _BSP_ISR_H

#include "esc.h"
#include "global_include.h"

extern volatile uint8_t ecat_isr_sem;

// After complete IRQn here, we also need to implement correspond functions in stm32xxxx_it.c

#define ESC_PDI_IRQn   EXTI4_IRQn
#define ESC_SYNC0_IRQn EXTI0_IRQn
#define ESC_SYNC1_IRQn EXTI1_IRQn

void lan9252_write_32(uint16_t address, uint32_t val);
uint32_t lan9252_read_32 (uint32_t address);

void ESC_interrupt_enable(uint32_t mask); // connect them in esc_cfg_t
void ESC_interrupt_disable(uint32_t mask);

void pdi_isr();    // put it in ESC_PDI_IRQn Handler
void pdi_isr_background();  // put it in while loop, no need when mixed polling/interrupt mode
void sync0_isr();  // put it in ESC_SYNC0_IRQn Handler

#endif