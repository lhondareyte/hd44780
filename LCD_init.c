 /*
  * Copyright (c) 2006 Luc HONDAREYTE
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted provided that the following conditions
  * are met:
  * 1. Redistributions of source code must retain the above copyright
  *    notice, this list of conditions and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
  * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
  * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  *  $Id: LCD_init.c,v 0.9 2006/09/16 15:03:30 luc Exp luc $
  */

#ifndef H44780_H
 #include "H44780.h"
#endif

#include <stdlib.h>
#include <avr/io.h>
#include <stdint.h>

void LCD_init (void)
{

        _H44780_DATA_REG_ = _H44780_DATA_MASK_;
        _H44780_CLOCK_REG_ |= (1<< H44780_CLOCK_PIN);
 	_H44780_RS_REG_ |= (1<< H44780_RS_PIN);
        _H44780_DATA_PORT_ = 0x00;
        _delay_ms (15);
        
#if H44780_PORT_IS_LSB  == 1 
 
        _H44780_DATA_PORT_ = 0x03;
 #else
        _H44780_DATA_PORT_ = 0x30;
 
#endif
        LCD_enable_ms(5);
        LCD_enable_us(150);

#if H44780_DATA_WIDTH == 8

        LCD_sendCommand( 0x30 + H44780_LINES_OFFSET );
 #else
        LCD_sendCommand( 0x20 + H44780_LINES_OFFSET );

#endif
        LCD_enable_us(400);
        LCD_sendCommand (H44780_DISPLAY_ON);
        LCD_sendCommand (H44780_CURSOR_HOME);
        LCD_sendCommand (H44780_BLINK_OFF);
        LCD_sendCommand (H44780_CLEAR_DISPLAY);

}
