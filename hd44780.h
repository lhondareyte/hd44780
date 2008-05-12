 /*
  * Copyright (c) 2006-2008 Luc HONDAREYTE
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
  *  $Id: H44780.h,v 1.3 2008/05/11 13:07:50 luc Exp luc $
  */

#ifndef H44780_H
 #define H44780_H
  
#include <stdlib.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

/*
 * Definition des valeurs par défaut:
 * Afficheur 2x16 caratères connecté sur PORTB piloté en mode 4bits.
 * Broche RS connectée sur la PIND2
 * Broche CLOCK connectée sur la PIND3
 */
#if !defined ( H44780_DISPLAY_TYPE )
  #define H44780_DISPLAY_TYPE     5			/* Afficheur 2x16 caractères par defaut */
#endif

#if !defined ( H44780_DATA_PORT )
  #define H44780_DATA_PORT        _H44780_PORTB_ 	/* Connexion sur PORTB */
#endif

#if !defined ( H44780_CLOCK_PORT )
  #define H44780_CLOCK_PORT       _H44780_PORTD_	/* CLOCK sur PORTD */
#endif

#if !defined ( H44780_CLOCK_PIN )
  #define H44780_CLOCK_PIN        2			/* CLOCK sur PIND2 */
#endif

#if !defined ( H44780_DATA_WIDTH )
  #define H44780_DATA_WIDTH       4			/* Connexion en 4bits */
#endif

#if !defined ( H44780_RS_PORT )
  #define H44780_RS_PORT          _H44780_PORTD_	/* RS sur PORTD */
#endif

#if !defined ( H44780_RS_PIN )
  #define H44780_RS_PIN           3			/* RS sur PIND3 */
#endif	

/*
 * Le préprocesseur ne sait pas faire de comparaison de chaînes. Il sait seulement 
 * faire des opérations arithmétiques.
 * Ceci explique les définitions ci-dessous:
 */
#define _H44780_PORTA_		1
#define _H44780_PORTB_		2
#define _H44780_PORTC_		3
#define _H44780_PORTD_		4


/*
 *  Port de données - 4 ou 8 bits
 */

#if ( H44780_DATA_WIDTH == 8 )
  #define _H44780_DATA_MASK_    0xFF
#else 
 #if ( H44780_PORT_IS_LSB  == 1 )
  #define _H44780_DATA_MASK_    0x0F
 #else
  #define _H44780_DATA_MASK_    0xF0
 #endif
#endif

#if ( H44780_DATA_PORT == _H44780_PORTB_ )
        #define _H44780_DATA_PORT_    PORTB
        #define _H44780_DATA_REG_     DDRB

#elif ( H44780_DATA_PORT == _H44780_PORTD_ )
        #define _H44780_DATA_PORT_    PORTD
        #define _H44780_DATA_REG_     DDRD

#elif ( H44780_DATA_PORT == _H44780_PORTC_ )
        #define _H44780_DATA_PORT_    PORTC
        #define _H44780_DATA_REG_     DDRC

#elif ( H44780_DATA_PORT == _H44780_PORTA_ )
        #define _H44780_DATA_PORT_    PORTA
        #define _H44780_DATA_REG_     DDRA
#endif

/*
 * Port d'horloge 
 */

#if   ( H44780_CLOCK_PORT == _H44780_PORTA_ )
        #define _H44780_CLOCK_PORT_    PORTA
        #define _H44780_CLOCK_REG_     DDRA
        
#elif ( H44780_CLOCK_PORT == _H44780_PORTB_ )
        #define _H44780_CLOCK_PORT_    PORTB
        #define _H44780_CLOCK_REG_     DDRB
        
#elif ( H44780_CLOCK_PORT == _H44780_PORTC_ )
        #define _H44780_CLOCK_PORT_    PORTC
        #define _H44780_CLOCK_REG_     DDRC
        
#elif ( H44780_CLOCK_PORT == _H44780_PORTD_ )
        #define _H44780_CLOCK_PORT_    PORTD
        #define _H44780_CLOCK_REG_     DDRD
#endif

/*
 * Port d'horloge 
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
#endif

#if !defined ( H44780_RW_PORT ) && defined ( H44780_RW_PORT_PRESENT )
        #warning "H44780_RW_PORT is connect but not defined"
        #define H44780_RW_PORT       4
#endif

#if defined ( H44780_RW_PORT_PRESENT )
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
   #endif
#endif

/*
 *  Display types
 */
#if    ( H44780_DISPLAY_TYPE == 1 )   /* Afficheur 5x2 caractères */
        #define H44780_ROWS     5
        #define H44780_LINES    2
        
#elif  ( H44780_DISPLAY_TYPE == 2 )   /* Afficheur 8x1 caractères */
        #define H44780_ROWS     8
        #define H44780_LINES    1
        
#elif  ( H44780_DISPLAY_TYPE == 3 )   /* Afficheur 8x2 caractères */
        #define H44780_ROWS     8
        #define H44780_LINES    2
        
#elif  ( H44780_DISPLAY_TYPE == 4 )   /* Afficheur 16x1 caractères */
        #define H44780_ROWS     16
        #define H44780_LINES    1
        
#elif  ( H44780_DISPLAY_TYPE == 5 )   /* Afficheur 16x2 caractères */
        #define H44780_ROWS     16
        #define H44780_LINES    2
        
