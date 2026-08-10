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

void LCD_puts_pgm (char * buf, PGM_P const *t, uint8_t index) {
	strcpy_P(buf, (PGM_P)pgm_read_word(&(t[index])));
	LCD_puts(buf);
}

