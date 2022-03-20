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
#define __HD44780_H__

#include <stdlib.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

/*
 * default value:
 * 2x16 character connected to PORTB in 4bits mode
 * RS connected to PIND2
 * ENABLE connected to PIND3 
 */

#ifndef H44780_DISPLAY_TYPE
#warning LCD Type is not set
#define H44780_DISPLAY_TYPE     5			/* 2x16 DISPLAY */
#endif

#ifndef H44780_DATA_PORT
#define H44780_DATA_PORT        _H44780_PORTB_ 	/* Connexion sur PORTB */
#endif

#ifndef H44780_ENABLE_PORT
#define H44780_ENABLE_PORT       _H44780_PORTB_	/* ENABLE on  PORTD */
#endif

#ifndef H44780_ENABLE_PIN
#define H44780_ENABLE_PIN        5			/* ENABLE to PIND2 */
#endif

#ifndef H44780_RS_PORT
#define H44780_RS_PORT          _H44780_PORTB_	/* RS on PORTD */
#endif

#ifndef H44780_RS_PIN
#define H44780_RS_PIN           4			/* RS to PIND3 */
#endif	

#ifndef H44780_DATA_WIDTH
#define H44780_DATA_WIDTH       4			/* 4bits mode */
#endif

#define _H44780_PORTA_		0x01
#define _H44780_PORTB_		0x02
#define _H44780_PORTC_		0x03
#define _H44780_PORTD_		0x04
#define _H44780_PORTE_		0x05

/*
 *  DATA pinout
 */

#if   ( H44780_DATA_PORT == _H44780_PORTA_ )
#define _H44780_DATA_PORT_    PORTA
#define _H44780_DATA_REG_     DDRA

#elif ( H44780_DATA_PORT == _H44780_PORTB_ )
#define _H44780_DATA_PORT_    PORTB
#define _H44780_DATA_REG_     DDRB

#elif ( H44780_DATA_PORT == _H44780_PORTD_ )
#define _H44780_DATA_PORT_    PORTD
#define _H44780_DATA_REG_     DDRD

#elif ( H44780_DATA_PORT == _H44780_PORTC_ )
#define _H44780_DATA_PORT_    PORTC
#define _H44780_DATA_REG_     DDRC

#elif ( H44780_DATA_PORT == _H44780_PORTE_ )
#define _H44780_DATA_PORT_    PORTE
#define _H44780_DATA_REG_     DDRE
#endif

/*
 * ENABLE pinout
 */

#if   ( H44780_ENABLE_PORT == _H44780_PORTA_ )
#define _H44780_ENABLE_PORT_    PORTA
#define _H44780_ENABLE_REG_     DDRA

#elif ( H44780_ENABLE_PORT == _H44780_PORTB_ )
#define _H44780_ENABLE_PORT_    PORTB
#define _H44780_ENABLE_REG_     DDRB

#elif ( H44780_ENABLE_PORT == _H44780_PORTC_ )
#define _H44780_ENABLE_PORT_    PORTC
#define _H44780_ENABLE_REG_     DDRC

#elif ( H44780_ENABLE_PORT == _H44780_PORTD_ )
#define _H44780_ENABLE_PORT_    PORTD
#define _H44780_ENABLE_REG_     DDRD

#elif ( H44780_ENABLE_PORT == _H44780_PORTE_ )
#define _H44780_ENABLE_PORT_    PORTE
#define _H44780_ENABLE_REG_     DDRE
#endif

/*
 * RS pinout
 */

#if   ( H44780_RS_PORT == _H44780_PORTA_ )
#define _H44780_RS_PORT_    PORTA
#define _H44780_RS_REG_     DDRA

#elif ( H44780_RS_PORT == _H44780_PORTB_ )
#define _H44780_RS_PORT_    PORTB
#define _H44780_RS_REG_     DDRB

#elif ( H44780_RS_PORT == _H44780_PORTC_ )
#define _H44780_RS_PORT_    PORTC
#define _H44780_RS_REG_     DDRC

#elif ( H44780_RS_PORT == _H44780_PORTD_ )
#define _H44780_RS_PORT_    PORTD
#define _H44780_RS_REG_     DDRD

#elif ( H44780_RS_PORT == _H44780_PORTE_ )
#define _H44780_RS_PORT_    PORTE
#define _H44780_RS_REG_     DDRE
#endif

#if ! defined ( H44780_RW_PORT ) && defined ( H44780_RW_PORT_PRESENT )
#warning "H44780_RW_PORT is connect but not defined"
#define H44780_RW_PORT       4
#endif

#ifdef H44780_RW_PORT_PRESENT
#if   ( H44780_RW_PORT == _H44780_PORTA_ )
#define _H44780_RW_PORT_    PORTA
#define _H44780_RW_REG_     DDRA

#elif ( H44780_RW_PORT == _H44780_PORTB_ )
#define _H44780_RW_PORT_    PORTB
#define _H44780_RW_REG_     DDRB

#elif ( H44780_RW_PORT == _H44780_PORTC_ )
#define _H44780_RW_PORT_    PORTC
#define _H44780_RW_REG_     DDRC

#elif ( H44780_RW_PORT == _H44780_PORTD_ )
#define _H44780_RW_PORT_    PORTD
#define _H44780_RW_REG_     DDRD

#elif ( H44780_RW_PORT == _H44780_PORTE_ )
#define _H44780_RW_PORT_    PORTE
#define _H44780_RW_REG_     DDRE
#endif
#endif

/*
 *  Models types
 */
#if    ( H44780_DISPLAY_TYPE == 1 )   /* 5x2 characters */
#define H44780_ROWS      5
#define H44780_LINES     2
#define H44780_DDRAM_L1  0x80
#define H44780_DDRAM_L2  0x40

