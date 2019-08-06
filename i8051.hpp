#include <stdint.h>
#include <iostream>

#define BYTE_TO_BINARY_PATTERN "%c %c %c %c  %c %c %c %c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 
//fuck std for having hex and octal but no binary

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
        bool load(const char*);
        void execute(uint8_t);
        void tick();


        uint8_t nextByte();
        int getRegAddr(int);
        
        void setParity(); 
        void setCarries();
        void overflow(int);


        void ADD(int);


};