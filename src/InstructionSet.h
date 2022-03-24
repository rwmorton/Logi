#ifndef __LOGI_INSTRUCTION_SET_H__
#define __LOGI_INSTRUCTION_SET_H__

//Logi includes
#include "Registers.h"
#include "RAM.h"
#include "Transform.h"

//std includes
#include <vector>
#include <string>
#include <ostream>

namespace Logi
{

enum OpCodes
{
    //data transfer
    LBI = 0,    // 0x00 load byte immediate
    LWI,        // 0x01 load word immediate
    LDI,        // 0x02 load double word immediate
    LQI,        // 0x03 load quad word immediate
    LF1I,       // 0x04 load single-precision float immediate
    LF2I,       // 0x05 load double precision float immediate
    LAD,        // 0x06 load address direct
    LAI,        // 0x07 load address indirect
    LB,         // 0x08 load byte
    LW,         // 0x09 load word
    LD,         // 0x0a load double word
    LQ,         // 0x0b load quad word
    LF1,        // 0x0c load single-precision float
    LF2,        // 0x0d load double-precision float
    SB,         // 0x0e store byte
    SW,         // 0x0f store word
    SD,         // 0x10 store double word
    SQ,         // 0x11 store quad word
    SF1,        // 0x12 store single-precision float
    SF2,        // 0x13 store double-precision float
    PUSHB,      // 0x14 push byte on stack
    PUSHW,      // 0x15 push word on stack
    PUSHD,      // 0x16 push double word on stack
    PUSHQ,      // 0x17 push quad word on stack
    PUSHF1,     // 0x18 push single-precision float on stack
    PUSHF2,     // 0x19 push double-precision float on stack
    POPB,       // 0x1a pop byte off stack
    POPW,       // 0x1b pop word off stack
    POPD,       // 0x1c pop double word off stack
    POPQ,       // 0x1d pop quad word off stack
    POPF1,      // 0x1e pop single-precision float off stack
    POPF2,      // 0x1f pop double-precision float off stack
    MOV,        // 0x20 move an integer value
    MOVF,       // 0x21 move a single-precision float value
    MOVD,       // 0x22 move a double-precision float value
    //program control flow
    JMP,        // 0x23 unconditional jump
    JE,         // 0x24 jump if equal
    JNE,        // 0x25 jump if not equal
    SLT,        // 0x26 set if less than
    INT,        // 0x27 perform interrupt
    DI,         // 0x28 disable interrupts
    EI,         // 0x29 enable interrupts
    HALT,       // 0x2a stop the virtual machine
    NOP,        // 0x2b no-op
    //bitwise
    AND,        // 0x2c bitwise AND
    OR,         // 0x2d bitwise OR
    XOR,        // 0x2e bitwise XOR
    NOT,        // 0x2f bitwise NOT
    BT,         // 0x30 bitwise test
    BS,         // 0x31 bitwise set
    //shift
    SRA,        // 0x32 shift airthmetic right
    SRL,        // 0x33 shift logical right
    SL,         // 0x34 shift left
    //integer arithmetic
    ADD,        // 0x35 integer addition
    SUB,        // 0x36 integer subtraction
    MULT,       // 0x37 integer multiplication
    DIV,        // 0x38 integer division
    //conversion
    CAST_IF,    // 0x39 convert a single-precision float to an integer
    CAST_ID,    // 0x3a convert a double-precision float to an integer
    CAST_FI,    // 0x3b convert an integer to a single-precision float
    CAST_FD,    // 0x3c double-precision float to single-precision
    CAST_DI,    // 0x3d integer to double-precision float
    CAST_DF,    // 0x3e single-precision float to double-precision
    //floating point math
    FADD,       // 0x3f single-precision float addition
    FSUB,       // 0x40 single-precision float subtraction
    FMULT,      // 0x41 single-precision float multiplication
    FDIV,       // 0x42 single-precision float division
    FSLT,       // 0x43 single-precision float set if less than
    DADD,       // 0x44 double-precision float addition
    DSUB,       // 0x45 double-precision float subtraction
    DMULT,      // 0x46 double-precision float multiplication
    DDIV,       // 0x47 double-precision float division
    DSLT,       // 0x48 double-precision float set if less than
    BAD = -1,   // not an instruction
};

static const unsigned int NUM_INSTRUCTIONS {73};

class VirtualMachine;
class Registers;
class RAM;
class Transform;

class InstructionSet
{
    public:
        InstructionSet(VirtualMachine* vm);
        void setVM(VirtualMachine* vm);
        const std::string& operator()(OpCodes code) const;
        // debug
        void debug_pre() const;
        void debug_post() const;
        //load instructions
        void LBI() const;
        void LWI() const;
        void LDI() const;
        void LQI() const;
        void LF1I() const;
        void LF2I() const;
        void LAD() const;
        void LAI() const;
        void LB() const;
        void LW() const;
        void LD() const;
        void LQ() const;
        void LF1() const;
        void LF2() const;
        //store instructions
        void SB() const;
        void SW() const;
        void SD() const;
        void SQ() const;
        void SF1() const;
        void SF2() const;
        //push/pop instructions
        void PUSHB() const;
        void PUSHW() const;
        void PUSHD() const;
        void PUSHQ() const;
        void PUSHF1() const;
        void PUSHF2() const;
        void POPB() const;
        void POPW() const;
        void POPD() const;
        void POPQ() const;
        void POPF1() const;
        void POPF2() const;
        //move instructions
        void MOV() const;
        void MOVF() const;
        void MOVD() const;
        //jump instructions
        void JMP() const;
        void JE() const;
        void JNE() const;
        void SLT() const;
        void INT() const;
        void DI();
        void EI();
        void HALT() const;
        void NOP() const;
        //bitwise instructions
        void AND() const;
        void OR() const;
        void XOR() const;
        void NOT() const;
        void BT() const;
        void BS() const;
        //shift instructions
        void SRA() const;
        void SRL() const;
        void SL() const;
        //integer math instructions
        void ADD() const;
        void SUB() const;
        void MULT() const;
        void DIV() const;
        //??
        void CAST_IF() const {}
        void CAST_ID() const {}
        void CAST_FI() const {}
        void CAST_FD() const {}
        void CAST_DI() const {}
        void CAST_DF() const {}
        //float math instructions
        void FADD() const;
        void FSUB() const;
        void FMULT() const;
        void FDIV() const;
        void FSLT() const;
        //double math instructions
        void DADD() const;
        void DSUB() const;
        void DMULT() const;
        void DDIV() const;
        void DSLT() const;
    private:
        //handle interrupts
        void handleInterrupt(U1 byte) const;
        bool interruptOn;
        //
        VirtualMachine* vm; //test
        static const std::vector<std::string> _InstructionSetStrings;
};

} //namespace Logi

#endif //__LOGI_INSTRUCTION_SET_H__
