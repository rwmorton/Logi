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

    std::ostream& out = stream->get();

    switch((*vm.ram)(currentByte))
    {
        case LBI: //LBI $R1, BBB
        {
            std::string inst = (*vm.iset)((OpCode)((*vm.ram)(currentByte)));
            U8 R1{};
            Transform::byteToRegister((*vm.ram)(currentByte+1),R1);
            U1 byte = (U1)(*vm.ram)(currentByte+2);
            out << "$IP= " << inst << ", " << vm.registers.R_str((RegisterCodes)R1) << "= " << vm.registers.R((RegisterCodes)R1) << ", byte= " << static_cast<int>(byte) << '\n';
        }
        break;
        case LWI: //LWI $R1, BBW
        {
            std::string inst = (*vm.iset)((OpCode)((*vm.ram)(currentByte)));
            U8 R1{};
            Transform::byteToRegister((*vm.ram)(currentByte+1),R1);
            U2 word = Transform::bytecodeToWord(&(*vm.ram)(currentByte+2));
            out << "$IP= " << inst << ", " << vm.registers.R_str((RegisterCodes)R1) << "= " << vm.registers.R((RegisterCodes)R1) << ", word= " << word << '\n';
        }
        break;
        case LDI: //LDI $R1, BBD
        {
            std::string inst = (*vm.iset)((OpCode)((*vm.ram)(currentByte)));
            U8 R1{};
            Transform::byteToRegister((*vm.ram)(currentByte+1),R1);
            U4 dword = Transform::bytecodeToDWord(&(*vm.ram)(currentByte+2));
            out << "$IP= " << inst << ", " << vm.registers.R_str((RegisterCodes)R1) << "= " << vm.registers.R((RegisterCodes)R1) << ", dword= " << dword << '\n';
        }
        break;
        case LQI: //LQI $R1, BBQ
        {
            std::string inst = (*vm.iset)((OpCode)((*vm.ram)(currentByte)));
            U8 R1{};
            Transform::byteToRegister((*vm.ram)(currentByte+1),R1);
            U8 qword = Transform::bytecodeToQWord(&(*vm.ram)(currentByte+2));
            out << "$IP= " << inst << ", " << vm.registers.R_str((RegisterCodes)R1) << "= " << vm.registers.R((RegisterCodes)R1) << ", qword= " << qword << '\n';
        }
        break;
        case LF1I: //LF1I $F1, BBD
        {
            std::string inst = (*vm.iset)((OpCode)((*vm.ram)(currentByte)));
            F4 F1{};
            Transform::floatToRegister(&(*vm.ram)(currentByte+2),F1);
            F4 float_ = Transform::bytecodeToFloat(&(*vm.ram)(currentByte+2));
            out << "$IP= " << inst << ", " << vm.registers.RF_str((FloatRegisterCodes)F1) << "= " << vm.registers.RF((FloatRegisterCodes)F1) << ", float= " << float_ << '\n';
        }
        break;
        case LF2I: //LF2I $D1, BBQ
        {
            std::string inst = (*vm.iset)((OpCode)((*vm.ram)(currentByte)));
            F8 D1{};
            Transform::doubleToRegister(&(*vm.ram)(currentByte+2),D1);
            F8 double_ = Transform::bytecodeToDouble(&(*vm.ram)(currentByte+2));
            out << "$IP= " << inst << ", " << vm.registers.RD_str((DoubleRegisterCodes)D1) << "= " << vm.registers.RD((DoubleRegisterCodes)D1) << ", double= " << double_ << '\n';
        }
        break;
        case LAD: //LAD $R1, address = BBQ
        {
            std::string inst = (*vm.iset)((OpCode)((*vm.ram)(currentByte)));
            U8 R1{};
            Transform::addressToRegister(&(*vm.ram)(currentByte+1),R1);
            U8 addr = Transform::bytecodeToQWord(&(*vm.ram)(currentByte+2));
            out << "$IP= " << inst << ", " << vm.registers.R_str((RegisterCodes)R1) << "= " << vm.registers.R((RegisterCodes)R1) << ", addr= " << addr << '\n';
        }
        break;
        case LAI: //LAI $R1,$R2,qword,  BBBQ
        {
            std::string inst = (*vm.iset)((OpCode)((*vm.ram)(currentByte)));
            U8 R1{},R2{};
            Transform::byteToRegister((*vm.ram)(currentByte+1),R1);
            Transform::byteToRegister((*vm.ram)(currentByte+2),R2);
            U8 addr = Transform::bytecodeToQWord(&(*vm.ram)(currentByte+3));
            out << "$IP= " << inst << ", " << vm.registers.R_str((RegisterCodes)R1) << "= " << vm.registers.R((RegisterCodes)R1) << ", " << vm.registers.R_str((RegisterCodes)R2) << "= " << vm.registers.R((RegisterCodes)R2) << ", addr= " << addr << '\n';
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
            std::string inst = (*vm.iset)((OpCode)((*vm.ram)(currentByte)));
            U8 R1{},R2{};
            Transform::byteToRegister((*vm.ram)(currentByte+1),R1);
            Transform::byteToRegister((*vm.ram)(currentByte+2),R2);
            out << "$IP= " << inst << ", " << vm.registers.R_str((RegisterCodes)R1) << "= " << vm.registers.R((RegisterCodes)R1) << ", " << vm.registers.R_str((RegisterCodes)R2) << "= " << vm.registers.R((RegisterCodes)R2) << '\n';
        }
        break;
        case LF1: // LF1 $F1,D       BBD
        case SF1:
        {
            std::string inst = (*vm.iset)((OpCode)((*vm.ram)(currentByte)));
            U8 R1{};
            F4 F1{};
            Transform::floatToRegister(&(*vm.ram)(currentByte+1),F1);
            Transform::byteToRegister((*vm.ram)(currentByte+2),R1);
            out << "$IP= " << inst << ", " << vm.registers.RF_str((FloatRegisterCodes)F1) << "= " << vm.registers.RF((FloatRegisterCodes)F1) << ", " << vm.registers.R_str((RegisterCodes)R1) << "= " << vm.registers.R((RegisterCodes)R1) << '\n';
        }
        break;
        case LF2: // LF2 $D1,Q       BBQ
        case SF2:
        {
            std::string inst = (*vm.iset)((OpCode)((*vm.ram)(currentByte)));
            U8 R1{};
            F8 D1{};
            Transform::doubleToRegister(&(*vm.ram)(currentByte+1),D1);
            Transform::byteToRegister((*vm.ram)(currentByte+2),R1);
            out << "$IP= " << inst << ", " << vm.registers.RD_str((DoubleRegisterCodes)D1) << "= " << vm.registers.RD((DoubleRegisterCodes)D1) << ", " << vm.registers.R_str((RegisterCodes)R1) << "= " << vm.registers.R((RegisterCodes)R1) << '\n';
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
            // ADD $R1, $R2, $R3
            // $R1 = $R2 + $R3
            std::string inst = (*vm.iset)((OpCode)((*vm.ram)(currentByte)));
            U8 R1,R2,R3;
            Transform::byteToRegister((*vm.ram)(currentByte+1),R3);
            Transform::byteToRegister((*vm.ram)(currentByte+2),R1);
            Transform::byteToRegister((*vm.ram)(currentByte+3),R2);
            out << "$IP= " << inst << ", " << vm.registers.R_str((RegisterCodes)R1) << "= " << vm.registers.R((RegisterCodes)R1);
            out << ", " << vm.registers.R_str((RegisterCodes)R2) << "= " << vm.registers.R((RegisterCodes)R2);
            out << ", " << vm.registers.R_str((RegisterCodes)R3) << "= " << vm.registers.R((RegisterCodes)R3) << '\n';
        }
        break;
        case INT: // INT #vector BB
        {
            //
            // TODO!!!
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
        case DADD: // DADD $D1,$D2,$D3 BBBB
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
