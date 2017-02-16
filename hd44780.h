 /*
  * Copyright (c) 2006-2013 Luc HONDAREYTE
  * All rights reserved.
  *
  */

#ifndef __HD44780_H__
 #define __HD44780_H__
  
#include <stdlib.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

/*
 * Definition des valeurs par défaut:
 * Afficheur 2x16 caratères connecté sur PORTB piloté en mode 4bits.
 * Broche RS connectée sur la PIND2
 * Broche ENABLE connectée sur la PIND3 (La broche ENABLE peut se nommer Enable)
 */
#ifndef H44780_DISPLAY_TYPE
  #warning LCD Type is not set
  #define H44780_DISPLAY_TYPE     5			/* Afficheur 2x16 */
#endif

#ifndef H44780_DATA_PORT
  #define H44780_DATA_PORT        _H44780_PORTB_ 	/* Connexion sur PORTB */
#endif

#ifndef H44780_ENABLE_PORT
  #define H44780_ENABLE_PORT       _H44780_PORTB_	/* ENABLE sur PORTD */
#endif

#ifndef H44780_ENABLE_PIN
  #define H44780_ENABLE_PIN        5			/* ENABLE sur PIND2 */
#endif

#ifndef H44780_RS_PORT
  #define H44780_RS_PORT          _H44780_PORTB_	/* RS sur PORTD */
#endif

#ifndef H44780_RS_PIN
  #define H44780_RS_PIN           4			/* RS sur PIND3 */
#endif	

#ifndef H44780_DATA_WIDTH
  #define H44780_DATA_WIDTH       4			/* Connexion en 4bits */
#endif

/*
 * Le préprocesseur ne sait pas faire de comparaison de chaînes. Il sait seulement 
 * faire des opérations arithmétiques.
 * Ceci explique les définitions ci-dessous:
 */
#define _H44780_PORTA_		0x01
#define _H44780_PORTB_		0x02
#define _H44780_PORTC_		0x03
#define _H44780_PORTD_		0x04
#define _H44780_PORTE_		0x05


/*
 *  Port de données - 4 ou 8 bits
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
 * Port d'horloge 
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
 *  Display types
 */
#if    ( H44780_DISPLAY_TYPE == 1 )   /* Afficheur 5x2 caractères */
        #define H44780_ROWS     5
        #define H44780_LINES    2
        #define H44780_DDRAM_L1  0x80
        #define H44780_DDRAM_L2  0x40
        
#elif  ( H44780_DISPLAY_TYPE == 2 )   /* Afficheur 8x1 caractères */
        #define H44780_ROWS     8
        #define H44780_LINES    1
        #define H44780_DDRAM_L1  0x80
        
#elif  ( H44780_DISPLAY_TYPE == 3 )   /* Afficheur 8x2 caractères */
        #define H44780_ROWS     8
        #define H44780_LINES    2
        #define H44780_DDRAM_L1  0x80
        #define H44780_DDRAM_L2  0x40
        
#elif  ( H44780_DISPLAY_TYPE == 4 )   /* Afficheur 16x1 caractères */
        #define H44780_ROWS     16
        #define H44780_LINES    1
        #define H44780_DDRAM_L1  0x80
        
#elif  ( H44780_DISPLAY_TYPE == 5 )   /* Afficheur 16x2 caractères */
        #define H44780_ROWS     16
        #define H44780_LINES    2
        #define H44780_DDRAM_L1  0x80
        #define H44780_DDRAM_L2  0x40
        
#elif  ( H44780_DISPLAY_TYPE == 6 )   /* Afficheur 16x4 caractères */
        #define H44780_ROWS     16
        #define H44780_LINES    4
        #define H44780_DDRAM_L1  0x80
        #define H44780_DDRAM_L2  0x40
        #define H44780_DDRAM_L3  0x80
        #define H44780_DDRAM_L4  0x40
        
#elif  ( H44780_DISPLAY_TYPE == 7 )   /* Afficheur 20x2 caractères */
        #define H44780_ROWS     20
        #define H44780_LINES    2
        #define H44780_DDRAM_L1  0x80
        #define H44780_DDRAM_L2  0x40
        
