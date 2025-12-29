//
// Created by cocon on 27.12.2025.
//

#ifndef HC_SR04_CONFIG_H
#define HC_SR04_CONFIG_H
#include <stdbool.h>
#include <avr/io.h>
#define READ false;
#define WRITE true;
#define LOW 0
#define HIGH 1
#define D0 0
#define D1 1
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define D8 8
#define D9 9
#define D10 10
#define D11 11
#define D12 12
#define D13 13
#define SCK 13
#define LED_BUILTIN 13

#define CHECK_PIN_VALIDITY(p) (p > 13)

#define SET_DATA_DIRECTION_WRITE(p) \
((p) <= 7 ? (DDRD |= (1U << (p))) : (DDRB |= (1U << ((p) - 8))))

#define SET_DATA_DIRECTION_READ(p) \
((p) <= 7 ? (DDRD &= ~(1U << (p))) : (DDRB &= ~(1U << ((p) - 8))))

#define CONVERT_NUM_TO_PORT(n)\
    ((n) <= 7 ? &PORTD : &PORTB)

#define CONVERT_NUM_TO_PIN(n)\
    ((n) <= 7 ? &PIND : &PINB)

# define EMPTY_PIN {0,0,0}

typedef struct Pin {
    uint8_t PinNumber;
    bool write;
    volatile uint8_t *port;
}Pin;


#endif //HC_SR04_CONFIG_H

int SetPin(Pin * pin, int PinNumber, bool write);
int DigitalWrite(const Pin * p, int value);