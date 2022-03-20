//Logi includes
#include "Validator.h"

namespace Logi
{

const std::string Validator::OPCODE {"opcode = "};
const std::string Validator::OPERAND {"operand = "};
const std::string Validator::ADDR {"address = "};
const std::string Validator::ENDL {'\n'};

Validator::Validator
(
    U8& currentByte,U8& stopByte,
    Registers& registers,RAM* ram
) : currentByte{currentByte},stopByte{stopByte},registers{registers},ram{ram},iset{iset}
{
    stream = Stream::getInstance();
    if(ram == nullptr) throw std::runtime_error("null pointer is passed in.");
    iset = InstructionSet::getInstance();
    transform = Transform::getInstance();
}

void Validator::integerRegister(U1 arg,U8 currentByte) const
{
    if(arg > RegisterCodes::$R24) throw std::runtime_error("invalid integer register code.");
}

void Validator::floatRegister(U1 arg,U8 currentByte) const
{
    if(arg > FloatRegisterCodes::$F10) throw std::runtime_error("invalid float register code.");
}

void Validator::doubleRegister(U1 arg,U8 currentByte) const
{
    if(arg > DoubleRegisterCodes::$D10) throw std::runtime_error("invalid double register code.");
}

//
// make sure that the bytecode address literals do not
// reference memory beyond the end of the address space.
//
void Validator::address_(U1* array,U8 currentByte,const Registers& registers) const
{
    U8* address = (U8*)&array[currentByte];
    if(*address > registers.R(RegisterCodes::$TOP)) throw std::runtime_error("address is out of bounds.");
}

//
// safeguard against incomplete instructions.
//
void Validator::currentByte_(U8 currentByte,U8 end) const
{
    if(currentByte >= end) throw std::runtime_error("incomplete instruction at address.");
}

//
// the last byte of an instruction is allowed to be at the end of the bytecode.
// this function checks for that.
//
void Validator::endCurrentByte(U8 currentByte,U8 end) const
{
    if(currentByte > end) throw std::runtime_error("incomplete instruction: passed end of bytecode.");
}

Validator& Validator::R()
{
    integerRegister(*ram->at(currentByte),currentByte);
    return *this;
}

Validator& Validator::RF()
{
    floatRegister(*ram->at(currentByte),currentByte);
    return *this;
}

Validator& Validator::RD()
{
    doubleRegister(*ram->at(currentByte),currentByte);
    return *this;
}

Validator& Validator::opcode()
{
    stream->string(Validator::OPCODE).string((*iset)((OpCodes)((*ram)(currentByte)))).string(Validator::ENDL);
    currentByte++;
    currentByte_(currentByte,stopByte);
    return *this;
}

Validator& Validator::operand()
{
    stream->string(Validator::OPERAND).string(registers.R_str((RegisterCodes)((*ram)(currentByte)))).string(Validator::ENDL);
    currentByte++;
    currentByte_(currentByte,stopByte);
    return *this;
}

Validator& Validator::end_byte()
{
    endCurrentByte(currentByte,stopByte);
    //currentByte += sizeof(U1);
    endCurrentByte(currentByte,stopByte);
    return *this;
}

Validator& Validator::end_word()
{
    transform->word(ram->at(currentByte),currentByte);
    currentByte += sizeof(U2);
    endCurrentByte(currentByte,stopByte);
    return *this;
}

Validator& Validator::end_dword()
{
    transform->dword(ram->at(currentByte),currentByte);
    currentByte += sizeof(U4);
    endCurrentByte(currentByte,stopByte);
    return *this;
}

Validator& Validator::end_qword()
{
    transform->qword(ram->at(currentByte),currentByte);
    currentByte += sizeof(U8);
    endCurrentByte(currentByte,stopByte);
    return *this;
}

Validator& Validator::address(TypeTag tag)
{
    address_(ram->at(currentByte),currentByte,registers);
    switch(tag)
    {
        case TypeTag::S1_TAG: stream->string(ADDR).S1(*((S1*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::U1_TAG: stream->string(ADDR).U1(*((U1*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::S2_TAG: stream->string(ADDR).S2(*((S2*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::U2_TAG: stream->string(ADDR).U2(*((U2*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::S4_TAG: stream->string(ADDR).S4(*((S4*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::U4_TAG: stream->string(ADDR).U4(*((U4*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::S8_TAG: stream->string(ADDR).S8(*((S8*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::U8_TAG: stream->string(ADDR).U8(*((U8*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::F4_TAG: stream->string(ADDR).F4(*((F4*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::F8_TAG: stream->string(ADDR).F8(*((F8*)ram->at(currentByte))).string(ENDL); break;
        default: throw std::runtime_error("invalid type tag.");
    }
    return *this;
}

} //namespace Logi
