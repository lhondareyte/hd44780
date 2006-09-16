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
#include <avr/pgmspace.h> 
void LCD_nputs (char *string, uint16_t index, uint8_t count)
{

  uint16_t i=0;
  while (i < count) 
  {
   LCD_sendText (pgm_read_dword(string+index));
   *string++;
   i++;
  }

}

/*
void LCD_nputs (char *string, uint16_t index, uint8_t count)
{

  uint8_t i = 0;
  count--;
  while (i <= count) {
  switch (string[i])
	{
	case '\n':
	  LCD_sendCommand (0xC0);

	case '\b':
	  LCD_sendCommand (0x10);

	default:
	  LCD_sendText (string[index+i]);
	}
      i++;
    }

}
*/
/*
void LCD_nputs (char *string, uint16_t index, uint8_t count)
{
  uint8_t j=0;
  count--;
  while (j <= count)
   {
    LCD_sendText(string[index+j]);
    j++;
   }

}
*/
