#include <avr/io.h>
#include <avr/delay.h>
#include "bitfield.h"
#include "rotaryencoder.h"


int main(void) {
    volatile uint8_t* colorPointers[3] = {&(OCR1A), &(OCR1B), &(OCR1D)};
    uint8_t currentColor = 0;
    volatile uint8_t* currentColorPointer = colorPointers[currentColor];
    
    uint16_t cyclesSinceLastChange = 0;

    RotaryEncoder encoder(FPINA3, FPINA4, 4);
    
    int8_t twobitState = 0;
    
    uint8_t oldButtonState = 0;
    uint8_t newButtonState = 0;
    uint16_t consistentButtonCycles = 0;
    uint8_t processedButtonChange = 0;
    
    FDDRB1 = 1;
    FDDRB3 = 1;
    FDDRB5 = 1;
    
    FDDRA3 = 0;
    FDDRA4 = 0;
    FDDRA5 = 0;
    FPORTA3 = 1;
    FPORTA4 = 1;
    FPORTA5 = 1;
    
    // Set the clock source and prescaling for the timer
    TCCR1B |= 0b00000011;
    // Enable PWM
    // First, set COM1* up in TCCR1C
    TCCR1C |= 0b10101000;
    // Then set PWM1A and PWM1B
    TCCR1A |= 0b00000011;
    // And then set PWM1D
    TCCR1C |= 0b00000001;
    // Set Phase & Frequency Correct PWM, because why not.
    TCCR1D |= 0b00000001;
    // Set OCR1C to 255 - this will cause the timer to reset to 0 every time it
    // hits 255, and therefore act as an 8-bit timer instead of a 10-bit timer.
    OCR1C = 255;
    // And we should be good to go.
    TCNT1 = 0;
    OCR1A = 0;
    OCR1B = 0;
    OCR1D = 32;
    
    while(1) {
        cyclesSinceLastChange++;
        
        twobitState = encoder.process(FPINA3, FPINA4);
        
        if(FPINA3 == 1 && FPINA4 == 1 && twobitState != 0) {
            uint8_t amount;
            if(cyclesSinceLastChange < 100) {
                amount = 16;
            } else if(cyclesSinceLastChange < 120) {
                amount = 12;
            } else if(cyclesSinceLastChange < 140) {
                amount = 9;
            } else if(cyclesSinceLastChange < 170) {
                amount = 7;
            } else if(cyclesSinceLastChange < 220) {
                amount = 5;
            } else if(cyclesSinceLastChange < 300) {
                amount = 3;
            } else if(cyclesSinceLastChange < 500) {
                amount = 2;
            } else {
                amount = 1;
            }
            cyclesSinceLastChange = 0;
            if(twobitState == -1) {
                if((*currentColorPointer) >= amount) {
                    (*currentColorPointer) -= amount;
                } else {
                    (*currentColorPointer) = 0;
                }
            }
            else if(twobitState == 1) {
                if((*currentColorPointer) <= (255 - amount)) {
                    (*currentColorPointer) += amount;
                } else {
                    (*currentColorPointer) = 255;
                }
            }
        }
        newButtonState = !FPINA5;
        if(newButtonState != oldButtonState) {
            consistentButtonCycles = 0;
            processedButtonChange = 0;
            oldButtonState = newButtonState;
        }
        else if(consistentButtonCycles < 25) {
            consistentButtonCycles++;
        }
        else if(!processedButtonChange) {
            processedButtonChange = 1;
            if(newButtonState) {
                currentColor = currentColor + 1;
                if(currentColor == 3) {
                    currentColor = 0;
                }
                currentColorPointer = colorPointers[currentColor];
            }
        }
    }
}

