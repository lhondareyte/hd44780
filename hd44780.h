/* 
 *   Copyright (c)2006-2021,  Luc Hondareyte
 *   All rights reserved.
 *     
 *   Redistribution and use in source and binary forms, with or without 
 *   modification, are permitted provided that the following conditions 
 *   are met:
 *  
 *   1. Redistributions of source code must retain the above copyright 
 *      notice, this list of conditions and the following disclaimer.
 *  
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 *   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 *   OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 *   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 *   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 *   SUCH DAMAGE.
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
#define H44780_CURSOR_RIGHT     0x06	/* Deplacement du curseur vers la droite */

#define H44780_DISPLAY_OFF      0x08	/* Display On/Off */
#define H44780_DISPLAY_ON       0x08	
#define H44780_DISPLAY_SHIFT    0x18	/* Display or cursor shift */
#define H44780_CURSOR_OFF       0x0C    /* Display on, crusor off */
#define H44780_CURSOR_ON        0x0E    /* Display on, steady cursor */
#define H44780_BLINK_ON         0x0F    /* Display on, blinking cursor */

#define LINE_1		        0x80	/* Adresse 1er caractère de la ligne 1 */
#define LINE_2			0xC0	/* Adresse 1er caractère de la ligne 2 */
#define LINE_3			0x94	/* Adresse 1er caractère de la ligne 3 */
#define LINE_4      		0xB6	/* Adresse 1er caractère de la ligne 4 */

#if defined (__BLINK_SUPPORT__)

/* Bit field for blink attribut */
struct {
	uint refresh : 1 ;
	uint [attribut] : H44780_ROWS * H44780_LINES;
} display;

#endif // __BLINK_SUPPORT__

/* Prototypes */
void LCD_init (void);			/* Initialisation du LCD */
void LCD_ioctl (uint8_t);		/* Envoi d'une commande vers le LCD */
void LCD_putc (char);			/* Envoi d'un caractère vers le LCD */
void LCD_puts (const char *);		/* Affichage d'un caractère */
void LCD_gotoxy(uint8_t,uint8_t);	/* Positionne le curseur en x,y */
void LCD_clrline(uint8_t);		/* Efface la ligne n */
void LCD_validate(void);		/* valide une commande */
void LCD_wait(void);			/* Gestion des delais */
void LCD_nputs(const char *, uint8_t, uint8_t);
void LCD_refresh(void);

/*
 *  Macros
 */

#define LCD_clrscr()            LCD_ioctl(H44780_CLEAR_DISPLAY)
#define LCD_blinkCursor()       LCD_ioctl(H44780_BLINK_ON)
#define LCD_fixCursor()         LCD_ioctl(H44780_BLINK_OFF)
#define LCD_cursorOn()          LCD_ioctl(H44780_CURSOR_ON)
#define LCD_cursorOff()         LCD_ioctl(H44780_CURSOR_OFF)
#define LCD_gotoLine(x)         LCD_ioctl(x)
#define LCD_DisplayOn()         LCD_ioctl(H44780_DISPLAY_ON)
#define LCD_DisplayOff()        LCD_ioctl(H44780_DISPLAY_OFF)


#if ( H44780_DATA_WIDTH == 4 )
#if H44780_PORT_IS_LSB == 1
#define WriteNibble(p,n)	p=(p & 0xf0) | ( n & 0xf)
#endif
#if H44780_PORT_IS_LSB == 0
#define WriteNibble(p,n)	p=(p & 0x0f) | ((n & 0xf) << 4)
#endif
#else
#endif

#endif   //     __HD44780_H__
