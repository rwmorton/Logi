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

//
// Transform is a singleton.
//
class Transform
{
    public:
        static const Transform* getInstance();
        //check system endian
        const Endian checkEndian() const;
        //transforms
        U2 bytecodeToWord(U1 bytes[]) const;
        U4 bytecodeToDWord(U1 bytes[]) const;
        U8 bytecodeToQWord(U1 bytes[]) const;
        F4 bytecodeToFloat(U1 bytes[]) const;
        F8 bytecodeToDouble(U1 bytes[]) const;
        //
        void wordToBytecode(U2 word,U1 bytes[]) const;
        void dwordToBytecode(U4 dword,U1 bytes[]) const;
        void qwordToBytecode(U8 qword,U1 bytes[]) const;
        void floatToBytecode(F4 float_,U1 bytes[]) const;
        void doubleToBytecode(F8 double_,U1 bytes[]) const;
        //
        static void byteToRegister(U1 byte,U8& reg);
        static void wordToRegister(U1 bytes[],U8& reg);
        static void dwordToRegister(U1 bytes[],U8& reg);
        static void qwordToRegister(U1 bytes[],U8& reg);
        //
        //big-endian to little-endian conversion
        //
        void word(U1 bytes[],unsigned int start) const;
        void dword(U1 bytes[],unsigned int start) const;
        void qword(U1 bytes[],unsigned int start) const;
    private:
        Transform();
        static Transform* instance;
};

} //namespace Logi

#endif //__LOGI_TRANSFORM_H__
