#ifndef __LOGI_VALIDATE_ASM_H__
#define __LOGI_VALIDATE_ASM_H__

//Logi includes
#include "Assembler.h"

//std includes
#include <vector>

namespace Logi
{

class ValidateASM
{
    public:
        ValidateASM(Line& line,std::vector<Token>::iterator& token_it);
        void setDefaultAssign(const TokenType type);
        const OpCode getInstr() const;
        const ASMIdentifier getId() const;
        ValidateASM& count(const int expectedCount);
        const unsigned int count(const int start,const int end);
        ValidateASM& assign();
        ValidateASM& assign(const TokenType type);
        ValidateASM& R(unsigned int count=1);
        ValidateASM& RF(unsigned int count=1);
        ValidateASM& RD(unsigned int count=1);
    private:
        Line& line;
        std::vector<Token>::iterator& token_it;
        TokenType defaultAssignType;
};

}

#endif //__LOGI_VALIDATE_ASM_H__
