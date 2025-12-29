//
// Created by cocon on 28.12.2025.
//
#include "Pin.h"

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
    if (write) {
        SET_DATA_DIRECTION_WRITE(PinNumber);
        pin->port = CONVERT_NUM_TO_PORT(PinNumber);
    }
    else {
        SET_DATA_DIRECTION_READ(PinNumber);
        pin->port = CONVERT_NUM_TO_PIN(PinNumber);
    }

    pin->PinNumber = (PinNumber <= 7 ? PinNumber : PinNumber - 8);
    pin->write = write;
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
