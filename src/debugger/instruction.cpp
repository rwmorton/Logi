//Logi includes
#include "../Debugger.h"
#include "../VirtualMachine.h"

//std includes
#include <iomanip>

namespace Logi
{

//
// display in assembler and binary
//
void Debugger::instruction(const U8 address)
{
    U8 currentByte = address; //lookahead from passed address
    U1 raw[11]; //buffer to hold binary representation

    std::ostream& out = stream->get();
    print.begin(currentByte);           //begin the printer on current byte

    //first dump ram
    dump(0,vm.executable.totalSize-1);
    out << "\nLAST INSTRUCTION: ";

    //instruction string
    std::string inst = (*vm.iset)((OpCode)((*vm.ram)(currentByte)));

    switch((*vm.ram)(currentByte))
    {
        case LBI: //LBI $R1, BBB
        {
            print.I().R().B();
        }
        break;
        case LWI: //LWI $R1, BBW
        {
            print.I().R().W();
        }
        break;
        case LDI: //LDI $R1, BBD
        {
            print.I().R().D();
        }
        break;
        case LQI: //LQI $R1, BBQ
        {
            print.I().R().Q();
        }
        break;
        case LF1I: //LF1I $F1, BBD
        {
            print.I().RF().F1();
        }
        break;
        case LF2I: //LF2I $D1, BBQ
        {
            print.I().RD().F2();
        }
        break;
        case LAD: //LAD $R1, address = BBQ
        {
            print.I().R().A();
        }
        break;
        case LAI: //LAI $R1,$R2,qword,  BBBQ
        {
            print.I().R(2).Q();
        }
        break;
        case LB: // LB $R1,$R2,     BBB
        case SB: // SB $R1,$R2,     BBB
        case LW:
        case SW:
        case LD:
        case SD:
        case LQ:
        case SQ:
        case MOV:
        {
            print.I().R().R_end();
        }
        break;
        case LF1: // LF1 $F1,D       BBD
        case SF1:
        {
            print.I().RF().F1();
        }
        break;
        case LF2: // LF2 $D1,Q       BBQ
        case SF2:
        {
            print.I().RD().F2();
        }
        break;
        case PUSHB: // PUSHB $R1, BB
        case POPB:
        case PUSHW:
        case POPW:
        case PUSHD:
        case POPD:
        case PUSHQ:
        case POPQ:
        {
            print.I().R_end();
        }
        break;
        case PUSHF1: // PUSHF1 $F
        case POPF1:
        {
            print.I().RF_end();
        }
        break;
        case PUSHF2:
        case POPF2:
        {
            print.I().RD_end();
        }
        break;
        case MOVF: // MOVF $F1,$F2
        {
            print.I().RF().RF_end();
        }
        break;
        case MOVD: // MOVD $D1,$D2
        {
            print.I().RD().RD_end();
        }
        break;
        case NOT:
        case BS:
        {
            print.I().R().R_end();
        }
        break;
        case JMP:
        {
            print.I().R_end();
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
            print.I().R(2).R_end();
        }
        break;
        case INT: // INT #vector BB
        {
            print.I().B();
        }
        break;
        case EI:
        case DI:
        case HALT:
        case NOP:
        {
            print.I_end();
        }
        break;
        case DIV: // DIV $R1,$R2,$R3,$R4
        {
            print.I().R(3).R_end();
        }
        break;
        case CAST_IF: // CAST_IF $R,$F
        {
            print.I().R().RF_end();
        }
        break;
        case CAST_ID: // CAST_ID $R,$D
        {
            print.I().R().RD_end();
        }
        break;
        case CAST_FI: // CAST_FI $F,$R
        {
            print.I().RF().R_end();
        }
        break;
        case CAST_FD: // CAST_FD $F,$D
        {
            print.I().RF().RD_end();
        }
        break;
        case CAST_DI: // CAST_DI $D,$R
        {
            print.I().RD().R_end();
        }
        break;
        case CAST_DF: // CAST_DF $D,$F
        {
            print.I().RD().RF_end();
        }
        break;
        case FADD: // FADD $F1,$F2,$F3 BBBB
        case FSUB:
        case FMULT:
        case FDIV:
        case FSLT:
        {
            print.I().RF(2).RF_end();
        }
        break;
        case DADD: // DADD $D1,$D2,$D3 BBBB
        case DSUB:
        case DMULT:
        case DDIV:
        case DSLT:
        {
            print.I().RD(2).RD_end();
        }
        break;
        default:
        {
            throw std::runtime_error("DEBUGGER: bad opcode.");
        }
    }
}

} //namespace Logi
