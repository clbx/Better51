#include "i8051.hpp"

i8051::i8051(){
    reset();
}

void i8051::reset(){
    memset(rom,0,sizeof(rom));
    memset(memory,0,sizeof(memory));   
    pc = 0;
    sp = 0;
    dp = 0;
    a = 0;
    b = 0;
    psw = 0;
    timer0 = 0;
    timer1 = 0; 
}

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
        case 0x5A:{ //ANL A,R2

        } break;
        case 0x5B:{ //ANL A,R3

        } break;
        case 0x5C:{ //ANL A,R4

        } break;
        case 0x5D:{ //ANL A,R5

        } break;
        case 0x5E:{ //ANL A,R6

        } break;
        case 0x5F:{ //ANL A,R7

        } break;
        case 0x82:{ //ANL C, Bit ADDR

        } break;
        case 0xB0:{ //ANL C, Bit ADDR?

        } break;

        //CJNE Compare and Jump if NOT equal
        case 0xB4:{ //CJNE A, #Data, reladdr

        } break;
        case 0xB5:{ //CJNE A, iram addr, reladdr

        } break;
        case 0xB6:{ //CJNE @R0, #data, reladdr

        } break;
        case 0xB7:{ //CJNE @R0, #data, reladdr

        } break;
        case 0xB8:{ //CJNE R0, #data, reladdr

        } break;
        case 0xB9:{ //CJNE R1, #data, reladdr

        } break;
        case 0xBA:{ //CJNE R1, #data, reladdr

        } break;
        case 0xBB:{ //CJNE R3, #data, reladdr

        } break;
        case 0xBC:{ //CJNE R4, #data, reladdr

        } break;
        case 0xBD:{ //CJNE R5, #data, reladdr

        } break;
        case 0xBE:{ //CJNE R6, #data, reladdr

        } break;
        case 0xBF:{ //CJNE R7, #data, reladdr

        } break;

        //CLR Clear Register
        case 0xC2:{ //CLR bit addr


        } break;
        case 0xC3:{ //CLR C
        } break;
        case 0xE4:{ //CLR A
        } break;

        //DA Decimad Adjust Accumulator
        case 0xD4:{

        }

        //DEC Decrement Register
        case 0x14:{ //DEC A

        }break;
        case 0x15:{ //DEC iram addr

        }break;
        case 0x16:{ //DEC @R0

        }break;
        case 0x17:{ //DEC @R1

        }break;
        case 0x18:{ //DEC R0

        }break;
        case 0x19:{ //DEC R1

        }break;
        case 0x1A:{ //DEC R2

        }break;
        case 0x1B:{ //DEC R3

        }break;
        case 0x1C:{ //DEC R4

        }break;
        case 0x1D:{ //DEC R5

        }break;
        case 0x1E:{ //DEC R6

        }break;
        case 0x1F:{ //DEC R7

        }break;

        //DIV Divides Accumulator by B
        case 0x84:{ //DIV AB

        }

        //DJNZ Decrement and Jump if not Zero


    }
}
