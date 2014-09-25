
Port::Port(char* ddr, char* port, char* pin) {
    this.ddr = ddr;
    this.port = port;
    this.pin = pin;
}

GPIO::GPIO(Port* port, char pinNumber) {
    this.port = port;
    this.mask = 1 << pinNumber;
}

GPIO::setDirection(bool isOutput) {
    if(isOutput) {
        *(this.port->ddr) |= this.mask;
    } else {
        *(this.port->ddr) &= ~this.mask;
    }
}

GPIO::setPort(bool isOn) {
    if(isOn) {
        *(this.port->port) |= this.mask;
    } else {
        *(this.port->port) &= ~this.mask;
    }
}

GPIO::getPin() {
    return *(this.port->pin) & this.mask != 0;
}

NRF24L01::NRF24L01(GPIO* clock, GPIO* select, GPIO* mosi, GPIO* miso) {
    this.clock = clock;
    this.select = select;
    this.mosi = mosi;
    this.miso = miso;
}










