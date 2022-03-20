//Logi includes
#include "VirtualMachine.h"
#include "Stream.h"
#include "Validator.h"

//std includes
#include <iostream>
#include <fstream>

namespace Logi
{

VirtualMachine::VirtualMachine() : registers{},ram{nullptr},validate{nullptr}
{
    ram = new Logi::RAM();
    iset = InstructionSet::getInstance();
    stream = Stream::getInstance();
    transform = Transform::getInstance();
}

VirtualMachine::~VirtualMachine()
{
    if(ram != nullptr) delete ram;
    if(validate != nullptr) delete validate;
}

const Logi::RAM* VirtualMachine::RAM() const
{
    return ram;
}

void VirtualMachine::init(int argc,char* argv[])
{
    stream->string("VM: Initializing virtual machine...").endl();
    stream->string("VM: Loading bytecode executable...").endl();
    //load the bytecode
    executable.load(argc,argv,*this);

    stream->string("VM: Bytecode executable loaded.").endl();
}

void VirtualMachine::run()
{
    stream->string("VM: running...").endl();

    std::cout << this->registers;
    std::cout << this->executable;
    std::cout << (*this->ram);

    std::ofstream ramDump("RAM_DUMP.BIN",std::ios::binary | std::ios::out);
    ramDump << (*this->ram);
    ramDump.close();
}

void VirtualMachine::shutdown()
{
    stream->string("VM: shutting down...").endl();
}

std::ostream& operator<<(std::ostream& out,const VirtualMachine& vm)
{
    out << vm.executable << std::endl;
    out << vm.registers << std::endl;
    out << (*vm.ram) << std::endl;
    return out;
}

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

    validate = new Validator(currentByte,stopByte,registers,ram);

    while(currentByte < stopByte)
    {
        switch((*ram)(currentByte))
        {
            case LBI: //LBI $R1, BBB
            {
                validate
                    ->opcode()
                    .R()
                    .operand()
                    .end_byte();
            }
            break;
            case LWI: //LWI $R1, BBW
            {
                validate
                    ->opcode()
                    .R()
                    .operand()
                    .end_word();
            }
            break;
            case LDI: //LDI $R1, BBD
            {
                validate
                    ->opcode()
                    .R()
                    .operand()
                    .end_dword();
            }
            break;
            case LQI: //LQI $R1, BBQ
            {
                validate
                    ->opcode()
                    .R()
                    .operand()
                    .end_qword();
            }
            break;
            case LF1I: //LF1I $R1, BBD
            {
                validate
                    ->opcode()
                    .R()
                    .operand()
                    .end_dword();
            }
            break;
            case LF2I: //LF2I $R1, BBQ
            {
                validate->opcode() /* B */
                    .R().operand() /* $R1 */
                    .end_qword(); /* Q */
            }
            break;
            case LAD: //LAD $R1, address = BBQ
            {
                validate->opcode() /* B */
                    .R().operand() /* $R1 */
                    .address(TypeTag::F4_TAG).end_qword(); /* Q */
            }
            break;
            case LAI: //LAI $R1,$R2,qword,  BBBQ
            {
                validate->opcode() /* B */
                    .R().operand() /* $R1 */
                    .R().operand() /* $R2 */
                    .end_qword(); /* Q */
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
                //
            }
            break;
            case LF1: // LF1 $F1,$R1,       BBB
            case SF1:
            {
                //
            }
            break;
            case LF2: // LF2 $D1,$R1,       BBB
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
            MOVF: // MOVF $F1,$F2
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
            case DADD: // FADD $F1,$F2,$F3 BBBB
            case DSUB:
            case DMULT:
            case DDIV:
            case DSLT:
            {
                //
            }
            break;
            default:
            {
                //
            }
        }
    }
}

} //namespace Logi
