/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
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
/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */
//#include "usart.h"
extern char led1;
extern char led2;
extern char led3;
extern char led4;
extern char led5;
extern char led6;
extern char led7;
#include "gpio.h"
/* USER CODE END 0 */

TIM_HandleTypeDef htim3;

/* TIM3 init function */
void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 8399;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 49;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();

    /* TIM3 interrupt Init */
    HAL_NVIC_SetPriority(TIM3_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();

    /* TIM3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspDeInit 1 */

  /* USER CODE END TIM3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim3)
	{
		__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);	//产生中断证明超过4ms没有接收到数据了，一帧接收完�???
		HAL_TIM_Base_Stop_IT(&htim3);		//中断之后停止定时器，�???启在下一次接收到数据�???�???
		uart1.rx_size = uart1.rx_buf_cnt;	//将接收到数据数量赋�??
		uart1.rx_buf_cnt = 0;				//清零
		uart1.rx_flag = 1;					//接收完成，置1
		  if(uart1_rx_buf[0] >= 0xC1 && uart1_rx_buf[0] <= 0xC7){
				  switch (uart1_rx_buf[0]){
				  case 0xC1:red7();
				  led7 = 3;
				  for_delay_us(10000);
				  break;
				  case 0xC2:red6();
				  led6 = 3;
				  for_delay_us(10000);
				  break;
				  case 0xC3:red5();
				  led5 = 3;
				  for_delay_us(10000);
				  break;
				  case 0xC4:red4();
				  led4 = 3;
				  for_delay_us(10000);
				  break;
				  case 0xC5:red3();
				  led3 = 3;
				  for_delay_us(10000);
				  break;
				  case 0xC6:red2();
				  led2 = 3;
				  for_delay_us(10000);
				  break;
				  case 0xC7:red1();
				  led1 = 3;
				  for_delay_us(10000);
				  break;
				  }
				  //uart1.rx_flag = 0;
			 }
	}

}

void E_TIM_INIT(TIM_HandleTypeDef *htim)
{
	if(htim == &htim3)
	{
		__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_UPDATE);		//手动添加
		HAL_TIM_Base_Start_IT(htim);
	}

}

/* USER CODE END 1 */
