/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

#include "stm32h7xx_ll_bdma.h"
#include "stm32h7xx_ll_dma.h"
#include "stm32h7xx_ll_rcc.h"
#include "stm32h7xx_ll_crs.h"
#include "stm32h7xx_ll_bus.h"
#include "stm32h7xx_ll_system.h"
#include "stm32h7xx_ll_exti.h"
#include "stm32h7xx_ll_cortex.h"
#include "stm32h7xx_ll_utils.h"
#include "stm32h7xx_ll_pwr.h"
#include "stm32h7xx_ll_tim.h"
#include "stm32h7xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "delay.h"
#include "global_include.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI4_CS_Pin LL_GPIO_PIN_4
#define SPI4_CS_GPIO_Port GPIOE
#define TEST_Pin LL_GPIO_PIN_0
#define TEST_GPIO_Port GPIOC
#define SPI1_CS_Pin LL_GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define LAN_IRQ_Pin LL_GPIO_PIN_4
#define LAN_IRQ_GPIO_Port GPIOC
#define LAN_IRQ_EXTI_IRQn EXTI4_IRQn
#define LAN_SYNC0_Pin LL_GPIO_PIN_0
#define LAN_SYNC0_GPIO_Port GPIOB
#define LAN_SYNC0_EXTI_IRQn EXTI0_IRQn
#define LAN_SYNC1_Pin LL_GPIO_PIN_1
#define LAN_SYNC1_GPIO_Port GPIOB
#define LAN_SYNC1_EXTI_IRQn EXTI1_IRQn
#define LAN_RST_Pin LL_GPIO_PIN_2
#define LAN_RST_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
