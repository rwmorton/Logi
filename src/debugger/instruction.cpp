//Logi includes
#include "../Debugger.h"
#include "../VirtualMachine.h"

//temp
#include <iostream>

namespace Logi
{

//
// display in assembler and binary
//
void Debugger::instruction(const U8 address) const
{
    U8 currentByte = address; //lookahead from passed address
    U1 raw[11]; //buffer to hold binary representation

    switch((*vm.ram)(currentByte))
    {
        case LBI: //LBI $R1, BBB
        {
            //
        }
        break;
        case LWI: //LWI $R1, BBW
        {
            //
        }
        break;
        case LDI: //LDI $R1, BBD
        {
            //
        }
        break;
        case LQI: //LQI $R1, BBQ
        {
            //
        }
        break;
        case LF1I: //LF1I $R1, BBD
        {
            //
        }
        break;
        case LF2I: //LF2I $R1, BBQ
        {
            //
        }
        break;
        case LAD: //LAD $R1, address = BBQ
        {
            //
        }
        break;
        case LAI: //LAI $R1,$R2,qword,  BBBQ
        {
            //
        }
        break;
        case LB: // LB $R1,$R2,     BBB
        case LW:
        case LD:
        case LQ:
        case SB: // SB $R1,$R2,     BBB
        case SW:
        case SD:
        case SQ:
        case MOV:
        {
            //
        }
        break;
        case LF1: // LF1 $F1,$R1,       BBB
        case SF1:
        {
            //
        }
        break;
        case LF2: // LF2 $D1,$R1,       BBB
        case SF2:
        {
            //
        }
        break;
        case PUSHB: // PUSHB $R1, BB
        case PUSHW:
        case PUSHD:
        case PUSHQ:
        case POPB:
        case POPW:
        case POPD:
        case POPQ:
        {
            //
        }
        break;
        case PUSHF1: // PUSHF1 $F
        case POPF1:
        {
            //
        }
        break;
        case PUSHF2:
        case POPF2:
        {
            //
        }
        break;
        case MOVF: // MOVF $F1,$F2
        {
            //
        }
        break;
        case MOVD: // MOVD $D1,$D2
        {
            //
        }
        break;
        case NOT:
        case BS:
        {
            //
        }
        break;
        case JMP:
        {
            //
        }
        break;
        case JE:
        case JNE:
        case SLT:
        case AND:
        case OR:
        case XOR:
        case BT:
        case SRA:
        case SRL:
        case SL:
        case ADD:
        case SUB:
        case MULT:
        {
            //
        }
        break;
        case INT: // INT #vector BB
        {
            //
        }
        break;
        case EI:
        case DI:
        case HALT:
        case NOP:
        {
            //
        }
        break;
        case DIV: // DIV $R1,$R2,$R3,$R4
        {
            //
        }
        break;
        case CAST_IF: // CAST_IF $R,$F
        {
            //
        }
        break;
        case CAST_ID: // CAST_ID $R,$D
        {
            //
        }
        break;
        case CAST_FI: // CAST_FI $F,$R
        {
            //
        }
        break;
        case CAST_FD: // CAST_FD $F,$D
        {
            //
        }
        break;
        case CAST_DI: // CAST_DI $D,$R
        {
            //
        }
        break;
        case CAST_DF: // CAST_DF $D,$F
        {
            //
        }
        break;
        case FADD: // FADD $F1,$F2,$F3 BBBB
        case FSUB:
        case FMULT:
        case FDIV:
        case FSLT:
        {
            //
        }
        break;
        case DADD: // FADD $F1,$F2,$F3 BBBB
        case DSUB:
        case DMULT:
        case DDIV:
        case DSLT:
        {
            //
        }
        break;
        default:
        {
            throw std::runtime_error("DEBUGGER: bad opcode.");
        }
    }
}

} //namespace Logi
