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
    while(1) {
    }
    return 0;
}
