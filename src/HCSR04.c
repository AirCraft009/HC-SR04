#include "HCSR04.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint64_t time_mircoS = 0;
Pin sig = EMPTY_PIN;

void setPins(int trigPin, int echoPin, HC_SR04 hcSR04) {
    // currently just accepts all pins but will control in future

    SetPin(&hcSR04.Trig, trigPin, true);
    SetPin(&hcSR04.Echo, echoPin, false);
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
HC_SR04 CreateHC_SR04(int trigPin, int echoPin) {
    HC_SR04 hc_sr04 = {EMPTY_PIN, EMPTY_PIN, 0, 0};
    setPins(trigPin, echoPin, hc_sr04);
    return hc_sr04;
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

void trigger(HC_SR04 *hc_sr04) {
    DigitalWrite(&hc_sr04->Trig, HIGH);
    DigitalWrite(&hc_sr04->Trig, LOW);
    hc_sr04->measureEnd = micros();
}


// ISR for PORTD == PORTB
ISR(PCINT2_vect, ISR_ALIASOF(PCINT0_vect));
ISR(PCINT0_vect) {
    /*
     *get what pin triggered
     */
    measureEnd = micros();
    DigitalWrite(&sig, LOW);
}

uint64_t measure(HC_SR04 *hc_sr04) {
    sei();
    trigger(hc_sr04);
    //make measure blocking
    return GET_CM_FROM_US(hc_sr04->measureEnd-hc_sr04->measureStart);
}


int main(void) {

    while (1) {}

}