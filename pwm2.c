#include <avr/io.h>
#include <avr/delay.h>
#include "bitfield.h"

// Run PWM against timer 0
#define DO_PWM(pin, value) if(TCNT0 > (value)) {(pin) = 0;} else {(pin) = 1;}
#define TWOBIT_NEXT(value) (((value) + 1) % 4)
// -1 if switch went backward, 0 if no movement, 1 if forward
#define TWOBIT_STATE(old, new) ((TWOBIT_NEXT(new) == old) ? -1 : ((TWOBIT_NEXT(old) == new) ? 1 : 0))
#define PINS_TO_TWOBIT(high, low) low | ((high ^ low) << 1)

int main(void) {
    uint8_t flipped = 0;
    uint8_t red = 255;
    uint8_t green = 0;
    uint8_t blue = 0;
    uint8_t mode = 0; // 0 = r -> g, 1 = g -> b, 2 = b -> r
    
    uint8_t oldTwobit = 0;
    uint8_t newTwobit = 0;
    
    FDDRA0 = 1;
    FDDRA1 = 1;
    FDDRA2 = 1;
    
    FDDRA3 = 0;
    FDDRA4 = 0;
    FPORTA3 = 1;
    FPORTA4 = 1;
    
    oldTwobit = PINS_TO_TWOBIT(FPINA3, FPINA4);
    newTwobit = oldTwobit;
    
    TCCR0B |= 0b010;
    while(1) {
        DO_PWM(FPORTA0, red);
        DO_PWM(FPORTA1, green);
        DO_PWM(FPORTA2, blue);
        if(TIFR0 & 1) { // Timer overflowed
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
        
        
    }
}

