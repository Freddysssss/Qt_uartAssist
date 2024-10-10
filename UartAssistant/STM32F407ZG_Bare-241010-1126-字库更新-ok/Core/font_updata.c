#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "usart.h"
#include "fonts.h"
#include "norflash.h"
#include "lcd.h"
#include "text.h"

#include "log.h"

#define USART_RX_BUF                g_usart3_rx_buf
#define USART_REC_LEN               USART3_REC_LEN
#define uart_rx_counter             g_usart3_rx_counter
#define uart_rx_last_counter        g_usart3_last_rx_counter
#define USART_SendBuf(buf, len)     USART_SendBuf(huart3, buf, len)
u8 uart_rx_buf[USART_REC_LEN];
uint16_t uart_rx_len=0;
uint16_t error_code = 0;

typedef struct 
{
	uint8_t Pack_Error[8];//升级文件错误
	uint8_t Get_Pack_Lenth[8];//请求文件信息，数据包长度
	uint8_t Get_Next_Pack[8];//请求下一帧数据
	uint8_t Uptata_Completed[8];//升级完成
    uint8_t Erasing_Old_Font[8];//擦除旧字库中
    uint8_t Erase_Old_Font_Completed[8];//擦除旧字库完成
}ReplyStructure;

ReplyStructure Reply=
{
	{0xAA,0x55,0x02,0x00,0x00,0x00,0x01,0x01},//升级文件错误
	{0xAA,0x55,0x02,0x01,0x00,0x00,0x01,0x02},//请求文件信息，数据包长度
	{0xAA,0x55,0x02,0x02,0x00,0x00,0x01,0x03},//请求下一帧数据
	{0xAA,0x55,0x02,0x03,0x00,0x00,0x01,0x04},//升级完成
    {0xAA,0x55,0x02,0x04,0x00,0x00,0x01,0x05},//擦除旧字库中
    {0xAA,0x55,0x02,0x05,0x00,0x00,0x01,0x06},//擦除旧字库完成
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
uint32_t currentAddr;

#define PRINTF_EN  1

#define BASE_ADDR_UGBK      12
#define BASE_ADDR_GBK12     17
#define BASE_ADDR_GBK16     22
#define BASE_ADDR_GBK24     27
void updata_font_library_process(void)
{
    uint8_t buff_to_write[USART_REC_LEN - 9];
    uint32_t buff_len_to_write = 0;
    
	if (uart_rx_counter)
	{
		// LOG_I("uart_rx_counter=%d",uart_rx_counter);
		// LOG_I("uart_rx_last_counter=%d",uart_rx_last_counter);
		if(uart_rx_last_counter == uart_rx_counter)
		{
//			int i;
			uart_rx_len = uart_rx_counter;
			uart_rx_counter=0;
			uart_rx_last_counter = 0;
			printf("\r\nuart_rx_len = %d\r\n", uart_rx_len);
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
            buff_len_to_write = (uint16_t)uart_rx_buf[2]<<8 | uart_rx_buf[3];
			if (((uint16_t)uart_rx_buf[2]<<8 | uart_rx_buf[3] + 9) != uart_rx_len)
            if (buff_len_to_write != uart_rx_len - 9)
			{
				error_code |= 0x02;
			}
			checkBytes = (uint16_t)uart_rx_buf[uart_rx_len - 2] << 8 | (uint16_t)uart_rx_buf[uart_rx_len - 1];
			checksum = checkSum(uart_rx_buf, uart_rx_len - 2);
			if (checksum != checkBytes)
			{
				printf("checkBytes = %x\r\n", checkBytes);
				printf("checksum = %x\r\n", checksum);
				error_code |= 0x04;
			}

			if (error_code)
			{
				printf("error_code = %x\r\n", error_code);
				USART_SendBuf(Reply.Pack_Error, sizeof(Reply.Pack_Error));//更新错误
				return;
			}
            
			switch (uart_rx_buf[4])
			{
                case 0xE0:
				{
                    #if PRINTF_EN
					printf("get file info.\r\n");
                    #else
                    LOG("get file info.\r\n");
                    #endif
                    ftinfo.fontok = 0xAA;//标记已更新字库
                    
                    /* UNIGBK.bin地址 和 大小 */
                    ftinfo.ugbkaddr = FONTINFOADDR + sizeof(ftinfo); /* 信息头之后，紧跟UNIGBK转换码表 */
                    ftinfo.ugbksize = uart_rx_buf[BASE_ADDR_UGBK+0] << 24;
                    ftinfo.ugbksize|= uart_rx_buf[BASE_ADDR_UGBK+1] << 16;
                    ftinfo.ugbksize|= uart_rx_buf[BASE_ADDR_UGBK+2] << 8;
                    ftinfo.ugbksize|= uart_rx_buf[BASE_ADDR_UGBK+3] << 0;
                    
                    /* GBK12.bin地址 和 大小 */
                    ftinfo.f12addr = ftinfo.ugbkaddr + ftinfo.ugbksize; /* UNIGBK转换码表之后，紧跟GBK12.bin */
                    ftinfo.gbk12size = uart_rx_buf[BASE_ADDR_GBK12+0] << 24;
                    ftinfo.gbk12size|= uart_rx_buf[BASE_ADDR_GBK12+1] << 16;
                    ftinfo.gbk12size|= uart_rx_buf[BASE_ADDR_GBK12+2] << 8;
                    ftinfo.gbk12size|= uart_rx_buf[BASE_ADDR_GBK12+3] << 0;
                    
                    /* GBK16.bin地址 和 大小 */
                    ftinfo.f16addr = ftinfo.f12addr + ftinfo.gbk12size; /* GBK12.bin之后，紧跟GBK16.bin */
                    ftinfo.gbk16size = uart_rx_buf[BASE_ADDR_GBK16+0] << 24;
                    ftinfo.gbk16size|= uart_rx_buf[BASE_ADDR_GBK16+1] << 16;
                    ftinfo.gbk16size|= uart_rx_buf[BASE_ADDR_GBK16+2] << 8;
                    ftinfo.gbk16size|= uart_rx_buf[BASE_ADDR_GBK16+3] << 0;
                    
                    /* GBK24.bin地址 和 大小 */
                    ftinfo.f24addr = ftinfo.f16addr + ftinfo.gbk16size; /* GBK16.bin之后，紧跟GBK24.bin */
                    ftinfo.gbk24size = uart_rx_buf[BASE_ADDR_GBK24+0] << 24;
                    ftinfo.gbk24size|= uart_rx_buf[BASE_ADDR_GBK24+1] << 16;
                    ftinfo.gbk24size|= uart_rx_buf[BASE_ADDR_GBK24+2] << 8;
                    ftinfo.gbk24size|= uart_rx_buf[BASE_ADDR_GBK24+3] << 0;
                    
                    printf("ugbkaddr    = 0x%08x\r\n",ftinfo.ugbkaddr);
                    printf("ugbksize    = 0x%08x\r\n",ftinfo.ugbksize);
                    printf("f12addr     = 0x%08x\r\n",ftinfo.f12addr);
                    printf("gbk12size   = 0x%08x\r\n",ftinfo.gbk12size);
                    printf("f16addr     = 0x%08x\r\n",ftinfo.f16addr);
                    printf("gbk16size   = 0x%08x\r\n",ftinfo.gbk16size);
                    printf("f24addr     = 0x%08x\r\n",ftinfo.f24addr);
                    printf("gbk24size   = 0x%08x\r\n",ftinfo.gbk24size);
                    
                    
					USART_SendBuf(Reply.Erasing_Old_Font, sizeof(Reply.Erasing_Old_Font));
                    
                    //擦除
                    printf("erase flash......\r\n");
                    lcd_clear(WHITE); /* 清屏 */
                    text_show_string(5, 60, "erase flash......", 16, BLUE);
                    norflash_erase_old_font();
                    printf("erased ok!\r\n");
                    text_show_string(5, 80, "erased ok!", 16, BLUE);
                    
                    
                #if 0
                    //写入flash
                    uint8_t *p = (uint8_t *)(&ftinfo);
                    printf("write:\r\n");
                    for (uint8_t i = 0; i < sizeof(ftinfo); i++)
                    printf("%02x ",p[i]);
                    printf("\r\n");
                    currentAddr = FONTINFOADDR;//当前写入地址
                    norflash_write((uint8_t *)(&ftinfo), currentAddr, sizeof(ftinfo));/* 从FONTINFOADDR开始写入个数据 */
                    currentAddr = ftinfo.ugbkaddr;//当前写入地址
                    printf("write finished.\r\n");
                    
                    //从flash读出
                    uint8_t buff[50] = {0};
                    norflash_read((uint8_t *)buff, FONTINFOADDR, sizeof(ftinfo));
                    printf("read:\r\n");
                    for (uint8_t i = 0; i < sizeof(ftinfo); i++)
                    printf("%02x ",buff[i]);
                    printf("\r\n");
                #endif
                
					USART_SendBuf(Reply.Erase_Old_Font_Completed, sizeof(Reply.Erase_Old_Font_Completed));
                    #if PRINTF_EN
                    printf("send Reply.\r\n");
                    #else
                    LOG("send Reply.\r\n");
                    #endif
				}break;
				case 0xE1:
				{
					printf("request update.\r\n");
					frameSerial = 0;
                    currentAddr = FONTINFOADDR + sizeof(ftinfo);//当前写入地址
					USART_SendBuf(Reply.Get_Pack_Lenth, sizeof(Reply.Get_Pack_Lenth));
				}break;
				case 0xE2:
				{
					framesNum = (uint16_t)uart_rx_buf[7]<<8|uart_rx_buf[8];
					printf("bin file packages number: %d",framesNum);
					frameSerial++;
					Reply.Get_Next_Pack[4] = (frameSerial>>8) & 0xFF;
					Reply.Get_Next_Pack[5] = frameSerial& 0xFF;
					checksum = checkSum(Reply.Get_Next_Pack, 6);
					Reply.Get_Next_Pack[6] = checksum>>8 & 0xFF;
					Reply.Get_Next_Pack[7] = checksum & 0xFF;
					USART_SendBuf(Reply.Get_Next_Pack, sizeof(Reply.Get_Next_Pack));//请求下一帧(第一帧)
				}break;
				case 0xE3:
				{
					if (frameSerial <= framesNum)
					{
                        printf("buff_len_to_write = %d\r\n",buff_len_to_write);
                        //拷贝数据
                        memcpy(buff_to_write, &uart_rx_buf[7], buff_len_to_write);
//                        printf("memcpy.\r\n");
                        //写入flash
                        norflash_write(buff_to_write, currentAddr, buff_len_to_write);/* 从开始写入个数据 */
                        currentAddr += buff_len_to_write;
//                        printf("written into flash.\r\n");
						frameSerial++;
						Reply.Get_Next_Pack[4] = (frameSerial>>8) & 0xFF;
						Reply.Get_Next_Pack[5] = frameSerial& 0xFF;
						checksum = checkSum(Reply.Get_Next_Pack, 6);
						Reply.Get_Next_Pack[6] = checksum>>8 & 0xFF;
						Reply.Get_Next_Pack[7] = checksum & 0xFF;
						USART_SendBuf(Reply.Get_Next_Pack, sizeof(Reply.Get_Next_Pack));//请求下一帧
					}
					else
					{
						USART_SendBuf(Reply.Pack_Error, sizeof(Reply.Pack_Error));//更新错误
					}
				}break;
				case 0xE4:
				{
					printf("update finished.\r\n");
                    
                #if 1
                    //写入flash
                    uint8_t *p = (uint8_t *)(&ftinfo);
                    printf("write:\r\n");
                    for (uint8_t i = 0; i < sizeof(ftinfo); i++)
                    printf("%02x ",p[i]);
                    printf("\r\n");
                    norflash_write((uint8_t *)(&ftinfo), FONTINFOADDR, sizeof(ftinfo));/* 从FONTINFOADDR开始写入个数据 */
                    printf("write finished.\r\n");
                    
                    //从flash读出
                    uint8_t buff[50] = {0};
                    norflash_read((uint8_t *)buff, FONTINFOADDR, sizeof(ftinfo));
                    printf("read:\r\n");
                    for (uint8_t i = 0; i < sizeof(ftinfo); i++)
                    printf("%02x ",buff[i]);
                    printf("\r\n");
                #endif
                    
//                    norflash_read((uint8_t *)&ftinfo, FONTINFOADDR, sizeof(ftinfo));
//                    text_show_string(5, 132, "更新成功，请复位!", 24, BLUE);
                    text_show_string(12, 132, "update ok,\n please reset!", 24, BLUE);
					USART_SendBuf(Reply.Uptata_Completed, sizeof(Reply.Uptata_Completed));
				}break;
			}
		}
		else
		{
			uart_rx_last_counter = uart_rx_counter;
		}
		
//		delay_ms(1); 
//        vTaskDelay(1);
	}
}

