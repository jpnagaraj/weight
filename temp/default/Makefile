###############################################################################
# Makefile for the project CYBOLYMB_ANGLE
###############################################################################

## General Flags
PROJECT = CYBOLYMB_ANGLE
MCU = atmega128
TARGET = MAIIN.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99                -DF_CPU=16000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += -Wl,-u,vfprintf -Wl,-Map=MAIIN.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Libraries
LIBS = -lm -lprintf_flt 

## Objects that must be built in order to link
OBJECTS = ContrllerModule.o MAIN.o lcd.o Devicefuctions.o HX711.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) MAIIN.hex MAIIN.eep MAIIN.lss size

## Compile
ContrllerModule.o: ../ContrllerModule.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

MAIN.o: ../MAIN.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

lcd.o: ../lcd.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Devicefuctions.o: ../Devicefuctions.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

HX711.o: ../HX711.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) MAIIN.elf dep/* MAIIN.hex MAIIN.eep MAIIN.lss MAIIN.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