#elif  ( H44780_DISPLAY_TYPE == 2 )   /* 8x1 characters */
#define H44780_ROWS      8
#define H44780_LINES     1
#define H44780_DDRAM_L1  0x80

#elif  ( H44780_DISPLAY_TYPE == 3 )   /* 8x2 characters */
#define H44780_ROWS      8
#define H44780_LINES     2
#define H44780_DDRAM_L1  0x80
#define H44780_DDRAM_L2  0x40

#elif  ( H44780_DISPLAY_TYPE == 4 )   /* 16x1 characters */
#define H44780_ROWS      16
#define H44780_LINES     1
#define H44780_DDRAM_L1  0x80

#elif  ( H44780_DISPLAY_TYPE == 5 )   /* 16x2 characters */
#define H44780_ROWS      16
#define H44780_LINES     2
#define H44780_DDRAM_L1  0x80
#define H44780_DDRAM_L2  0x40

#elif  ( H44780_DISPLAY_TYPE == 6 )   /* 16x4 characters */
#define H44780_ROWS      16
#define H44780_LINES     4
#define H44780_DDRAM_L1  0x80
#define H44780_DDRAM_L2  0x40
#define H44780_DDRAM_L3  0x80
#define H44780_DDRAM_L4  0x40

#elif  ( H44780_DISPLAY_TYPE == 7 )   /* 20x2 characters */
#define H44780_ROWS      20
#define H44780_LINES     2
#define H44780_DDRAM_L1  0x80
#define H44780_DDRAM_L2  0x40

#elif  ( H44780_DISPLAY_TYPE == 8 )   /* 20x4 characters */
#define H44780_ROWS      20
#define H44780_LINES     4
#define H44780_DDRAM_L1  0x80
#define H44780_DDRAM_L2  0x40
#define H44780_DDRAM_L3  0x80
#define H44780_DDRAM_L4  0x40

#elif  ( H44780_DISPLAY_TYPE == 9 )   /* 40x2 characters */
#define H44780_ROWS      40
#define H44780_LINES     2
#define H44780_DDRAM_L1  0x80
#define H44780_DDRAM_L2  0x40

#elif  ( H44780_DISPLAY_TYPE == 10 )   /* 24x2 characters */
#define H44780_ROWS      24
#define H44780_LINES     2
#define H44780_DDRAM_L1  0x80
#define H44780_DDRAM_L2  0x40
#endif

#if   (H44780_LINES == 1) 
#define H44780_LINES_ARG 0
#elif (H44780_LINES == 2)
#define H44780_LINES_ARG 8
#endif

#define H44780_BUSY_FLAG 7

/*
 * H44780 command codes
 */

#define H44780_CLEAR_DISPLAY    0x01	/* clear screen */
#define H44780_CURSOR_HOME      0x02	/* Return home */
#define H44780_CURSOR_RIGHT     0x06	/* Right shift cursor */

#define H44780_DISPLAY_OFF      0x08	/* Display On/Off */
#define H44780_DISPLAY_ON       0x08	
#define H44780_DISPLAY_SHIFT    0x18	/* Display or cursor shift */
#define H44780_CURSOR_OFF       0x0C    /* Display on, cursor off */
#define H44780_CURSOR_ON        0x0E    /* Display on, steady cursor */
#define H44780_BLINK_ON         0x0F    /* Display on, blinking cursor */

#define LINE_1		        0x80	/* first line address  */
#define LINE_2			0xC0	/* etc.               */
#define LINE_3			0x94
#define LINE_4      		0xB6

#if defined (__BLINK_SUPPORT__)

// unfinished

/* Bit field for blink attribut */
struct {
	uint refresh : 1 ;
	uint [attribut] : H44780_ROWS * H44780_LINES;
} display;

#endif // __BLINK_SUPPORT__

/* Prototypes */
void LCD_init (void);			/* Call it first  */
void LCD_ioctl (uint8_t);		/* Send command to LCD */
void LCD_putc (char);			/* Send char to LCD */
void LCD_puts (const char *);		/* Send string to LCD */
void LCD_gotoxy(uint8_t,uint8_t);	/* Set cursor position */
void LCD_clrline(uint8_t);		/* Clear current line */
void LCD_validate(void);		/* Command validate */
void LCD_wait(void);			/* Internal delays */
void LCD_nputs(const char *, uint8_t);

#if defined (__BLINK_SUPPORT__)
void LCD_refresh(void);
#endif

//  Macros
#define LCD_clrscr()            LCD_ioctl(H44780_CLEAR_DISPLAY)
#define LCD_blinkCursor()       LCD_ioctl(H44780_BLINK_ON)
#define LCD_fixCursor()         LCD_ioctl(H44780_CURSOR_ON)
#define LCD_cursorOn()          LCD_ioctl(H44780_CURSOR_ON)
#define LCD_cursorOff()         LCD_ioctl(H44780_CURSOR_OFF)
#define LCD_gotoLine(x)         LCD_ioctl(x)
#define LCD_DisplayOn()         LCD_ioctl(H44780_DISPLAY_ON)
#define LCD_DisplayOff()        LCD_ioctl(H44780_DISPLAY_OFF)
#define LCD_wait()        	_delay_ms(1)

#if ( H44780_DATA_WIDTH == 4 )
#if H44780_PORT_IS_LSB == 1
#define WriteNibble(p,n)	p=(p & 0xf0) | ( n & 0xf)
#endif
#if H44780_PORT_IS_LSB == 0
#define WriteNibble(p,n)	p=(p & 0x0f) | ((n & 0xf) << 4)
#endif
#endif

#endif   //     __HD44780_H__
