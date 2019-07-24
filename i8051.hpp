#include <stdint.h>

class i8051{

    private:

        uint16_t pc; //Program Counter
        uint8_t sp; //Stack Pointer
        uint16_t dp; //Data Pointer (probably never used in this scenario)

        uint8_t memory[128]; //128 byte RAM
        uint8_t rom[4096]; //4k byte ROM

        uint8_t a; //Accumulator
        uint8_t b; //B register

        uint8_t psw; //Program status word

        uint16_t timer0; //First timer
        uint16_t timer1; //Second timer

        void execute(uint8_t);

    public:
        //Setters and getters for the debugger
        uint16_t getPC(){
            return pc;
        }
        void setPC(uint16_t val){
            pc = val;
        }

        uint8_t getSP(){
            return sp;
        }
        void setSP(uint8_t val){
            sp = val;
        }

        uint16_t getDP(){
            return dp;
        }
        void setDP(uint16_t val){
            dp = val;
        }

        










};