/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
void yellowOn1(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, SET);

}
void yellowOff1(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
}
void red1(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, RESET);
}
void green1(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, SET);
}
void yellowOn2(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, SET);

}
void yellowOff2(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, RESET);
}
void red2(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
}
void green2(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, SET);
}
void yellowOn3(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, SET);
}
void yellowOff3(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, RESET);
}
void red3(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, RESET);
}
void green3(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, SET);
}
void yellowOn4(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
}
void yellowOff4(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
}
void red4(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
}
void green4(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
}
void yellowOn5(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, SET);
}
void yellowOff5(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, RESET);
}
void red5(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, RESET);
}
void green5(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, SET);
}
void yellowOn6(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, SET);
}
void yellowOff6(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, RESET);
}
void red6(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET);
}
void green6(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, SET);
}
void yellowOn7(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, SET);

}
void yellowOff7(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET);
}
void red7(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET);
}
void green7(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, SET);
}
void ledInit(){
	//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 1){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, RESET);
		}else{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
	}
	//Ôø?????Ôø?????2Âè∑ÁÅØÁä∂ÔøΩ??
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 1){
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
		}else{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, RESET);
		}
	//Ôø?????Ôø?????3Âè∑ÁÅØÁä∂ÔøΩ??
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 1){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, RESET);
		}else{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, RESET);
		}
	//Ôø?????Ôø?????4Âè∑ÁÅØÁä∂ÔøΩ??
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == 1){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
		}else{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
				}
	//Ôø?????Ôø?????5Âè∑ÁÅØÁä∂ÔøΩ??
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 1){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, RESET);
		}else{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, RESET);
		}
	//Ôø?????Ôø?????6Âè∑ÁÅØÁä∂ÔøΩ??
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == 1){
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, RESET);
		}else{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, RESET);
		}
	//Ôø?????Ôø?????7Âè∑ÁÅØÁä∂ÔøΩ??
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == 1){
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, RESET);
		}else{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET);
		}
}
/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_5
                          |GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC0 PC1 PC3 PC4
                           PC5 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = D1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(D1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA2 PA3 PA5
                           PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_5
                          |GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = D2_Pin|D3_Pin|D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = D5_Pin|D6_Pin|D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB1 PB10 PB12 PB13 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 2 */
void for_delay_us(uint32_t nus)
{
	uint32_t Delay = nus * 72/4;
do{__NOP();}while (Delay --);
}
/* USER CODE END 2 */
