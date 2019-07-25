#include "i8051.hpp"


void i8051::execute(uint8_t op){
    switch(op){
        // NOP - No Opcode
        case 0x00: pc++; break;

        // ACALL - Absolute Call
        case 0x11:{ // ACALL page0

        } break;
        case 0x31:{ // ACALL page1

        } break;
        case 0x51:{ // ACALL page2

        } break;
        case 0x71:{ // ACALL page3

        } break;
        case 0x91:{ // ACALL page4

        } break;
        case 0xB1:{ // ACALL page5

        } break;
        case 0xD1:{ // ACALL page6

        } break;
        case 0xF1:{ // ACALL page7

        } break;

        // ADD - Add Accumulator
        case 0x24:{ //ADD A, #DATA

        } break;
        case 0x25:{ //ADD A, iram addr

        } break;
        case 0x26:{ //ADD A, @R0

        } break;
        case 0x27:{ //ADD A, @R1

        } break;
        case 0x28:{ //ADD A, R0

        } break;
        case 0x29:{ //ADD A, R1

        } break;
        case 0x2A:{ //ADD A, R2

        } break;
        case 0x2B:{ //ADD A, R3

        } break;
        case 0x2C:{ //ADD A, R4

        } break;
        case 0x2D:{ //ADD A, R5

        } break;
        case 0x2E:{ //ADD A, R6

        } break;
        case 0x2F:{ //ADD A, R7

        } break;

        // ADDC - Add accumulator with carry
        case 0x34:{ //ADDC A, #DATA

        } break;
        case 0x35:{ //ADDC A, iram addr

        } break;
        case 0x36:{ //ADDC A, @R0

        } break;
        case 0x37:{ //ADDC A, @R1

        } break;
        case 0x38:{ //ADDC A, R0

        } break;
        case 0x39:{ //ADDC A, R1

        } break;
        case 0x3A:{ //ADDC A, R2

        } break;
        case 0x3B:{ //ADDC A, R3

        } break;
        case 0x3C:{ //ADDC A, R4

        } break;
        case 0x3D:{ //ADDC A, R5

        } break;
        case 0x3E:{ //ADDC A, R6

        } break;
        case 0x3F:{ //ADDC A, R7

        } break;

        // AJMP - Absolute Jump
        case 0x01:{ //AJMP page0

        } break;
        case 0x21:{ //AJMP page1

        } break;
        case 0x41:{ //AJMP page2

        } break;
        case 0x61:{ //AJMP page3

        } break;
        case 0x81:{ //AJMP page4

        } break;
        case 0xA1:{ //AJMP page5

        } break;
        case 0xC1:{ //AJMP page6

        } break;
        case 0xE1:{ //AJMP page7

        } break;

        // ANL - Bitwise AND
        case 0x52:{ //ANL iram addr,A

        } break;
        case 0x53:{ //ANL iram addr,#data

        } break;
        case 0x54:{ //ANL A,#data

        } break;
        case 0x55:{ //ANL A,iram addr

        } break;
        case 0x56:{ //ANL A,@R0

        } break;
        case 0x57:{ //ANL A,@R0

        } break;
        case 0x58:{ //ANL A,R0

        } break;
        case 0x59:{ //ANL A,R1

        } break;


    }
}
