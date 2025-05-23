/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c)2006-2023 Luc Hondareyte
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
	/* Set 4bits mode */
	WriteNibble(_H44780_DATA_PORT_, 0x02);
        _H44780_ENABLE_PORT_ &= ~(1<< H44780_ENABLE_PIN);
        _H44780_RS_PORT_ &= ~(1<< H44780_RS_PIN);

	LCD_validate();
	LCD_validate();

	/* Set lines number  */
	WriteNibble(_H44780_DATA_PORT_, 8);
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
