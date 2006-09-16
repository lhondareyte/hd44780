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

void LCD_gotoxy (uint8_t x, uint8_t y) 
{
        uint8_t code;

        if ( y <= H44780_ROWS )
           code = 0x80 -1 + y;
        else code = 0x7F + H44780_ROWS;
        
        if (x == 1) {
           // do nothing
        }
        
#if H44780_LINES >= 2                   
        else if (x == 2) {
         code = code + 0x40;
        }                 

 #if H44780_LINES >= 3  
        else if (x == 3) { 
         code = code + H44780_ROWS; 
        }
        else if (x == 4) {
         code = code + H44780_ROWS + 0x40; 
        }                 
 #endif    
#endif             
        else  code = H44780_CURSOR_HOME;
        LCD_sendCommand(code);
}
