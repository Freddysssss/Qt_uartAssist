/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"
#include "gpio.h"
#include "usbd_hid.h"
#include "delay.h"
#include "usart.h"

#include "lcd.h"
#include "fonts.h"
#include "malloc.h"
#include "norflash.h"
#include "text.h"
#include "font_updata.h"

#define LOG_TAG     "main"
#include "log.h"

/* USER CODE END PV */
extern USBD_HandleTypeDef hUsbDeviceFS;
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
    HAL_Init();

    SystemClock_Config();
    delay_init(168);                    /* 延时初始化 */
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();
    MX_USART3_UART_Init();
    
    printf("hello world111\r\n!");
    lcd_init();                             /* 初始化LCD */
    printf("hello world222\r\n!");
    g_point_color = RED;
    my_mem_init(SRAMIN);
    norflash_init();//初始化外部flash    
    printf("hello world!\r\n");
    LOG_I("hello world!");
    lcd_show_string(0, 0, 240, 24, 24, "TFTLCD TEST", RED);
    text_show_string(0, 24, "123abcd", 12, BLUE);
    
    //读取字库信息
    uint8_t *pBuff = (uint8_t *)&ftinfo;
    norflash_read((uint8_t *)&ftinfo, FONTINFOADDR, sizeof(ftinfo));
    for (uint8_t i = 0; i < sizeof(ftinfo); i++)
    printf("%02x ",pBuff[i]);
    printf("\r\n");
    printf("ugbkaddr    = 0x%08x\r\n",ftinfo.ugbkaddr);
    printf("ugbksize    = 0x%08x\r\n",ftinfo.ugbksize);
    printf("f12addr     = 0x%08x\r\n",ftinfo.f12addr);
    printf("gbk12size   = 0x%08x\r\n",ftinfo.gbk12size);
    printf("f16addr     = 0x%08x\r\n",ftinfo.f16addr);
    printf("gbk16size   = 0x%08x\r\n",ftinfo.gbk16size);
    printf("f24addr     = 0x%08x\r\n",ftinfo.f24addr);
    printf("gbk24size   = 0x%08x\r\n",ftinfo.gbk24size);
    
    if (ftinfo.fontok == 0xAA)
    {
        text_show_font(80, 280, "你", 24, 0, BLUE);
        text_show_font(80+24, 280, "好", 16, 0, BLUE);
        text_show_font(80+24+16, 280, "啊", 12, 0, BLUE);
        text_show_string(30, 60, "小号你好啊哈哈能够阿巴贡阿娇你当给你高信号没货癞蛤蟆123abcd", 12, BLUE);
        text_show_string(30, 84, "中号你好啊哈哈能够阿巴贡阿娇你当给你高信号没货癞蛤蟆123abcd", 16, BLUE);
        text_show_string(30, 132, "大号你好啊哈哈能够阿巴贡阿娇你当给你高信号没货癞蛤蟆123abcd", 24, BLUE);
    }
    else
    {
        text_show_string(5, 40, "Fonts is not exist!", 24, RED);
    }
    
    while (1)
    {
        updata_font_library_process();
        delay_us(100);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
