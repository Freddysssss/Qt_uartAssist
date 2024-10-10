/**
 ****************************************************************************************************
 * @file        text.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2021-11-06
 * @brief       汉字显示 代码
 *              提供text_show_font和text_show_string两个函数,用于显示汉字
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20211106
 * 第一次发布
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
 * @brief       显示一个指定大小的汉字
 * @param       x,y   : 汉字的坐标
 * @param       font  : 汉字GBK码
 * @param       size  : 字体大小
 * @param       mode  : 显示模式
 *   @note              0, 正常显示(不需要显示的点,用LCD背景色填充,即g_back_color)
 *   @note              1, 叠加显示(仅显示需要显示的点, 不需要显示的点, 不做处理)
 * @param       color : 字体颜色
 * @retval      无
 */
void text_show_font(uint16_t x, uint16_t y, uint8_t *font, uint8_t size, uint8_t mode, uint16_t color)
{
    uint8_t gbk_h;//汉字高字节,0x81~0xFE,共126个区(不包括0x00~0x80,以及0xFF)
    uint8_t gbk_l;//汉字低字节,0x40~0x7E,0x80~0xFE,共190个编码（不包括0x00~0x39,以及0x7F和0xFF）
    uint8_t csize;//单个汉字点阵数据大小
    uint32_t offset;//汉字点阵数据在字库里的偏移地址
    uint8_t *pHanziDz;//目标汉字点阵数据
    uint16_t y0 = y;//纵坐标初始值
    uint8_t i;
    uint8_t j;
    
    //获取汉字高低字节
    gbk_h = *font;
    gbk_l = *(font + 1);
    
    //获取汉字点阵数据大小
    csize = ((size/8) + ((size%8)?1:0)) * size;
    
    //过滤非正常范围值
    if (size != 12 && size != 16 && size != 24)
    {
        return;     /* 不支持的size */
    }
    pHanziDz = mymalloc(SRAMIN, csize);
    if (pHanziDz == 0) return;
    if (gbk_h < 0x81 || gbk_h == 0xFF ||
        gbk_l <0x40 || gbk_l == 0x7F || gbk_l == 0xFF)
    {
        for (i = 0; i < csize; i++)
        {
            *pHanziDz++ = 0x00;//全部填充空白值
        }
        return;
    }
    
    //获取汉字点阵数据在字库里的偏移地址
    gbk_h -= 0x81;
    if (gbk_l < 0x7F) gbk_l -= 0x40;
    else gbk_l -= 0x41;
    offset = ((uint32_t)gbk_h*190 + gbk_l) *csize;
    
    //提取目标汉字点阵数据
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
    
    //显示汉字（逐列，高位在前）
    for (i = 0; i < csize; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (pHanziDz[i] & (0x80>>j))//从高位开始逐次递减
            {
                lcd_draw_point(x, y, color);//画需要显示的点
            }
            else if (mode == 0)//非叠加模式，不需要显示的点用背景色填充
            {
                lcd_draw_point(x, y, g_back_color);//填充背景色
            }
            
            y++;
            if (y - y0 == size)//纵坐标越界了，则纵坐标重头开始，横坐标向右移一个单位
            {
                y = y0;
                x++;
                break;
            }
        }
    }
    
    myfree(SRAMIN, pHanziDz);//释放内存
}

/**
 * @brief       在指定位置开始显示一个字符串
 *   @note      该函数支持自动换行
 * @param       x,y   : 起始坐标
 * @param       width : 显示区域宽度
 * @param       height: 显示区域高度
 * @param       str   : 字符串
 * @param       size  : 字体大小
 * @param       mode  : 显示模式
 *   @note              0, 正常显示(不需要显示的点,用LCD背景色填充,即g_back_color)
 *   @note              1, 叠加显示(仅显示需要显示的点, 不需要显示的点, 不做处理)
 * @param       color : 字体颜色
 * @retval      无
 */
void text_show_string(uint16_t x, uint16_t y, char *str, uint8_t size, uint16_t color)
{
    uint8_t *pStr = (uint8_t *)str;
    
    while(*pStr != 0)
    {
        if (*pStr < 0x81)//字符
        {
            if (x + size/2 > 240)//x坐标越界了,换行
            {
                x = 0;//x坐标回到起始位置
                y += size;//y坐标下移一个单位(字符高度与汉字高度一样)
            }
            if (y + size > 320)//y坐标越界了，退出
            {
                break;
            }
            
            if (*pStr == '\n')//换行
            {
                x = 0;//x坐标回到起始位置
                y += size;//y坐标下移一个单位(字符高度与汉字高度一样)
            }
            else
            {
                lcd_show_char(x, y, *pStr, size, 0, color);//有效部分写入
                x += size/2;//横坐标往右移动一个字符单位(一个字符只有半个汉字宽)
            }
            pStr++;
        }
        else //中文
        {
            if (x + size > 240)//x坐标越界了,换行
            {
                x = 0;//x坐标回到起始位置
                y += size;//y坐标下移一个单位(字符高度与汉字高度一样)
            }
            if (y + size > 320)//y坐标越界了，退出
            {
                break;
            }
            text_show_font(x, y, pStr, size, 0, color);
            x += size;//横坐标往右移动一个汉字单位(1个汉字宽度相当于2个字符宽度)
            pStr += 2;
        }
    }
}








