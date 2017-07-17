/* 
 *   Copyright (c)2006-2017,  Luc Hondareyte <lhondareyte_AT_laposte.net>.
 *   All rights reserved.
 *     
 *   Redistribution and use in source and binary forms, with or without 
 *   modification, are permitted provided that the following conditions 
 *   are met:
 *  
 *   1. Redistributions of source code must retain the above copyright 
 *      notice, this list of conditions and the following disclaimer.
 *  
 *   2. redistributions in binary form must reproduce the above copyright 
 *      notice, this list of conditions and the following disclaimer in 
 *      the documentation and/or other materials provided with the distribution.
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
 /*
  * Copyright (c) 2006-2012 Luc HONDAREYTE
  */


#ifndef __HD44780_H__
 #include "hd44780.h"
#endif

void LCD_ioctl (uint8_t c)
{
#if H44780_DATA_WIDTH == 4 
	char t;
	t = c >> 4;
	_H44780_ENABLE_PORT_ &= ~(1<< H44780_ENABLE_PIN);
	WriteNibble(_H44780_DATA_PORT_,t);
	_H44780_RS_PORT_ &= ~(1<< H44780_RS_PIN);
        LCD_validate();
	_H44780_ENABLE_PORT_ &= ~(1<< H44780_ENABLE_PIN);
	c &= 0x0f;
	WriteNibble(_H44780_DATA_PORT_,c);
	_H44780_RS_PORT_ &= ~(1<< H44780_RS_PIN);
        LCD_validate();
#else
	_H44780_RS_PORT_ |= (1<< H44780_RS_PIN);
        _H44780_DATA_PORT_ = t;
        LCD_validate();
#endif
	LCD_wait();
}
