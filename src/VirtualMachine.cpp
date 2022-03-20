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
    stream->string("VM: Initializing virtual machine...\n");
    stream->string("VM: Loading bytecode executable...\n");
    //load the bytecode
    executable.load(argc,argv,*this);
    stream->string("VM: Bytecode executable loaded.\n");

    //debug
    std::cout << this->registers;
    std::cout << this->executable;
    std::cout << (*this->ram);
    std::cout << std::endl;

    //validate the bytecode
    validateBytecode();
    stream->string("VM: bytecode passed validation!\n");
}

void VirtualMachine::run()
{
    stream->string("VM: running...\n");

    //std::ofstream ramDump("RAM_DUMP.BIN",std::ios::binary | std::ios::out);
    //ramDump << (*this->ram);
    //ramDump.close();

    int index {0}; //TEMP FOR TESTING
    while((*ram)(registers.R($IP)) != OpCodes::HALT)
    {
        //switch((*ram)(registers.R($IP)))
        switch((*ram)(registers.R(index))) // !!!!!!!TEMP FOR TESTING
        {
            case LBI: break;
            case LWI: break;
            case LDI: break;
            case LQI: break;
            case LF1I: break;
            case LF2I: break;
            case LAD: break;
            case LAI: break;
            case LB: break;
            case LW: break;
            case LD: break;
            case LQ: break;
            case LF1: break;
            case LF2: break;
            case SB: break;
            case SW: break;
            case SD: break;
            case SQ: break;
            case SF1: break;
            case SF2: break;
            case PUSHB: break;
            case PUSHW: break;
            case PUSHD: break;
            case PUSHQ: break;
            case PUSHF1: break;
            case PUSHF2: break;
            case POPB: break;
            case POPW: break;
            case POPD: break;
            case POPQ: break;
            case POPF1: break;
            case POPF2: break;
            case MOV: break;
            case MOVF: break;
            case MOVD: break;
            case JMP: break;
            case JE: break;
            case JNE: break;
            case SLT: break;
            case INT: break;
            case DI: break;
            case EI: break;
            case HALT: iset->HALT(); break;
            case NOP: break;
            case AND: break;
            case OR: break;
            case XOR: break;
            case NOT: break;
            case BT: break;
            case BS: break;
            case SRA: break;
            case SRL: break;
            case SL: break;
            case ADD: break;
            case SUB: break;
            case MULT: break;
            case DIV: break;
            case CAST_IF: break;
            case CAST_ID: break;
            case CAST_FI: break;
            case CAST_FD: break;
            case CAST_DI: break;
            case CAST_DF: break;
            case FADD: break;
            case FSUB: break;
            case FMULT: break;
            case FDIV: break;
            case FSLT: break;
            case DADD: break;
            case DSUB: break;
            case DMULT: break;
            case DDIV: break;
            case DSLT: break;
            default: throw std::runtime_error("invalid instruction.");
        }
        index++;
    }
    
    std::cout << std::endl << std::endl;
    for(int i=0; i<ram->size(); i++)
    {
        std::cout << (int)(*ram)(i) << 'x';
    }
}

void VirtualMachine::shutdown()
{
    stream->string("VM: shutting down...\n");
    exit(0); //TEMP
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

    stream->string("stopByte = ").U8(stopByte).endl();

    while(currentByte < stopByte)
    {
        stream->string("while() : currentByte = ").U8(currentByte).endl();
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
            case LF1I: //LF1I $R1, BBD
            {
                validate->opcode() /* B */
                    .R().operand() /* $R1 */
                    .end_dword(); /* D */
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
            MOVF: // MOVF $F1,$F2
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
                throw std::runtime_error("bad opcode.");
            }
        }
    }
}

} //namespace Logi
