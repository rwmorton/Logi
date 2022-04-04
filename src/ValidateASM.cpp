//Logi includes
#include "ValidateASM.h"
#include "Assembler.h"
#include "Registers.h"
#include "InstructionSet.h"

#include <iostream>
using namespace std;

namespace Logi
{

ValidateASM::ValidateASM(Line& line,std::vector<Token>::iterator& token_it) : line{line}, token_it{token_it} {}

//
// Convenience method for assigning types without passing anything.
//
void ValidateASM::setDefaultAssign(const TokenType type)
{
    defaultAssignType = type;
}

const OpCode ValidateASM::getInstr() const
{
    return InstructionSet::OpCode_fromStr(token_it->str);
}

const ASMIdentifier ValidateASM::getId() const
{
    return Assembler::ASMIdentifier_fromStr(token_it->str);
}

ValidateASM& ValidateASM::count(const int expectedCount)
{
    if(expectedCount != line.tokens.size())
    {
        throw std::runtime_error("ASSEMBLER: invalid number of tokens on line.");
    }

    return *this;
}

//
// Verify number of tokens on line is correct.
//
const unsigned int ValidateASM::count(const int start,const int end)
{
    if(line.tokens.size() < start || line.tokens.size() > end)
    {
        throw std::runtime_error("ASSEMBLER: invalid number of tokens on line.");
    }
    
    return line.tokens.size();
}

//
// Assign type of token using stored type
// then move onto the next token.
//
ValidateASM& ValidateASM::assign()
{
    return assign(defaultAssignType);
}

//
// Assign type of token then move onto the next token.
//
ValidateASM& ValidateASM::assign(const TokenType type)
{
    token_it->type = type;

    switch(type)
    {
        case CHAR_CONSTANT:
        {
            throw std::runtime_error("VALIDATE_ASM: unimplemented CHAR_CONSTANT assign.");
            token_it->val.S8_val = static_cast<S8>(token_it->str.at(0));
        }
        break;
        case INTEGER_CONSTANT:
        {
            token_it->val.S8_val = std::stol(token_it->str);
        }
        break;
        case FLOAT_CONSTANT:
        {
            token_it->val.F8_val = std::stod(token_it->str);
        }
    }

    ++token_it;

    return *this;
}

ValidateASM& ValidateASM::R(unsigned int count)
{
    for(int i=0; i<count; i++)
    {
        const std::string& str = token_it->str;
        if(str.length() < 3 || str.length() > 4 || str.at(0) != '$' || str.at(1) == 'F' || str.at(1) == 'D')
        {
            std::string errorStr {"ASSEMBLER: not a valid integer register ("};
            errorStr += str;
            errorStr += ").";
            throw std::runtime_error(errorStr);
        }

        //do the assignment and move on to next token
        token_it->type = TokenType::INTEGER_REGISTER;
        token_it++;
    }

    return *this;
}

ValidateASM& ValidateASM::RF(unsigned int count)
{
    for(int i=0; i<count; i++)
    {
        const std::string& str = token_it->str;
        if(str.length() < 3 || str.length() > 4 || str.at(0) != '$' || str.at(1) != 'F')
        {
            std::string errorStr {"ASSEMBLER: not a valid float register ("};
            errorStr += str;
            errorStr += ").";
            throw std::runtime_error(errorStr);
        }

        //do the assignment and move on to next token
        token_it->type = TokenType::FLOAT_REGISTER;
        token_it++;
    }

    return *this;
}

ValidateASM& ValidateASM::RD(unsigned int count)
{
    for(int i=0; i<count; i++)
    {
        const std::string& str = token_it->str;
        if(str.length() < 3 || str.length() > 4 || str.at(0) != '$' || str.at(1) != 'D')
        {
            std::string errorStr {"ASSEMBLER: not a valid double register ("};
            errorStr += str;
            errorStr += ").";
            throw std::runtime_error(errorStr);
        }

        //do the assignment and move on to next token
        token_it->type = TokenType::DOUBLE_REGISTER;
        token_it++;
    }

    return *this;
}

} //namespace Logi
