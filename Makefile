# Configuration
CC = avr-gcc
AR = avr-ar
MCU = atmega328p
F_CPU = 16000000UL
CFLAGS = -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)

# Dossiers
SRC_DIR = src
INC_DIR = include
LIB_DIR = i2c-libs

# Fichiers sources
SOURCES = $(SRC_DIR)/i2c.c
OBJECTS = $(SOURCES:.c=.o)

# Cible de la bibliothèque
TARGET = $(LIB_DIR)/libi2c.a

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(LIB_DIR)/include
	$(AR) rcs $@ $^
	cp $(INC_DIR)/*.h $(LIB_DIR)/include/
	@echo "Bibliothèque créée: $@"

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -rf $(LIB_DIR)/include

install: $(TARGET)
	@echo "Bibliothèque prête dans $(LIB_DIR)/"
