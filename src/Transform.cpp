//Logi includes
#include "Transform.h"
#include "Stream.h"

namespace Logi
{

Endian Transform::PLATFORM {Transform::setPlatform()};

const U2 Transform::bytecodeToWord(U1 bytes[])
{
    U2 word;
    U1* buffer = (U1*)&word;
    if(PLATFORM == Endian::LITTLE)
    {
        buffer[0] = bytes[1];
        buffer[1] = bytes[0];
    }
    else
    {
        buffer[0] = bytes[0];
        buffer[1] = bytes[1];
    }

    return word;
}

const U4 Transform::bytecodeToDWord(U1 bytes[])
{
    U4 dword;
    U1* buffer = (U1*)&dword;
    if(PLATFORM == Endian::LITTLE)
    {
        buffer[0] = bytes[3];
        buffer[1] = bytes[2];
        buffer[2] = bytes[1];
        buffer[3] = bytes[0];
    }
    else
    {
        buffer[0] = bytes[0];
        buffer[1] = bytes[1];
        buffer[2] = bytes[2];
        buffer[3] = bytes[3];
    }

    return dword;
}

const U8 Transform::bytecodeToQWord(U1 bytes[])
{
    U8 qword;
    U1* buffer = (U1*)&qword;
    if(PLATFORM == Endian::LITTLE)
    {
        buffer[0] = bytes[7];
        buffer[1] = bytes[6];
        buffer[2] = bytes[5];
        buffer[3] = bytes[4];
        buffer[4] = bytes[3];
        buffer[5] = bytes[2];
        buffer[6] = bytes[1];
        buffer[7] = bytes[0];
    }
    else
    {
        buffer[0] = bytes[0];
        buffer[1] = bytes[1];
        buffer[2] = bytes[2];
        buffer[3] = bytes[3];
        buffer[4] = bytes[4];
        buffer[5] = bytes[5];
        buffer[6] = bytes[6];
        buffer[7] = bytes[7];
    }

    return qword;
}

const F4 Transform::bytecodeToFloat(U1 bytes[])
{
    F4 float_;
    U1 buffer[4];
    if(PLATFORM == Endian::LITTLE)
    {
        buffer[0] = bytes[3];
        buffer[1] = bytes[2];
        buffer[2] = bytes[1];
        buffer[3] = bytes[0];
    }
    else
    {
        buffer[0] = bytes[0];
        buffer[1] = bytes[1];
        buffer[2] = bytes[2];
        buffer[3] = bytes[3];
    }

    float_ = *(F4*)&buffer;

    return float_;
}

const F8 Transform::bytecodeToDouble(U1 bytes[])
{
    F8 double_;
    U1 buffer[8];
    if(PLATFORM == Endian::LITTLE)
    {
        buffer[0] = bytes[7];
        buffer[1] = bytes[6];
        buffer[2] = bytes[5];
        buffer[3] = bytes[4];
        buffer[4] = bytes[3];
        buffer[5] = bytes[2];
        buffer[6] = bytes[1];
        buffer[7] = bytes[0];
    }
    else
    {
        buffer[0] = bytes[0];
        buffer[1] = bytes[1];
        buffer[2] = bytes[2];
        buffer[3] = bytes[3];
        buffer[4] = bytes[4];
        buffer[5] = bytes[5];
        buffer[6] = bytes[6];
        buffer[7] = bytes[7];
    }

    double_ = *(F8*)&buffer;

    return double_;
}

void Transform::wordToBytecode(U2 word,U1 bytes[])
{
    U1* buffer = (U1*)&word;
    if(PLATFORM == Endian::LITTLE)
    {
        bytes[0] = buffer[1];
        bytes[1] = buffer[0];
    }
    else
    {
        bytes[0] = buffer[0];
        bytes[1] = buffer[1];
    }
}

void Transform::dwordToBytecode(U4 dword,U1 bytes[])
{
    U1* buffer = (U1*)&dword;
    if(PLATFORM == Endian::LITTLE)
    {
        bytes[0] = buffer[3];
        bytes[1] = buffer[2];
        bytes[2] = buffer[1];
        bytes[3] = buffer[0];
    }
    else
    {
        bytes[0] = buffer[0];
        bytes[1] = buffer[1];
        bytes[2] = buffer[2];
        bytes[3] = buffer[3];
    }
}

void Transform::qwordToBytecode(U8 qword,U1 bytes[])
{
    U1* buffer = (U1*)&qword;
    if(PLATFORM == Endian::LITTLE)
    {
        bytes[0] = buffer[7];
        bytes[1] = buffer[6];
        bytes[2] = buffer[5];
        bytes[3] = buffer[4];
        bytes[4] = buffer[3];
        bytes[5] = buffer[2];
        bytes[6] = buffer[1];
        bytes[7] = buffer[0];
    }
    else
    {
        bytes[0] = buffer[0];
        bytes[1] = buffer[1];
        bytes[2] = buffer[2];
        bytes[3] = buffer[3];
        bytes[4] = buffer[4];
        bytes[5] = buffer[5];
        bytes[6] = buffer[6];
        bytes[7] = buffer[7];
    }
}

void Transform::floatToBytecode(F4 float_,U1 bytes[])
{
    U1* buffer = (U1*)&float_;
    if(PLATFORM == Endian::LITTLE)
    {
        bytes[0] = buffer[3];
        bytes[1] = buffer[2];
        bytes[2] = buffer[1];
        bytes[3] = buffer[0];
    }
    else
    {
        bytes[0] = buffer[0];
        bytes[1] = buffer[1];
        bytes[2] = buffer[2];
        bytes[3] = buffer[3];
    }
}

void Transform::doubleToBytecode(F8 double_,U1 bytes[])
{
    U1* buffer = (U1*)&double_;
    if(PLATFORM == Endian::LITTLE)
    {
        bytes[0] = buffer[7];
        bytes[1] = buffer[6];
        bytes[2] = buffer[5];
        bytes[3] = buffer[4];
        bytes[4] = buffer[3];
        bytes[5] = buffer[2];
        bytes[6] = buffer[1];
        bytes[7] = buffer[0];
    }
    else
    {
        bytes[0] = buffer[0];
        bytes[1] = buffer[1];
        bytes[2] = buffer[2];
        bytes[3] = buffer[3];
        bytes[4] = buffer[4];
        bytes[5] = buffer[5];
        bytes[6] = buffer[6];
        bytes[7] = buffer[7];
    }
}

//store data in registers
void Transform::byteToRegister(U1 byte,U8& reg)
{
    reg = 0;
    U1* buffer = (U1*)&reg;
    PLATFORM == Endian::LITTLE ? buffer[7] = byte : buffer[0] = byte;
}

void Transform::wordToRegister(U1 bytes[],U8& reg)
{
    reg = 0;
    U1* buffer = (U1*)&reg;
    if(PLATFORM == Endian::LITTLE)
    {
        buffer[7] = bytes[0];
        buffer[6] = bytes[1];
    }
    else
    {
        buffer[0] = bytes[0];
        buffer[1] = bytes[1];
    }
}

void Transform::dwordToRegister(U1 bytes[],U8& reg)
{
    reg = 0;
    U1* buffer = (U1*)&reg;
    if(PLATFORM == Endian::LITTLE)
    {
        buffer[7] = bytes[0];
        buffer[6] = bytes[1];
        buffer[5] = bytes[2];
        buffer[4] = bytes[3];
    }
    else
    {
        buffer[0] = bytes[0];
        buffer[1] = bytes[1];
        buffer[2] = bytes[2];
        buffer[3] = bytes[3];
    }
}

void Transform::qwordToRegister(U1 bytes[],U8& reg)
{
    reg = 0;
    U1* buffer = (U1*)&reg;
    if(PLATFORM == Endian::LITTLE)
    {
        buffer[0] = bytes[7];
        buffer[1] = bytes[6];
        buffer[2] = bytes[5];
        buffer[3] = bytes[4];
        buffer[4] = bytes[3];
        buffer[5] = bytes[2];
        buffer[6] = bytes[1];
        buffer[7] = bytes[0];
    }
    else
    {
        buffer[0] = bytes[0];
        buffer[1] = bytes[1];
        buffer[2] = bytes[2];
        buffer[3] = bytes[3];
        buffer[4] = bytes[4];
        buffer[5] = bytes[5];
        buffer[6] = bytes[6];
        buffer[7] = bytes[7];
    }
}

void Transform::floatToRegister(U1 bytes[],F4& reg)
{
    U1 buffer[4];
    if(PLATFORM == Endian::LITTLE)
    {
        buffer[0] = bytes[3];
        buffer[1] = bytes[2];
        buffer[2] = bytes[1];
        buffer[3] = bytes[0];
    }
    else
    {
        buffer[0] = bytes[0];
        buffer[1] = bytes[1];
        buffer[2] = bytes[2];
        buffer[3] = bytes[3];
    }
    reg = *(F4*)&buffer;
}

void Transform::doubleToRegister(U1 bytes[],F8& reg)
{
    U1 buffer[8];
    if(PLATFORM == Endian::LITTLE)
    {
        buffer[0] = bytes[7];
        buffer[1] = bytes[6];
        buffer[2] = bytes[5];
        buffer[3] = bytes[4];
        buffer[4] = bytes[3];
        buffer[5] = bytes[2];
        buffer[6] = bytes[1];
        buffer[7] = bytes[0];
    }
    else
    {
        buffer[0] = bytes[0];
        buffer[1] = bytes[1];
        buffer[2] = bytes[2];
        buffer[3] = bytes[3];
        buffer[4] = bytes[4];
        buffer[5] = bytes[5];
        buffer[6] = bytes[6];
        buffer[7] = bytes[7];
    }
    reg = *(F8*)&buffer;
}

void Transform::addressToRegister(U1 bytes[],U8& reg)
{
    reg = 0;
    U1* buffer = (U1*)&reg;
    if(PLATFORM == Endian::LITTLE)
    {
        buffer[0] = bytes[7];
        buffer[1] = bytes[6];
        buffer[2] = bytes[5];
        buffer[3] = bytes[4];
        buffer[4] = bytes[3];
        buffer[5] = bytes[2];
        buffer[6] = bytes[1];
        buffer[7] = bytes[0];
    }
    else
    {
        buffer[0] = bytes[0];
        buffer[1] = bytes[1];
        buffer[2] = bytes[2];
        buffer[3] = bytes[3];
        buffer[4] = bytes[4];
        buffer[5] = bytes[5];
        buffer[6] = bytes[6];
        buffer[7] = bytes[7];
    }
}

//push data to top of stack
void Transform::byteToStack(const U1 byte,U1* stackTop)
{
    stackTop[0] = byte;
}

void Transform::wordToStack(const U2 word,U1* stackTop)
{
    U1* buffer = (U1*)&word;
    if(PLATFORM == Endian::LITTLE)
    {
        stackTop[0] = buffer[1];
        stackTop[-1] = buffer[0];
    }
    else
    {
        stackTop[0] = buffer[0];
        stackTop[-1] = buffer[1];
    }
}

void Transform::dwordToStack(const U4 dword,U1* stackTop)
{
    U1* buffer = (U1*)&dword;
    if(PLATFORM == Endian::LITTLE)
    {
        stackTop[0] = buffer[3];
        stackTop[-1] = buffer[2];
        stackTop[-2] = buffer[1];
        stackTop[-3] = buffer[0];
    }
    else
    {
        stackTop[0] = buffer[0];
        stackTop[-1] = buffer[1];
        stackTop[-2] = buffer[2];
        stackTop[-3] = buffer[3];
    }
}

void Transform::qwordToStack(const U8 qword,U1* stackTop)
{
    U1* buffer = (U1*)&qword;
    if(PLATFORM == Endian::LITTLE)
    {
        stackTop[0] = buffer[7];
        stackTop[-1] = buffer[6];
        stackTop[-2] = buffer[5];
        stackTop[-3] = buffer[4];
        stackTop[-4] = buffer[3];
        stackTop[-5] = buffer[2];
        stackTop[-6] = buffer[1];
        stackTop[-7] = buffer[0];
    }
    else
    {
        stackTop[0] = buffer[0];
        stackTop[-1] = buffer[1];
        stackTop[-2] = buffer[2];
        stackTop[-3] = buffer[3];
        stackTop[-4] = buffer[4];
        stackTop[-5] = buffer[5];
        stackTop[-6] = buffer[6];
        stackTop[-7] = buffer[7];
    }
}

void Transform::floatToStack(const F4 float_,U1* stackTop)
{
    U1* buffer = (U1*)&float_;
    if(PLATFORM == Endian::LITTLE)
    {
        stackTop[0] = buffer[3];
        stackTop[-1] = buffer[2];
        stackTop[-2] = buffer[1];
        stackTop[-3] = buffer[0];
    }
    else
    {
        stackTop[0] = buffer[0];
        stackTop[-1] = buffer[1];
        stackTop[-2] = buffer[2];
        stackTop[-3] = buffer[3];
    }
}

void Transform::doubleToStack(const F8 double_,U1* stackTop)
{
    U1* buffer = (U1*)&double_;
    if(PLATFORM == Endian::LITTLE)
    {
        stackTop[0] = buffer[7];
        stackTop[-1] = buffer[6];
        stackTop[-2] = buffer[5];
        stackTop[-3] = buffer[4];
        stackTop[-4] = buffer[3];
        stackTop[-5] = buffer[2];
        stackTop[-6] = buffer[1];
        stackTop[-7] = buffer[0];
    }
    else
    {
        stackTop[0] = buffer[0];
        stackTop[-1] = buffer[1];
        stackTop[-2] = buffer[2];
        stackTop[-3] = buffer[3];
        stackTop[-4] = buffer[4];
        stackTop[-5] = buffer[5];
        stackTop[-6] = buffer[6];
        stackTop[-7] = buffer[7];
    }
}

//get data from top of stack
void Transform::byteFromStack(U8& byte,const U1* stackTop)
{
    byte = 0;
    U1* buffer = (U1*)&byte;
    PLATFORM == Endian::LITTLE ? buffer[7] = stackTop[0] : buffer[0] = stackTop[0];
}

void Transform::wordFromStack(U8& word,const U1* stackTop)
{
    word = 0;
    U1* buffer = (U1*)&word;
    if(PLATFORM == Endian::LITTLE)
    {
        buffer[7] = stackTop[0];
        buffer[6] = stackTop[-1];
    }
    else
    {
        buffer[0] = stackTop[0];
        buffer[1] = stackTop[-1];
    }
}

void Transform::dwordFromStack(U8& dword,const U1* stackTop)
{
    dword = 0;
    U1* buffer = (U1*)&dword;
    if(PLATFORM == Endian::LITTLE)
    {
        buffer[7] = stackTop[0];
        buffer[6] = stackTop[-1];
        buffer[5] = stackTop[-2];
        buffer[4] = stackTop[-3];
    }
    else
    {
        buffer[0] = stackTop[0];
        buffer[1] = stackTop[-1];
        buffer[2] = stackTop[-2];
        buffer[3] = stackTop[-3];
    }
}

void Transform::qwordFromStack(U8& qword,const U1* stackTop)
{
    qword = 0;
    U1* buffer = (U1*)&qword;
    if(PLATFORM == Endian::LITTLE)
    {
        buffer[0] = stackTop[-7];
        buffer[1] = stackTop[-6];
        buffer[2] = stackTop[-5];
        buffer[3] = stackTop[-4];
        buffer[4] = stackTop[-3];
        buffer[5] = stackTop[-2];
        buffer[6] = stackTop[-1];
        buffer[7] = stackTop[0];
    }
    else
    {
        buffer[0] = stackTop[0];
        buffer[1] = stackTop[-1];
        buffer[2] = stackTop[-2];
        buffer[3] = stackTop[-3];
        buffer[4] = stackTop[-4];
        buffer[5] = stackTop[-5];
        buffer[6] = stackTop[-6];
        buffer[7] = stackTop[-7];
    }
}

void Transform::floatFromStack(F4& float_,const U1* stackTop)
{
    U1 buffer[4];
    if(PLATFORM == Endian::LITTLE)
    {
        buffer[0] = stackTop[-3];
        buffer[1] = stackTop[-2];
        buffer[2] = stackTop[-1];
        buffer[3] = stackTop[0];
    }
    else
    {
        buffer[0] = stackTop[0];
        buffer[1] = stackTop[-1];
        buffer[2] = stackTop[-2];
        buffer[3] = stackTop[-3];
    }
    float_ = *(F4*)&buffer;
}

void Transform::doubleFromStack(F8& double_,const U1* stackTop)
{
    U1 buffer[8];
    if(PLATFORM == Endian::LITTLE)
    {
        buffer[0] = stackTop[-7];
        buffer[1] = stackTop[-6];
        buffer[2] = stackTop[-5];
        buffer[3] = stackTop[-4];
        buffer[4] = stackTop[-3];
        buffer[5] = stackTop[-2];
        buffer[6] = stackTop[-1];
        buffer[7] = stackTop[0];
    }
    else
    {
        buffer[0] = stackTop[0];
        buffer[1] = stackTop[-1];
        buffer[2] = stackTop[-2];
        buffer[3] = stackTop[-3];
        buffer[4] = stackTop[-4];
        buffer[5] = stackTop[-5];
        buffer[6] = stackTop[-6];
        buffer[7] = stackTop[-7];
    }
    double_ = *(F8*)&buffer;
}

Transform::Transform() {}

//
// if LSB is placed first followed by the MSB
// then the system is little-endian.
//
// if MSB is placed first followed by LSB
// then the system is big-endian.
//
const Endian Transform::setPlatform()
{
    int i = 184594741; //0x0B00B135

    U1* buf = (U1*)&i;
    Endian platform = buf[0] == 0x35 ? Endian::LITTLE : Endian::BIG;

    std::string msg {"TRANSFORM: detected "};
    platform == Endian::LITTLE ? msg += "little" : msg += "big";
    msg += "-endian system. Appropriate conversions will be done.";
    Stream::getInstance()->string(msg).endl();

    return platform;
}

} //namespace Logi
