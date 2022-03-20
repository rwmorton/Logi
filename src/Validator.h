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
        Validator(U8& currentByte,U8& stopByte,Registers& registers,RAM* ram);
        void integerRegister(U1 arg,U8 currentByte) const;
        void floatRegister(U1 arg,U8 currentByte) const;
        void doubleRegister(U1 arg,U8 currentByte) const;
        void address_(U1* array,U8 currentByte,const Registers& registers) const;
        void currentByte_(U8 currentByte,U8 end) const;
        void endCurrentByte(U8 currentByte,U8 end) const;
        //
        // implement a fluent interface
        //
        Validator& R();
        Validator& RF();
        Validator& RD();
        Validator& opcode();
        Validator& operand();
        Validator& end_byte();
        Validator& end_word();
        Validator& end_dword();
        Validator& end_qword();
        Validator& address(TypeTag tag);
    private:
        U8 currentByte;
        U8 stopByte;
        Registers registers;
        RAM* ram;
        const Transform* transform;
        const InstructionSet* iset;
        const Stream* stream;
        static const std::string OPCODE;
        static const std::string OPERAND;
        static const std::string ADDR;
        static const std::string ENDL;
};

} //namespace Logi

#endif //__LOGI_VALIDATOR_H__
