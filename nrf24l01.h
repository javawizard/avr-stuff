
class Port {
    public:
        char* ddr;
        char* port;
        char* pin;
        Port(char* ddr, char* port, char* pin);
}

class GPIO {
    public:
        Port* port;
        char* mask;
        // Constructed as e.g. GPIO(&DDRA, &PORTA, &PINA, _bv(7))
        GPIO(Port* port, char pinNumber);
        void setDirection(bool isOutput);
        void setPort(bool value);
        bool getPin();
}

class NRF24L01 {
    public:
        GPIO* clock;
        GPIO* select;
        GPIO* mosi;
        GPIO* miso;
        NRF24L01(GPIO* clock, GPIO* select, GPIO* mosi, GPIO* miso);
        
}


















