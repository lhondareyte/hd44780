#
# Copyright (c) 2006 Luc Hondareyte
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# $Id: Makefile,v 1.1 2007/01/07 11:56:23 luc Exp luc $
#

HEADERS         := $(wildcard *.h)
HD44780_SRC     := $(wildcard *.c) 
ASMSRCS         := $(wildcard *.s)
OBJECTS         := $(patsubst %.c,%.o,$(HD44780_SRC))
OBJECTS         += $(patsubst %.s,%.o,$(ASMSRCS))
LCD_LIB		:= hd44780.a

.c.o:
	@printf "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o ../$@
	@echo done
.S.o:
	@printf "Compiling $<..."
	$(AS) $(AFLAGS) $< -o $@
	@echo done
.s.o:
	@printf "Compiling $<..."
	$(AS) $(AFLAGS) $< -o $@
	@echo done

#all: $(LCD_LIB)
all: $(OBJECTS)

$(LCD_LIB): $(OBJECTS)
	@printf "Creating $(LCD_LIB)..."
	@avr-ar rvs $(LCD_LIB) $(OBJECTS) > /dev/null 2>&1
	@echo done
clean:
	rm -f $(OBJECTS) $(LCD_LIB) *~