#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include <string.h>

#include "log.h"

 
/************************************************
 ALIENTEK精英STM32开发板实验4
 串口 实验   
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/
uint16_t uart_rx_len=0;
uint16_t error_code = 0;
u8 uart_rx_buf[USART_REC_LEN];
typedef struct 
{
	u8 Pack_Error[8];//升级文件错误
	u8 Get_Pack_Lenth[8];//请求文件信息，数据包长度
	u8 Get_Next_Pack[8];//请求下一帧数据
	u8 Uptata_Completed[8];//升级完成
}ReplyStructure;

ReplyStructure Reply=
{
	{0xAA,0x55,0x02,0x00,0x00,0x00,0x01,0x01},//升级文件错误
	{0xAA,0x55,0x02,0x01,0x00,0x00,0x01,0x02},//请求文件信息，数据包长度
	{0xAA,0x55,0x02,0x02,0x00,0x00,0x01,0x03},//请求下一帧数据
	{0xAA,0x55,0x02,0x03,0x00,0x00,0x01,0x04},//升级完成
};

uint16_t checkSum(uint8_t *buf, uint16_t len)
{
    uint16_t checksum = 0;
    uint16_t i = 0;
    for(i = 0; i < len; i++)
    {
        checksum += (uint16_t)buf[i];
    }
    return checksum;
}

uint16_t checksum = 0;
uint16_t checkBytes = 0;
uint16_t framesNum = 0;//分包数量
uint16_t frameSerial = 0;//分包序列号
void uart_process(void)
{
	if (uart_rx_counter)
	{
		// LOG_I("uart_rx_counter=%d",uart_rx_counter);
		// LOG_I("uart_rx_last_counter=%d",uart_rx_last_counter);
		if(uart_rx_last_counter == uart_rx_counter)
		{
			int i;
			uart_rx_len = uart_rx_counter;
			uart_rx_counter=0;
			uart_rx_last_counter = 0;
			LOG_I("uart_rx_len = %d", uart_rx_len);
			memcpy(uart_rx_buf, USART_RX_BUF, uart_rx_len);
			// LOG_HEX("rec:", uart_rx_buf, uart_rx_len);
			// for (i=0;i<uart_rx_len;i++)
			// {
			// 	LOG("%x ", uart_rx_buf[i]);
			// }
			// LOG("\r\n");

			error_code = 0;
			if (uart_rx_buf[0]!=0xA9 || uart_rx_buf[1]!=0x54)
			{
				error_code |= 0x01;
			}
			if (((uint16_t)uart_rx_buf[2]<<8 | uart_rx_buf[3] + 9) != uart_rx_len)
			{
				error_code |= 0x02;
			}
			checkBytes = (uint16_t)uart_rx_buf[uart_rx_len - 2] << 8 | (uint16_t)uart_rx_buf[uart_rx_len - 1];
			checksum = checkSum(uart_rx_buf, uart_rx_len - 2);
			if (checksum != checkBytes)
			{
				LOG_I("checkBytes = %x", checkBytes);
				LOG_I("checksum = %x", checksum);
				error_code |= 0x04;
			}

			if (error_code)
			{
				LOG_I("error_code = %x", error_code);
				USART1_SendBuf(Reply.Pack_Error, sizeof(Reply.Pack_Error));//更新错误
				return;
			}

			switch (uart_rx_buf[4])
			{
				case 0xE1:
				{
					LOG_I("request update.");
					frameSerial = 0;
					USART1_SendBuf(Reply.Get_Pack_Lenth, sizeof(Reply.Get_Pack_Lenth));
				}break;
				case 0xE2:
				{
					framesNum = (uint16_t)uart_rx_buf[7]<<8|uart_rx_buf[8];
					LOG_I("bin file packages number: %d",framesNum);
					frameSerial++;
					Reply.Get_Next_Pack[4] = (frameSerial>>8) & 0xFF;
					Reply.Get_Next_Pack[5] = frameSerial& 0xFF;
					checksum = checkSum(Reply.Get_Next_Pack, 6);
					Reply.Get_Next_Pack[6] = checksum>>8 & 0xFF;
					Reply.Get_Next_Pack[7] = checksum & 0xFF;
					USART1_SendBuf(Reply.Get_Next_Pack, sizeof(Reply.Get_Next_Pack));//请求下一帧(第一帧)
				}break;
				case 0xE3:
				{
					LOG_I("packages.");
					if (frameSerial <= framesNum)
					{
						frameSerial++;
						Reply.Get_Next_Pack[4] = (frameSerial>>8) & 0xFF;
						Reply.Get_Next_Pack[5] = frameSerial& 0xFF;
						checksum = checkSum(Reply.Get_Next_Pack, 6);
						Reply.Get_Next_Pack[6] = checksum>>8 & 0xFF;
						Reply.Get_Next_Pack[7] = checksum & 0xFF;
						USART1_SendBuf(Reply.Get_Next_Pack, sizeof(Reply.Get_Next_Pack));//请求下一帧
					}
					else
					{
						USART1_SendBuf(Reply.Pack_Error, sizeof(Reply.Pack_Error));//更新错误
					}
				}break;
				case 0xE4:
				{
					LOG_I("update finished.");
					USART1_SendBuf(Reply.Uptata_Completed, sizeof(Reply.Uptata_Completed));
				}break;
			}
		}
		else
		{
			uart_rx_last_counter = uart_rx_counter;
		}
		
		delay_ms(1); 
	}
}
 int main(void)
 {	
    delay_init();	    	 //延时函数初始化	  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    // uart_init(115200);	 //串口初始化为115200
	uart_init(921600);
    LED_Init();			     //LED端口初始化
    KEY_Init();          //初始化与按键连接的硬件接口
    LOG_I("hello world");
 	while(1)
	{
		uart_process();
	}	 
 }

