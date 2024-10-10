/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "sys.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;


void USART_SendBuf(UART_HandleTypeDef huart, uint8_t *buf, uint16_t len)
{
  uint16_t i=0;
  for (i = 0; i < len; i++)
  {
//    HAL_UART_Transmit(&huart,(uint8_t*)buf,len,1000);    /* 发送接收到的数据 */
//    while(__HAL_UART_GET_FLAG(&huart,UART_FLAG_TC)!=SET);           /* 等待发送结束 */
    while ((huart.Instance->SR & 0X40) == 0);               /* 等待上一个字符发送完成 */
    huart.Instance->DR = (uint8_t)buf[i];                       /* 将要发送的字符 ch 写入到DR寄存器 */
  }
}

#if USART1_RX_IT_EN                                        /* 如果使能了接收 */
uint8_t g_hal_usart1_rx_buffer[USART1_RX_BUFFER_SIZE];  /* HAL库使用的串口接收缓冲 */
uint8_t g_usart1_rx_buf[USART1_REC_LEN];                /* 接收缓冲, 最大USART_REC_LEN个字节. */
uint16_t g_usart1_rx_counter = 0;

/**
 * @brief       串口1中断服务函数
 * @param       无
 * @retval      无
 */
void USART1_IRQHandler(void)
{ 
//#if SYS_SUPPORT_OS                              /* 使用OS */
//    OSIntEnter();    
//#endif

    HAL_UART_IRQHandler(&huart1);       /* 调用HAL库中断处理公用函数 */

//#if SYS_SUPPORT_OS                              /* 使用OS */
//    OSIntExit();
//#endif
}
#endif

#if USART2_RX_IT_EN                                        /* 如果使能了接收 */
uint8_t g_hal_usart2_rx_buffer[USART2_RX_BUFFER_SIZE];  /* HAL库使用的串口接收缓冲 */
uint8_t g_usart2_rx_buf[USART2_REC_LEN];                /* 接收缓冲, 最大USART_REC_LEN个字节. */
uint16_t g_usart2_rx_counter = 0;

/**
 * @brief       串口2中断服务函数
 * @param       无
 * @retval      无
 */
void USART2_IRQHandler(void)
{ 
//#if SYS_SUPPORT_OS                              /* 使用OS */
//    OSIntEnter();    
//#endif

    HAL_UART_IRQHandler(&huart2);       /* 调用HAL库中断处理公用函数 */

//#if SYS_SUPPORT_OS                              /* 使用OS */
//    OSIntExit();
//#endif
}
#endif

#if USART3_RX_IT_EN                                        /* 如果使能了接收 */
uint8_t g_hal_usart3_rx_buffer[USART3_RX_BUFFER_SIZE];  /* HAL库使用的串口接收缓冲 */
uint8_t g_usart3_rx_buf[USART3_REC_LEN];                /* 接收缓冲, 最大USART_REC_LEN个字节. */
uint16_t g_usart3_rx_counter = 0;
uint16_t g_usart3_last_rx_counter = 0;

/**
 * @brief       串口3中断服务函数
 * @param       无
 * @retval      无
 */
void USART3_IRQHandler(void)
{ 
//#if SYS_SUPPORT_OS                              /* 使用OS */
//    OSIntEnter();    
//#endif

    HAL_UART_IRQHandler(&huart3);       /* 调用HAL库中断处理公用函数 */

//#if SYS_SUPPORT_OS                              /* 使用OS */
//    OSIntExit();
//#endif
}
#endif

/**
 * @brief       Rx传输回调函数
 * @param       huart: UART句柄类型指针
 * @retval      无
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
#if USART1_RX_IT_EN
    if(huart->Instance == USART1)             /* 如果是串口1 */
    {
        g_usart1_rx_buf[g_usart1_rx_counter++] = g_hal_usart1_rx_buffer[0] ;
//        HAL_UART_Transmit(&huart1,g_hal_usart1_rx_buffer,1,100);
        printf("%c",g_hal_usart1_rx_buffer[0]);
        if(g_usart1_rx_counter > (USART1_REC_LEN - 1))
        {
            g_usart1_rx_counter = 0;     /* 接收数据错误,重新开始接收 */
        }
        
        HAL_UART_Receive_IT(&huart1, (uint8_t *)g_hal_usart1_rx_buffer, USART1_RX_BUFFER_SIZE);
    }
