
// Run PWM against timer 0
#define DO_PWM(pin, value) if(TCNT0 >= (value)) {(pin) = 0;} else {(pin) = 1;}
#define WRAP_ONE_OFF_TO(value, size) ((value) == (size) ? 0 : ((value) == -1 ? (size) - 1 : (value)))
#define NEXT_MOD(value, mod) (((value) + 1) % (mod))
#define TWOBIT_NEXT(value) NEXT_MOD(value, 4)
// -1 if switch went backward, 0 if no movement, 1 if forward
#define TWOBIT_STATE(old, new) ((TWOBIT_NEXT(new) == old) ? -1 : ((TWOBIT_NEXT(old) == new) ? 1 : 0))
#define PINS_TO_TWOBIT(high, low) (high << 1) | (high ^ low)


class RotaryEncoder {
    uint8_t currentTwobit, lagAmount, currentValue, currentLaggedValue;
    
    public:
        RotaryEncoder(uint8_t high, uint8_t low, uint8_t lagAmount) {
            currentTwobit = PINS_TO_TWOBIT(high, low);
            // With this calculation, the lag amount passed into the
            // constructor represents the number of transitions required to
            // produce an "apparent transition", i.e. if this is 4 (and so the
            // value that ends up in this->lagAmount is 5), then the first
            // three transitions will be ignored, and the fourth will produce
            // a transition as far as process() is concerned. 1 can be passed
            // to disable lag, i.e. produce transitions every time.
            this->lagAmount = lagAmount + 1;
            currentValue = 0;
            currentLaggedValue = 1;
        }
        int8_t process(uint8_t high, uint8_t low) {
            uint8_t newTwobit = PINS_TO_TWOBIT(high, low);
            int8_t twobitState = TWOBIT_STATE(currentTwobit, newTwobit);
            #ifdef ROTARYTEST
            printf("ts: %d\n", twobitState);
            #endif
            currentTwobit = newTwobit;
            currentValue = WRAP_ONE_OFF_TO(currentValue + twobitState, lagAmount);
            if(currentValue == currentLaggedValue) {
                currentLaggedValue = WRAP_ONE_OFF_TO(currentLaggedValue + twobitState, lagAmount);
                #ifdef ROTARYTEST
                printf("final cv: %d, clv: %d\n", currentValue, currentLaggedValue);
                #endif
                return twobitState;
            }
            #ifdef ROTARYTEST
            printf("final cv: %d, clv: %d\n", currentValue, currentLaggedValue);
            #endif
            return 0;
        }
};


