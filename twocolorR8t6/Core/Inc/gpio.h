/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
void for_delay_us(uint32_t nus);
void yellowOn1();
void yellowOff1();
void yellowOn2();
void yellowOff2();
void yellowOn3();
void yellowOff3();
void yellowOn4();
void yellowOff4();
void yellowOn5();
void yellowOff5();
void yellowOn6();
void yellowOff6();
void yellowOn7();
void yellowOff7();
void ledInit();
void red1();
void red2();
void red3();
void red4();
void red5();
void red6();
void red7();
void green1();
void green2();
void green3();
void green4();
void green5();
void green6();
void green7();
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

