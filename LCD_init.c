 /*
  * Copyright (c) 2006-2012 Luc HONDAREYTE
  * All rights reserved.
  *
  */

#include "hd44780.h"

void LCD_init (void)
{

	/* Initialisaion des ports */
	
	#if H44780_DATA_WIDTH == 8
        _H44780_DATA_REG_ =  0xff ;

	#else
 	  #if H44780_PORT_IS_LSB == 1
          _H44780_DATA_REG_ |= 0x0f ;
	  #else
          _H44780_DATA_REG_ |= 0xf0 ;
	  #endif
	#endif

 	_H44780_RS_REG_ |= (1<< H44780_RS_PIN);
        _H44780_ENABLE_REG_ |= (1<< H44780_ENABLE_PIN);

        _delay_ms(42);

	/* Debut d'initialisation HD44780 */

	WriteNibble(_H44780_DATA_PORT_, 0x03);
        _H44780_ENABLE_PORT_ &= ~(1<< H44780_ENABLE_PIN);
        _H44780_RS_PORT_ &= ~(1<< H44780_RS_PIN);

	LCD_validate();

        _delay_ms(4);
	LCD_validate();
	LCD_validate();

#if ( H44780_DATA_WIDTH == 8 )
        LCD_ioctl( 0x30 + H44780_LINES_ARG );
	LCD_validate();
#else

	/* Envoi du mode 4bits */
	WriteNibble(_H44780_DATA_PORT_, 0x02);
        _H44780_ENABLE_PORT_ &= ~(1<< H44780_ENABLE_PIN);
        _H44780_RS_PORT_ &= ~(1<< H44780_RS_PIN);

	LCD_validate();
	LCD_validate();

	/* Envoi du nb de lignes */
	WriteNibble(_H44780_DATA_PORT_, H44780_LINES_ARG);
        _H44780_ENABLE_PORT_ &= ~(1<< H44780_ENABLE_PIN);
        _H44780_RS_PORT_ &= ~(1<< H44780_RS_PIN);

	LCD_validate();
#endif
        LCD_ioctl (H44780_DISPLAY_OFF);
        LCD_ioctl (H44780_CURSOR_OFF);
        LCD_ioctl (H44780_CLEAR_DISPLAY);
        LCD_ioctl (H44780_CURSOR_RIGHT);
        LCD_ioctl (H44780_CURSOR_HOME);

}
