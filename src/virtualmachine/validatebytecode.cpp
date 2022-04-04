//Logi includes
#include "../VirtualMachine.h"

//temp
#include <iostream>
using std::cout;
using std::endl;

namespace Logi
{

//
// validation begins at address 0 and continues until the beginning
// of the heap segemenht is reached. each time an instruction has
// been validated the next byte is expected to be an instruction
// opcode or the end of the text segment.
//
void VirtualMachine::validateBytecode()
{
    U8 currentByte = 0;
    U8 stopByte  = registers.R(RegisterCodes::$HS);     //heap start address

    validate = new Validator(currentByte,stopByte,iset,registers,ram);

    while(currentByte < stopByte)
    {
        switch((*ram)(currentByte))
        {
            case LBI: //LBI $R1, BBB
            {
                validate->opcode() /* B */
                    .R().operand() /* R1 */
                    .end_byte(); /* B */
            }
            break;
            case LWI: //LWI $R1, BBW
            {
                validate->opcode() /* B */
                    .R().operand() /* $R1 */
                    .end_word(); /* W */
            }
            break;
            case LDI: //LDI $R1, BBD
            {
                validate->opcode() /* B */
                    .R().operand() /* $R1 */
                    .end_dword(); /* D */
            }
            break;
            case LQI: //LQI $R1, BBQ
            {
                validate->opcode() /* B */
                    .R().operand() /* $R1 */
                    .end_qword(); /* Q */
            }
            break;
            case LF1I: //LF1I $F1, BBD
            {
                validate->opcode() /* B */
                    .RF().operand() /* $R1 */
                    .end_dword(); /* D */
            }
            break;
            case LF2I: //LF2I $D1, BBQ
            {
                validate->opcode() /* B */
                    .RD().operand() /* $R1 */
                    .end_qword(); /* Q */
            }
            break;
            case LAD: //LAD $R1, address = BBQ
            {
                validate->opcode() /* B */
                    .R().operand() /* $R1 */
                    .address(TypeTag::U8_TAG).end(); /* Q */
            }
            break;
            case LAI: //LAI $R1,$R2,qword,  BBBQ
            {
                validate->opcode() /* B */
                    .R().operand() /* $R1 */
                    .R().operand() /* $R2 */
                    .address(TypeTag::U8_TAG) /* qword (address) */
                    .end();
                    //.end_qword(); /* Q */
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
                validate->opcode() /* B */
                    .R().operand() /* $R1 */
                    .R().operand() /* $R2 */
                    .end();
            }
            break;
            case LF1: // LF1 $F1,$R1,       BBB
            case SF1:
            {
                validate->opcode() /* B */
                    .RF().operand() /* $F */
                    .R().operand() /* $R1 */
                    .end();
            }
            break;
            case LF2: // LF2 $D1,$R1,       BBB
            case SF2:
            {
                validate->opcode() /* B */
                    .RD().operand() /* $D */
                    .R().operand() /* $R1 */
                    .end();
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
                validate->opcode() /* B */
                    .R().operand() /* $R1 */
                    .end();
            }
            break;
            case PUSHF1: // PUSHF1 $F
            case POPF1:
            {
                validate->opcode() /* B */
                    .RF().operand() /* $F */
                    .end();
            }
            break;
            case PUSHF2:
            case POPF2:
            {
                validate->opcode() /* B */
                    .RD().operand() /* $D */
                    .end();
            }
            break;
            case MOVF: // MOVF $F1,$F2
            {
                validate->opcode() /* B */
                    .RF().operand() /* $F1 */
                    .RF().operand() /* $F2 */
                    .end();
            }
            break;
            case MOVD: // MOVD $D1,$D2
            {
                validate->opcode() /* B */
                    .RD().operand() /* $D1 */
                    .RD().operand() /* $D2 */
                    .end();
            }
            break;
            case MOV:
            case NOT:
            case BS:
            {
                validate->opcode() /* B */
                    .R().operand() /* $R1 */
                    .R().operand() /* $R2 */
                    .end();
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
                validate->opcode() /* B */
                    .R().operand() /* $R1 */
                    .R().operand() /* $R2 */
                    .R().operand() /* $R3 */
                    .end();
            }
            break;
            case INT: // INT #vector BB
            {
                validate->opcode() /* B */
                    .end_byte(); /* B */
            }
            break;
            case EI:
            case DI:
            case HALT:
            case NOP:
            {
                //validate single byte and
                //then do end byte check.
                validate->opcode(true); /* B */
                return;
            }
            break;
            case DIV: // DIV $R1,$R2,$R3,$R4
            {
                validate->opcode() /* B */
                    .R().operand() /* $R1 */
                    .R().operand() /* $R2 */
                    .R().operand() /* $R3 */
                    .end();
            }
            break;
            case CAST_IF: // CAST_IF $R,$F
            {
                validate->opcode() /* B */
                    .R().operand() /* $R1 */
                    .RF().operand() /* $F */
                    .end();
            }
            break;
            case CAST_ID: // CAST_ID $R,$D
            {
                validate->opcode() /* B */
                    .R().operand() /* $R1 */
                    .RD().operand() /* $D */
                    .end();
            }
            break;
            case CAST_FI: // CAST_FI $F,$R
            {
                validate->opcode() /* B */
                    .RF().operand() /* $F */
                    .R().operand() /* $R1 */
                    .end();
            }
            break;
            case CAST_FD: // CAST_FD $F,$D
            {
                validate->opcode() /* B */
                    .RF().operand() /* $F */
                    .RD().operand() /* $D */
                    .end();
            }
            break;
            case CAST_DI: // CAST_DI $D,$R
            {
                validate->opcode() /* B */
                    .RD().operand() /* $D */
                    .R().operand() /* $R1 */
                    .end();
            }
            break;
            case CAST_DF: // CAST_DF $D,$F
            {
                validate->opcode() /* B */
                    .RD().operand() /* $D */
                    .RF().operand() /* $F */
                    .end();
            }
            break;
            case FADD: // FADD $F1,$F2,$F3 BBBB
            case FSUB:
            case FMULT:
            case FDIV:
            case FSLT:
            {
                validate->opcode() /* B */
                    .RF().operand() /* $F1 */
                    .RF().operand() /* $F2 */
                    .RF().operand() /* $F3 */
                    .end();

                //after testing
                //validate->opcode().RF(3).end();
            }
            break;
            case DADD: // FADD $F1,$F2,$F3 BBBB
            case DSUB:
            case DMULT:
            case DDIV:
            case DSLT:
            {
                validate->opcode() /* B */
                    .RD().operand() /* $D1 */
                    .RD().operand() /* $D2 */
                    .RD().operand() /* $D3 */
                    .end();
                
                //after testing
                //validate->opcode().RD(3).end();
            }
            break;
            default:
            {
                throw std::runtime_error("VALIDATOR: bad opcode.");
            }
        }
    }
}

} //namespace Logi
