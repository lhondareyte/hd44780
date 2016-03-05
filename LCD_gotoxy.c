 /*
  * Copyright (c) 2006-2012 Luc HONDAREYTE
  * All rights reserved.
  *
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
	LCD_wait();
	LCD_wait();
}
