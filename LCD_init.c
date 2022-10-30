/*
 * Copyright (c) 2006-2022 Luc Hondareyte
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "hd44780.h"

void LCD_init (void)
{
	/* Initialisaion des ports */
	
#ifndef H44780_4BITS_MODE
        _H44780_DATA_REG_ =  0xff ;

#else
#ifdef H44780_DATA_IS_LSB
          _H44780_DATA_REG_ |= 0x0f ;
#else
          _H44780_DATA_REG_ |= 0xf0 ;
#endif
#endif

 	_H44780_RS_REG_ |= (1<< H44780_RS_PIN);
        _H44780_ENABLE_REG_ |= (1<< H44780_ENABLE_PIN);

        _delay_ms(42);

	/* Debut d'initialisation HD44780 */
	WriteNibble(_H44780_DATA_PORT_, 0x03);
        _H44780_ENABLE_PORT_ &= ~(1<< H44780_ENABLE_PIN);
        _H44780_RS_PORT_ &= ~(1<< H44780_RS_PIN);

	LCD_validate();

        _delay_ms(4);
	LCD_validate();
	LCD_validate();

#ifdef H44780_8BITS_MODE
        LCD_ioctl( 0x30 + H44780_LINES_ARG );
	LCD_validate();
#else
	/* Envoi du mode 4bits */
	WriteNibble(_H44780_DATA_PORT_, 0x02);
        _H44780_ENABLE_PORT_ &= ~(1<< H44780_ENABLE_PIN);
        _H44780_RS_PORT_ &= ~(1<< H44780_RS_PIN);

	LCD_validate();
	LCD_validate();

	/* Envoi du nb de lignes */
	WriteNibble(_H44780_DATA_PORT_, H44780_LINES_ARG);
        _H44780_ENABLE_PORT_ &= ~(1<< H44780_ENABLE_PIN);
        _H44780_RS_PORT_ &= ~(1<< H44780_RS_PIN);

	LCD_validate();
#endif
        LCD_ioctl (H44780_DISPLAY_OFF);
        LCD_ioctl (H44780_CURSOR_OFF);
        LCD_ioctl (H44780_CLEAR_DISPLAY);
        LCD_ioctl (H44780_CURSOR_RIGHT);
        LCD_ioctl (H44780_CURSOR_HOME);
}
