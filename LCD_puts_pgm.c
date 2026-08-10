/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c)2025 Luc Hondareyte
 *
 */
#ifndef __HD44780_H__
#include "hd44780.h"
#endif

void LCD_puts_pgm (char * buf, PGM_P const *t, uint8_t index) {
#if defined H44780_QUIRK
	LCD_ioctl(H44780_SET_DDRAM_ADDR);
#endif
	strcpy_P(buf, (PGM_P)pgm_read_word(&(t[index])));
	LCD_puts(buf);
}

