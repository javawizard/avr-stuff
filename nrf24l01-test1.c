#include <avr/io.h>

#define F_CPU 1000000UL
#include <util/delay.h>

#include "bitfield.h"

#define CE FPORTA1
#define DDRCE FDDRA1
#define CSN FPORTA2
#define DDRCSN FDDRA2
#define SCK FPORTA3
#define DDRSCK FDDRA3
#define MOSI FPORTA4
#define DDRMOSI FDDRA4
#define MISO FPINA5
#define DDRMISO FDDRA5
#define PORTMISO FPORTA5

#define LED FPORTA0
#define DDRLED FDDRA0

#define DEBUG_WAIT debug_wait();

#define SHOULD_USE_RX 0

void debug_wait(void) {
    // _delay_ms(300);
}

void spi_start(void) {
    CSN = 0;
    DEBUG_WAIT
}

uint8_t spi_transmit(uint8_t data) {
    uint8_t output = 0;
    uint8_t i;
    for(i = 0; i < 8; i++) {
        MOSI = (data & 0b10000000) >> 7;
        DEBUG_WAIT
        SCK = 1;
        DEBUG_WAIT
        output = output << 1;
        output |= MISO;
        SCK = 0;
        DEBUG_WAIT
        data = (data & 0b01111111) << 1;
    }
    return output;
}

void spi_end(void) {
    CSN = 1;
    DEBUG_WAIT
    // Most likely not necessary
    _delay_us(5);
}

void flash_out(uint8_t data) {
    int i;
    for(i = 0; i < 8; i++) {
        if((data & 0b10000000) >> 7 == 1) {
            LED = 1;
            _delay_ms(440);
            LED = 0;
            _delay_ms(60);
        } else {
            LED = 1;
            _delay_ms(60);
            LED = 0;
            _delay_ms(440);
        }
        data = (data & 0b01111111) << 1;
    }
    _delay_ms(1000);
}

int main() {
    int i = 0;    
    
    DDRLED = 1;
    
    DDRCE = 1;
    DDRCSN = 1;
    DDRSCK = 1;
    DDRMOSI = 1;
    DDRMISO = 0;

    PORTMISO = 1;
    
    CE = 0;
    CSN = 1;
    SCK = 0;
    
    LED = 0;
    
    _delay_ms(100);
/*    
    LED = 1;
    _delay_ms(500);
    LED = 0;
    _delay_ms(500);
    LED = 1;
    _delay_ms(500);
    LED = 0;
    _delay_ms(500);
*/    
    spi_start();
    spi_transmit(0b00100000 + 0x11);
    spi_transmit(1);
    spi_end();
    
    // Set to 250 Kbps
    spi_start();
    spi_transmit(0b00100000 + 6);
    spi_transmit(0b00100110);
    spi_end();
    
    spi_start();
    spi_transmit(0b00100000 + 0x0);
    spi_transmit(0b00001110 + SHOULD_USE_RX);
    spi_end();
    
    
    
/*    // Set up config
    spi_start();
    spi_transmit(0b00100000 + 0);
    spi_transmit(0b01111110 + SHOULD_USE_RX);
    spi_end();
    // Enable pipe 0 only
    spi_start();
    spi_transmit(0b00100000 + 1);
    spi_transmit(1);
    spi_end();
    // Set address width to 3
    spi_start();
    spi_transmit(0b00100000 + 3);
    spi_transmit(0b01);
    spi_end();
    // Disable auto retransmit
    spi_start();
    spi_transmit(0b00100000 + 4);
    spi_transmit(0);
    spi_end();
    // Set channel
    spi_start();
    spi_transmit(0b00100000 + 5);
    spi_transmit(0b00000010);
    spi_end();
    // Set data rate to 250Kbps etc.
    spi_start();
    spi_transmit(0b00100000 + 6);
    spi_transmit(0b00100110);
    spi_end();
    // Set pipe 0's address to 0b01110001 (113), repeated three times
    spi_start();
    spi_transmit(0b00100000 + 0x0a);
    spi_transmit(113);
    spi_transmit(113);
    spi_transmit(113);
    spi_end();
    // Set transmit address (to our own address)
    spi_start();
    spi_transmit(0b00100000 + 0x10);
    spi_transmit(113);
    spi_transmit(113);
    spi_transmit(113);
    spi_end();
    // Set payload to 1 byte
    spi_start();
    spi_transmit(0b00100000 + 0x11);
    spi_transmit(1);
    spi_end();
    */
    
    if(SHOULD_USE_RX) {
    
        while(1) {
            CE = 1;
            _delay_ms(250);
            CE = 0;
            _delay_ms(1);
            spi_start();
            uint8_t data = spi_transmit(0xFF);
            spi_end();
            // flash_out(data);
            if((data & 0b01000000) >> 6 == 1) {
                LED = 1;
                CE = 0;
                _delay_us(150);
                // Clear the interrupt bit
                spi_start();
                spi_transmit(0b00100000 + 7);
                spi_transmit(0b01000000);
                spi_end();
                // Read the payload
                spi_start();
                spi_transmit(0b01100001);
                spi_transmit(0);
                spi_end();
                CE = 1;
            } else {
                LED = 0;
            }
        }
    } else {
        while(1) {
            _delay_ms(20);
            // Flush TX (pretty sure it shouldn't have anything in it, but just
            // in case)
            spi_start();
            spi_transmit(0b11100001);
            spi_end();
            // Write payload byte
            spi_start();
            spi_transmit(0b10100000);
            spi_transmit(0b01011010);
            spi_end();
            // Enable transmitter
            CE = 1;
            // Wait 30 milliseconds, which should be more than plenty
            _delay_ms(30);
            // Disable transmitter
            CE = 0;
            // Flash out status
            spi_start();
            uint8_t data = spi_transmit(0xFF);
            spi_end();
            spi_start();
            spi_transmit(0b00100000 + 7);
            spi_transmit(0b01110000);
            spi_end();
//            flash_out(data);
        }
    }



}

