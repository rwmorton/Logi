#ifndef __LOGI_TRANSFORM_H__
#define __LOGI_TRANSFORM_H__

//Logi includes
#include "Types.h"

namespace Logi
{

//
// TODO: add flag to check endian of system
// this is an optimization to add later.
//

class Transform
{
    public:
        //check system endianess
        static Endian checkEndian();
        //transforms
        static U2 bytecodeToWord(U1 bytes[]);
        static U4 bytecodeToDWord(U1 bytes[]);
        static U8 bytecodeToQWord(U1 bytes[]);
        static F4 bytecodeToFloat(U1 bytes[]);
        static F8 bytecodeToDouble(U1 bytes[]);
        //
        static void byteToBytecode(U1 byte,U1 bytes[]);
        static void wordToBytecode(U2 word,U1 bytes[]);
        static void dwordToBytecode(U4 dword,U1 bytes[]);
        static void qwordToBytecode(U8 qword,U1 bytes[]);
        static void floatToBytecode(F4 float_,U1 bytes[]);
        static void doubleToBytecode(F8 double_,U1 bytes[]);
        //
        static void byteToRegister(U1 byte,U8& reg);
        static void wordToRegister(U1 bytes[],U8& reg);
        static void dwordToRegister(U1 bytes[],U8& reg);
        static void qwordToRegister(U1 bytes[],U8& reg);
        static void floatToRegister(U1 bytes[],U8& reg);
        static void doubleToRegister(U1 bytes[],U8& reg);
        static void addressToRegister(U1 bytes[],U8& reg);
        //
        //big-endian to little-endian conversion
        //
        static void word(U1 bytes[],unsigned int start);
        static void dword(U1 bytes[],unsigned int start);
        static void qword(U1 bytes[],unsigned int start);
    private:
        Transform();
};

} //namespace Logi

#endif //__LOGI_TRANSFORM_H__
