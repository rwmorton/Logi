#ifndef __LOGI_VALIDATOR_H__
#define __LOGI_VALIDATOR_H__

//Logi includes
#include "Types.h"
#include "Registers.h"
#include "RAM.h"
#include "Transform.h"
#include "Stream.h"

namespace Logi
{

class Stream;

class Validator
{
    public:
        Validator(U8& currentByte,U8& stopByte,const InstructionSet* iset,Registers& registers,RAM* ram);
        //
        // implement a fluent interface
        //
        Validator& R(const U1 count);
        Validator& RF(const U1 count);
        Validator& RD(const U1 count);
        //
        Validator& R();
        Validator& RF();
        Validator& RD();
        Validator& opcode(const bool thenEnd=false);
        Validator& operand();
        Validator& end();
        Validator& end_byte();
        Validator& end_word();
        Validator& end_dword();
        Validator& end_qword();
        Validator& address(TypeTag tag);
    private:
        void checkIReg(U1 arg,U8 currentByte) const;
        void checkFReg(U1 arg,U8 currentByte) const;
        void checkDReg(U1 arg,U8 currentByte) const;
        void checkAddr(U1* array,U8 currentByte,const Registers& registers) const;
        void checkCB(U8 currentByte,U8 endByte) const;
        void checkEndCB(U8 currentByte,U8 endByte) const;
        U8& currentByte;
        const U8& stopByte;
        const InstructionSet* iset;
        Registers registers;
        RAM* ram;
        const Transform* transform;
        const Stream* stream;
        static const std::string OPCODE;
        static const std::string OPERAND;
        static const std::string ADDR;
        static const std::string ENDL;
};

} //namespace Logi

#endif //__LOGI_VALIDATOR_H__
