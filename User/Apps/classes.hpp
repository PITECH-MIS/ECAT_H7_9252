#include "global_include.h"
#include "usbd_cdc_if.h"
#include "rtos_task.hpp"
#include "ws2812.h"
#include "platform.hpp"
#include "spi_interface.hpp"
#include "stm32_gpio.hpp"
#include "ethercat_wrapper.hpp"
#include "uart_handler.hpp"
#include "uart_arbiter.hpp"

#include "shell.hpp"
#include "pdo_slave_protocol.hpp"

UART UART_1 __section(".ram_d1_area")(&huart1);
UART UART_2 __section(".ram_d1_area")(&huart2);
UART UART_3 __section(".ram_d1_area")(&huart3);
UART UART_4 __section(".ram_d1_area")(&huart4);
UART UART_6 __section(".ram_d1_area")(&huart6);
UART UART_7 __section(".ram_d1_area")(&huart7);
UART UART_8 __section(".ram_d1_area")(&huart8);
UARTArbiter arbiter;

WS2812LightStrip ws2812 __section(".ram_d1_area")(TIM16, LL_TIM_CHANNEL_CH1, DMA1, LL_DMA_STREAM_0);

Shell usb_shell;
PDOSlaveProtocol pdo_protocol;

void usb_rx_callback(uint8_t* Buf, uint32_t Len)
{
    usb_shell.OnRxMsg(Buf, Len);
}

void _putchar(char character)
{
    // UART3.print(1, "%c", character);
    // UART_1.TransmitBlocking((uint8_t*)&character, 1);
    usb_shell.PutTxFifo((uint8_t*)&character, 1);
    // usb_shell.Transmit();
}