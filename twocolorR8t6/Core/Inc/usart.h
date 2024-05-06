/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#define UART1_RXSIZE	1024	//�???帧接收数据的�???大�??
#define UART1_TXSIZE	1024	//�???帧发送数据的�???大�??
#define UART2_RXSIZE	1024	//�???帧接收数据的�???大�??
#define UART2_TXSIZE	1024	//�???帧发送数据的�???大�??
#define UART3_RXSIZE	1024	//�???帧接收数据的�???大�??
#define UART3_TXSIZE	1024	//�???帧发送数据的�???大�??
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

extern USART_HandleTypeDef husart3;

/* USER CODE BEGIN Private defines */
typedef struct
{
	uint8_t *rx_buf;		//接收缓冲数组
	uint16_t rx_buf_cnt;	//接收缓冲计数�??
	uint16_t rx_size;		//接收数据大小
	uint8_t rx_flag;		//接收完成标志�??

	uint8_t *tx_buf;		//发�?�缓冲数�??
	uint16_t tx_buf_cnt;	//发�?�缓冲计数�??
	uint16_t tx_size;		//实际发�?�数据大�??
}UART_BUF;					//串口结构�??

extern UART_BUF uart1;		//串口结构体实�??
extern UART_BUF uart2;		//串口结构体实�??
extern UART_BUF uart3;		//串口结构体实�??
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART3_Init(void);

/* USER CODE BEGIN Prototypes */
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

