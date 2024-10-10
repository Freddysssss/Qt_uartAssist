/* Includes ------------------------------------------------------------------*/
#include "led.h"
#include "log.h"
#include "delay.h"

/** 
*   ∞¥º¸≥ı ºªØ≈‰÷√
*/
void led_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LED0_GPIO_CLK_ENABLE();
  LED1_GPIO_CLK_ENABLE();

  /*Configure GPIO pins*/
  GPIO_InitStruct.Pin = LED0_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LED1_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);
  
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_SET);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
