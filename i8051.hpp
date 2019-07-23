#include <stdint.h>

class i8051{

    private:

        uint16_t pc; //Program Counter

        uint8_t memory[128]; //128 byte RAM
        uint8_t rom[64000]; //64k byte ROM

        uint8_t a; //Accumulator
        uint8_t b; //B register

        uint8_t psw; //Program status word

        void execute(uint8_t);


        void ACALL();
        void ADD();
        void AJMP();
        void ANL();
        void CJNE();
        void CLR();
        void CPL();
        void DA();
        void DEC();
        void DIV();
        void DJNZ();
        void INC();
        void JB();
        void JBC();
        void JMP();
        void JNB();
        void JNC();
        void JNZ();
        void JZ();
        void LCALL();
        void LJMP();
        void MOV();
        void MOVC();
        void MOVX();
        void MUL();
        void NOP();
        void ORL();
        void POP();
        void PUSH();
        void RET();
        void RETI();
        void RL();
        void RLC();
        void RR();
        void RRC();
        void SETB();
        void SJMP();
        void SUBB();
        void SWAP();
        void XCH();
        void XCHD();
        void XRL();


};