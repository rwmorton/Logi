//Logi includes
#include "BytecodeFromASM.h"
#include "Assembler.h"

namespace Logi
{

BytecodeFromASM::BytecodeFromASM() : currentByte{0} {}

//
// initialize
//
void BytecodeFromASM::init()
{
    currentByte = 0;
}

//
// begin at given line.
//
void BytecodeFromASM::begin(const Line& line)
{
    token_it = line.token_iter();

    switch(InstructionSet::OpCode_fromStr(token_it->str))
    {
        case LBI: //LBI $R1, BBB
        case LWI: //LWI $R1, BBW
        case LDI: //LDI $R1, BBD
        case LQI: //LQI $R1, BBQ
        {
            I().R().C();
        }
        break;
        case LF1I: //LF1I $F1, BBD
        {
            I().F().C();
        }
        break;
        case LF2I: //LF2I $D1, BBQ
        {
            I().D().C();
        }
        break;
        case LAD: //LAD $R1, address = BBQ
        {
            I().R().A();
        }
        break;
        case LAI: //LAI $R1,$R2,qword,  BBBQ
        {
            I().R(2).C();
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
        {
            I().R(2);
        }
        break;
        case LF1: // LF1 $F1,$R1,       BBB
        case SF1:
        {
            I().F().R();
        }
        break;
        case LF2: // LF2 $D1,$R1,       BBB
        case SF2:
        {
            I().D().R();
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
        case JMP:
        {
            I().R();
        }
        break;
        case PUSHF1: // PUSHF1 $F
        case POPF1:
        {
            I().F();
        }
        break;
        case PUSHF2:
        case POPF2:
        {
            I().D();
        }
        break;
        case MOVF: // MOVF $F1,$F2
        {
            I().F(2);
        }
        break;
        case MOVD: // MOVD $D1,$D2
        {
            I().D(2);
        }
        break;
        case MOV: // MOV $R1,$R2
        case NOT: // NOT $R1,$R2
        case BS: // BS $R1,$R2
        {
            I().R(2);
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
            I().R(3);
        }
        break;
        case INT: // INT #vector BB
        {
            I().C();
        }
        break;
        case EI:
        case DI:
        case HALT:
        case NOP:
        {
            I();
        }
        break;
        case DIV: // DIV $R1,$R2,$R3,$R4
        {
            I().R(4);
        }
        break;
        case CAST_IF: // CAST_IF $R,$F
        {
            I().R().F();
        }
        break;
        case CAST_ID: // CAST_ID $R,$D
        {
            I().R().D();
        }
        break;
        case CAST_FI: // CAST_FI $F,$R
        {
            I().F().R();
        }
        break;
        case CAST_FD: // CAST_FD $F,$D
        {
            I().F().D();
        }
        break;
        case CAST_DI: // CAST_DI $D,$R
        {
            I().D().R();
        }
        break;
        case CAST_DF: // CAST_DF $D,$F
        {
            I().D().F();
        }
        break;
        case FADD: // FADD $F1,$F2,$F3 BBBB
        case FSUB:
        case FMULT:
        case FDIV:
        case FSLT:
        {
            I().F(3);
        }
        break;
        case DADD: // DADD $D1,$D2,$D3 BBBB
        case DSUB:
        case DMULT:
        case DDIV:
        case DSLT:
        {
            I().D(3);
        }
        break;
        case BAD:
        default:
        {
            throw std::runtime_error("BYTECODE_FROM_ASM: bad opcode.");
        }
    }
}

//
// get current byte for address assignment.
//
const U8 BytecodeFromASM::getCurrentByte() const
{
    return currentByte;
}

//
// Load instruction (single byte)
//
BytecodeFromASM& BytecodeFromASM::I()
{
    bytecode.push_back(InstructionSet::OpCode_fromStr(token_it->str));
    ++token_it;
    currentByte++;

    return *this;
}

//
// Load identifier (resolved to address of 8 bytes).
//
BytecodeFromASM& BytecodeFromASM::A()
{
    U1 addr[8];
    Transform::qwordToBytecode(token_it->val.S8_val,&addr[0]);
    
    for(int i=0; i<8; i++)
    {
        bytecode.push_back(addr[i]);
        currentByte++;
    }

    token_it++; //next token

    return *this;
}

//
// Load byte constant (byte constant is 8 bytes long).
//
BytecodeFromASM& BytecodeFromASM::B()
{
    U1 qword_bytes[8];
    Transform::qwordToBytecode(token_it->val.S8_val,&qword_bytes[0]);
    
    for(int i=0; i<8; i++)
    {
        bytecode.push_back(qword_bytes[i]);
        currentByte++;
    }

    token_it++; //next token

    return *this;
}

//
// Load constant (also 8 bytes long).
//
BytecodeFromASM& BytecodeFromASM::C()
{
    U1 qword_bytes[8];
    Transform::qwordToBytecode(token_it->val.S8_val,&qword_bytes[0]);
    
    for(int i=0; i<8; i++)
    {
        bytecode.push_back(qword_bytes[i]);
        currentByte++;
    }

    token_it++; //next token

    return *this;
}

//
// Load integer register (single byte up to count times).
//
BytecodeFromASM& BytecodeFromASM::R(unsigned int count)
{
    for(int i=0; i<count; i++)
    {
        bytecode.push_back(Registers::R_fromStr(token_it->str));
        ++token_it;
        currentByte++;
    }

    return *this;
}

//
// Load float register (single byte up to count times).
//
BytecodeFromASM& BytecodeFromASM::F(unsigned int count)
{
    for(int i=0; i<count; i++)
    {
        bytecode.push_back(Registers::RF_fromStr(token_it->str));
        ++token_it;
        currentByte++;
    }

    return *this;
}

//
// Load double register (single byte up to count times).
//
BytecodeFromASM& BytecodeFromASM::D(unsigned int count)
{
    for(int i=0; i<count; i++)
    {
        bytecode.push_back(Registers::RD_fromStr(token_it->str));
        ++token_it;
        currentByte++;
    }

    return *this;
}

//
// write bytecode to stream.
//
std::ostream& operator<<(std::ostream& out,const BytecodeFromASM& li)
{
    std::vector<U1>::const_iterator i = li.bytecode.begin();
    while(i != li.bytecode.end())
    {
        out << std::hex << std::showbase << static_cast<int>(*i) << ' ';
        ++i;
    }

    out << std::dec;

    return out;
}

} //namespace Logi
