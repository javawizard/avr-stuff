
#ifndef __AVR_ATtiny861__
#error "This (presumably) only works on the ATtiny861 at the moment."
#endif

/*
To use, call setup() once, then just change the values of channel1, channel2,
and channel3. The duty cycles of pins 2, 4, and 8 on the ATtiny861 will change
automatically.

I'll be adding more options for e.g. changing the frequency and so forth later.

Note that this takes over timer 1, so make sure you don't need it.
*/

namespace HardwarePWM {
    void setup(void) {
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
    }
    
    uint8_t& channel1 = OCR1A;
    uint8_t& channel2 = OCR1B;
    uint8_t& channel3 = OCR1D;
}
