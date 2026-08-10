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

#if defined H44780_QUIRK  
	uint8_t i = 0;
	LCD_ioctl(H44780_SET_DDRAM_ADDR);
	while ((c = *s++)) {
		LCD_putc (c);
		i++;
		if (i == H44780_ROWS / 2)
			LCD_ioctl(H44780_SET_DDRAM_ADDR | H44780_NEXT_LINE);
	}

#else
	while ((c = *s++)) {
#if (H44780_LINES >= 2)
		if (c == 0x0a)
			LCD_gotoxy(2,1);
		else
#endif
			LCD_putc (c);
	}
#endif
}

