/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c)2006-2026 Luc Hondareyte
 *
 */

#ifndef __HD44780_H__
#include "hd44780.h"
#endif

extern Cursor cursor;

void LCD_gotoxy (uint8_t x, uint8_t y) 
{
	uint8_t cur = 0;

	cursor.row = y;
	cursor.line = x;
	y--;

#if defined (H44780_QUIRK)
	
	if ( y < H44780_ROWS / 2 )
		cur = H44780_ADDR_LINE1;
	else
		cur = H44780_ADDR_LINE2;
#else
	if (x > H44780_LINES || y > H44780_ROWS)
		return;
	if (x == 1 ){
		cur = H44780_ADDR_LINE1 + y;
	}
#if (H44780_LINES > 1)
	else if (x == 2) {
		cur = H44780_ADDR_LINE2;
	}
#endif
#if (H44780_LINES > 2)
	else if (x == 3) {
		cur = H44780_ADDR_LINE3;
	}
#endif
#if (H44780_LINES > 3) 
	else if (x == 4) {
		cur = H44780_ADDR_LINE4;
	}
#endif
#endif
	cur += y;
	LCD_ioctl(cur);
}

