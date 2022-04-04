//Logi includes
#include "../Assembler.h"
#include "../InstructionSet.h"

//TEMP
#include <iostream>

namespace Logi
{

//
// Here we give each token the correct identity and also
// check for logical errors in the assembler.
//
void Assembler::assignTokenIds()
{
    std::vector<Line>::iterator tokenizedLines_it = tokenizedLines.begin();
    bool match;

    while(tokenizedLines_it != tokenizedLines.end())
    {
        std::vector<Token>::iterator token_it = tokenizedLines_it->tokens.begin(); //get first token
        match;

        //and check it against the possible opcodes
        match = checkOpCodes(*tokenizedLines_it,*token_it);

        //check against possible assembler identifiers
        if(!match) checkASMIds(*tokenizedLines_it,*token_it);

        ++tokenizedLines_it;
    }
}

const bool Assembler::checkOpCodes(Line& line,Token& token)
{
    bool match = true;

    switch(InstructionSet::OpCode_fromStr(token.str))
    {
        case LBI: //LBI $R1, BBB
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case LWI: //LWI $R1, BBW
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case LDI: //LDI $R1, BBD
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case LQI: //LQI $R1, BBQ
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case LF1I: //LF1I $R1, BBD
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case LF2I: //LF2I $R1, BBQ
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case LAD: //LAD $R1, address = BBQ
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case LAI: //LAI $R1,$R2,qword,  BBBQ
        {
            Assembler::checkTokenCount(line,4);
        }
        break;
        case LB: // LB $R1,$R2,     BBB
        case LW:
        case LD:
        case LQ:
        case SB: // SB $R1,$R2,     BBB
        case SW:
        case SD:
        case SQ:
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case LF1: // LF1 $F1,$R1,       BBB
        case SF1:
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case LF2: // LF2 $D1,$R1,       BBB
        case SF2:
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case PUSHB: // PUSHB $R1, BB
        case PUSHW:
        case PUSHD:
        case PUSHQ:
        case POPB:
        case POPW:
        case POPD:
        case POPQ:
        case JMP:
        {
            Assembler::checkTokenCount(line,2);
        }
        break;
        case PUSHF1: // PUSHF1 $F
        case POPF1:
        {
            Assembler::checkTokenCount(line,2);
        }
        break;
        case PUSHF2:
        case POPF2:
        {
            Assembler::checkTokenCount(line,2);
        }
        break;
        case MOVF: // MOVF $F1,$F2
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case MOVD: // MOVD $D1,$D2
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case MOV:
        case NOT:
        case BS:
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case JE:
        case JNE:
        case SLT:
        case AND:
        case OR:
        case XOR:
        case BT:
        case SRA:
        case SRL:
        case SL:
        case ADD:
        case SUB:
        case MULT:
        {
            Assembler::checkTokenCount(line,4);
        }
        break;
        case INT: // INT #vector BB
        {
            // TODO!
        }
        break;
        case EI:
        case DI:
        case HALT:
        case NOP:
        {
            Assembler::checkTokenCount(line,1);
        }
        break;
        case DIV: // DIV $R1,$R2,$R3,$R4
        {
            Assembler::checkTokenCount(line,5);
        }
        break;
        case CAST_IF: // CAST_IF $R,$F
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case CAST_ID: // CAST_ID $R,$D
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case CAST_FI: // CAST_FI $F,$R
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case CAST_FD: // CAST_FD $F,$D
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case CAST_DI: // CAST_DI $D,$R
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case CAST_DF: // CAST_DF $D,$F
        {
            Assembler::checkTokenCount(line,3);
        }
        break;
        case FADD: // FADD $F1,$F2,$F3 BBBB
        case FSUB:
        case FMULT:
        case FDIV:
        case FSLT:
        {
            Assembler::checkTokenCount(line,4);
        }
        break;
        case DADD: // DADD $D1,$D2,$D3 BBBB
        case DSUB:
        case DMULT:
        case DDIV:
        case DSLT:
        {
            Assembler::checkTokenCount(line,4);
        }
        break;
        case BAD:
        default:
        {
            match = false;
        }
    }

    return match;
}

void Assembler::checkASMIds(Line& line,Token& token)
{
    switch(Assembler::ASMIdentifier_fromStr(token.str))
    {
        case GB:
        {
            //
        }
        break;
        case GW:
        {
            //
        }
        break;
        case GD:
        {
            //
        }
        break;
        case GQ:
        {
            //
        }
        break;
        case PB:
        {
            //
        }
        break;
        case PE:
        {
            //
        }
        break;
        case PR:
        {
            //
        }
        break;
        case PA:
        {
            //
        }
        break;
        case PV:
        {
            //
        }
        break;
        case PL:
        {
            //
        }
        break;
        case BAD_ID:
        default:
        {
            std::cout << line << " : " << token.str << std::endl;
            throw std::runtime_error("ASSEMBLER: bad token.");
        }
    }
}

//////////////////////////////////////////////////////////////
////////////////////// ASSEMBLER CHECKS //////////////////////
//////////////////////////////////////////////////////////////
// if checks fail a runtime error is thrown
//////////////////////////////////////////////////////////////
void Assembler::checkTokenCount(const Line& line,const int expectedCount)
{
    if(expectedCount != line.tokens.size())
    {
        std::cout << line << " : " << line.tokens.size() << " != " << expectedCount << " (expected)\n";
        std::cout << "first token string = " << line.tokens.at(0).str << std::endl;
        throw std::runtime_error("ASSEMBLER: invalid number of tokens on line.");
    }
}

void Assembler::checkTokenCountWithinRange(const Line& line,const int start,const int end)
{
    if(line.tokens.size() < start || line.tokens.size() > end)
    {
        std::cout << line << " : " << line.tokens.size() << " not in range [" << start << ',' << end << "] (expected)\n";
        throw std::runtime_error("ASSEMBLER: invalid number of tokens on line.");
    }
}

const RegisterCodes Assembler::checkIntRegister(const std::string& str)
{
    throw std::runtime_error("ASSEMBLER: unimplemented check.");
}

const FloatRegisterCodes Assembler::checkFloatRegister(const std::string& str)
{
    throw std::runtime_error("ASSEMBLER: unimplemented check.");
}

const DoubleRegisterCodes Assembler::checkDoubleRegister(const std::string& str)
{
    throw std::runtime_error("ASSEMBLER: unimplemented check.");
}

} //namespace Logi
