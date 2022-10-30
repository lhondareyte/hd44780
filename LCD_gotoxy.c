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

#ifndef __HD44780_H__
 #include "hd44780.h"
#endif

void LCD_gotoxy (uint8_t x, uint8_t y) 
{
	if (x > H44780_LINES || y > H44780_ROWS)
		return;
        uint8_t cur= H44780_DDRAM_L1 - 1;
	if (x == 1) {
		cur += y;
	}
	else if (x == 2) {	
		cur += y;
		cur += H44780_DDRAM_L2;
	}
#if (H44780_LINES >= 3) 
	else if (x == 3) {	
		cur += y;
		cur += H44780_DDRAM_L3;
	}
#endif
#if (H44780_LINES >= 4) 
	else if (x == 4) {	
		cur += y;
		cur += H44780_DDRAM_L4;
	}
#endif
	LCD_ioctl(cur);
	LCD_wait();
}
