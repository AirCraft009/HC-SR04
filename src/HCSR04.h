#ifndef HC_SR04_LIBRARY_H
#define HC_SR04_LIBRARY_H
#include "../include/Pin.h"

#define GET_CM_FROM_US(t) (t/58)
#define GET_IN_FROM_US(t) (t/148)

#endif // HC_SR04_LIBRARY_H

int sendPulse(void);

typedef struct ControlState {
    Pin Trig;
    Pin Echo;
    // in mikrosec
    uint64_t measureStart;
    uint64_t measureEnd;
}ControlState;

extern ControlState control;