#endif

#if USART2_RX_IT_EN
    if(huart->Instance == USART2)             /* 如果是串口2 */
    {
        g_usart2_rx_buf[g_usart2_rx_counter++] = g_hal_usart2_rx_buffer[0] ;
//        printf("%c",g_hal_usart2_rx_buffer[0]);
        if(g_usart2_rx_counter > (USART2_REC_LEN - 1))
        {
            g_usart2_rx_counter = 0;     /* 接收数据错误,重新开始接收 */
        }
        
        HAL_UART_Receive_IT(&huart2, (uint8_t *)g_hal_usart2_rx_buffer, USART2_RX_BUFFER_SIZE);
    }
#endif

#if USART3_RX_IT_EN
    if(huart->Instance == USART3)             /* 如果是串口3 */
    {
        g_usart3_rx_buf[g_usart3_rx_counter++] = g_hal_usart3_rx_buffer[0] ;
//        printf("%c",g_hal_usart3_rx_buffer[0]);
        if(g_usart3_rx_counter > (USART3_REC_LEN - 1))
        {
            g_usart3_rx_counter = 0;     /* 接收数据错误,重新开始接收 */
        }
        
        HAL_UART_Receive_IT(&huart3, (uint8_t *)g_hal_usart3_rx_buffer, USART3_RX_BUFFER_SIZE);
    }
#endif
}

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

  #if USART1_RX_IT_EN  
  /* 该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量 */
  HAL_UART_Receive_IT(&huart1, (uint8_t *)g_hal_usart1_rx_buffer, USART1_RX_BUFFER_SIZE);
  #endif
  
//  HAL_UART_Transmit(&huart1,"hhhaahgha\r\n",10,1000);
}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  
  #if USART2_RX_IT_EN  
  /* 该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量 */
  HAL_UART_Receive_IT(&huart2, (uint8_t *)g_hal_usart2_rx_buffer, USART2_RX_BUFFER_SIZE);
  #endif
  
}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
//  huart3.Init.BaudRate = 115200;
  huart3.Init.BaudRate = 921600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  
  #if USART3_RX_IT_EN  
  /* 该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量 */
  HAL_UART_Receive_IT(&huart3, (uint8_t *)g_hal_usart3_rx_buffer, USART3_RX_BUFFER_SIZE);
  #endif
}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

#if USART1_RX_IT_EN
        HAL_NVIC_EnableIRQ(USART1_IRQn);                      /* 使能USART1中断通道 */
        HAL_NVIC_SetPriority(USART1_IRQn, 3, 3);              /* 抢占优先级3，子优先级3 */
#endif
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

#if USART2_RX_IT_EN
        HAL_NVIC_EnableIRQ(USART2_IRQn);                      /* 使能USART2中断通道 */
        HAL_NVIC_SetPriority(USART2_IRQn, 3, 3);              /* 抢占优先级3，子优先级3 */
#endif
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

#if USART3_RX_IT_EN
        HAL_NVIC_EnableIRQ(USART3_IRQn);                      /* 使能USART3中断通道 */
        HAL_NVIC_SetPriority(USART3_IRQn, 3, 3);              /* 抢占优先级3，子优先级3 */
#endif
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/* 不使用半主机模式，至少需要重定义_ttywrch\_sys_exit\_sys_command_string函数,以同时兼容AC6和AC5模式 */
int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

/* 定义_sys_exit()以避免使用半主机模式 */
void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}

/* FILE 在 stdio.h里面定义. */
//FILE __stdout;

/* 重定义fputc函数, printf函数最终会通过调用fputc输出字符串到串口 */
int fputc(int ch, FILE *f)
{
    while ((USART1->SR & 0X40) == 0);               /* 等待上一个字符发送完成 */

    USART1->DR = (uint8_t)ch;                       /* 将要发送的字符 ch 写入到DR寄存器 */
    return ch;
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
