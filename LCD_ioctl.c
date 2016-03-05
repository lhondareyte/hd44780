 /*
  * Copyright (c) 2006-2012 Luc HONDAREYTE
  * All rights reserved.
  *
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
