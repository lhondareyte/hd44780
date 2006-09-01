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
  *  $Id: H44780.h,v 0.8 2006/09/01 10:13:05 luc Exp luc $
  */
#ifndef H44780_H
#define H44780_H

#undef __PORTA__
#define         __PORTA__       0x00
#undef __PORTB__
#define         __PORTB__       0x01
#undef __PORTC__
#define         __PORTC__       0x02
#undef __PORTD__
#define         __PORTD__       0x03


#undef setBIT
#define setBIT(byte,bit)	( byte |= (1<<bit))
#undef clearBIT
#define clearBIT(byte,bit)	( byte &= ~(1<<bit))

#include <stdlib.h>
#include <avr/io.h>
#include <stdint.h>

#if !defined (F_CPU)
#define F_CPU   10000000
#endif
#include <util/delay.h>


/*
 *  Default values
 */

#if !defined (H44780_DISPLAY_TYPE)
        #warning "H44780_DISPLAY_TYPE is not defined"
        #define H44780_DISPLAY_TYPE     5
#endif

#if !defined (H44780_DATA_PORT)
        #warning "H44780_DATA_PORT is not defined"
        #define H44780_DATA_PORT    B

#endif

#if H44780_DATA_PORT == __PORTB__
        #define _H44780_DATA_PORT_    PORTB
        #define _H44780_DATA_REG_     DDRB

#elif H44780_DATA_PORT == __PORTD__
        #define _H44780_DATA_PORT_    PORTD
        #define _H44780_DATA_REG_     DDRD

#elif H44780_DATA_PORT == __PORTC__
        #define _H44780_DATA_PORT_    PORTC
        #define _H44780_DATA_REG_     DDRC

#elif H44780_DATA_PORT == __PORTA__
        #define _H44780_DATA_PORT_    PORTA
        #define _H44780_DATA_REG_     DDRA
#endif

#define H44780_BUSY_FLAG        7	

#if !defined(H44780_CLOCK_PORT)
        #warning "H44780_CLOCK_PORT is not defined"
        #define _H44780_CLOCK_PORT_    D
        #define _H44780_CLOCK_REG_     D
        #define H44780_CLOCK_PIN       2
#endif

#if   H44780_CLOCK_PORT == __PORTB__
        #define _H44780_CLOCK_PORT_    PORTB
        #define _H44780_CLOCK_REG_     DDRB
        
#elif H44780_CLOCK_PORT == __PORTD__
        #define _H44780_CLOCK_PORT_    PORTD
        #define _H44780_CLOCK_REG_     DDRD
        
#elif H44780_CLOCK_PORT == __PORTC__
        #define _H44780_CLOCK_PORT_    PORTC
        #define _H44780_CLOCK_REG_     DDRC
        
#elif H44780_CLOCK_PORT == __PORTA__
        #define _H44780_CLOCK_PORT_    PORTA
        #define _H44780_CLOCK_REG_     DDRA
#endif

#if !defined (H44780_DATA_WIDTH)
        #warning "H44780_DATA_WIDTH is not defined"
        #define H44780_DATA_WIDTH    8
#endif

#if !defined (H44780_RS_PORT)
        #warning "H44780_RS_PORT is not defined"
        #define _H44780_RS_PORT_       D
        #define _H44780_RS_REG_        D
        #define H44780_RS_PIN          3
#endif

#if   H44780_RS_PORT == __PORTB__
        #warning error
        #define _H44780_RS_PORT_    PORTB
        #define _H44780_RS_REG_     DDRB
        
#elif H44780_RS_PORT == __PORTD__
        #define _H44780_RS_PORT_    PORTD
        #define _H44780_RS_REG_     DDRD
        
#elif H44780_RS_PORT == __PORTC__
        #define _H44780_RS_PORT_    PORTC
        #define _H44780_RS_REG_     DDRC
        
#elif H44780_RS_PORT == __PORTA__
        #define _H44780_RS_PORT_    PORTA
        #define _H44780_RS_REG_     DDRA
#endif

#if !defined (H44780_RW_PORT) && defined (H44780_RW_PORT_PRESENT)
        #warning "H44780_RW_PORT is present but not defined"
        #define H44780_RW_PORT       4
#endif

#if defined (H44780_RW_PORT_PRESENT)
#if   H44780_RW_PORT == __PORTB__
        #warning error
        #define _H44780_RW_PORT_    PORTB
        #define _H44780_RW_REG_     DDRB
        
#elif H44780_RW_PORT == __PORTD__
        #define _H44780_RW_PORT_    PORTD
        #define _H44780_RW_REG_     DDRD
        
#elif H44780_RW_PORT == __PORTC__
        #define _H44780_RW_PORT_    PORTC
        #define _H44780_RW_REG_     DDRC
        
#elif H44780_RW_PORT == __PORTA__
        #define _H44780_RW_PORT_    PORTA
        #define _H44780_RW_REG_     DDRA
