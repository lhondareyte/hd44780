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

void LCD_puts_eeprom(const uint8_t *p)
{
	uint8_t c;
	do {
		c = eeprom_read_byte(p);
		LCD_putc(c);
		p++;
	} while (c != '\0');
}
