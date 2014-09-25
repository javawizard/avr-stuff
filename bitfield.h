
typedef struct {
    uint8_t bit0:1;
    uint8_t bit1:1;
    uint8_t bit2:1;
    uint8_t bit3:1;
    uint8_t bit4:1;
    uint8_t bit5:1;
    uint8_t bit6:1;
    uint8_t bit7:1;
} _bitfield;

#define BITFIELD(port) ((volatile _bitfield*) &(port))


#define FPORTA BITFIELD(PORTA)
#define FPORTB BITFIELD(PORTB)
#define FPORTC BITFIELD(PORTC)

#define FPINA BITFIELD(PINA)
#define FPINB BITFIELD(PINB)
#define FPINC BITFIELD(PINC)

#define FDDRA BITFIELD(DDRA)
#define FDDRB BITFIELD(DDRB)
#define FDDRC BITFIELD(DDRC)


#define FPORTA0 (FPORTA->bit0)
#define FPORTA1 (FPORTA->bit1)
#define FPORTA2 (FPORTA->bit2)
#define FPORTA3 (FPORTA->bit3)
#define FPORTA4 (FPORTA->bit4)
#define FPORTA5 (FPORTA->bit5)
#define FPORTA6 (FPORTA->bit6)
#define FPORTA7 (FPORTA->bit7)

#define FPINA0 (FPINA->bit0)
#define FPINA1 (FPINA->bit1)
#define FPINA2 (FPINA->bit2)
#define FPINA3 (FPINA->bit3)
#define FPINA4 (FPINA->bit4)
#define FPINA5 (FPINA->bit5)
#define FPINA6 (FPINA->bit6)
#define FPINA7 (FPINA->bit7)

#define FDDRA0 (FDDRA->bit0)
#define FDDRA1 (FDDRA->bit1)
#define FDDRA2 (FDDRA->bit2)
#define FDDRA3 (FDDRA->bit3)
#define FDDRA4 (FDDRA->bit4)
#define FDDRA5 (FDDRA->bit5)
#define FDDRA6 (FDDRA->bit6)
#define FDDRA7 (FDDRA->bit7)


#define FPORTB0 (FPORTB->bit0)
#define FPORTB1 (FPORTB->bit1)
#define FPORTB2 (FPORTB->bit2)
#define FPORTB3 (FPORTB->bit3)
#define FPORTB4 (FPORTB->bit4)
#define FPORTB5 (FPORTB->bit5)
#define FPORTB6 (FPORTB->bit6)
#define FPORTB7 (FPORTB->bit7)

#define FPINB0 (FPINB->bit0)
#define FPINB1 (FPINB->bit1)
#define FPINB2 (FPINB->bit2)
#define FPINB3 (FPINB->bit3)
#define FPINB4 (FPINB->bit4)
#define FPINB5 (FPINB->bit5)
#define FPINB6 (FPINB->bit6)
#define FPINB7 (FPINB->bit7)

#define FDDRB0 (FDDRB->bit0)
#define FDDRB1 (FDDRB->bit1)
#define FDDRB2 (FDDRB->bit2)
#define FDDRB3 (FDDRB->bit3)
#define FDDRB4 (FDDRB->bit4)
#define FDDRB5 (FDDRB->bit5)
#define FDDRB6 (FDDRB->bit6)
#define FDDRB7 (FDDRB->bit7)




