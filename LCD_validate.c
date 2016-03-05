 /*
  * Copyright (c) 2006-2012 Luc HONDAREYTE
  * All rights reserved.
  *
  *  $Id: LCD_puts.c,v 0.9 2006/09/16 15:03:34 luc Exp luc $
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
