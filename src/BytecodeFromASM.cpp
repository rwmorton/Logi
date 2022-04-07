//Logi includes
#include "BytecodeFromASM.h"
#include "Assembler.h"

//std includes
#include <map>

//TEMP
#include <iostream>
using std::cout;
using std::endl;

namespace Logi
{

BytecodeFromASM::BytecodeFromASM() : currentByte{0}, symbolRepository{nullptr} {}

//
// initialize
//
void BytecodeFromASM::init(SymbolRepository* symbolRepository,const bool skip)
{
    currentByte = 0;    
    this->symbolRepository = symbolRepository;
    this->skip = skip;
}

//
// load bytecode at given line.
//
void BytecodeFromASM::load(const Line& line)
{
    if(symbolRepository == nullptr) throw std::runtime_error("BYTECODE_FROM_ASM: null pointer to SymbolRepository.");

    token_it = line.token_iter();

    switch(InstructionSet::OpCode_fromStr(token_it->str))
    {
        case LBI: //LBI $R1, BBB
        {
            I().R().B();
        }
        break;
        case LWI: //LWI $R1, BBW
        {
            I().R().W();
        }
        break;
        case LDI: //LDI $R1, BBD
        {
            I().R().D();
        }
        break;
        case LQI: //LQI $R1, BBQ
        {
            I().R().Q();
        }
        break;
        case LF1I: //LF1I $F1, BBD
        {
            I().RF().F1();
        }
        break;
        case LF2I: //LF2I $D1, BBQ
        {
            I().RD().F2();
        }
        break;
        case LAD: //LAD $R1, address = BBQ
        {
            I().R().A();
        }
        break;
        case LAI: //LAI $R1,$R2,qword,  BBBQ
        {
            I().R(2).A();
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
            I().RF().R();
        }
        break;
        case LF2: // LF2 $D1,$R1,       BBB
        case SF2:
        {
            I().RD().R();
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
            I().RF();
        }
        break;
        case PUSHF2:
        case POPF2:
        {
            I().RD();
        }
        break;
        case MOVF: // MOVF $F1,$F2
        {
            I().RF(2);
        }
        break;
        case MOVD: // MOVD $D1,$D2
        {
            I().RD(2);
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
            I().B();
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
            I().R().RF();
        }
        break;
        case CAST_ID: // CAST_ID $R,$D
        {
            I().R().RD();
        }
        break;
        case CAST_FI: // CAST_FI $F,$R
        {
            I().RF().R();
        }
        break;
        case CAST_FD: // CAST_FD $F,$D
        {
            I().RF().RD();
        }
        break;
        case CAST_DI: // CAST_DI $D,$R
        {
            I().RD().R();
        }
        break;
        case CAST_DF: // CAST_DF $D,$F
        {
            I().RD().RF();
        }
        break;
        case FADD: // FADD $F1,$F2,$F3 BBBB
        case FSUB:
        case FMULT:
        case FDIV:
        case FSLT:
        {
            I().RF(3);
        }
        break;
        case DADD: // DADD $D1,$D2,$D3 BBBB
        case DSUB:
        case DMULT:
        case DDIV:
        case DSLT:
        {
            I().RD(3);
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
    if(!skip) bytecode.push_back(InstructionSet::OpCode_fromStr(token_it->str));

    ++token_it;
    currentByte++;

    return *this;
}

//
// Load identifier (resolved to address of 8 bytes).
//
BytecodeFromASM& BytecodeFromASM::A()
{
    //as we cannot be guaranteed to get the correct
    //addresses we save an id/byte pair for later
    //assignment once all the assembler has been loaded.

    //first address resolution stage
    if(skip)
    {
        //first save the string label of this addressable
        //as well as the byte it begins on.
        addressesToResolve.insert(std::pair<std::string,U8>(token_it->str,currentByte));

        cout << "adding (" << token_it->str << ") to the list of addresses to resolve at (" << currentByte << ")" << endl;

        currentByte += 8;
    }
    else //save bytecode
    {
        //get address of identifier
        const int index = symbolRepository->getIdentifier(token_it->str);
        U8 addr = symbolRepository->getSymbolTable().getAddressable(index)->address;

        cout << "found identifier (" << token_it->str << ") with address (" << addr << ")" << endl;

        U1 bytes[8];
        Transform::qwordToBytecode(addr,&bytes[0]);
        for(int i=0; i<8; i++)
        {
            bytecode.push_back(bytes[i]);
            currentByte++;
        }
    }

    ++token_it; //next token

    return *this;
}

//
// Load single byte.
//
BytecodeFromASM& BytecodeFromASM::B()
{
    if(!skip)
    {
        U1 byte = static_cast<U1>(token_it->val.S8_val);
        bytecode.push_back(byte);
    }

    ++token_it; //next token
    currentByte++;

    return *this;
}

//
// Load word (2 bytes)
//
BytecodeFromASM& BytecodeFromASM::W()
{
    if(!skip)
    {
        U2 word = static_cast<U2>(token_it->val.S8_val);
        U1 bytes[2];
        Transform::wordToBytecode(word,&bytes[0]);
        for(int i=0; i<2; i++)
        {
            bytecode.push_back(bytes[i]);
            currentByte++;
        }
    }
    else
    {
        currentByte += 2;
    }

    ++token_it; //next token

    return *this;
}

//
// Load dword (4 bytes)
//
BytecodeFromASM& BytecodeFromASM::D()
{
    if(!skip)
    {
        U4 dword = static_cast<U4>(token_it->val.S8_val);
        U1 bytes[4];
        Transform::dwordToBytecode(dword,&bytes[0]);
        for(int i=0; i<4; i++)
        {
            bytecode.push_back(bytes[i]);
            currentByte++;
        }
    }
    else
    {
        currentByte += 4;
    }

    ++token_it; //next token

    return *this;
}

//
// Load qword (8 bytes)
//
BytecodeFromASM& BytecodeFromASM::Q()
{
    if(!skip)
    {
        U8 qword = static_cast<U8>(token_it->val.S8_val);
        U1 bytes[8];
        Transform::qwordToBytecode(qword,&bytes[0]);
        for(int i=0; i<8; i++)
        {
            bytecode.push_back(bytes[i]);
            currentByte++;
        }
    }
    else
    {
        currentByte += 8;
    }

    ++token_it; //next token

    return *this;
}

//
// Load single-precision float (4 bytes).
//
BytecodeFromASM& BytecodeFromASM::F1()
{
    if(!skip)
    {
        F4 float_ = static_cast<F4>(token_it->val.F8_val);
        U1 bytes[4];
        Transform::floatToBytecode(float_,&bytes[0]);
        for(int i=0; i<4; i++)
        {
            bytecode.push_back(bytes[i]);
            currentByte++;
        }
    }
    else
    {
        currentByte += 4;
    }

    ++token_it; //next token

    return *this;
}

//
// Load double-precision float (8 bytes).
//
BytecodeFromASM& BytecodeFromASM::F2()
{
    if(!skip)
    {
        F8 double_ = token_it->val.F8_val;
        U1 bytes[8];
        Transform::doubleToBytecode(double_,&bytes[0]);
        for(int i=0; i<8; i++)
        {
            bytecode.push_back(bytes[i]);
            currentByte++;
        }
    }
    else
    {
        currentByte += 8;
    }

    ++token_it; //next token

    return *this;
}

//
// Load constant (also 8 bytes long).
//
BytecodeFromASM& BytecodeFromASM::C()
{
    if(!skip)
    {
        U1 qword_bytes[8];
        Transform::qwordToBytecode(token_it->val.S8_val,&qword_bytes[0]);
        
        for(int i=0; i<8; i++)
        {
            bytecode.push_back(qword_bytes[i]);
            currentByte++;
        }
    }
    else
    {
        currentByte += 8;
    }

    ++token_it; //next token

    return *this;
}

//
// Load integer register (single byte up to count times).
//
BytecodeFromASM& BytecodeFromASM::R(unsigned int count)
{
    for(int i=0; i<count; i++)
    {
        if(!skip) bytecode.push_back(Registers::R_fromStr(token_it->str));
        ++token_it;
        currentByte++;
    }

    return *this;
}

//
// Load float register (single byte up to count times).
//
BytecodeFromASM& BytecodeFromASM::RF(unsigned int count)
{
    for(int i=0; i<count; i++)
    {
        if(!skip) bytecode.push_back(Registers::RF_fromStr(token_it->str));
        ++token_it;
        currentByte++;
    }

    return *this;
}

//
// Load double register (single byte up to count times).
//
BytecodeFromASM& BytecodeFromASM::RD(unsigned int count)
{
    for(int i=0; i<count; i++)
    {
        if(!skip) bytecode.push_back(Registers::RD_fromStr(token_it->str));
        ++token_it;
        currentByte++;
    }

    return *this;
}

//
// Get the addresses to resolve.
//
std::map<std::string,U8>& BytecodeFromASM::getAddressesToResolve()
{
    return addressesToResolve;
}

//
// Get the bytecode vector.
//
std::vector<U1>& BytecodeFromASM::getBytecode()
{
    return bytecode;
}

//
// Write the bytecode to file.
//
void BytecodeFromASM::write(std::ofstream& out) const
{
    std::vector<U1>::const_iterator i = bytecode.begin();
    while(i != bytecode.end())
    {
        out.put(*i); //write byte
        ++i;
    }
}

//
// write bytecode to stream.
//
std::ostream& operator<<(std::ostream& out,const BytecodeFromASM& li)
{
    std::vector<U1>::const_iterator i = li.bytecode.begin();
    while(i != li.bytecode.end())
    {
        //out << std::hex << std::showbase << static_cast<int>(*i) << ' ';
        out << static_cast<int>(*i) << ' ';
        ++i;
    }

    out << std::dec;

    return out;
}

} //namespace Logi
