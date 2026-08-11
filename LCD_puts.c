/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c)2006-2026 Luc Hondareyte
 *
 */

#ifndef __HD44780_H__
#include "hd44780.h"
#endif

void LCD_puts (const char *s)
{
	register char c;
	while ((c = *s++)) {
		LCD_putc(c);
	}
}
