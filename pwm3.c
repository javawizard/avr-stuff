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
    
    FDDRA0 = 1;
    FDDRA1 = 1;
    FDDRA2 = 1;
    FPORTA0 = 0;
    FPORTA1 = 0;
    FPORTA2 = 0;
    
    FDDRA3 = 0;
    FDDRA4 = 0;
    FDDRA5 = 0;
    FPORTA3 = 1;
    FPORTA4 = 1;
    FPORTA5 = 1;
    
    oldTwobit = PINS_TO_TWOBIT(FPINA3, FPINA4);
    newTwobit = oldTwobit;
    
    TCCR0B |= 0b101; // 001 to not divide, 010 to divide by 8, 011 to divide by 64
    while(1) {
        DO_PWM(FPORTA0, red);
        DO_PWM(FPORTA1, green);
        DO_PWM(FPORTA2, blue);
        if(0 && TIFR0 & 1) { // Timer overflowed
            TIFR0 = 1;
            if(mode == 0) {
                red--;
                green++;
                if(red == 0) {
                    mode = 1;
                }
            }
            else if(mode == 1) {
                green--;
                blue++;
                if(green == 0) {
                    mode = 2;
                }
            }
            else if(mode == 2) {
                blue--;
                red++;
                if(blue == 0) {
                    mode = 0;
                }
            }
        }
        
        newTwobit = PINS_TO_TWOBIT(FPINA3, FPINA4);
        twobitState = TWOBIT_STATE(oldTwobit, newTwobit);
        oldTwobit = newTwobit;
        
        if(twobitState == -1) {
            if(blue >= 4) {
                blue -= 4;
            } else {
                blue = 0;
            }
        }
        else if(twobitState == 1) {
            if(blue <= 251) {
                blue += 4;
            } else {
                blue = 255;
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
                if(green < 240) {
                    green += 4;
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

