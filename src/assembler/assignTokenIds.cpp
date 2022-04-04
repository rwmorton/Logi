//Logi includes
#include "../Assembler.h"
#include "../ValidateASM.h"

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

        //begin validator for current line
        ValidateASM validator {*tokenizedLines_it,token_it};

        //and check it against the possible opcodes
        match = checkOpCodes(validator);

        //check against possible assembler identifiers
        //if(!match) checkASMIds(validator);

        ++tokenizedLines_it;
    }
}

const bool Assembler::checkOpCodes(ValidateASM& validator)
{
    bool match = true;

    switch(validator.getInstr())
    {
        case LBI: //LBI $R1, BBB
        case LWI: //LWI $R1, BBW
        case LDI: //LDI $R1, BBD
        case LQI: //LQI $R1, BBQ
        {
            validator.count(3)
                .assign(INSTRUCTION) /* L{B,W,D,Q}I */
                .R() /* $R1 */
                .assign(INTEGER_CONSTANT); /* {B,W,D,Q} */
        }
        break;
        case LF1I: //LF1I $F1, BBD
        {
            validator.count(3)
                .assign(INSTRUCTION) /* LF1I */
                .RF() /* $F1 */
                .assign(FLOAT_CONSTANT); /* D */
        }
        break;
        case LF2I: //LF2I $D1, BBQ
        {
            validator.count(3)
                .assign(INSTRUCTION) /* LF2I */
                .RD() /* $D1 */
                .assign(FLOAT_CONSTANT); /* Q */
        }
        break;
        case LAD: //LAD $R1, address = BBQ
        {
            validator.count(3)
                .assign(INSTRUCTION) /* LAD */
                .R() /* $R1 */
                .assign(INTEGER_CONSTANT); /* Q */
        }
        break;
        case LAI: //LAI $R1,$R2,qword,  BBBQ
        {
            validator.count(4)
                .assign(INSTRUCTION) /* LAI */
                .R().R() /* $R1,$R2 */
                .assign(IDENTIFIER); /* Q */
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
            validator.count(3)
                .assign(INSTRUCTION) /* {L,S}{B,W,D,Q} */
                .R().R(); /* $R1,$R2 */
        }
        break;
        case LF1: // LF1 $F1,$R1,       BBB
        case SF1:
        {
            validator.count(3)
                .assign(INSTRUCTION) /* {L,S}F1 */
                .RF().R(); /* $F1,$R1 */
        }
        break;
        case LF2: // LF2 $D1,$R1,       BBB
        case SF2:
        {
            //
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
            //
        }
        break;
        case PUSHF1: // PUSHF1 $F
        case POPF1:
        {
            //
        }
        break;
        case PUSHF2:
        case POPF2:
        {
            //
        }
        break;
        case MOVF: // MOVF $F1,$F2
        {
            //
        }
        break;
        case MOVD: // MOVD $D1,$D2
        {
            //
        }
        break;
        case MOV:
        case NOT:
        case BS:
        {
            //
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
            //
        }
        break;
        case INT: // INT #vector BB
        {
            //
        }
        break;
        case EI:
        case DI:
        case HALT:
        case NOP:
        {
            //
        }
        break;
        case DIV: // DIV $R1,$R2,$R3,$R4
        {
            //
        }
        break;
        case CAST_IF: // CAST_IF $R,$F
        {
            //
        }
        break;
        case CAST_ID: // CAST_ID $R,$D
        {
            //
        }
        break;
        case CAST_FI: // CAST_FI $F,$R
        {
            //
        }
        break;
        case CAST_FD: // CAST_FD $F,$D
        {
            //
        }
        break;
        case CAST_DI: // CAST_DI $D,$R
        {
            //
        }
        break;
        case CAST_DF: // CAST_DF $D,$F
        {
            //
        }
        break;
        case FADD: // FADD $F1,$F2,$F3 BBBB
        case FSUB:
        case FMULT:
        case FDIV:
        case FSLT:
        {
            //
        }
        break;
        case DADD: // DADD $D1,$D2,$D3 BBBB
        case DSUB:
        case DMULT:
        case DDIV:
        case DSLT:
        {
            //
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
    switch(validator.getId())
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
            throw std::runtime_error("ASSEMBLER: bad token.");
        }
    }
}

} //namespace Logi
