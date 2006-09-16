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
  *  $Id$
  */

#ifndef H44780_H
 #include "H44780.h"
#endif

#include <stdlib.h>
#include <avr/io.h>
#include <stdint.h>


void LCD_sendCommand (uint8_t command)
{
        _H44780_DATA_PORT_ = command;
        _H44780_DATA_REG_ = _H44780_DATA_MASK_;

#if H44780_DATA_WIDTH == 4 

  #if H44780_PORT_IS_LSB  == 1
        _H44780_DATA_PORT_ = _H44780_DATA_PORT_ >> 4;
        LCD_enable_us(200);
        LCD_wait_ms(2);
        _H44780_DATA_PORT_ = command;
  #else
        LCD_enable_us(200);
        LCD_wait_ms(2);
        _H44780_DATA_PORT_ = _H44780_DATA_PORT_ << 4;
  #endif

#endif
        LCD_enable_us(200);
        LCD_wait_ms(2);
        _H44780_DATA_PORT_ = 0x00;

}
