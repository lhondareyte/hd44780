Yet another HD77480 library for AVR

Tested Ok with 
 * at90s2313
 * attiny2313, attiny4313
 * atmega8
 * atmega32u2
 * atmega32u4

See differents files to set hd44780 pinout. 
### Hello, world!

You should copy all files in subdirectory (eg. hd44780) of your project. 
```
#include <avr.h>

/* 
 * 2x24 character in 4 bits mode connected as follow :
 *     DATA   = PIN[4-7] PORTD
 *     ENABLE = PIN3 PORTD
 *     RS     = PIN4 PORTC
 *     RW to GND
 */

#define H44780_DISPLAY_TYPE 	10              /* 2x24 characters type  */
#define H44780_DATA_WIDTH 	4               /* 4bits mode            */
#define H44780_PORT_IS_LSB 	0               /* DATA = PIN[4-7] PORTD */
#define H44780_DISPLAY_PORT 	_H44780_PORTD_
#define H44780_ENABLE_PIN 	3               /* ENABLE on PIN3 PORTD  */
#define H44780_ENABLE_PORT 	_H44780_PORTD_
#define H44780_RS_PIN	 	4               /* RS on PIN4 PORTC      */
#define H44780_RS_PORT	 	_H44780_PORTC_

#include "hd44780/hd44780.h"

int main(void) {
	LCD_init();
	LCD_puts("Hello, world!\n");
	_delay_ms(1000);
	LCD_clrscr();
	LCD_puts("   Goodbye\n");
	LCD_puts("  Cruel World!  ");
	while (1) {}
	return 0;
}
