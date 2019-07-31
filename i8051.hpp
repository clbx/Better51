#include <stdint.h>
#include <iostream>

class i8051{

    public:

        uint16_t pc; //Program Counter
        uint8_t sp; //Stack Pointer
        uint16_t dp; //Data Pointer (probably never used in this scenario)

        uint8_t rom[4096]; //4k byte ROM
        uint8_t memory[128]; //128 byte RAM

        uint8_t a; //Accumulator
        uint8_t b; //B register

        uint8_t psw; //Program status word

        uint16_t timer0; //First timer
        uint16_t timer1; //Second timer

        i8051();
        void reset();
        void execute(uint8_t);
        uint8_t nextByte();
        int getRegAddr(int);
        void setParity(); 




        










};