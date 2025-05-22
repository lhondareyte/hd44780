#ifndef __HD44780_H__
 #include "hd44780.h"
#endif

void LCD_puts_pgm (uint8_t i, char * buf, PGM_P const *t) {
        strcpy_P(buf, (PGM_P)pgm_read_word(&(t[i])));
        LCD_puts(buf);
}

