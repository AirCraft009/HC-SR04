#ifndef HC_SR04_LIBRARY_H
#define HC_SR04_LIBRARY_H
#include "../include/Pin.h"
#endif // HC_SR04_LIBRARY_H

int sendPulse(void);

typedef struct ControlState {
    Pin Vcc;
    Pin Trig;
    Pin Echo;
    // in mikrosec
    int time_since_last_trigger;
}ControlState;

extern ControlState control;