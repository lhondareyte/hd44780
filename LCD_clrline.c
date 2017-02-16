/*
 * Copyright (c) 2006-2017 Luc HONDAREYTE
 * All rights reserved.
 *
 */


#ifndef __HD44780_H__
#include "hd44780.h"
#endif

void LCD_clrline (uint8_t n)
{
	LCD_gotoxy(n,1);
	n=H44780_ROWS-1;
	while  ( n ) {
		LCD_putc (0x20);
		n--;
	}
}
