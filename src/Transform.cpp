//Logi includes
#include "Transform.h"

namespace Logi
{

//
// if LSB is placed first followed by the MSB
// then the system is little-endian.
//
// if MSB is placed first followed by LSB
// then the system is big-endian.
//
Endian Transform::checkEndianness()
{
    int i = 184594741; //0x0B00B135

    U1* buf = (U1*)&i;
    return buf[0] == 0x35 ? Endian::LITTLE : Endian::BIG;
}

U2 Transform::bytecodeToWord(U1 bytes[])
{
    U2 word;
    U1* buffer = (U1*)&word;
    buffer[0] = bytes[1];
    buffer[1] = bytes[0];

    return word;
}

U4 Transform::bytecodeToDWord(U1 bytes[])
{
    U4 dword;
    U1* buffer = (U1*)&dword;
    buffer[0] = bytes[3];
    buffer[1] = bytes[2];
    buffer[2] = bytes[1];
    buffer[3] = bytes[0];

    return dword;
}

U8 Transform::bytecodeToQWord(U1 bytes[])
{
    U8 qword;
    U1* buffer = (U1*)&qword;
    buffer[0] = bytes[7];
    buffer[1] = bytes[6];
    buffer[2] = bytes[5];
    buffer[3] = bytes[4];
    buffer[4] = bytes[3];
    buffer[5] = bytes[2];
    buffer[6] = bytes[1];
    buffer[7] = bytes[0];

    return qword;
}

F4 Transform::bytecodeToFloat(U1 bytes[])
{
    F4 float_;
    U1* buffer = (U1*)&float_;
    buffer[0] = bytes[3];
    buffer[1] = bytes[2];
    buffer[2] = bytes[1];
    buffer[3] = bytes[0];

    return float_;
}

F8 Transform::bytecodeToDouble(U1 bytes[])
{
    F8 double_;
    U1* buffer = (U1*)&double_;
    buffer[0] = bytes[7];
    buffer[1] = bytes[6];
    buffer[2] = bytes[5];
    buffer[3] = bytes[4];
    buffer[4] = bytes[3];
    buffer[5] = bytes[2];
    buffer[6] = bytes[1];
    buffer[7] = bytes[0];

    return double_;
}

void Transform::byteToBytecode(U1 byte,U1 bytes[])
{
    U1* buffer = (U1*)&word;
    bytes[0] = buffer[1];
}

void Transform::wordToBytecode(U2 word,U1 bytes[])
{
    U1* buffer = (U1*)&word;
    bytes[0] = buffer[1];
    bytes[1] = buffer[0];
}

void Transform::dwordToBytecode(U4 dword,U1 bytes[])
{
    U1* buffer = (U1*)&dword;
    bytes[0] = buffer[3];
    bytes[1] = buffer[2];
    bytes[2] = buffer[1];
    bytes[3] = buffer[0];
}

void Transform::qwordToBytecode(U8 qword,U1 bytes[])
{
    U1* buffer = (U1*)&qword;
    bytes[0] = buffer[7];
    bytes[1] = buffer[6];
    bytes[2] = buffer[5];
    bytes[3] = buffer[4];
    bytes[4] = buffer[3];
    bytes[5] = buffer[2];
    bytes[6] = buffer[1];
    bytes[7] = buffer[0];
}

void Transform::floatToBytecode(F4 float_,U1 bytes[])
{
    U1* buffer = (U1*)&float_;
    bytes[0] = buffer[3];
    bytes[1] = buffer[2];
    bytes[2] = buffer[1];
    bytes[3] = buffer[0];
}

void Transform::doubleToBytecode(F8 double_,U1 bytes[])
{
    U1* buffer = (U1*)&double_;
    bytes[0] = buffer[7];
    bytes[1] = buffer[6];
    bytes[2] = buffer[5];
    bytes[3] = buffer[4];
    bytes[4] = buffer[3];
    bytes[5] = buffer[2];
    bytes[6] = buffer[1];
    bytes[7] = buffer[0];
}

//store data in registers
void Transform::byteToRegister(U1 byte,U8& reg)
{
    U1* buffer = (U1*)&reg;
    buffer[0] = byte;
}

void Transform::wordToRegister(U1 bytes[],U8& reg)
{
    U1* buffer = (U1*)&reg;
    buffer[0] = bytes[0];
    buffer[1] = bytes[1];
}

void Transform::dwordToRegister(U1 bytes[],U8& reg)
{
    U1* buffer = (U1*)&reg;
    buffer[0] = bytes[0];
    buffer[1] = bytes[1];
    buffer[2] = bytes[2];
    buffer[3] = bytes[3];
}

void Transform::qwordToRegister(U1 bytes[],U8& reg)
{
    U1* buffer = (U1*)&reg;
    buffer[0] = bytes[0];
    buffer[1] = bytes[1];
    buffer[2] = bytes[2];
    buffer[3] = bytes[3];
    buffer[4] = bytes[4];
    buffer[5] = bytes[5];
    buffer[6] = bytes[6];
    buffer[7] = bytes[7];
}

void Transform::floatToRegister(U1 bytes[],U8& reg)
{
    U1* buffer = (U1*)&reg;
    buffer[0] = bytes[0];
    buffer[1] = bytes[1];
    buffer[2] = bytes[2];
    buffer[3] = bytes[3];
}

void Transform::doubleToRegister(U1 bytes[],U8& reg)
{
    U1* buffer = (U1*)&reg;
    buffer[0] = bytes[0];
    buffer[1] = bytes[1];
    buffer[2] = bytes[2];
    buffer[3] = bytes[3];
    buffer[4] = bytes[4];
    buffer[5] = bytes[5];
    buffer[6] = bytes[6];
    buffer[7] = bytes[7];
}

void Transform::addressToRegister(U1 bytes[],U8& reg)
{
    U1* buffer = (U1*)&reg;
    buffer[0] = bytes[0];
    buffer[1] = bytes[1];
    buffer[2] = bytes[2];
    buffer[3] = bytes[3];
    buffer[4] = bytes[4];
    buffer[5] = bytes[5];
    buffer[6] = bytes[6];
    buffer[7] = bytes[7];
}

//push data to top of stack
void Transform::byteToStack(const U1 byte,U1* stackTop)
{
    stackTop[0] = byte;
}

void Transform::wordToStack(const U2 word,U1* stackTop)
{
    U1* buffer = (U1*)&word;
    stackTop[0] = buffer[0];
    stackTop[-1] = buffer[1];
}

void Transform::dwordToStack(const U4 dword,U1* stackTop)
{
    U1* buffer = (U1*)&dword;
    stackTop[0] = buffer[0];
    stackTop[-1] = buffer[1];
    stackTop[-2] = buffer[2];
    stackTop[-3] = buffer[3];
}

void Transform::qwordToStack(const U8 qword,U1* stackTop)
{
    U1* buffer = (U1*)&qword;
    stackTop[0] = buffer[0];
    stackTop[-1] = buffer[1];
    stackTop[-2] = buffer[2];
    stackTop[-3] = buffer[3];
    stackTop[-4] = buffer[4];
    stackTop[-5] = buffer[5];
    stackTop[-6] = buffer[6];
    stackTop[-7] = buffer[7];
}

void Transform::floatToStack(const F4 float_,U1* stackTop)
{
    U1* buffer = (U1*)&float_;
    stackTop[0] = buffer[0];
    stackTop[-1] = buffer[1];
    stackTop[-2] = buffer[2];
    stackTop[-3] = buffer[3];
}

void Transform::doubleToStack(const F8 double_,U1* stackTop)
{
    U1* buffer = (U1*)&double_;
    stackTop[0] = buffer[0];
    stackTop[-1] = buffer[1];
    stackTop[-2] = buffer[2];
    stackTop[-3] = buffer[3];
    stackTop[-4] = buffer[4];
    stackTop[-5] = buffer[5];
    stackTop[-6] = buffer[6];
    stackTop[-7] = buffer[7];
}

//get data from top of stack
void Transform::byteFromStack(U8& byte,const U1* stackTop)
{
    U1* buffer = (U1*)&byte;
    buffer[0] = stackTop[0];
}


void Transform::wordFromStack(U8& word,const U1* stackTop)
{
    U1* buffer = (U1*)&word;
    buffer[0] = stackTop[0];
    buffer[1] = stackTop[-1];
}

void Transform::dwordFromStack(U8& dword,const U1* stackTop)
{
    U1* buffer = (U1*)&dword;
    buffer[0] = stackTop[0];
    buffer[1] = stackTop[-1];
    buffer[2] = stackTop[-2];
    buffer[3] = stackTop[-3];
}

void Transform::qwordFromStack(U8& qword,const U1* stackTop)
{
    U1* buffer = (U1*)&qword;
    buffer[0] = stackTop[0];
    buffer[1] = stackTop[-1];
    buffer[2] = stackTop[-2];
    buffer[3] = stackTop[-3];
    buffer[4] = stackTop[-4];
    buffer[5] = stackTop[-5];
    buffer[6] = stackTop[-6];
    buffer[7] = stackTop[-7];
}

void Transform::floatFromStack(U8& float_,const U1* stackTop)
{
    U1* buffer = (U1*)&float_;
    buffer[0] = stackTop[0];
    buffer[1] = stackTop[-1];
    buffer[2] = stackTop[-2];
    buffer[3] = stackTop[-3];
}

void Transform::doubleFromStack(U8& double_,const U1* stackTop)
{
    U1* buffer = (U1*)&double_;
    buffer[0] = stackTop[0];
    buffer[1] = stackTop[-1];
    buffer[2] = stackTop[-2];
    buffer[3] = stackTop[-3];
    buffer[4] = stackTop[-4];
    buffer[5] = stackTop[-5];
    buffer[6] = stackTop[-6];
    buffer[7] = stackTop[-7];
}

//big-endian to little-endian conversion
void Transform::word(U1 bytes[],unsigned int start)
{
    U1 temp[2];
    temp[0] = bytes[start+1];
    temp[1] = bytes[start];
    //flip
    bytes[start] = temp[1];
    bytes[start+1] = temp[0];
}

void Transform::dword(U1 bytes[],unsigned int start)
{
    U1 temp[4];
    temp[0] = bytes[start+3];
    temp[1] = bytes[start+2];
    temp[2] = bytes[start+1];
    temp[3] = bytes[start];
    //flip
    bytes[start] = temp[0];
    bytes[start+1] = temp[1];
    bytes[start+2] = temp[2];
    bytes[start+3] = temp[3];
}

void Transform::qword(U1 bytes[],unsigned int start)
{
    U1 temp[8];
    temp[0] = bytes[start+7];
    temp[1] = bytes[start+6];
    temp[2] = bytes[start+5];
    temp[3] = bytes[start+4];
    temp[4] = bytes[start+3];
    temp[5] = bytes[start+2];
    temp[6] = bytes[start+1];
    temp[7] = bytes[start];
    //flip
    bytes[start] = temp[0];
    bytes[start+1] = temp[1];
    bytes[start+2] = temp[2];
    bytes[start+3] = temp[3];
    bytes[start+4] = temp[4];
    bytes[start+5] = temp[5];
    bytes[start+6] = temp[6];
    bytes[start+7] = temp[7];
}

Transform::Transform() {}

} //namespace Logi