#elif  ( H44780_DISPLAY_TYPE == 6 )   /* Afficheur 16x4 caractères */
        #define H44780_ROWS     16
        #define H44780_LINES    4
        
#elif  ( H44780_DISPLAY_TYPE == 7 )   /* Afficheur 20x2 caractères */
        #define H44780_ROWS     20
        #define H44780_LINES    2
        
#elif  ( H44780_DISPLAY_TYPE == 8 )   /* Afficheur 20x4 caractères */
        #define H44780_ROWS     20
        #define H44780_LINES    4
        
#elif  ( H44780_DISPLAY_TYPE == 9 )   /* Afficheur 40x2 caractères */
        #define H44780_ROWS     40
        #define H44780_LINES    2
#endif

#if ( H44780_LINES <= 1 )
        #define H44780_LINES_OFFSET    0
#else
        #define H44780_LINES_OFFSET    8
#endif

#define H44780_BUSY_FLAG        7	/* Pourquoi doit-on le définir? */

/*
 * H44780 command codes
 */

#define H44780_CLEAR_DISPLAY    0x01		/* Effacement de l'écran */
#define H44780_CURSOR_HOME      0x02		/* Positionne le curseur en haut à gauche */

#define H44780_DISPLAY_OFF      0x08		/* Eteint l'écran */
#define H44780_DISPLAY_ON       0x0C		/* Allume l'écran */

#define H44780_DISPLAY_SHIFT    0x18		/* Décalage à droite */
#define H44780_CURSOR_SHIFT     0x18		/* Décalage à droite */

#define H44780_BLINK_ON         0x0F		/* Curseur clignotant */
#define H44780_BLINK_OFF        0x0C		/* Curseur fixe */

#define H44780_CURSOR_ON        0x0E		/* curseur visible */
#define H44780_CURSOR_OFF       0x0C		/* curseur invisible */

#define LINE_1		        0x80		/* Adresse 1er caractère de la ligne 1 */
#define LINE_2			0xC0		/* Adresse 1er caractère de la ligne 2 */
#define LINE_3			0x94		/* Adresse 1er caractère de la ligne 3 */
#define LINE_4      		0xB6		/* Adresse 1er caractère de la ligne 4 */

/*
 * Prototypes
 */
void LCD_init (void);				/* Initialisation de l'afficheur */
void LCD_sendCommand (uint8_t);			/* Envoi d'une commande vers l'afficheur */
void LCD_puts (char *);				/* Affichage d'un caractère */
void LCD_nputs (char *, uint8_t);		/* Affichage de n caractères */
void LCD_putc (char *);				/* Affichage d'un caratère */
void LCD_sendText (char);			/* Affichage d'un caratère */
void LCD_gotoxy(uint8_t,uint8_t);		/* Positionne le curseur en x,y */
void LCD_clearLine(uint8_t);			/* Efface la ligne courante */

/*
 *  Macros
 */

#define LCD_clrscr()            LCD_sendCommand(H44780_CLEAR_DISPLAY)
#define LCD_blinkOn()           LCD_sendCommand(H44780_BLINK_ON)
#define LCD_blinkOff()          LCD_sendCommand(H44780_BLINK_OFF)
#define LCD_cursorOn()          LCD_sendCommand(H44780_CURSOR_ON)
#define LCD_cursorOff()         LCD_sendCommand(H44780_CURSOR_OFF)
//#define LCD_gotoLine(x)         LCD_sendCommand(x)
#define LCD_switchOn()          LCD_sendCommand(H44780_DISPLAY_ON)
#define LCD_switchOff()         LCD_sendCommand(H44780_DISPLAY_OFF)


#if defined (H44780_RW_PORT_PRESENT)
 #define LCD_wait_ms()	        _H44780_RW_REG_, |= (1<< _H44780_RW_PIN); \
                                loop_until_bit_is_clear(_H44780_DATA_PORT_,H44780_BUSY_FLAG); \
                                _H44780_RW_REG_ &= ~(1<<H44780_RW_PIN)

 #define LCD_wait_us()          _H44780_RW_REG_ |= (1<< _H44780_RW_PIN); \
                                loop_until_bit_is_clear(_H44780_DATA_PORT_,H44780_BUSY_FLAG); \
                                _H44780_RW_REG_ &= ~(1<<H44780_RW_PIN)

 #define LCD_enable_ms()        _H44780_CLOCK_PORT_, |= (1<< H44780_CLOCK_PIN); \
                                LCD_wait(); \
                                _H44780_CLOCK_PORT_, &= ~(1<<H44780_CLOCK_PIN)

 #define LCD_enable_us()        _H44780_CLOCK_PORT_, |= (1<<H44780_CLOCK_PIN); \
                                LCD_wait(); \
                                _H44780_CLOCK_PORT_, &= ~(1<<H44780_CLOCK_PIN)
#else
 #define LCD_wait_ms()          _delay_ms()

 #define LCD_wait_us()          _delay_us()

 #define LCD_enable_ms()        _H44780_CLOCK_PORT_ |= (1<< H44780_CLOCK_PIN); \
                                _delay_ms (); \
                                _H44780_CLOCK_PORT_ &= ~(1<<H44780_CLOCK_PIN)

 #define LCD_enable_us()        _H44780_CLOCK_PORT_ |= (1<<H44780_CLOCK_PIN); \
                                _delay_us (); \
                                _H44780_CLOCK_PORT_ &= ~(1<<H44780_CLOCK_PIN)
#endif

#endif   //     H44780_H
