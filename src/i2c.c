//
// Created by Adjy Sedar Desir on 28/10/2025.
//

#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include "../include/i2c.h"


void i2c_init(void) {
    TWBR = (uint8_t)TWBR_val;
}

void i2c_start_write(uint8_t address) {
    TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
    while (!(TWCR & (1<<TWINT)));
    TWDR = (address << 1); // écriture
    TWCR = (1<<TWEN)|(1<<TWINT);
    while (!(TWCR & (1<<TWINT)));
}
void i2c_start_read(uint8_t address) {
    TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
    while (!(TWCR & (1<<TWINT)));
    TWDR = (address << 1) | 1; // bit R/W = 1 pour lecture
    TWCR = (1<<TWEN)|(1<<TWINT);
    while (!(TWCR & (1<<TWINT)));
}

void i2c_stop(void) {
    TWCR = (1<<TWSTO)|(1<<TWEN)|(1<<TWINT);
    _delay_us(10);
}

void i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1<<TWEN)|(1<<TWINT);
    while (!(TWCR & (1<<TWINT)));
}
uint8_t i2c_read(uint8_t ack) {
    if (ack)
        TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
    else
        TWCR = (1<<TWEN)|(1<<TWINT);
    while (!(TWCR & (1<<TWINT)));
    return TWDR;
}
