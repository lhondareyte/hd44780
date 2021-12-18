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

#ifndef __HD44780_H__
 #include "hd44780.h"
#endif

void LCD_validate (void)
{
#ifdef H44780_RW_PORT_ENABLE
	_H44780_RW_REG_ &= ~(1<<H44780_RW_PIN);
	loop_until_bit_is_clear(_H44780_DATA_PORT_,H44780_BUSY_FLAG);
	_H44780_RW_REG_ |= (1<< H44780_RW_PIN);
#else
	_H44780_ENABLE_PORT_ |= (1<<H44780_ENABLE_PIN); 
	_delay_us(50);
	_H44780_ENABLE_PORT_ &= ~(1<<H44780_ENABLE_PIN);
	LCD_wait();
#endif
}
