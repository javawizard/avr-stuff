
#define ROTARYTEST

#include "stdint.h"
#include "stdio.h"
#include "rotaryencoder.h"

int main() {
    RotaryEncoder encoder(0, 0, 4);
    printf("State: %d\n", encoder.process(1, 0));
    printf("State: %d\n", encoder.process(1, 1));
    printf("State: %d\n", encoder.process(0, 1));
    printf("State: %d\n", encoder.process(0, 0));
    printf("Going forward now\n");
    printf("State: %d\n", encoder.process(0, 1));
    printf("State: %d\n", encoder.process(1, 1));
    printf("State: %d\n", encoder.process(1, 0));
    printf("State: %d\n", encoder.process(0, 0));
    printf("State: %d\n", encoder.process(0, 1));
    printf("State: %d\n", encoder.process(1, 1));
    printf("State: %d\n", encoder.process(1, 0));
    printf("State: %d\n", encoder.process(0, 0));
    return 0;
}
