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
