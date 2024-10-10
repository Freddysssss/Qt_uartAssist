/**
 ****************************************************************************************************
 * @file        text.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2021-11-06
 * @brief       ������ʾ ����
 *              �ṩtext_show_font��text_show_string��������,������ʾ����
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
#include "text.h"
#include "lcd.h"
#include "malloc.h"
#include "usart.h"
#include "norflash.h"
#include "fonts.h"


/**
 * @brief       ��ʾһ��ָ����С�ĺ���
 * @param       x,y   : ���ֵ�����
 * @param       font  : ����GBK��
 * @param       size  : �����С
 * @param       mode  : ��ʾģʽ
 *   @note              0, ������ʾ(����Ҫ��ʾ�ĵ�,��LCD����ɫ���,��g_back_color)
 *   @note              1, ������ʾ(����ʾ��Ҫ��ʾ�ĵ�, ����Ҫ��ʾ�ĵ�, ��������)
 * @param       color : ������ɫ
 * @retval      ��
 */
void text_show_font(uint16_t x, uint16_t y, uint8_t *font, uint8_t size, uint8_t mode, uint16_t color)
{
    uint8_t gbk_h;//���ָ��ֽ�,0x81~0xFE,��126����(������0x00~0x80,�Լ�0xFF)
    uint8_t gbk_l;//���ֵ��ֽ�,0x40~0x7E,0x80~0xFE,��190�����루������0x00~0x39,�Լ�0x7F��0xFF��
    uint8_t csize;//�������ֵ������ݴ�С
    uint32_t offset;//���ֵ����������ֿ����ƫ�Ƶ�ַ
    uint8_t *pHanziDz;//Ŀ�꺺�ֵ�������
    uint16_t y0 = y;//�������ʼֵ
    uint8_t i;
    uint8_t j;
    
    //��ȡ���ָߵ��ֽ�
    gbk_h = *font;
    gbk_l = *(font + 1);
    
    //��ȡ���ֵ������ݴ�С
    csize = ((size/8) + ((size%8)?1:0)) * size;
    
    //���˷�������Χֵ
    if (size != 12 && size != 16 && size != 24)
    {
        return;     /* ��֧�ֵ�size */
    }
    pHanziDz = mymalloc(SRAMIN, csize);
    if (pHanziDz == 0) return;
    if (gbk_h < 0x81 || gbk_h == 0xFF ||
        gbk_l <0x40 || gbk_l == 0x7F || gbk_l == 0xFF)
    {
        for (i = 0; i < csize; i++)
        {
            *pHanziDz++ = 0x00;//ȫ�����հ�ֵ
        }
        return;
    }
    
    //��ȡ���ֵ����������ֿ����ƫ�Ƶ�ַ
    gbk_h -= 0x81;
    if (gbk_l < 0x7F) gbk_l -= 0x40;
    else gbk_l -= 0x41;
    offset = ((uint32_t)gbk_h*190 + gbk_l) *csize;
    
    //��ȡĿ�꺺�ֵ�������
    switch (size)
    {
        case 12:
            norflash_read(pHanziDz, ftinfo.f12addr + offset, csize);
            break;
        case 16:
            norflash_read(pHanziDz, ftinfo.f16addr + offset, csize);
            break;
        case 24:
            norflash_read(pHanziDz, ftinfo.f24addr + offset, csize);
            break;
        default: break;
    }
    
    //��ʾ���֣����У���λ��ǰ��
    for (i = 0; i < csize; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (pHanziDz[i] & (0x80>>j))//�Ӹ�λ��ʼ��εݼ�
            {
                lcd_draw_point(x, y, color);//����Ҫ��ʾ�ĵ�
            }
            else if (mode == 0)//�ǵ���ģʽ������Ҫ��ʾ�ĵ��ñ���ɫ���
            {
                lcd_draw_point(x, y, g_back_color);//��䱳��ɫ
            }
            
            y++;
            if (y - y0 == size)//������Խ���ˣ�����������ͷ��ʼ��������������һ����λ
            {
                y = y0;
                x++;
                break;
            }
        }
    }
    
    myfree(SRAMIN, pHanziDz);//�ͷ��ڴ�
}

/**
 * @brief       ��ָ��λ�ÿ�ʼ��ʾһ���ַ���
 *   @note      �ú���֧���Զ�����
 * @param       x,y   : ��ʼ����
 * @param       width : ��ʾ������
 * @param       height: ��ʾ����߶�
 * @param       str   : �ַ���
 * @param       size  : �����С
 * @param       mode  : ��ʾģʽ
 *   @note              0, ������ʾ(����Ҫ��ʾ�ĵ�,��LCD����ɫ���,��g_back_color)
 *   @note              1, ������ʾ(����ʾ��Ҫ��ʾ�ĵ�, ����Ҫ��ʾ�ĵ�, ��������)
 * @param       color : ������ɫ
 * @retval      ��
 */
void text_show_string(uint16_t x, uint16_t y, char *str, uint8_t size, uint16_t color)
{
    uint8_t *pStr = (uint8_t *)str;
    
    while(*pStr != 0)
    {
        if (*pStr < 0x81)//�ַ�
        {
            if (x + size/2 > 240)//x����Խ����,����
            {
                x = 0;//x����ص���ʼλ��
                y += size;//y��������һ����λ(�ַ��߶��뺺�ָ߶�һ��)
            }
            if (y + size > 320)//y����Խ���ˣ��˳�
            {
                break;
            }
            
            if (*pStr == '\n')//����
            {
                x = 0;//x����ص���ʼλ��
                y += size;//y��������һ����λ(�ַ��߶��뺺�ָ߶�һ��)
            }
            else
            {
                lcd_show_char(x, y, *pStr, size, 0, color);//��Ч����д��
                x += size/2;//�����������ƶ�һ���ַ���λ(һ���ַ�ֻ�а�����ֿ�)
            }
            pStr++;
        }
        else //����
        {
            if (x + size > 240)//x����Խ����,����
            {
                x = 0;//x����ص���ʼλ��
                y += size;//y��������һ����λ(�ַ��߶��뺺�ָ߶�һ��)
            }
            if (y + size > 320)//y����Խ���ˣ��˳�
            {
                break;
            }
            text_show_font(x, y, pStr, size, 0, color);
            x += size;//�����������ƶ�һ�����ֵ�λ(1�����ֿ���൱��2���ַ����)
            pStr += 2;
        }
    }
}








