//Logi includes
#include "Stream.h"

//std includes
#include <iostream>
#include <iomanip>

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

const Stream& Stream::string(const std::string& str) const
{
    out << str;
    return *this;
}

const Stream& Stream::endl() const
{
    out << std::endl;
    return *this;
}

const Stream& Stream::U_REG(const std::string& regStr,Logi::U8 reg) const
{
    out << regStr << " = " << std::showbase << std::hex << (CAST_TO)reg;
    std::dec;
    return *this;
}

const Stream& Stream::S_REG(const std::string& regStr,Logi::U8 reg) const
{
    out << regStr << " = " << std::showbase << std::hex << (CAST_TO)reg;
    std::dec;
    return *this;
}

const Stream& Stream::F_REG(const std::string& regStr,Logi::U8 reg) const
{
    out << regStr << " = " << std::showbase << std::hex << (CAST_TO)reg;
    std::dec;
    return *this;
}

const Stream& Stream::D_REG(const std::string& regStr,Logi::U8 reg) const
{
    out << regStr << " = " << std::showbase << std::hex << (CAST_TO)reg;
    std::dec;
    return *this;
}

const Stream& Stream::U1(Logi::U1 byte) const
{
    out << std::showbase << std::hex << (CAST_TO)byte << std::dec;
    return *this;
}

const Stream& Stream::U2(Logi::U2 word) const
{
    Logi::U1* buffer = (Logi::U1*)&word;
    for(int i=0; i<2; i++) out << std::showbase << std::hex << (CAST_TO)(*(&buffer[i])) << ' ';
    std::dec;
    return *this;
}

const Stream& Stream::U4(Logi::U4 dword) const
{
    Logi::U1* buffer = (Logi::U1*)&dword;
    for(int i=0; i<4; i++) out << std::showbase << std::hex << (CAST_TO)(*(&buffer[i])) << ' ';
    std::dec;
    return *this;
}

const Stream& Stream::U8(Logi::U8 qword) const
{
    Logi::U1* buffer = (Logi::U1*)&qword;
    for(int i=0; i<8; i++) out << std::showbase << std::hex << (CAST_TO)(*(&buffer[i])) << ' ';
    std::dec;
    return *this;
}

const Stream& Stream::S1(Logi::S1 byte) const
{
    out << std::showbase << std::hex << (CAST_TO)byte << std::dec;
    return *this;
}

const Stream& Stream::S2(Logi::S2 word) const
{
    out << std::showbase << std::hex << (CAST_TO)word << std::dec;
    return *this;
}

const Stream& Stream::S4(Logi::S4 dword) const
{
    out << std::showbase << std::hex << (CAST_TO)dword << std::dec;
    return *this;
}

const Stream& Stream::S8(Logi::S8 qword) const
{
    out << std::showbase << std::hex << (CAST_TO)qword << std::dec;
    return *this;
}

const Stream& Stream::F4(Logi::F4 float_) const
{
    out << std::showbase << std::hex << (CAST_TO)float_ << std::dec;
    return *this;
}

const Stream& Stream::F8(Logi::F8 double_) const
{
    out << std::showbase << std::hex << (CAST_TO)double_ << std::dec;
    return *this;
}

const Stream& Stream::bytes(const Logi::U1 bytes[],unsigned int length) const
{
    for(int i=0; i<length; i++)
    {
        out << std::hex << std::showbase << static_cast<int>(bytes[i]);
        if(i < length-1) out << ' ';
    }
    out << std::dec;
    return *this;
}

//prevent copies - singleton
Stream::Stream() : out(std::cout) {}

} //namespace Logi
