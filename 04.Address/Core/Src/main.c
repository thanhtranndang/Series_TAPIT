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


	/*Bài 1:
  * Giả sử thanh ghi ODR của GPIOA có giá trị ban đầu bằng 0xABCD,
	thực hiện lệnh HAL_GPIO_TogglePin (GPIOA, GPIO_PIN_5).
	Trình bày các bước thực hiện lệnh và giá trị ODR sau khi thực hiện lệnh.
	(Thực hiện giống như mình đã phân tích với HAL_GPIO_ReadPin).
	-----------------------------------------------------
	ODR GPIOA: 0xABCD, GPIO_PIN_0
	void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
	{
	  uint32_t odr;
	  odr = GPIOx->ODR;
	  GPIOx->BSRR = ((odr & GPIO_Pin) << GPIO_NUMBER) | (~odr & GPIO_Pin);
	}
	-----------------------------------------------------
	((odr & GPIO_Pin) << GPIO_NUMBER) | (~odr & GPIO_Pin)
	GPIO_Pin =        	0000 0000 0010 0000
	odr = 0xABCD = 0b 	1010 1011 1100 1101
   ~odr =        = 0b 	0101 0100 0011 0010
   ------------------------------------------------------
   (~odr & GPIO_Pin) = 	0000 0000 0010 0000 <--------- Ket qua phia sau
   ------------------------------------------------------
   (odr & GPIO_Pin)  =  0000 0000 0000 0000
    GPIO_NUMBER = 16
   	   	   	   	   	   	0000 0000 0000 0000 << 16
   	0000 0000 0000 0000 0000 0000 0000 0000 <--------- Ket qua phia truoc
   ------------------------------------------------------
    ((odr & GPIO_Pin) << GPIO_NUMBER) | (~odr & GPIO_Pin)
  = 0000 0000 0000 0000 0000 0000 0010 0000 <--------- Ket qua phep toan
  --> BS5 = 1  --> ODR5 = 1
  	Ban đầu: 0b 	1010 1011 1100 1101    A B C D
  	Sau    : 0b 	1010 1011 1110 1101    A B E D

	*/

	/*
	 Bài 2
	Giả sử thanh ghi ODR của GPIOA có giá trị ban đầu bằng 0xABED,
	thực hiện lệnh HAL_GPIO_TogglePin (GPIOA, GPIO_PIN_5).
	Trình bày các bước thực hiện lệnh và giá trị ODR sau khi thực hiện lệnh.
		void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
		{
		  uint32_t odr;
		  odr = GPIOx->ODR;
		  GPIOx->BSRR = ((odr & GPIO_Pin) << GPIO_NUMBER) | (~odr & GPIO_Pin);
		}
	GPIO_Pin =        	0000 0000 0010 0000
	odr = 0xABED = 0b 	1010 1011 1110 1101
   ~odr =        = 0b 	0101 0100 0001 0010
   ------------------------------------------------------
   (~odr & GPIO_Pin) = 	0000 0000 0000 0000 <--------- Ket qua phia sau
    0000 0000 0000 0000 0000 0000 0000 0000
   ------------------------------------------------------
   (odr & GPIO_Pin)  =  0000 0000 0010 0000
    GPIO_NUMBER = 16
   	   	   	   	   	   	0000 0000 0010 0000 << 16
   	0000 0000 0010 0000 0000 0000 0000 0000 <--------- Ket qua phia truoc
   ------------------------------------------------------
    ((odr & GPIO_Pin) << GPIO_NUMBER) | (~odr & GPIO_Pin)
  = 0000 0000 0010 0000 0000 0000 0000 0000 <--------- Ket qua phep toan
  16 bit thấp bằng 0, 16 bit cao, có bit cao số 5 là bằng 1
  --> sẽ reset bit thấp tương ứng ( bit cao số 5 ~ bit thấp số 5 )

  --> BS5 = 1  --> ODR5 = 0

  	Ban đầu: 0b 	1010 1011 1110 1101    A B E D
  	Sau    : 0b 	1010 1011 1100 1101    A B C D

	 */









void SystemClock_Config(void);

int main(void)
{

  HAL_Init();

  SystemClock_Config();

  while (1)
  {

  }

}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
