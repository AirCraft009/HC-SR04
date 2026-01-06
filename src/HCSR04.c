#include "main.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


ControlState control = {EMPTY_PIN, EMPTY_PIN, 0, 0};
volatile uint64_t time_mircoS = 0;
Pin sig = EMPTY_PIN;

void setPins(int trigPin, int echoPin) {
    // currently just accepts all pins but will control in future

    SetPin(&control.Trig, trigPin, true);
    SetPin(&control.Echo, echoPin, false);
} 

/**
 *
 * Inits the internal state of the HC-SR04
 *
 * @param trigPin Normal IO pin
 * @param echoPin Normal IO pin
 * @param gndPin Gnd Pin
 * @param VccPin A 5.5V VCC pin
 */
void InitHC_SR04(int trigPin, int echoPin) {
    setPins(trigPin, echoPin);
    sei();
}

// triggers on TCNT1 == OCR1A
ISR(TIMER1_COMPA_vect) {
    time_mircoS ++;
}

void initTimer1() {
    TCCR1A = 0;
    // x8 prescaler
    TCCR1B |= (1 << WGM12) | (0 << CS11) | (1 << CS10);
    // when TCNT1 == OCR1A it fires the intr
    // that'S 250 ticks 0...249
    OCR1A = 249;
    // allow Timer1 to trigger
    TIMSK1 |= (1 << OCIE1A);
    //enable interrupts
    sei();
}

uint32_t micros() {
    uint32_t t;
    cli();
    t = time_mircoS;
    sei();
    return t;
}

void trigger() {
    DigitalWrite(&control.Trig, HIGH);
    DigitalWrite(&control.Trig, LOW);
    control.measureStart = micros();
}


// ISR for PORTD == PORTB
ISR(PCINT2_vect, ISR_ALIASOF(PCINT0_vect));
ISR(PCINT0_vect) {
    control.measureEnd = micros();
    DigitalWrite(&sig, LOW);
}

uint64_t measure() {
    sei();
    trigger();
    //make measure blocking
    while (control.measureStart < );
}


int main(void) {

    while (1) {}

}