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
    iset = new InstructionSet{this};
    stream = Stream::getInstance();
    transform = Transform::getInstance();
}

VirtualMachine::~VirtualMachine()
{
    if(ram != nullptr) delete ram;
    if(iset != nullptr) delete iset;
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

    while((*ram)(registers.R($IP)) != OpCodes::HALT)
    {
        switch((*ram)(registers.R($IP)))
        {
            case LBI: iset->LBI(); break;
            case LWI: iset->LWI(); break;
            case LDI: iset->LDI(); break;
            case LQI: iset->LQI(); break;
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

} //namespace Logi
