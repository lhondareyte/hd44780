/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c)2026 Luc Hondareyte
 *
 */
#ifndef __HD44780_H__
#include "hd44780.h"
#endif

void LCD_nputs_pgm(char *buf, size_t len, PGM_P const *t, uint8_t index)
{
    strncpy_P(buf, (PGM_P)pgm_read_word(&(t[index])), len);
    if (len > 0) {
        buf[len - 1] = '\0';
    }
    LCD_puts(buf);
}
