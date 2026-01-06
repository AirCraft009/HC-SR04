//
// Created by cocon on 28.12.2025.
//
#include "Pin.h"
#include <avr/interrupt.h>

/**
 *
 * Sets Pins and returns information in struct
 *
 * @param PinNumber Number from 0-13 like on the Arduino
 * @param write Set to Write or Read
 * @return A Pin Struct containg this information
 */
int SetPin(Pin *pin, int PinNumber, bool write) {
    if (CHECK_PIN_VALIDITY(PinNumber)) return 1;

    pin->dataDirReg = GET_DATA_DIRECTION_REGISTER(PinNumber);
    pin->PinNumber = (PinNumber <= 7 ? PinNumber : PinNumber - 8);
    pin->write = write;

    if (write) {
        SET_DATA_DIRECTION_WRITE(*pin->dataDirReg, pin->PinNumber);
        pin->port = CONVERT_NUM_TO_PORT(PinNumber);
    }
    else {
        SET_DATA_DIRECTION_READ(*pin->dataDirReg, pin->PinNumber);
        pin->port = CONVERT_NUM_TO_PIN(PinNumber);
    }
    return 0;
}



int DigitalWrite(const Pin *p, int value) {
    if (!p || !p->write) return 1;

    if (value != LOW)
        *p->port |=  (1 << p->PinNumber);
    else
        *p->port &= ~(1 << p->PinNumber);

    return 0;
}

int DigitalRead(const Pin *p) {
    if (!p || p->write) return 1;

    uint8_t val = (*p->port & (1 << p->PinNumber)) == 0;
    return val;
}

void InitPCINT(const Pin *p) {
    // set as input
    SET_DATA_DIRECTION_READ(*p->dataDirReg, p->PinNumber);
    SET_PULL_DOWN(*p->port, p->PinNumber);
    PCICR |= (1 << GET_PCIE_BIT(p->port));
    volatile uint8_t* mask = (GET_INTERRUPT_MASK(p->port));
    // TODO: replace p.PinNumber with translated PCINTn so that PDn works
    *mask |= (1 << p->PinNumber);
}