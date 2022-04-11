#ifndef __LOGI_TRANSFORM_H__
#define __LOGI_TRANSFORM_H__

//Logi includes
#include "Types.h"
#include "RAM.h"

namespace Logi
{

//
// Internally data is stored in big-endian format, so
// the the platform endianness must be detected in order
// to do the correct conversions. This is done in the
// constructor.
//
class Transform
{
    public:
        //bytecode to XYZ
        static const U2 bytecodeToWord(U1 bytes[]);
        static const U4 bytecodeToDWord(U1 bytes[]);
        static const U8 bytecodeToQWord(U1 bytes[]);
        static const F4 bytecodeToFloat(U1 bytes[]);
        static const F8 bytecodeToDouble(U1 bytes[]);
        //XYZ to bytecode
        static void wordToBytecode(U2 word,U1 bytes[]);
        static void dwordToBytecode(U4 dword,U1 bytes[]);
        static void qwordToBytecode(U8 qword,U1 bytes[]);
        static void floatToBytecode(F4 float_,U1 bytes[]);
        static void doubleToBytecode(F8 double_,U1 bytes[]);
        //XYZ to register
        static void byteToRegister(U1 byte,U8& reg);
        static void wordToRegister(U1 bytes[],U8& reg);
        static void dwordToRegister(U1 bytes[],U8& reg);
        static void qwordToRegister(U1 bytes[],U8& reg);
        static void floatToRegister(U1 bytes[],U8& reg);
        static void doubleToRegister(U1 bytes[],U8& reg);
        static void floatToRegister(U1 bytes[],F4& reg);
        static void doubleToRegister(U1 bytes[],F8& reg);
        static void addressToRegister(U1 bytes[],U8& reg);
        //XYZ to stack
        static void byteToStack(const U1 byte,U1* stackTop);
        static void wordToStack(const U2 word,U1* stackTop);
        static void dwordToStack(const U4 dword,U1* stackTop);
        static void qwordToStack(const U8 qword,U1* stackTop);
        static void floatToStack(const F4 float_,U1* stackTop);
        static void doubleToStack(const F8 double_,U1* stackTop);
        //XYZ from stack
        static void byteFromStack(U8& byte,const U1* stackTop);
        static void wordFromStack(U8& byte,const U1* stackTop);
        static void dwordFromStack(U8& byte,const U1* stackTop);
        static void qwordFromStack(U8& byte,const U1* stackTop);
        static void floatFromStack(F4& byte,const U1* stackTop);
        static void doubleFromStack(F8& byte,const U1* stackTop);
        //TESTS
        #ifdef __LOGI_TESTS_ON__
            static void TEST_run_all_tests();
        #endif //__LOGI_TESTS_ON__
        //END TEST
    private:
        //TESTS
        #ifdef __LOGI_TESTS_ON__
            static void TEST_setPlatform(const Endian end);
            static void TEST_bytecodeToXYZ();
            static void TEST_xyzToBytecode();
            static void TEST_xyzToRegister();
            static void TEST_xyzToStack();
            static void TEST_xyzFromStack();
        #endif //__LOGI_TESTS_ON__
        Transform();
        //set system endianess
        static const Endian setPlatform();
        static Endian PLATFORM;
};

} //namespace Logi

#endif //__LOGI_TRANSFORM_H__
