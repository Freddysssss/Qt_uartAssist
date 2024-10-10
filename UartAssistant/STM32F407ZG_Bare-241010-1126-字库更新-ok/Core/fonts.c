/**
 ****************************************************************************************************
 * @file        font.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2021-11-06
 * @brief       �ֿ� ����
 *              �ṩfonts_update_font��fonts_init�����ֿ���ºͳ�ʼ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20211106
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#include "string.h"
#include "lcd.h"
#include "fonts.h"
#include "malloc.h"
#include "norflash.h"
#include "delay.h"

#include "log.h"

/* �ֿ�����ռ�õ�����������С(3���ֿ�+unigbk��+�ֿ���Ϣ=3238700 �ֽ�,Լռ791��25QXX����,һ������4K�ֽ�) */
#define FONTSECSIZE         791

 
/* ���������ֿ������Ϣ����ַ����С�� */
_font_info ftinfo;

/* �ֿ����ڴ����е�·�� */
char *const FONT_GBK_PATH[4] =
{
    "/SYSTEM/FONT/UNIGBK.BIN",      /* UNIGBK.BIN�Ĵ��λ�� */
    "/SYSTEM/FONT/GBK12.FON",       /* GBK12�Ĵ��λ�� */
    "/SYSTEM/FONT/GBK16.FON",       /* GBK16�Ĵ��λ�� */
    "/SYSTEM/FONT/GBK24.FON",       /* GBK24�Ĵ��λ�� */
};

/* ����ʱ����ʾ��Ϣ */
char *const FONT_UPDATE_REMIND_TBL[4] =
{
    "Updating UNIGBK.BIN",          /* ��ʾ���ڸ���UNIGBK.bin */
    "Updating GBK12.FON ",          /* ��ʾ���ڸ���GBK12 */
    "Updating GBK16.FON ",          /* ��ʾ���ڸ���GBK16 */
    "Updating GBK24.FON ",          /* ��ʾ���ڸ���GBK24 */
};



/**
 * @brief       ��ʼ������
 * @param       ��
 * @retval      0, �ֿ����; ����, �ֿⶪʧ;
 */
uint8_t fonts_init(void)
{
    uint8_t t = 0;
    
    while(t < 10)
    {
        t++;
        
        norflash_read((uint8_t *)&ftinfo, FONTINFOADDR, sizeof(ftinfo));
        LOG_I("ftinfo.fontok = 0x%x",ftinfo.fontok);
        if (ftinfo.fontok == 0xAA)
        {
            return 0;
        }
        delay_ms(20);
    }
    
    return 1;
}









