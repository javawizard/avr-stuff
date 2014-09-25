#include <avr/io.h>

// #define F_CPU 20000000UL
#include <avr/delay.h>

int main(void)
{
    unsigned char data[] = {
        3, 1, 2, 2, 4, 3, 3, 4, 2, 4, 3, 2, 1, 2, 2, 2, 4, 3, 2, 3, 1, 1, 1, 9
    };
    DDRA = 0xFF;
    DDRB = 0xFF;
    while( 1 ) {
        int i = 0;
        while(i < 24) {
            PORTA = 1;
            _delay_ms(80);
            PORTA = 0;
            int j = 1;
            while(j < data[i]) {
                _delay_ms(160);
                j++;
            }
            _delay_ms(80);
            i = i + 1;
        }
    }
}



