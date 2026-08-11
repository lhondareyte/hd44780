/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c)2026 Luc Hondareyte
 *
 */
#ifndef __HD44780_H__
#include "hd44780.h"
#endif

#if ! defined (H44780_QUIRK)

extern Cursor cursor;

inline void LCD_next_line(void) {
#if (H44780_LINES > 1) 
	if (cursor.line == 1) {
		LCD_ioctl(H44780_ADDR_LINE2);
		cursor.line++;
	}
#endif
#if (H44780_LINES > 2) 
	else if (cursor.line == 2) {
		LCD_ioctl(H44780_ADDR_LINE4);
		cursor.line++;

	}
#endif
#if (H44780_LINES > 3) 
	else if (cursor.line == 3) {
		LCD_ioctl(H44780_ADDR_LINE4);
		cursor.line++;
	}
#endif
#if (H44780_LINES == 4) 
	else if (cursor.line == 4) {
		LCD_ioctl(H44780_ADDR_LINE1);
		cursor.line = 1;
	}
#endif
}
#endif
