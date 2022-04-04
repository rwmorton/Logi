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
        const OpCode getInstr() const;
        const ASMIdentifier getId() const;
        ValidateASM& count(const int expectedCount);
        ValidateASM& count(const int start,const int end);
        ValidateASM& assign(const TokenType type);
        ValidateASM& R();
        ValidateASM& RF();
        ValidateASM& RD();
    private:
        Line& line;
        std::vector<Token>::iterator& token_it;
};

}

#endif //__LOGI_VALIDATE_ASM_H__
