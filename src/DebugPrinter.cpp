//Logi includes
#include "DebugPrinter.h"
#include "VirtualMachine.h"

namespace Logi
{

DebugPrinter::DebugPrinter(VirtualMachine& vm) : vm{vm}, out(Stream::getInstance()->get()) {}

void DebugPrinter::begin(const U8 currentByte)
{
    this->currentByte = currentByte;
}

DebugPrinter& DebugPrinter::I()
{
    std::string inst = (*vm.iset)((OpCode)((*vm.ram)(currentByte++)));
    out << "$IP= " << inst << ", ";
    return *this;
}

void DebugPrinter::I_end()
{
    std::string inst = (*vm.iset)((OpCode)((*vm.ram)(currentByte)));
    out << "$IP= " << inst << '\n';
}

DebugPrinter& DebugPrinter::R(int count)
{
    for(int i=0; i<count; i++)
    {
        U8 R = (*vm.ram)(currentByte++);
        out << vm.registers.R_str((RegisterCodes)R) << "= " << vm.registers.R((RegisterCodes)R) << ", ";
    }
    return *this;
}

void DebugPrinter::R_end()
{
    U8 R1 = (*vm.ram)(currentByte);
    out << vm.registers.R_str((RegisterCodes)R1) << "= " << vm.registers.R((RegisterCodes)R1) << '\n';
}

DebugPrinter& DebugPrinter::RF(int count)
{
    for(int i=0; i<count; i++)
    {
        F4 F = (*vm.ram)(currentByte++);
        out << vm.registers.RF_str((FloatRegisterCodes)F) << "= " << vm.registers.RF((FloatRegisterCodes)F) << ", ";
    }
    return *this;
}

void DebugPrinter::RF_end()
{
    F4 F = (*vm.ram)(currentByte++);
    out << vm.registers.RF_str((FloatRegisterCodes)F) << "= " << vm.registers.RF((FloatRegisterCodes)F) << '\n';
}

DebugPrinter& DebugPrinter::RD(int count)
{
    for(int i=0; i<count; i++)
    {
        F8 D = (*vm.ram)(currentByte++);
        out << vm.registers.RD_str((DoubleRegisterCodes)D) << "= " << vm.registers.RD((DoubleRegisterCodes)D) << ", ";
    }
    return *this;
}

void DebugPrinter::RD_end()
{
    F8 D = (*vm.ram)(currentByte++);
    out << vm.registers.RD_str((DoubleRegisterCodes)D) << "= " << vm.registers.RD((DoubleRegisterCodes)D) << '\n';
}

void DebugPrinter::B()
{
    S1 byte = (S1)(*vm.ram)(currentByte);
    out << "byte= " << static_cast<int>(byte) << '\n';
}

void DebugPrinter::W()
{
    S2 word = (S2)Transform::bytecodeToWord(&(*vm.ram)(currentByte));
    out << "word= " << word << '\n';
}

void DebugPrinter::D()
{
    S4 dword = (S4)Transform::bytecodeToDWord(&(*vm.ram)(currentByte));
    out << "dword= " << dword << '\n';
}

void DebugPrinter::Q()
{
    S8 qword = (S8)Transform::bytecodeToQWord(&(*vm.ram)(currentByte));
    out << "qword= " << qword << '\n';
}

void DebugPrinter::F1()
{
    F4 float_ = Transform::bytecodeToFloat(&(*vm.ram)(currentByte));
    out << "float= " << float_ << '\n';
}

void DebugPrinter::F2()
{
    F8 double_ = Transform::bytecodeToDouble(&(*vm.ram)(currentByte));
    out << "double= " << double_ << '\n';
}

void DebugPrinter::A()
{
    U8 addr = Transform::bytecodeToQWord(&(*vm.ram)(currentByte));
    out << "addr= " << addr << '\n';
}

} //namespace Logi
