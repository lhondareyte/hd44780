/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c)2006-2026 Luc Hondareyte
 *
 */

#ifdef __AVR__

#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#ifndef H44780_DATA_PORT
#define H44780_DATA_PORT        _H44780_PORTB_ 
#endif

#ifndef H44780_ENABLE_PORT
#define H44780_ENABLE_PORT       _H44780_PORTB_	
#endif

#ifndef H44780_ENABLE_PIN
#define H44780_ENABLE_PIN        5	
#endif

#ifndef H44780_RS_PORT
#define H44780_RS_PORT          _H44780_PORTB_	/* RS on PORTD */
#endif

#ifndef H44780_RS_PIN
#define H44780_RS_PIN           4
#endif	

#ifndef H44780_8BITS_MODE
#define H44780_4BITS_MODE       /* default 4bits */
#endif

#ifndef H44780_DATA_IS_MSB
#define H44780_DATA_IS_LSB      /* default MSB */
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

#endif // __AVR__