#elif  ( H44780_DISPLAY_TYPE == 8 )   /* Afficheur 20x4 caractères */
        #define H44780_ROWS     20
        #define H44780_LINES    4
        #define H44780_DDRAM_L1  0x80
        #define H44780_DDRAM_L2  0x40
        #define H44780_DDRAM_L3  0x80
        #define H44780_DDRAM_L4  0x40
        
#elif  ( H44780_DISPLAY_TYPE == 9 )   /* Afficheur 40x2 caractères */
        #define H44780_ROWS     40
        #define H44780_LINES    2
        #define H44780_DDRAM_L1  0x80
        #define H44780_DDRAM_L2  0x40
        
#elif  ( H44780_DISPLAY_TYPE == 10 )   /* Afficheur 24x2 caractères */
        #define H44780_ROWS     24
        #define H44780_LINES    2
        #define H44780_DDRAM_L1  0x80
        #define H44780_DDRAM_L2  0x40
#endif

#if   (H44780_LINES == 1) 
        #define H44780_LINES_ARG    0
#elif (H44780_LINES == 2)
        #define H44780_LINES_ARG    8
#endif

#define H44780_BUSY_FLAG        7	/* Pourquoi doit-on le définir? */

/*
 * H44780 command codes
 */

#define H44780_CLEAR_DISPLAY    0x01	/* Effacement de l'écran */
#define H44780_CURSOR_HOME      0x02	/* Positionne le curseur en haut à gauche */
#define H44780_CURSOR_RIGHT     0x06	/* Deplacement du curseur vers la droite */

#define H44780_DISPLAY_OFF      0x08	/* Eteint l'écran */
#define H44780_DISPLAY_ON       0x0C	/* Allume l'écran */

#define H44780_DISPLAY_SHIFT    0x18	/* Décalage à droite */
#define H44780_CURSOR_SHIFT     0x18	/* Décalage à droite */

#define H44780_BLINK_OFF        0x0C	/* Curseur fixe */
#define H44780_BLINK_ON         0x0F	/* Curseur clignotant */

#define H44780_CURSOR_ON        0x0E	/* curseur visible */
#define H44780_CURSOR_OFF       0x0C	/* curseur invisible */

#define LINE_1		        0x80	/* Adresse 1er caractère de la ligne 1 */
#define LINE_2			0xC0	/* Adresse 1er caractère de la ligne 2 */
#define LINE_3			0x94	/* Adresse 1er caractère de la ligne 3 */
#define LINE_4      		0xB6	/* Adresse 1er caractère de la ligne 4 */

/*
 * HD44780 temporisations
 */

#define H44780_WAIT_COMMIT	0x01
#define H44780_WAIT_CMD		0x02

/*
 * Prototypes
 */
void LCD_init (void);			/* Initialisation du LCD */
void LCD_ioctl (uint8_t);		/* Envoi d'une commande vers le LCD */
void LCD_putc (char);			/* Envoi d'un caractère vers le LCD */
void LCD_puts (const char *);			/* Affichage d'un caractère */
void LCD_gotoxy(uint8_t,uint8_t);	/* Positionne le curseur en x,y */
void LCD_clrline(uint8_t);		/* Efface la ligne n */
void LCD_validate(void);		/* valide une commande */
void LCD_wait(void);			/* Gestion des delais */

/*
 *  Macros
 */

#define LCD_clrscr()            LCD_ioctl(H44780_CLEAR_DISPLAY)
#define LCD_blinkOn()           LCD_ioctl(H44780_BLINK_ON)
#define LCD_blinkOff()          LCD_ioctl(H44780_BLINK_OFF)
#define LCD_cursorOn()          LCD_ioctl(H44780_CURSOR_ON)
#define LCD_cursorOff()         LCD_ioctl(H44780_CURSOR_OFF)
#define LCD_BigCursorOff()      LCD_ioctl(H44780_CURSOR_OFF)
#define LCD_BigCursorOn()       LCD_ioctl(H44780_BLINK_ON)
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
