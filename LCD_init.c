/* 
 *   Copyright (c)2006-2017,  Luc Hondareyte
 *   All rights reserved.
 *     
 *   Redistribution and use in source and binary forms, with or without 
 *   modification, are permitted provided that the following conditions 
 *   are met:
 *  
 *   1. Redistributions of source code must retain the above copyright 
 *      notice, this list of conditions and the following disclaimer.
 *  
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 *   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 *   OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 *   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 *   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 *   SUCH DAMAGE.
 */

#include "hd44780.h"

void LCD_init (void)
{

	/* Initialisaion des ports */
	
	#if H44780_DATA_WIDTH == 8
        _H44780_DATA_REG_ =  0xff ;

	#else
 	  #if H44780_PORT_IS_LSB == 1
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

#if ( H44780_DATA_WIDTH == 8 )
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
