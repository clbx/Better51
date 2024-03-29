#include "i8051.hpp"

i8051::i8051(){
    reset();
}

bool i8051::load(const char* filename){
    reset();
    FILE* file = fopen(filename,"r");
    if(file == nullptr){
        return false;
    }
    fread(rom,1,sizeof(rom),file);
    fclose(file);

    return true;
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

uint8_t i8051::nextByte(){
    pc++;
    return rom[pc];
}

int i8051::getRegAddr(int reg){
    return reg + (8*((psw & 0x18) >> 3)); //0001 1000  where the psw holds the current register bank;
}

void i8051::setParity(){
    //Set parity bit in psw
    unsigned int v = a;
    unsigned int c = 0;
    for(c = 0; v; c++){
        v &= v - 1; //thanks brian 
    }
    if(c%2 == 0){
        psw = psw >> 1; //drop the lowest bit
        psw = psw << 1; // 1000 0001  -> 0100 0000 -> 1000 0000
    } else{
        psw = psw | 0x01; //Set the lowest bit 1101 1100 | 0000 0001 = 1101 1101
    }
}

// carry  |  aux carry | Flag 0 | reg bank 1 | reg bank 0 | Overflow | user deniable | parity | 
//  0x80       0x40       0x20      0x10         0x08        0x04        0x02           0x01
/** ADD Opcode 
 *  Adds and then, does carry logic
 */


//This function is from jarikomppa's emu8051 project. I had a lot of trouble figuring out a better way to 
//get the overflow flags. 
void i8051::overflow(int value1, int value2, int acc){
    psw = psw & 0x59;   //0011 1011  to clear carry bits

    /* Carry: overflow from 7th bit to 8th bit */
    int carry = ((value1 & 255) + (value2 & 255) + acc) >> 8;
    
    /* Auxiliary carry: overflow from 3th bit to 4th bit */
    int auxcarry = ((value1 & 7) + (value2 & 7) + acc) >> 3;
    
    /* Overflow: overflow from 6th or 7th bit, but not both */
    int overflow = (((value1 & 127) + (value2 & 127) + acc) >> 7)^carry;

    if(carry){psw = psw | 0x80;}
    if(auxcarry){psw = psw | 0x40;}
    if(overflow){psw = psw | 0x04;}
}



void i8051::ADD(int val){
    overflow(a,val,0);
    a = a + val;
}

void i8051::ADDC(int val){
    overflow(a,val,psw&0x80);
    a = a + val;
}


void i8051::tick(){
    printf("tick\n");
    execute(rom[pc]);
}



void i8051::execute(uint8_t op){
    
    setParity();

    printf("Execute OP: %X\n", op);


    switch(op){
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
            ADD(nextByte());
        } break;
        case 0x25:{ //ADD A, iram addr
            ADD(memory[nextByte()]);
        } break;
        case 0x26:{ //ADD A, @R0
            ADD(memory[memory[getRegAddr(0)]]);
        } break;
        case 0x27:{ //ADD A, @R1
            ADD(memory[memory[getRegAddr(1)]]);
        } break;
        case 0x28:{ //ADD A, R0
            ADD(memory[getRegAddr(0)]);
        } break;
        case 0x29:{ //ADD A, R1
            ADD(memory[getRegAddr(1)]);
        } break;
        case 0x2A:{ //ADD A, R2
            ADD(memory[getRegAddr(2)]);
        } break;
        case 0x2B:{ //ADD A, R3
            ADD(memory[getRegAddr(3)]);
        } break;
        case 0x2C:{ //ADD A, R4
            ADD(memory[getRegAddr(4)]);
        } break;
        case 0x2D:{ //ADD A, R5
            ADD(memory[getRegAddr(5)]);
        } break;
        case 0x2E:{ //ADD A, R6
            ADD(memory[getRegAddr(6)]);
        } break;
        case 0x2F:{ //ADD A, R7
            ADD(memory[getRegAddr(7)]);
        } break;

        // ADDC - Add accumulator with carry
        case 0x34:{ //ADDC A, #DATA
            ADDC(nextByte());
        } break;
        case 0x35:{ //ADDC A, iram addr
            ADDC(memory[nextByte()]);
        } break;
        case 0x36:{ //ADDC A, @R0
            ADDC(memory[memory[getRegAddr(0)]]);
        } break;
        case 0x37:{ //ADDC A, @R1
            ADDC(memory[memory[getRegAddr(1)]]);
        } break;
        case 0x38:{ //ADDC A, R0
            ADDC(memory[getRegAddr(0)]);
        } break;
        case 0x39:{ //ADDC A, R1
            ADDC(memory[getRegAddr(1)]);
        } break;
        case 0x3A:{ //ADDC A, R2
            ADDC(memory[getRegAddr(2)]);
        } break;
        case 0x3B:{ //ADDC A, R3
            ADDC(memory[getRegAddr(3)]);
        } break;
        case 0x3C:{ //ADDC A, R4
            ADDC(memory[getRegAddr(4)]);
        } break;
        case 0x3D:{ //ADDC A, R5
            ADDC(memory[getRegAddr(5)]);
        } break;
        case 0x3E:{ //ADDC A, R6
            ADDC(memory[getRegAddr(6)]);
        } break;
        case 0x3F:{ //ADDC A, R7
            ADDC(memory[getRegAddr(7)]);
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

        //DA Decimal Adjust Accumulator
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

        } break;

        //DJNZ Decrement and Jump if not Zero
        case 0xD5:{ //DJNZ iram addr, reladdr

        }break;
        case 0xD8:{ //DJNZ R0, reladdr

        }break;
        case 0xD9:{ //DJNZ R1, reladdr

        }break;
        case 0xDA:{ //DJNZ R2, reladdr

        }break;
        case 0xDB:{ //DJNZ R3, reladdr

        }break;
        case 0xDC:{ //DJNZ R4, reladdr

        }break;
        case 0xDD:{ //DJNZ R5, reladdr

        }break;
        case 0xDE:{ //DJNZ R6, reladdr

        }break;
        case 0xDF:{ //DJNZ R7, reladdr

        }break;

        //INC Increments Register
        case 0x04:{ //INC A

        }break;
        case 0x05:{ //INC iram addr

        }break;
        case 0x06:{ //INC @R0

        }break;
        case 0x07:{ //INC @R1

        }break;
        case 0x08:{ //INC R0

        }break;
        case 0x09:{ //INC R1

        }break;
        case 0x0A:{ //INC R2

        }break;
        case 0x0B:{ //INC R3

        }break;
        case 0x0C:{ //INC R4

        }break;
        case 0x0D:{ //INC R5

        }break;
        case 0x0E:{ //INC R6

        }break;
        case 0x0F:{ //INC R7

        }break;
        case 0xA3:{ //INC DPTR

        }break;

        //JB Jump if bit set
        case 0x20:{ //JB bit addr,reladdr

        }break;

        //JBC Jump if Bit Set and Clear Bit
        case 0x10:{ //JBC bit addr,reladdr

        }break;

        //JC Jump if Carry Set
        case 0x40:{ //JC reladdr

        }break;

        //JMP Jump to Data Point + Accumulator
        case 0x73:{ //JMP @A+DPTR

        }break;

        //JNB Jump if Bit not set
        case 0x30:{ //JNP bit addr, reladdr

        }break;

        //JNC Jump if Carry not Set
        case 0x50:{ //JNC reladdr

        }break;

        //JNZ Jump if Accumulator Not Zero
        case 0x70:{ //JNZ Accumulator

        }break;

        //JZ Jump if Accumulator zero
        case 0x60:{ //JZ reladdr

        }break;

        //LCALL Long Call
        case 0x12:{ //LCALL code addr

        }break;

        //LJMP Long Jump
        case 0x02:{ //LJMP code addr

        }

        //MOV move memory
        case 0x76:{ // MOV @R0, #data

        }break;
        case 0x77:{ // MOV @R1, #data

        }break;
        case 0xF6:{ // MOV @R0, A

        }break;
        case 0xF7:{ // MOV @R1, A

        }break;
        case 0xA6:{ // MOV @R0, iram addr

        }break;
        case 0xA7:{ // MOV @R1, iram addr

        }break;
        case 0x74:{ // MOV A,#data

        }break;
        case 0xE6:{ // MOV A, @R0

        }break;
        case 0xE7:{ // MOV A, @R1

        }break;
        case 0xE8:{ // MOV A, R0

        }break;
        case 0xE9:{ // MOV A, R1

        }break;
        case 0xEA:{ // MOV A, R2

        }break;
        case 0xEB:{ // MOV A, R3

        }break;
        case 0xEC:{ // MOV A, R4

        }break;
        case 0xED:{ // MOV A, R5

        }break;
        case 0xEE:{ // MOV A, R6

        }break;
        case 0xEF:{ // MOV A, R7

        }break;
        case 0xE5:{ // MOV A, iram addr
 
        }break;
        case 0xA2:{ // MOV C, bit addr

        }break;
        case 0x90:{ // MOV DPTR, #data16

        }break;
        case 0x78:{ // MOV R0, #data

        }break;
        case 0x79:{ // MOV R1, #data

        }break;
        case 0x7A:{ // MOV R2, #data

        }break;
        case 0x7B:{ // MOV R3, #data

        }break;
        case 0x7C:{ // MOV R4, #data

        }break;
        case 0x7D:{ // MOV R5, #data

        }break;
        case 0x7E:{ // MOV R6, #data

        }break;
        case 0x7F:{ // MOV R6, #data

        }break;
        case 0xF8:{ // MOV R0, A

        }break;
        case 0xF9:{ // MOV R1, A 

        }break;
        case 0xFA:{ // MOV R2, A

        }break;
        case 0xFB:{ // MOV R3, A

        }break;
        case 0xFC:{ // MOV R4, A

        }break;
        case 0xFD:{ // MOV R5, A

        }break;
        case 0xFE:{ // MOV R6, A

        }break;
        case 0xFF:{ // MOV R7, A

        }break;
        case 0xA8:{ // MOV R0, iram addr

        }break;
        case 0xA9:{ // MOV R1, iram addr

        }break;
        case 0xAA:{ // MOV R2, iram addr

        }break;
        case 0xAB:{ // MOV R3, iram addr

        }break;
        case 0xAC:{ // MOV R4, iram addr

        }break;
        case 0xAD:{ // MOV R5, iram addr

        }break;
        case 0xAE:{ // MOV R6, iram addr

        }break;
        case 0xAF:{ // MOV R7, iram addr

        }break;
        case 0x92:{ // MOV bit addr, C

        }break;
        case 0x75:{ // MOV iram addr, #data

        }break;
        case 0x86:{ // MOV iram addr, @R0

        }break;
        case 0x87:{ // MOV iram addr, @R1

        }break;
        case 0x88:{ // MOV iram addr, R0

        }break;
        case 0x89:{ // MOV iram addr, R1

        }break;
        case 0x8A:{ // MOV iram addr, R2

        }break;
        case 0x8B:{ // MOV iram addr, R3

        }break;
        case 0x8C:{ // MOV iram addr, R4

        }break;
        case 0x8D:{ // MOV iram addr, R5

        }break;
        case 0x8E:{ // MOV iram addr, R6

        }break;
        case 0x8F:{ // MOV iram addr, R7

        }break;
        case 0xF5:{ // MOV iram addr, A

        }break;
        case 0x85:{ // MOV iram addr, iram addr

        }break;

        // MOVC Move Code Byte to Accumulator
        case 0x93:{ // MOVC A, @A+DPTR

        }break;
        case 0x83:{ // MOVC A, @A+PC

        }break;

        // MOVX Move Data To/Form External Memory **NOT IMPLEMENTING**
        // 0xF0 0xF2 0xF3 0xE0 0xE2 0xE3

        
        // MUL Multiply Accumulator by B
        case 0xA4:{ // MUL AB

        }

        //ORL Bitwise OR
        case 0x42:{ // ORL iram addr, A

        }break;
        case 0x43:{ // ORL iram addr, #data
        
        }break;
        case 0x44:{ // ORL A, #data

        }break;
        case 0x45:{ // ORL A, iram addr

        }break;
        case 0x46:{ // ORL A, @R0

        }break;
        case 0x47:{ // ORL A, @R1

        }break;
        case 0x48:{ // ORL A, R0 

        }break;
        case 0x49:{ // ORL A, R1

        }break;
        case 0x4A:{ // ORL A, R2

        }break;
        case 0x4B:{ // ORL A, R3

        }break;
        case 0x4C:{ // ORL A, R4

        }break;
        case 0x4D:{ // ORL A, R5

        }break;
        case 0x4E:{ // ORL A, R6

        }break;
        case 0x4F:{ // ORL A, R7

        }break;
        case 0x72:{ // ORL C, bit addr

        }break;
        case 0xA0:{ // ORL C, bit addr

        }break;

        //POP Pop value from stack
        case 0xD0:{ // POP iram addr

        }break;

        //PUSH Push Value onto stack
        case 0xC0:{ // PUSH iram addr

        }break;

        //RET Return from subroutine
        case 0x22:{ // RET

        }break;

        //RETI return from interrupt
        case 0x32:{ // RETI

        }break;

        //RL Rotate accumulator left
        case 0x23:{// RL A

        }break;

        //RLC Rotate Accumulator Left Through Carry
        case 0x33:{ //RLC A

        }break;

        //RR Rotate accumulator right
        case 0x03:{ //RR A
            
        }break;

        //RRC Rotate accumulator right through carry
        case 0x13:{

        }break;

        //SETB Set bit
        case 0xD3:{ // SETB C

        }break;
        case 0xD2:{// SETB bit addr
        
        }break;

        //SJMP Short jump
        case 0x80:{//SJMP reladdr
        
        }break;

        //SUBB Subtract from accumulator with borrow
        case 0x94:{//SUBB A,#data
        
        }break;
        case 0x95:{//SUBB A, iram addr

        }
        case 0x96:{//SUBB A, @R0
        
        }break;
        case 0x97:{//SUBB A, @R1

        }break;
        case 0x98:{//SUBB A, R0

        }break;
        case 0x99:{//SUBB A, R1

        }break;
        case 0x9A:{//SUBB A, R2

        }break;
        case 0x9B:{//SUBB A, R3

        }break;
        case 0x9C:{//SUBB A, R4

        }break;
        case 0x9D:{//SUBB A, R5

        }break;
        case 0x9E:{//SUBB A, R6

        }break;
        case 0x9F:{//SUBB A, R7

        }break;

        //SWAP Swap accumulator nibbles
        case 0xC4:{//SWAP A
        
        }

        //XCH Exchange bytes
        case 0xC6:{// XCH A, @R0
        
        }break;
        case 0xC7:{// XCH A, @R1 
        
        }break;
        case 0xC8:{// XCH A, R0 
        
        }break;
        case 0xC9:{// XCH A, R1 
        
        }break;
        case 0xCA:{// XCH A, R2
        
        }break;
        case 0xCB:{// XCH A, R3
        
        }break;
        case 0xCC:{// XCH A, R4 
        
        }break;
        case 0xCD:{// XCH A, R5 
        
        }break;
        case 0xCE:{// XCH A, R6 
        
        }break;
        case 0xCF:{// XCH A, R7 
        
        }break;
        case 0xC5:{// XCH A, iramaddr 
        
        }break;

        //XCHD Exchange digit
        case 0xD6:{// XCHD A, @R0
        
        }break;
        case 0xD7:{// XCHD A, @R1
        
        }break;

        //XRL Bitwise exclusive OR
        case 0x62:{// XRL iram addr, A

        }break;
        case 0x63:{// XRL iram addr, #data

        }break;
        case 0x64:{// XRL A, #data
        
        }break;
        case 0x65:{// XRL A, iram addr 
        
        }break;
        case 0x66:{// XRL A, @R0 
        
        }break;
        case 0x67:{// XRL A, @R1 
        
        }break;
        case 0x68:{// XRL A, R0 
        
        }break;
        case 0x69:{// nice XRL A,R1 
        
        }break;
        case 0x6A:{// XRL A, R2
        
        }break;
        case 0x6B:{// XRL A, R3 
        
        }break;
        case 0x6C:{// XRL A, R4 
        
        }break;
        case 0x6D:{// XRL A, R5 
        
        }break;
        case 0x6E:{// XRL A, R6 
        
        }break;
        case 0x6F:{// XRL A, R7 
        
        }break;
    }
    pc++;
}
