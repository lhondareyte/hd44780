/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2006-2022 Luc Hondareyte
 *
 */

#ifndef __HD44780_H__
 #include "hd44780.h"
#endif

void LCD_putc (char c)
{
	char t;
#ifdef H44780_4BITS_MODE
	t = c >> 4;
	_H44780_ENABLE_PORT_ &= ~(1<< H44780_ENABLE_PIN);
	WriteNibble(_H44780_DATA_PORT_, t);
	_H44780_RS_PORT_ |= (1<< H44780_RS_PIN);
        LCD_validate();
	_H44780_ENABLE_PORT_ &= ~(1<< H44780_ENABLE_PIN);
	c &= 0x0f;
	WriteNibble(_H44780_DATA_PORT_, c);
	_H44780_RS_PORT_ |= (1<< H44780_RS_PIN);
        LCD_validate();
#else
	_H44780_RS_PORT_ |= (1<< H44780_RS_PIN);
        _H44780_DATA_PORT_ = t;
        LCD_validate();
#endif
	LCD_wait();
}
