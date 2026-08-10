/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c)2026 Luc Hondareyte
 *
 */
#ifndef __HD44780_H__
#include "hd44780.h"
#endif
#include <avr/eeprom.h>

extern Cursor cursor;

void LCD_nputs_eeprom(const uint8_t *p, size_t len)
{
#if defined H44780_QUIRK
	LCD_ioctl(H44780_SET_DDRAM_ADDR);
#endif
	uint8_t c;
	size_t i = 0;

	while (i < len && (c = eeprom_read_byte(p)) != '\0') {
		LCD_putc(c);
		p++;
		i++;
	}
}
