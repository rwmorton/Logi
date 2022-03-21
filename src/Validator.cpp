//Logi includes
#include "Validator.h"

//temp
#include <iostream>
using namespace std;

namespace Logi
{

const std::string Validator::OPCODE {"opcode = "};
const std::string Validator::OPERAND {"operand = "};
const std::string Validator::ADDR {"address = "};
const std::string Validator::ENDL {'\n'};

Validator::Validator
(
    U8& currentByte,U8& stopByte,
    const InstructionSet* iset,
    Registers& registers,RAM* ram
) : currentByte{currentByte},stopByte{stopByte},registers{registers},ram{ram},iset{iset}
{
    stream = Stream::getInstance();
    if(ram == nullptr) throw std::runtime_error("null pointer is passed in.");
    transform = Transform::getInstance();
}

Validator& Validator::R(const U1 count)
{
    for(U1 i=0; i<count; i++) R().opcode();
    return *this;
}

Validator& Validator::RF(const U1 count)
{
    for(U1 i=0; i<count; i++) RF().opcode();
    return *this;
}

Validator& Validator::RD(const U1 count)
{
    for(U1 i=0; i<count; i++) RD().opcode();
    return *this;
}

Validator& Validator::R()
{
    checkIReg(*ram->at(currentByte),currentByte);
    return *this;
}

Validator& Validator::RF()
{
    checkFReg(*ram->at(currentByte),currentByte);
    return *this;
}

Validator& Validator::RD()
{
    checkDReg(*ram->at(currentByte),currentByte);
    return *this;
}

//
// increment defaults to 1.
// Pass 0 if this is doesn't require a forward check.
// ex. only single byte opcode.
//
Validator& Validator::opcode(const bool thenEnd)
{
    stream->string("opcode() : currentByte = ").U8(currentByte).endl();
    stream->string(Validator::OPCODE).string((*iset)((OpCodes)((*ram)(currentByte)))).string(Validator::ENDL);
    if(thenEnd)
    {
        checkEndCB(currentByte,stopByte);
    }
    else
    {
        currentByte++;
        checkCB(currentByte,stopByte);
    }
    return *this;
}

//
// increment defaults to 1.
//
Validator& Validator::operand(const U8 increment)
{
    stream->string(Validator::OPERAND).string(registers.R1_24_str((RegisterCodes)((*ram)(currentByte)))).string(Validator::ENDL);
    
    /*
    for(int i=0; i<increment; i++)
    {
        stream->string("operand() : currentByte = ").U8(currentByte).endl();
        currentByte++;
        checkCB(currentByte,stopByte);
    }
    */
    currentByte++;
    stream->string("operand() : currentByte = ").U8(currentByte).endl();
    checkCB(currentByte,stopByte);
    return *this;
}

Validator& Validator::end()
{
    checkEndCB(currentByte,stopByte);
    return *this;
}

Validator& Validator::end_byte()
{
    currentByte += sizeof(U1);
    checkEndCB(currentByte,stopByte);
    return *this;
}

Validator& Validator::end_word()
{
    //transform->word(ram->at(currentByte),currentByte);
    currentByte += sizeof(U2);
    checkEndCB(currentByte,stopByte);
    return *this;
}

Validator& Validator::end_dword()
{
    //transform->dword(ram->at(currentByte),currentByte);
    stream->endl();
    stream->string("currentByte = ").U8(currentByte).endl();
    currentByte += sizeof(U4);
    stream->string("currentByte = ").U8(currentByte).endl();
    stream->endl();
    checkEndCB(currentByte,stopByte);
    return *this;
}

Validator& Validator::end_qword()
{
    //transform->qword(ram->at(currentByte),currentByte);
    currentByte += sizeof(U8);
    checkEndCB(currentByte,stopByte);
    return *this;
}

Validator& Validator::address(TypeTag tag)
{

    cout << endl << endl;
    cout << "REGISTERS:\n" << registers << endl;
    cout << "currentByte = " << currentByte << endl;
    cout << "RAM(" << currentByte << ") = " << static_cast<int>(*ram->at(currentByte)) << endl;

    //checkAddr(ram->at(currentByte),currentByte,registers);
    checkAddr(currentByte);

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
        default: throw std::runtime_error("VALIDATOR: invalid type tag.");
    }
    return *this;
}

void Validator::checkIReg(U1 arg,U8 currentByte) const
{
    Stream::getInstance()->string("arg = ").U1(arg).string(", currentByte = ").U8(currentByte).endl();
    if(arg > RegisterCodes::$R24) throw std::runtime_error("VALIDATOR: invalid integer register code.");
}

void Validator::checkFReg(U1 arg,U8 currentByte) const
{
    if(arg > FloatRegisterCodes::$F10) throw std::runtime_error("VALIDATOR: invalid float register code.");
}

void Validator::checkDReg(U1 arg,U8 currentByte) const
{
    if(arg > DoubleRegisterCodes::$D10) throw std::runtime_error("VALIDATOR: invalid double register code.");
}

//
// make sure that the bytecode address literals do not
// reference memory beyond the end of the address space.
//
void Validator::checkAddr(U1* array,U8 currentByte,const Registers& registers) const
{
    stream->string("checkAddr() : currentByte = ").U8(currentByte).endl();
    cout << registers.R(RegisterCodes::$TOP) << endl;
    stream->string("R[$TOP] = ").U8(registers.R(RegisterCodes::$TOP)).endl();
    
    U8* address = (U8*)&array[currentByte];

    cout << "address = " << *address << endl;
    
    if(*address > registers.R(RegisterCodes::$TOP)) throw std::runtime_error("VALIDATOR: address is out of bounds.");
}

void Validator::checkAddr(U8 currentByte) const
{
    stream->string("checkAddr() : currentByte = ").U8(currentByte).endl();
    cout << registers.R(RegisterCodes::$TOP) << endl;
    stream->string("R[$TOP] = ").U8(registers.R(RegisterCodes::$TOP)).endl();
    
    //U8* address = (U8*)(*ram)(currentByte);

    //U8 address = Transform::bytecodeToQWord(&(*ram)(currentByte));
    U1* address = &(*ram)(currentByte);

    cout << "address = " << static_cast<int>(*address) << endl;
    
    if(*address > registers.R(RegisterCodes::$TOP)) throw std::runtime_error("VALIDATOR: address is out of bounds.");
}

//
// safeguard against incomplete instructions.
//
void Validator::checkCB(U8 currentByte,U8 endByte) const
{
    stream->string("checkCB() : currentByte = ").U8(currentByte).endl();
    if(currentByte >= endByte) throw std::runtime_error("VALIDATOR: incomplete instruction at address.");
}

//
// the last byte of an instruction is allowed to be at the end of the bytecode.
// this function checks for that.
//
void Validator::checkEndCB(U8 currentByte,U8 endByte) const
{
    stream->string("checkEndCB() : currentByte = ").U8(currentByte).string(", endByte = ").U8(endByte).endl();
    if(currentByte > endByte) throw std::runtime_error("VALIDATOR: incomplete instruction: passed end of bytecode.");
}

} //namespace Logi
