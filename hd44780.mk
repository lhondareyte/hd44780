HD44780_SOURCES = hd44780/LCD_clrline.c hd44780/LCD_gotoxy.c hd44780/LCD_init.c
HD44780_SOURCES += hd44780/LCD_ioctl.c hd44780/LCD_nputs.c hd44780/LCD_putc.c
HD44780_SOURCES += hd44780/LCD_puts.c hd44780/LCD_validate.c hd44780/LCD_puts_pgm.c
HD44780_SOURCES += hd44780/LCD_nputs_pgm.c hd44780/LCD_puts_eeprom.c
HD44780_SOURCES += hd44780/LCD_nputs_eeprom.c hd44780/LCD_next_line.c

HD44780_OBJECTS = hd44780/LCD_clrline.o hd44780/LCD_gotoxy.o hd44780/LCD_init.o
HD44780_OBJECTS += hd44780/LCD_ioctl.o hd44780/LCD_nputs.o hd44780/LCD_putc.o
HD44780_OBJECTS += hd44780/LCD_puts.o hd44780/LCD_validate.o hd44780/LCD_puts_pgm.o
HD44780_OBJECTS += hd44780/LCD_nputs_pgm.o hd44780/LCD_puts_eeprom.o 
HD44780_OBJECTS += hd44780/LCD_nputs_eeprom.o hd44780/LCD_next_line.o 

CFLAGS   += -ffunction-sections -fdata-sections
LDFLAGS  += -Wl,-gc-sections
