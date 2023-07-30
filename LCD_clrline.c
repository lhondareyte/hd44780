/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2006-2022 Luc Hondareyte
 *
 */

#ifndef __HD44780_H__
#include "hd44780.h"
#endif

void LCD_clrline (uint8_t n)
{
	LCD_gotoxy(n,1);
	n=H44780_ROWS;
	while  ( n ) {
		LCD_putc (0x20);
		n--;
	}
}
