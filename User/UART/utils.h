#ifndef _UART_UTILS_H
#define _UART_UTILS_H

#include "main.h"

uint8_t trimData(char* pSource);
uint16_t getCRC16(uint8_t *data, uint16_t len);

#endif