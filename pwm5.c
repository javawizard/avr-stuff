#include <avr/io.h>
#include <avr/delay.h>
#include "bitfield.h"

// Run PWM against timer 0
#define DO_PWM(pin, value) if(TCNT0 >= (value)) {(pin) = 0;} else {(pin) = 1;}
#define TWOBIT_NEXT(value) (((value) + 1) % 4)
// -1 if switch went backward, 0 if no movement, 1 if forward
#define TWOBIT_STATE(old, new) ((TWOBIT_NEXT(new) == old) ? -1 : ((TWOBIT_NEXT(old) == new) ? 1 : 0))
#define PINS_TO_TWOBIT(high, low) (high << 1) | (high ^ low)

int main(void) {
    uint8_t flipped = 0;
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;

    uint8_t mode = 0;
    
    uint8_t oldTwobit = 0;
    uint8_t newTwobit = 0;
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
    TCCR1B |= 0b00001100;
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
    
    oldTwobit = PINS_TO_TWOBIT(FPINA3, FPINA4);
    newTwobit = oldTwobit;
    
    while(1) {
        newTwobit = PINS_TO_TWOBIT(FPINA3, FPINA4);
        twobitState = TWOBIT_STATE(oldTwobit, newTwobit);
        oldTwobit = newTwobit;
        
        if(twobitState == -1) {
            if(OCR1D >= 4) {
                OCR1D -= 4;
            } else {
                OCR1D = 0;
            }
        }
        else if(twobitState == 1) {
            if(OCR1D <= 251) {
                OCR1D += 4;
            } else {
                OCR1D = 255;
            }
        }
        newButtonState = !FPINA5;
        if(newButtonState != oldButtonState) {
            consistentButtonCycles = 0;
            processedButtonChange = 0;
            oldButtonState = newButtonState;
        }
        else if(consistentButtonCycles < 1000) {
            consistentButtonCycles++;
        }
        else if(!processedButtonChange) {
            processedButtonChange = 1;
            if(newButtonState) {
                if(OCR1B < 240) {
                    OCR1B += 4;
                }
            }
        }
        /*
        if(FPINA3) {
            red = 255;
        } else {
            red = 0;
        }
        if(FPINA4) {
            blue = 255;
        } else {
            blue = 0;
        }
        */
    }
}

