/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c)2006-2022 Luc Hondareyte
 *
 */

#ifndef __HD44780_H__
#include "hd44780.h"
#endif

void LCD_nputs (const char *s, uint8_t n, uint8_t idx)
{
	register char c;
	s+=idx;
	while (n) {
		n--;
		c = *s++;
		LCD_putc (c);
	}
}

