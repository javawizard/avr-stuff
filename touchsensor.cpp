#include <avr/io.h>
#include <avr/delay.h>
#include "bitfield.h"

int main(void) {
    FDDRA0 = 1;
    FDDRA1 = 0;
    FDDRA3 = 1;
    
    FPORTA0 = 0;
    FPORTA1 = 0;
    FPORTA3 = 0;
    
    int32_t cycles = 0;
    
    while(1) {
        FPORTA0 = 1;
        while(FPINA1 != 1) {
            
        }

        FPORTA0 = 0;

        FPORTA3 = 1;

        FDDRA1 = 1;

        _delay_us(10);

        FDDRA1 = 0;

        _delay_us(10);

        FPORTA3 = 0;
    }
    
    return 0;
}

