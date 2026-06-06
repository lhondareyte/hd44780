/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c)2006-2026 Luc Hondareyte
 *
 */

#ifndef __HD44780_H__
#define __HD44780_H__

#ifdef __AVR__
#include "avr.h"
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

#elif  ( H44780_DISPLAY_TYPE == 32 )  /* 8x2 charaters on single line */
#define H44780_ROWS      16           // i.e Vishay LCD-1601
#define H44780_LINES     1
#define H44780_DDRAM_L1  0x80
#define H44780_DDRAM_L2  0xC0

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

#ifndef H44780_BUSY_FLAG 
#define H44780_BUSY_FLAG 7
#endif

/*
 * H44780 command codes
 */

#define H44780_CLEAR_DISPLAY    0x01	/* clear screen */
#define H44780_CURSOR_HOME      0x02	/* Return home */
#define H44780_CURSOR_RIGHT     0x06	/* Right shift cursor */

#define H44780_DISPLAY_OFF      0x08	/* Display On/Off */
#define H44780_DISPLAY_ON       0x08	
#define H44780_DISPLAY_SHIFT    0x18	/* Display or cursor shift */
#define H44780_CURSOR_OFF       0x0C    /* Cursor off */
#define H44780_CURSOR_ON        0x0E    /* Steady cursor */
#define H44780_BLINK_ON         0x0F    /* Blinking cursor */

/* Prototypes */
void LCD_init (void);			/* Call it first  */
void LCD_ioctl (uint8_t);		/* Send command to LCD */
void LCD_putc (char);			/* Send char to LCD */
void LCD_puts (const char *);		/* Send string to LCD */
void LCD_gotoxy(uint8_t,uint8_t);	/* Set cursor position */
void LCD_clrline(uint8_t);		/* Clear current line */
void LCD_validate(void);		/* Command validate */
void LCD_wait(void);			/* Internal delays */
void LCD_nputs(const char *, uint8_t, uint8_t);
void LCD_puts_pgm(uint8_t, char *, PGM_P const *);

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

#ifdef H44780_4BITS_MODE
#ifdef H44780_DATA_IS_LSB
#define WriteNibble(p,n)	p=(p & 0xf0) | ( n & 0xf)
#else
#define WriteNibble(p,n)	p=(p & 0x0f) | ((n & 0xf) << 4)
#endif
#endif

#endif   /* __HD44780_H__ */

