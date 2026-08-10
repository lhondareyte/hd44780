/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c)2006-2023 Luc Hondareyte
 *
 */

#ifndef __HD44780_H__
#include "hd44780.h"
#endif

void LCD_gotoxy (uint8_t x, uint8_t y) 
{
	uint8_t cur = 0;
	y--;
	if (x > H44780_LINES || y > H44780_ROWS)
		return;
	if (x == 1 ){
		cur = H44780_SET_DDRAM_ADDR | y;
	}
#if defined HD44780_LINE2
	else if (x == 2) {
		cur = H44780_SET_DDRAM_ADDR | H44780_NEXT_LINE | y;
	}
#endif
#if defined HD44780_LINE4
	else if (x == 3) {
		cur = H44780_SET_DDRAM_ADDR | (y + H44780_ROWS) ;
	}
#endif
#if defined HD44780_LINE4
	else if (x == 4) {
		cur = H44780_SET_DDRAM_ADDR | H44780_NEXT_LINE | (y + H44780_ROWS) ;
	}
#endif
	LCD_ioctl(cur);
	LCD_wait();
}

