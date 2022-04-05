//Logi includes
#include "../Assembler.h"
#include "../ValidateASM.h"

namespace Logi
{

//
// Here we give each token the correct identity and also
// check for logical errors in the assembler.
//
void Assembler::identifyTokens()
{
    std::vector<Line>::iterator tokenizedLines_it = tokenizedLines.begin();
    bool match;

    while(tokenizedLines_it != tokenizedLines.end())
    {
        std::vector<Token>::iterator token_it = tokenizedLines_it->tokens.begin(); //get first token on line

        //begin validator for current line
        ValidateASM validator {*tokenizedLines_it,token_it};

        //and check it against the possible opcodes
        match = checkOpCodes(validator);

        //if no match check against possible assembler identifiers
        if(!match) checkASMIds(validator);

        ++tokenizedLines_it;
    }
}

const bool Assembler::checkOpCodes(ValidateASM& validator)
{
    bool match = true;

    validator.setDefaultAssign(TokenType::INSTRUCTION); //all default assignments are instructions

    switch(validator.getInstr())
    {
        case LBI: //LBI $R1, BBB
        case LWI: //LWI $R1, BBW
        case LDI: //LDI $R1, BBD
        case LQI: //LQI $R1, BBQ
        {
            validator.count(3).assign().R().assign(INTEGER_CONSTANT);
        }
        break;
        case LF1I: //LF1I $F1, BBD
        {
            validator.count(3).assign().RF().assign(FLOAT_CONSTANT);
        }
        break;
        case LF2I: //LF2I $D1, BBQ
        {
            validator.count(3).assign().RD().assign(FLOAT_CONSTANT);
        }
        break;
        case LAD: //LAD $R1, address = BBQ
        {
            validator.count(3).assign().R().assign(IDENTIFIER);
        }
        break;
        case LAI: //LAI $R1,$R2,qword,  BBBQ
        {
            validator.count(4).assign().R(2).assign(IDENTIFIER);
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
            validator.count(3).assign().R(2);
        }
        break;
        case LF1: // LF1 $F1,$R1,       BBB
        case SF1:
        {
            validator.count(3).assign().RF().R();
        }
        break;
        case LF2: // LF2 $D1,$R1,       BBB
        case SF2:
        {
            validator.count(3).assign().RD().R();
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
            validator.count(2).assign().R();
        }
        break;
        case PUSHF1: // PUSHF1 $F
        case POPF1:
        {
            validator.count(2).assign().RF();
        }
        break;
        case PUSHF2:
        case POPF2:
        {
            validator.count(2).assign().RD();
        }
        break;
        case MOVF: // MOVF $F1,$F2
        {
            validator.count(3).assign().RF(2);
        }
        break;
        case MOVD: // MOVD $D1,$D2
        {
            validator.count(3).assign().RD(2);
        }
        break;
        case MOV: // MOV $R1,$R2
        case NOT: // NOT $R1,$R2
        case BS: // BS $R1,$R2
        {
            validator.count(3).assign().R(2);
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
            validator.count(4).assign().R(3);
        }
        break;
        case INT: // INT #vector BB
        {
            validator.count(2).assign().assign(INTEGER_CONSTANT);
        }
        break;
        case EI:
        case DI:
        case HALT:
        case NOP:
        {
            validator.count(1).assign();
        }
        break;
        case DIV: // DIV $R1,$R2,$R3,$R4
        {
            validator.count(5).assign().R(4);
        }
        break;
        case CAST_IF: // CAST_IF $R,$F
        {
            validator.count(3).assign().R().RF();
        }
        break;
        case CAST_ID: // CAST_ID $R,$D
        {
            validator.count(3).assign().R().RD();
        }
        break;
        case CAST_FI: // CAST_FI $F,$R
        {
            validator.count(3).assign().RF().R();
        }
        break;
        case CAST_FD: // CAST_FD $F,$D
        {
            validator.count(3).assign().RF().RD();
        }
        break;
        case CAST_DI: // CAST_DI $D,$R
        {
            validator.count(3).assign().RD().R();
        }
        break;
        case CAST_DF: // CAST_DF $D,$F
        {
            validator.count(3).assign().RD().RF();
        }
        break;
        case FADD: // FADD $F1,$F2,$F3 BBBB
        case FSUB:
        case FMULT:
        case FDIV:
        case FSLT:
        {
            validator.count(4).assign().RF(3);
        }
        break;
        case DADD: // DADD $D1,$D2,$D3 BBBB
        case DSUB:
        case DMULT:
        case DDIV:
        case DSLT:
        {
            validator.count(4).assign().RD(3);
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

void Assembler::checkASMIds(ValidateASM& validator)
{
    validator.setDefaultAssign(TokenType::DIRECTIVE); //all default assignments are directives

    switch(validator.getId())
    {
        case GB:
        {
            int count = validator.count(2,3);
            validator.assign();
            count == 2 ? validator.assign(IDENTIFIER) : validator.assign(IDENTIFIER).assign(INTEGER_CONSTANT);
        }
        break;
        case GW:
        {
            int count = validator.count(2,3);
            validator.assign();
            count == 2 ? validator.assign(IDENTIFIER) : validator.assign(IDENTIFIER).assign(INTEGER_CONSTANT);
        }
        break;
        case GD:
        {
            int count = validator.count(2,3);
            validator.assign();
            count == 2 ? validator.assign(IDENTIFIER) : validator.assign(IDENTIFIER).assign(INTEGER_CONSTANT);
        }
        break;
        case GQ:
        {
            int count = validator.count(2,3);
            validator.assign();
            count == 2 ? validator.assign(IDENTIFIER) : validator.assign(IDENTIFIER).assign(INTEGER_CONSTANT);
        }
        break;
        case PB:
        {
            validator.count(2).assign().assign(IDENTIFIER);
        }
        break;
        case PE:
        {
            validator.count(1).assign();
        }
        break;
        case PR:
        case PA:
        case PV:
        {
            validator.count(3).assign().assign(IDENTIFIER).assign(INTEGER_CONSTANT);
        }
        break;
        case PL:
        {
            validator.count(2).assign().assign(IDENTIFIER);
        }
        break;
        case BAD_ID:
        default:
        {
            throw std::runtime_error("ASSEMBLER: bad token.");
        }
    }
}

} //namespace Logi
