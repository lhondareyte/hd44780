/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c)2025 Luc Hondareyte
 *
 */

#ifndef __HD44780_H__
#include "hd44780.h"
#endif


extern Cursor cursor;

void LCD_setchar (const uint8_t *s, uint8_t n)
{
	register char c;
	uint8_t cmd  = H44780_SET_CGRAM_ADDR | n;
	LCD_ioctl(cmd);

	for (uint8_t i = 0; i< 8; i++) {
		c = s[i];
#ifdef H44780_4BITS_MODE
		uint8_t t;
		t = c >> 4;
		_H44780_ENABLE_PORT_ &= ~(1<< H44780_ENABLE_PIN);
		WriteNibble(_H44780_DATA_PORT_, t);
		_H44780_RS_PORT_ |= (1<< H44780_RS_PIN);
		LCD_validate();
		c &= 0x0f;
		_H44780_ENABLE_PORT_ &= ~(1<< H44780_ENABLE_PIN);
		WriteNibble(_H44780_DATA_PORT_, c);
		_H44780_RS_PORT_ |= (1<< H44780_RS_PIN);
		LCD_validate();
#else
		_H44780_RS_PORT_ |= (1<< H44780_RS_PIN);
		_H44780_DATA_PORT_ = c;
		LCD_validate();
#endif
		LCD_wait();
	}
	cursor.row = 1;
	cursor.line = 1;
	LCD_ioctl(H44780_CURSOR_HOME);
}

