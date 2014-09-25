#include "hardware-pwm.hpp"
#include "bitfield.h"
#include <util/delay.h>

int main(void) {
    FDDRA7 = 1;
    FPORTA7 = 1;
    _delay_ms(1000);
    FPORTA7 = 0;
    _delay_ms(500);
    HardwarePWM::setup();
    
    uint16_t current = 0;
    while(1) {
        current = current + 1;
        if (current == 768) {
            current = 0;
        }
        if (current < 256) {
            HardwarePWM::channel1 = 255 - current;
            HardwarePWM::channel2 = current;
        } else if (current < 512) {
            HardwarePWM::channel2 = 512 - current;
            HardwarePWM::channel3 = current - 256;
        } else {
            HardwarePWM::channel3 = 768 - current;
            HardwarePWM::channel1 = current - 512;
        }
        _delay_ms(8);
    }
    return 0;
}
