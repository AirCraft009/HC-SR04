#include "main.h"
#include <util/delay.h>

/**
 *
 * Inits the internal state of the HC-SR04
 *
 * @param trigPin Normal IO pin
 * @param echoPin Normal IO pin
 * @param gndPin Gnd Pin
 * @param VccPin A 5.5V VCC pin
 */

ControlState control = {EMPTY_PIN, EMPTY_PIN, EMPTY_PIN, 0};

void setPins(int trigPin, int echoPin,  int vccPin) {
    // currently just accepts all pins but will control in future
    Pin trig = EMPTY_PIN;
    Pin echo = EMPTY_PIN;
    Pin vcc = EMPTY_PIN;

    SetPin(&trig, trigPin, true);
    SetPin(&echo, echoPin, false);
    SetPin(&vcc, vccPin, true);

    control.Echo = echo;
    control.Trig = trig;
    control.Vcc = vcc;
    DigitalWrite(&vcc, HIGH);

}

void InitHC_SR04(int trigPin, int echoPin, int VccPin) {
    setPins(trigPin, echoPin, VccPin);
}


int main(void) {
    Pin pin = EMPTY_PIN;
    SetPin(&pin, LED_BUILTIN, true);
    while (1) {
        DigitalWrite(&pin, LOW);
        _delay_ms(500);
        DigitalWrite(&pin, HIGH);
        _delay_ms(500);
    }
}