#endif

#endif
/*
 *  Display types
 */
#if !defined (H44780_DISPLAY_TYPE)
        #warning "H44780_DISPLAY_TYPE is not defined"
        #define H44780_DISPLAY_TYPE       4
#endif

#if   H44780_DISPLAY_TYPE == 1
        #define H44780_ROWS     5
        #define H44780_LINES    2

        
#elif H44780_DISPLAY_TYPE == 2
        #define H44780_ROWS     8
        #define H44780_LINES    1
        
#elif H44780_DISPLAY_TYPE == 3
        #define H44780_ROWS     8
        #define H44780_LINES    2
        
#elif H44780_DISPLAY_TYPE == 4
        #define H44780_ROWS     16
        #define H44780_LINES    1
        
#elif H44780_DISPLAY_TYPE == 5
        #define H44780_ROWS     16
        #define H44780_LINES    2
        
#elif H44780_DISPLAY_TYPE == 6
        #define H44780_ROWS     16
        #define H44780_LINES    4
        
#elif H44780_DISPLAY_TYPE == 7
        #define H44780_ROWS     20
        #define H44780_LINES    2
        
#elif H44780_DISPLAY_TYPE == 8
        #define H44780_ROWS     20
        #define H44780_LINES    4
        
#elif H44780_DISPLAY_TYPE == 9
        #define H44780_ROWS     40
        #define H44780_LINES    2
#endif

#if H44780_LINES <= 1
        #define _H44780_LINES_          0x00
#else
        #define _H44780_LINES_          0x08
#endif

/*
 * Prototypes
 */
uint8_t LCD_puts (char *);
void LCD_init (void);
void LCD_sendCommand (uint8_t);
void LCD_sendText (uint8_t);
void LCD_gotoxy(uint8_t,uint8_t);

/*
 *  Macros
 */

#define LCD_clear()             LCD_sendCommand(H44780_CLEAR_DISPLAY)
#define LCD_blinkOn()           LCD_sendCommand(H44780_BLINK_ON)
#define LCD_blinkOff()          LCD_sendCommand(H44780_BLINK_OFF)
#define LCD_cursorOn()          LCD_sendCommand(H44780_CURSOR_ON)
#define LCD_cursorOff()         LCD_sendCommand(H44780_CURSOR_OFF)

#if defined (H44780_RW_PORT_PRESENT)
 #define LCD_wait_us(delay)     setBIT(_H44780_RW_REG_, _H44780_RW_PIN); \
                                loop_until_bit_is_clear(_H44780_DATA_PORT_,H44780_BUSY_FLAG); \
                                clearBIT(_H44780_RW_REG_, _H44780_RW_PIN)
#else
 #define LCD_wait_us(delay)     _delay_us(delay)
#endif
#if defined (H44780_RW_PORT_PRESENT)
 #define LCD_wait_ms(delay)     setBIT(_H44780_RW_REG_, _H44780_RW_PIN); \
                                loop_until_bit_is_clear(_H44780_DATA_PORT_,H44780_BUSY_FLAG); \
                                clearBIT(_H44780_RW_REG_, H44780_RW_PIN)
#else
 #define LCD_wait_ms(delay)     _delay_ms(delay)
#endif

#if defined (H44780_RW_PORT_PRESENT)
 #define LCD_enable_ms(delay)   setBIT (_H44780_CLOCK_PORT_, H44780_CLOCK_PIN); LCD_wait(); \
                                clearBIT(_H44780_CLOCK_PORT_, H44780_CLOCK_PIN)
#else             
 #define LCD_enable_ms(delay)   setBIT (_H44780_CLOCK_PORT_, H44780_CLOCK_PIN); _delay_ms (delay); \
                                clearBIT(_H44780_CLOCK_PORT_, H44780_CLOCK_PIN)
#endif

#if defined (H44780_RW_PORT_PRESENT)
 #define LCD_enable_us(delay)   setBIT (_H44780_CLOCK_PORT_, H44780_CLOCK_PIN); LCD_wait(); \
                                clearBIT(_H44780_CLOCK_PORT_, H44780_CLOCK_PIN);
#else             
 #define LCD_enable_us(delay)   setBIT (_H44780_CLOCK_PORT_, H44780_CLOCK_PIN); _delay_us (delay); \
                                clearBIT(_H44780_CLOCK_PORT_, H44780_CLOCK_PIN)
#endif
/*
 * H44780 command codes
 */

#define H44780_CLEAR_DISPLAY    0x01
#define H44780_CURSOR_HOME      0x02

#define H44780_DISPLAY_OFF      0x08
#define H44780_DISPLAY_ON       0x0C

#define H44780_BLINK_ON         0x0F
#define H44780_BLINK_OFF        0x0C

#define H44780_CURSOR_ON        0x0E
#define H44780_CURSOR_OFF       0x0C


#endif   //     H44780_H

//
