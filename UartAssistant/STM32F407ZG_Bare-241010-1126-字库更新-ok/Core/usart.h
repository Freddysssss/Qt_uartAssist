/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"



#define USART1_RX_IT_EN         1       /* 使能（1）/禁止（0）串口1接收 */
#define USART1_RX_BUFFER_SIZE   1       /* 缓存大小 */
#define USART1_REC_LEN          200     /* 定义最大接收字节数  */

#define USART2_RX_IT_EN         1       /* 使能（1）/禁止（0）串口2接收 */
#define USART2_RX_BUFFER_SIZE   1       /* 缓存大小 */
#define USART2_REC_LEN          200     /* 定义最大接收字节数  */

#define USART3_RX_IT_EN         1       /* 使能（1）/禁止（0）串口3接收 */
#define USART3_RX_BUFFER_SIZE   1       /* 缓存大小 */
#define USART3_REC_LEN          (4096+9)     /* 定义最大接收字节数  */

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;


#if USART3_RX_IT_EN                                        /* 如果使能了接收 */
extern uint8_t g_hal_usart3_rx_buffer[USART3_RX_BUFFER_SIZE];  /* HAL库使用的串口接收缓冲 */
extern uint8_t g_usart3_rx_buf[USART3_REC_LEN];                /* 接收缓冲, 最大USART_REC_LEN个字节. */
extern uint16_t g_usart3_rx_counter;
extern uint16_t g_usart3_last_rx_counter;
#endif

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */
void USART_SendBuf(UART_HandleTypeDef huart, uint8_t *buf, uint16_t len);

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
