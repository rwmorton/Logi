//Logi includes
#include "Stream.h"

//std includes
#include <iostream>

namespace Logi
{

Stream* Stream::instance {nullptr};

Stream* Stream::getInstance()
{
    if(Stream::instance == nullptr)
    {
        Stream::instance = new Stream();
    }
    return Stream::instance;
}

void Stream::set(const std::ostream* out)
{
    out = &(*out);
}

void Stream::U_REG(const std::string& regStr,Logi::U8 reg) const
{
    out << regStr << " = " << std::showbase << std::hex << reg;
    std::dec;
}

void Stream::S_REG(const std::string& regStr,Logi::U8 reg) const
{
    out << regStr << " = " << std::showbase << std::hex << reg;
    std::dec;
}

void Stream::F_REG(const std::string& regStr,Logi::U8 reg) const
{
    out << regStr << " = " << std::showbase << std::hex << reg;
    std::dec;
}

void Stream::D_REG(const std::string& regStr,Logi::U8 reg) const
{
    out << regStr << " = " << std::showbase << std::hex << reg;
    std::dec;
}

void Stream::U1(Logi::U1 byte) const
{
    out << std::hex << byte << std::dec;
}

void Stream::U2(Logi::U2 word) const
{
    out << std::hex << word << std::dec;
}

void Stream::U4(Logi::U4 dword) const
{
    out << std::hex << dword << std::dec;
}

void Stream::U8(Logi::U8 qword) const
{
    out << std::hex << qword << std::dec;
}

void Stream::S1(Logi::S1 byte) const
{
    out << std::hex << byte << std::dec;
}

void Stream::S2(Logi::S2 word) const
{
    out << std::hex << word << std::dec;
}

void Stream::S4(Logi::S4 dword) const
{
    out << std::hex << dword << std::dec;
}

void Stream::S8(Logi::S8 qword) const
{
    out << std::hex << qword << std::dec;
}

void Stream::mem(const RAM* ram,Logi::U8 index) const
{
    out << "RAM[" << index << "] = " << std::hex << (*ram)._ram[index] << std::dec;
}

void Stream::bytes(const Logi::U1 bytes[],unsigned int length) const
{
    for(int i=0; i<length; i++)
    {
        out << std::hex << std::showbase << static_cast<int>(bytes[i]);
        if(i < length-1) out << ' ';
    }
    out << std::dec;
}

void Stream::memSection(const VirtualMachine& vm,Logi::U8 address,Logi::U8 bytes) const
{
    Logi::U8 index;
    for(index=address; index<address+bytes; index++)
    {
        if(index > vm.registers.R($TOP))
        {
            out << "memSection: address ";
            U8(index);
            out << " is out of bounds." << std::endl;
        }
        else
        {
            mem(vm.ram,index);
            out << std::endl;
        }
    }
}

void Stream::allRAM(const VirtualMachine& vm) const
{
    Logi::U8 index;
    for(index = 0; index<(Logi::U8)vm.registers.R($TOP); index++)
    {
        mem(vm.ram,index);
        out << std::endl;
    }
}

void Stream::basicRegisters(const VirtualMachine& vm) const
{
    out << "-----------------" << std::endl;
    out << "BASIC REGISTERS" << std::endl;
    out << "---------------" << std::endl;
    for(int i=0; i<8; i++)
    {
        U_REG(vm.registers.R_str(i),vm.registers.R(i));
        out << std::endl;
    }
    out << "---------------" << std::endl;
}

void Stream::generalRegisters(const VirtualMachine& vm) const
{
    out << "-----------------" << std::endl;
    out << "GENERAL REGISTERS" << std::endl;
    out << "-----------------" << std::endl;
    for(int i=8; i<32; i++)
    {
        S_REG(vm.registers.R_str(i),vm.registers.R(i));
        out << std::endl;
    }
    out << "-----------------" << std::endl;
}

void Stream::floatRegisters(const VirtualMachine& vm) const
{
    out << "-----------------" << std::endl;
    out << "FLOAT REGISTERS" << std::endl;
    out << "---------------" << std::endl;
    for(int i=0; i<10; i++)
    {
        F_REG(vm.registers.R_str(i),vm.registers.R(i));
        out << std::endl;
    }
    out << "---------------" << std::endl;
}

void Stream::doubleRegisters(const VirtualMachine& vm) const
{
    out << "-----------------" << std::endl;
    out << "DOUBLE REGISTERS" << std::endl;
    out << "----------------" << std::endl;
    for(int i=0; i<10; i++)
    {
        D_REG(vm.registers.R_str(i),vm.registers.R(i));
        out << std::endl;
    }
    out << "----------------" << std::endl;
}

//prevent copies - singleton
Stream::Stream() : out(std::cout) {}

} //namespace Logi
