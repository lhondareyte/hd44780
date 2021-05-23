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

void LCD_gotoxy (uint8_t x, uint8_t y) 
{
	if ( x > H44780_LINES || y > H44780_ROWS ) return;
        uint8_t cur= H44780_DDRAM_L1 - 1;
	if      ( x == 1 ) 
	{
		cur += y;
	}
	else if ( x == 2 ) 
	{	
		cur += y;
		cur += H44780_DDRAM_L2;
	}
#if ( H44780_LINES >= 3 ) 
	else if ( x == 3 ) 
	{	
		cur += y;
		cur += H44780_DDRAM_L3;
	}
#endif
#if ( H44780_LINES >= 4 ) 
	else if ( x == 4 ) 
	{	
		cur += y;
		cur += H44780_DDRAM_L4;
	}
#endif
	LCD_ioctl(cur);
	LCD_wait();
}
