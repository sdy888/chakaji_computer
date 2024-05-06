/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "cmsis_os.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern uint8_t uart1_rx_buf[UART1_RXSIZE];
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
char led1 = 0;
char led2 = 0;
char led3 = 0;
char led4 = 0;
char led5 = 0;
char led6 = 0;
char led7 = 0;

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART3_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  E_USART_INIT(&huart1);

  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, SET);
  red1();
  green1();
  yellowOn1();
  yellowOff1();
  yellowOn1();
  yellowOn2();
  yellowOn3();
  yellowOn4();
  yellowOn5();
  yellowOn6();
  yellowOn7();
  //ledInit();
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
/*	  uint8_t receive_buff[1024] = {0};
      HAL_UART_Receive(&huart1,receive_buff,10,0xff);// 接收10个字�????????
      if(receive_buff[0] != 0)
      {
      yellowOn7();
      }else{
      yellowOff7();
      }*/
	/*  if(uart1.rx_flag == 1){
		  switch (uart1_rx_buf[0]){
		  case 0xA1:green7();
		  break;
		  case 0xA2:green6();
		  break;
		  case 0xA3:green5();
		  break;
		  case 0xA4:green4();
		  break;
		  case 0xA5:green3();
		  break;
		  case 0xA6:green2();
		  break;
		  case 0xA7:green1();
		  break;
		  case 0xB1:yellowOn7();
		  break;
		  case 0xB2:yellowOn6();
		  break;
		  case 0xB3:yellowOn5();
		  break;
		  case 0xB4:yellowOn4();
		  break;
		  case 0xB5:yellowOn3();
		  break;
		  case 0xB6:yellowOn2();
		  break;
		  case 0xB7:yellowOn1();
		  break;
		  }
		  uart1.rx_flag = 0;
	 }*/
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)//外部中断回调函数
{
	for_delay_us(10000);
//led1
	if(GPIO_Pin == D1_Pin){
	  	  uint8_t TxDataon[2]= {0x01, 0xDD};
	  	  HAL_UART_Transmit(&huart1,TxDataon,2,10);
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 1){
			/*yellowOn1();
			for_delay_us(10000);
			yellowOff1();
			for_delay_us(10000);
			yellowOn1();
			for_delay_us(10000);
			yellowOff1();
			for_delay_us(30000);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, RESET);*/
			led1 = 1;
		}else{
			/*HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);
			yellowOn1();
			for_delay_us(10000);
			yellowOff1();
			for_delay_us(10000);
			yellowOn1();
			for_delay_us(10000);
			yellowOff1();
			for_delay_us(30000);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, RESET);*/
		}
	}
//led2
	if(GPIO_Pin == D2_Pin){
	  	  uint8_t TxDataon[2]= {0x06, 0xDD};
	  	  HAL_UART_Transmit(&huart1,TxDataon,2,10);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 1){
			/*while(1){
				if(uart1_rx_buf[0] == 0xC6){
								break;
							}
			yellowOn2();
			for_delay_us(10000);
			yellowOff2();
			for_delay_us(10000);
			}*/
			led2 = 1;
			//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, SET);
			//HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, RESET);
		}else{
			/*HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, RESET);
			yellowOn2();
			for_delay_us(10000);
			yellowOff2();
			for_delay_us(10000);
			yellowOn2();
			for_delay_us(10000);
			yellowOff2();
			for_delay_us(10000);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, RESET);*/
		}
	}
//led3
	if(GPIO_Pin == D3_Pin){
	  	  uint8_t TxDataon[2]= {0x05, 0xDD};
	  	  HAL_UART_Transmit(&huart1,TxDataon,2,10);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 1){
        led3 = 1;
		}else{
			/*HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, RESET);
			yellowOn3();
			for_delay_us(10000);
			yellowOff3();
			for_delay_us(10000);
			yellowOn3();
			for_delay_us(10000);
			yellowOff3();
			for_delay_us(10000);*/
			//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, SET);
			//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, RESET);
		}
	}
//led4
	if(GPIO_Pin == D4_Pin){
	  	  uint8_t TxDataon[2]= {0x04, 0xDD};
	  	  HAL_UART_Transmit(&huart1,TxDataon,2,10);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == 1){
         led4 = 1;
		}else{
			/*HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
			yellowOn4();
			for_delay_us(10000);
			yellowOff4();
			for_delay_us(10000);
			yellowOn4();
			for_delay_us(10000);
			yellowOff4();
			for_delay_us(30000);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);*/
		}
	}
//led5
	if(GPIO_Pin == D5_Pin){
	  	  uint8_t TxDataon[2]= {0x03, 0xDD};
	  	  HAL_UART_Transmit(&huart1,TxDataon,2,10);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 1){
             led5 = 1;
		}else{
			/*HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, RESET);
			yellowOn5();
			for_delay_us(10000);
			yellowOff5();
			for_delay_us(10000);
			yellowOn5();
			for_delay_us(10000);
			yellowOff5();
			for_delay_us(30000);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, RESET);*/
		}
	}
//led6
	if(GPIO_Pin == D6_Pin){
	  	  uint8_t TxDataon[2]= {0x02, 0xDD};
	  	  HAL_UART_Transmit(&huart1,TxDataon,2,10);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == 1){
        led6 = 1;
		}else{
			/*HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, RESET);
			yellowOn6();
			for_delay_us(10000);
			yellowOff6();
			for_delay_us(10000);
			yellowOn6();
			for_delay_us(10000);
			yellowOff6();
			for_delay_us(30000);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, RESET);*/
		}
	}
//led7
	if(GPIO_Pin == D7_Pin){
	  	  uint8_t TxDataon[2]= {0x01, 0xDD};
	  	  HAL_UART_Transmit(&huart1,TxDataon,2,10);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == 1){
        led7 = 1;
		}else{
			/*HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET);
			yellowOn7();
			for_delay_us(10000);
			yellowOff7();
			for_delay_us(10000);
			yellowOn7();
			for_delay_us(10000);
			yellowOff7();
			for_delay_us(30000);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, RESET);*/
		}
	}
	//_HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin_2);//中断清理，防止影响下次按�?????????????????????????????

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
