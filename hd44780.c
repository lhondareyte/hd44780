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
  *  $Id: H44780.c,v 0.6 2006/08/31 19:20:32 luc Exp luc $
  */

// Configuration de l'afficheur

#define H44780_DISPLAY_TYPE     5
#define H44780_DATA_PORT        __PORTB__
#define H44780_CLOCK_PORT       __PORTD__
#define H44780_CLOCK_PIN        2
#define H44780_DATA_WIDTH       4
#define H44780_RS_PORT          __PORTD__
#define H44780_RS_PIN           3

#include "H44780.h"


//static uint8_t lines, rows;

void LCD_sendCommand (uint8_t command)
{
#if H44780_DATA_WIDTH == 8 

        _H44780_DATA_REG_ = 0xFF;
        _H44780_DATA_PORT_ = command;
        LCD_enable_us(400);
        LCD_wait_ms(2);

#else 
        _H44780_DATA_REG_ = 0xF0;
        _H44780_DATA_PORT_ = command;
        LCD_enable_us(500);
        LCD_wait_ms(2);
        _H44780_DATA_PORT_ = _H44780_DATA_PORT_ << 4;
        LCD_enable_us(500);
        LCD_wait_ms(2);

#endif
        _H44780_DATA_PORT_ = 0x00;

}

void
LCD_sendText (uint8_t character)
{
  setBIT (_H44780_RS_PORT_, H44780_RS_PIN);
  LCD_sendCommand (character);
  clearBIT (_H44780_RS_PORT_, H44780_RS_PIN);
}


void
LCD_init (uint8_t mode)
{

#if H44780_DATA_WIDTH == 8
  _H44780_DATA_REG_ = 0xFF;
#else  
  _H44780_DATA_REG_ = 0xF0;
#endif
  setBIT (_H44780_CLOCK_REG_, H44780_CLOCK_PIN);
  setBIT (_H44780_RS_REG_, H44780_RS_PIN);
  _H44780_DATA_PORT_ = 0x00;
  _delay_ms (15);
  _H44780_DATA_PORT_ = 0x30;
  LCD_enable_ms(5);
  LCD_enable_us(150);
  LCD_sendCommand(mode);
  LCD_enable_us(500);
  LCD_sendCommand (H44780_DISPLAY_ON);
  LCD_sendCommand (H44780_CURSOR_HOME);
  LCD_sendCommand (H44780_BLINK_OFF);
  LCD_sendCommand (H44780_CLEAR_DISPLAY);
  _H44780_DATA_PORT_ = 0x00;

}


uint8_t
LCD_printf (char *string)
{
  uint8_t i = 0;
  while (string[i] != '\0')
    {
      switch (string[i])
	{
	case '\n':

	  LCD_sendCommand (0xC0);

	case '\b':
	  LCD_sendCommand (0x10);



	default:

	  LCD_sendText (string[i]);
	}
      i++;
    }
  return 0;
}


int
main (void)
{
#if H44780_DATA_WIDTH == 4
  LCD_init (0x28);
#else
  LCD_init (0x38);
#endif
  LCD_printf ("Bonjour, Monde\n");
  LCD_printf ("Comment va?");
  return 0;
}

//
