/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2006-2022 Luc Hondareyte
 *
 */

#ifndef __HD44780_H__
 #include "hd44780.h"
#endif

void LCD_puts (const char *s)
{
	register char c;
	while ((c = *s++)) {
		if (c == 0x0a)
			LCD_gotoxy(2,1);
		else
			LCD_putc (c);
	}
}
