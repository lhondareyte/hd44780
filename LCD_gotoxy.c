/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c)2006-2026 Luc Hondareyte
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
		cur = H44780_SET_DDRAM_ADDR + y;
	}
#if defined (H44780_LINE2) || defined (H44780_QUIRK)
	else if (x == 2) {
		cur = H44780_SET_DDRAM_ADDR | H44780_NEXT_LINE;
	}
#endif
#if defined H44780_LINE3
	else if (x == 3) {
		cur = H44780_SET_DDRAM_ADDR | H44780_ROWS ;
	}
#endif
#if defined H44780_LINE4
	else if (x == 4) {
		cur = H44780_SET_DDRAM_ADDR | H44780_NEXT_LINE | H44780_ROWS ;
	}
#endif
	cur += y;
	LCD_ioctl(cur);
}

