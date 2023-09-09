/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2006-2023 Luc Hondareyte
 *
 */

#ifndef __HD44780_H__
 #include "hd44780.h"
#endif

void LCD_gotoxy (uint8_t x, uint8_t y) 
{
	if (x > H44780_LINES || y > H44780_ROWS)
		return;
        uint8_t cur= H44780_DDRAM_L1 - 1;
	cur += y;

#if (H44780_LINES == 1) 
	if ( y > (H44780_ROWS/2))
		cur += 49;
#endif
#if (H44780_LINES >= 2) 
	else if (x == 2) {	
		cur += H44780_DDRAM_L2;
	}
#endif
#if (H44780_LINES >= 3) 
	else if (x == 3) {	
		cur += H44780_DDRAM_L3;
	}
#endif
#if (H44780_LINES >= 4) 
	else if (x == 4) {	
		cur += H44780_DDRAM_L4;
	}
#endif
	LCD_ioctl(cur);
	LCD_wait();
}
