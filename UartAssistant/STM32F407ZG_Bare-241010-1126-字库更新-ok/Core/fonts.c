/**
 ****************************************************************************************************
 * @file        font.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2021-11-06
 * @brief       字库 代码
 *              提供fonts_update_font和fonts_init用于字库更新和初始化
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
#include "lcd.h"
#include "fonts.h"
#include "malloc.h"
#include "norflash.h"
#include "delay.h"

#include "log.h"

/* 字库区域占用的总扇区数大小(3个字库+unigbk表+字库信息=3238700 字节,约占791个25QXX扇区,一个扇区4K字节) */
#define FONTSECSIZE         791

 
/* 用来保存字库基本信息，地址，大小等 */
_font_info ftinfo;

/* 字库存放在磁盘中的路径 */
char *const FONT_GBK_PATH[4] =
{
    "/SYSTEM/FONT/UNIGBK.BIN",      /* UNIGBK.BIN的存放位置 */
    "/SYSTEM/FONT/GBK12.FON",       /* GBK12的存放位置 */
    "/SYSTEM/FONT/GBK16.FON",       /* GBK16的存放位置 */
    "/SYSTEM/FONT/GBK24.FON",       /* GBK24的存放位置 */
};

/* 更新时的提示信息 */
char *const FONT_UPDATE_REMIND_TBL[4] =
{
    "Updating UNIGBK.BIN",          /* 提示正在更新UNIGBK.bin */
    "Updating GBK12.FON ",          /* 提示正在更新GBK12 */
    "Updating GBK16.FON ",          /* 提示正在更新GBK16 */
    "Updating GBK24.FON ",          /* 提示正在更新GBK24 */
};



/**
 * @brief       初始化字体
 * @param       无
 * @retval      0, 字库完好; 其他, 字库丢失;
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









