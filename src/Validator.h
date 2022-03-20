#ifndef __LOGI_VALIDATOR_H__
#define __LOGI_VALIDATOR_H__

//Logi includes
#include "Types.h"
#include "Registers.h"

namespace Logi
{

//
// Validator is a singleton.
//
class Validator
{
    public:
        static const Validator* getInstance();
        void integerRegister(U1 arg,U8 currentByte) const;
        void floatRegister(U1 arg,U8 currentByte) const;
        void doubleRegister(U1 arg,U8 currentByte) const;
        void address_(U1* array,U8 currentByte,const Registers& registers) const;
        void currentByte(U8 currentByte,U8 end) const;
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
        Validator();
        static Validator* instance;
};

} //namespace Logi

#endif //__LOGI_VALIDATOR_H__
