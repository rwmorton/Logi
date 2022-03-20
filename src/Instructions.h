#ifndef __LOGI_INSTRUCTIONS_H__
#define __LOGI_INSTRUCTIONS_H__

namespace Logi
{

//load instructions
void handle_LBI();
void handle_LWI();
void handle_LDI();
void handle_LQI();
void handle_LF1I();
void handle_LF2I();
void handle_LAD();
void handle_LAI();
void handle_LB();
void handle_LW();
void handle_LD();
void handle_LQ();
void handle_LF1();
void handle_LF2();

//store instructions
void handle_SB();
void handle_SW();
void handle_SD();
void handle_SQ();
void handle_SF1();
void handle_SF2();

//push/pop instructions
void handle_PUSHB();
void handle_PUSHW();
void handle_PUSHD();
void handle_PUSHQ();
void handle_PUSHF1();
void handle_PUSHF2();
void handle_POPB();
void handle_POPW();
void handle_POPD();
void handle_POPQ();
void handle_POPF1();
void handle_POPF2();

//move instructions
void handle_MOV();
void handle_MOVF();
void handle_MOVD();

//jump instructions
void handle_JMP();
void handle_JE();
void handle_JNE();

//shift instructions
void handle_SLT();

//interrupt instructions
void handle_INT();
void handle_DI();
void handle_EI();
void handle_HALT();
void handle_NOP();

//bitwise instructions
void handle_AND();
void handle_OR();
void handle_XOR();
void handle_NOT();
void handle_BT();
void handle_BS();

//shift instructions
void handle_SRA();
void handle_SRL();
void handle_SL();

//integer math instructions
void handle_ADD();
void handle_SUB();
void handle_MULT();
void handle_DIV();

//??
void handle_CAST_IF() {}
void handle_CAST_ID() {}
void handle_CAST_FI() {}
void handle_CAST_FD() {}
void handle_CAST_DI() {}
void handle_CAST_DF() {}

//float math instructions
void handle_FADD();
void handle_FSUB();
void handle_FMULT();
void handle_FDIV();
void handle_FSLT();

//double math instructions
void handle_DADD();
void handle_DSUB();
void handle_DMULT();
void handle_DDIV();
void handle_DSLT();

} //namespace Logi

#endif //__LOGI_INSTRUCTIONS_H__
