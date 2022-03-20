//Logi includes
#include "VirtualMachine.h"
#include "Stream.h"
#include "Validator.h"

//std includes
#include <iostream>
#include <fstream>

namespace Logi
{

const std::string VirtualMachine::OPCODE {"opcode = "};
const std::string VirtualMachine::OPERAND {"operand = "};
const std::string VirtualMachine::ADDR {"address = "};
const std::string VirtualMachine::ENDL {'\n'};

VirtualMachine::VirtualMachine() : registers{},ram{nullptr}
{
    ram = new Logi::RAM();
    iset = InstructionSet::getInstance();
    stream = Stream::getInstance();
    validate = Validator::getInstance();
    transform = Transform::getInstance();
}

VirtualMachine::~VirtualMachine()
{
    if(ram != nullptr) delete ram;
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
// validate helpers - note that these use the internal
// currentByte and stopByte.
//
void VirtualMachine::VALIDATE_R()
{
    validate->integerRegister(*ram->at(currentByte),currentByte);
}

void VirtualMachine::VALIDATE_RF()
{
    validate->floatRegister(*ram->at(currentByte),currentByte);
}

void VirtualMachine::VALIDATE_RD()
{
    validate->doubleRegister(*ram->at(currentByte),currentByte);
}

void VirtualMachine::VALIDATE_OPCODE()
{
    stream->string(VirtualMachine::OPCODE).string((*iset)((OpCodes)((*ram)(currentByte)))).string(VirtualMachine::ENDL);
    currentByte++;
    validate->currentByte(currentByte,stopByte);
}

void VirtualMachine::VALIDATE_OPERAND()
{
    stream->string(VirtualMachine::OPERAND).string(registers.R_str((RegisterCodes)((*ram)(currentByte)))).string(VirtualMachine::ENDL);
    currentByte++;
    validate->currentByte(currentByte,stopByte);
}

void VirtualMachine::VALIDATE_END_BYTE()
{
    validate->endCurrentByte(currentByte,stopByte);
    //currentByte += sizeof(U1);
    validate->endCurrentByte(currentByte,stopByte);
}

void VirtualMachine::VALIDATE_END_WORD()
{
    transform->word(ram->at(currentByte),currentByte);
    currentByte += sizeof(U2);
    validate->endCurrentByte(currentByte,stopByte);
}

void VirtualMachine::VALIDATE_END_DWORD()
{
    transform->dword(ram->at(currentByte),currentByte);
    currentByte += sizeof(U4);
    validate->endCurrentByte(currentByte,stopByte);
}

void VirtualMachine::VALIDATE_END_QWORD()
{
    transform->qword(ram->at(currentByte),currentByte);
    currentByte += sizeof(U8);
    validate->endCurrentByte(currentByte,stopByte);
}

void VirtualMachine::VALIDATE_ADDRESS(TypeTag tag)
{
    validate->address(ram->at(currentByte),currentByte,registers);
    switch(tag)
    {
        case TypeTag::S1_TAG: stream->string(ADDR).S1(*((S1*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::U1_TAG: stream->string(ADDR).U1(*((U1*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::S2_TAG: stream->string(ADDR).S2(*((S2*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::U2_TAG: stream->string(ADDR).U2(*((U2*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::S4_TAG: stream->string(ADDR).S4(*((S4*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::U4_TAG: stream->string(ADDR).U4(*((U4*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::S8_TAG: stream->string(ADDR).S8(*((S8*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::U8_TAG: stream->string(ADDR).U8(*((U8*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::F4_TAG: stream->string(ADDR).F4(*((F4*)ram->at(currentByte))).string(ENDL); break;
        case TypeTag::F8_TAG: stream->string(ADDR).F8(*((F8*)ram->at(currentByte))).string(ENDL); break;
        default: throw std::runtime_error("invalid type tag.");
    }
}

//
// validation begins at address 0 and continues until the beginning
// of the heap segemenht is reached. each time an instruction has
// been validated the next byte is expected to be an instruction
// opcode or the end of the text segment.
//
void VirtualMachine::validateBytecode()
{
    currentByte = 0;
    stopByte  = registers.R(RegisterCodes::$HS);     //heap start address

    while(currentByte < stopByte)
    {
        switch((*ram)(currentByte))
        {
            case LBI: //LBI $R1, BBB
            {
                VALIDATE_OPCODE(); //LBI
                VALIDATE_R(); //$R1
                VALIDATE_OPERAND(); //$R1
                VALIDATE_END_BYTE();
            }
            break;
            case LWI: //LWI $R1, BBW
            {
                VALIDATE_OPCODE(); //LWI
                VALIDATE_R(); //$R1
                VALIDATE_OPERAND(); //$R1
                VALIDATE_END_WORD();
            }
            break;
            case LDI: //LDI $R1, BBD
            {
                VALIDATE_OPCODE(); //LDI
                VALIDATE_R(); //$R1
                VALIDATE_OPERAND(); //$R1
                VALIDATE_END_DWORD();
            }
            break;
            case LQI: //LQI $R1, BBQ
            {
                VALIDATE_OPCODE(); //LQI
                VALIDATE_R(); //$R1
                VALIDATE_OPERAND(); //$R1
                VALIDATE_END_QWORD();
            }
            break;
            case LF1I: //LF1I $R1, BBD
            {
                VALIDATE_OPCODE(); //LF1I
                VALIDATE_R(); //$R1
                VALIDATE_OPERAND(); //$R1
                VALIDATE_END_DWORD();
            }
            break;
            case LF2I: //LF2I $R1, BBQ
            {
                VALIDATE_OPCODE(); //LF2I
                VALIDATE_R(); //$R1
                VALIDATE_OPERAND(); //$R1
                VALIDATE_END_QWORD();
            }
            break;
            case LAD: //LAD $R1, address = BBQ
            {
                VALIDATE_OPCODE(); //LAD
                VALIDATE_R(); //$R1
                VALIDATE_OPERAND(); //$R1
                VALIDATE_ADDRESS(TypeTag::F4_TAG);
                VALIDATE_END_QWORD();
            }
            break;
            case LAI: //LAI $R1,$R2,qword,  BBBQ
            {
                VALIDATE_OPCODE(); //LAI
                VALIDATE_R(); //$R1
                VALIDATE_OPERAND(); //$R1
                VALIDATE_R(); //$R2
                VALIDATE_OPERAND(); //$R2
                VALIDATE_END_QWORD();
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
