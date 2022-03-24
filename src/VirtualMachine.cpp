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
    std::cout << this->executable << std::endl;
    //std::cout << this->executable;
    std::cout << (*this->ram);
    //std::cout << std::endl;

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

    //set register temp
    //registers.R1_24(2) = 0x04; // 14_LAI.RUN test
    //registers.R1_24(3) = 0x0b; // 15_LAI_LWI_LBI_HALT.RUN test
    //registers.R1_24(4) = 0x04; // 16_LB_HALT.RUN test through to 21_LF2_HALT.RUN
    //
    //SB_HALT.RUN through SQ_SQ_HALT.RUN
    //registers.R1_24(1) = 0xfa37ef58;
    //registers.R1_24(2) = 0x15a;
    //registers.R1_24(3) = 0x14;
    //registers.R1_24(4) = 0xabcdef12ea34fa37;
    //
    //registers.RF(0) = 0xf;
    //registers.RF(1) = 0xabcdef;

    //pushpop byte
    //registers.R1_24(1) = 0xf;
    //registers.R1_24(2) = 0x73;
    //pushpop word
    //registers.R1_24(1) = 0xfa73;
    //registers.R1_24(2) = 0x87bc;
    //pushpop dword
    //registers.R1_24(1) = 0xbe73ab91;
    //registers.R1_24(2) = 0x87bc73fa;
    //pushpop dword
    //registers.R1_24(1) = 0xbe73ab9157c5d3a8;
    //registers.R1_24(2) = 0x87bc73fa7c5a8e9b;
    //pushpop float
    //registers.RF($F1) = 565465; //0xbe73ab91;
    //registers.RF($F2) = 65454; //0x87bc73fa;
    //pushpop double
    //registers.RD($D1) = 35635632;//0xbe73ab9157c5d3a8;
    //registers.RD($D2) = 345343;//0x87bc73fa7c5a8e9b;

    //mov
    //registers.R1_24(1) = 0xf;
    //registers.R1_24(2) = 0xff;
    //registers.RF($F1) = 1;
    //registers.RF($F2) = 354343;
    //registers.RD($D1) = 2;
    //registers.RD($D2) = 34354353;

    //jump
    //registers.R1_24(1) = 0x7;
    //registers.R1_24(2) = 0x7;
    //registers.R1_24(3) = 0x22;
    //registers.R1_24(4) = 0x21;
    //registers.R1_24(5) = 0x1;

    //bitwise
    //registers.R1_24(1) = 0x7;
    //registers.R1_24(2) = 0x7;
    //registers.R1_24(3) = 0x0;
    //registers.R1_24(4) = 33;
    //registers.R1_24(5) = 0x5; //test bit 5

    //shift
    registers.R1_24(1) = 0x0;
    registers.R1_24(2) = 0xf0f0f0f0;
    registers.R1_24(3) = 0x5; //shift

    while((*ram)(registers.R($IP)) != OpCodes::HALT)
    {
        iset->debug_pre();

        switch((*ram)(registers.R($IP)))
        {
            case LBI: iset->LBI(); break;
            case LWI: iset->LWI(); break;
            case LDI: iset->LDI(); break;
            case LQI: iset->LQI(); break;
            case LF1I: iset->LF1I(); break;
            case LF2I: iset->LF2I(); break;
            case LAD: iset->LAD(); break;
            case LAI: iset->LAI(); break;
            case LB: iset->LB(); break;
            case LW: iset->LW(); break;
            case LD: iset->LD(); break;
            case LQ: iset->LQ(); break;
            case LF1: iset->LF1(); break;
            case LF2: iset->LF2(); break;
            case SB: iset->SB(); break;
            case SW: iset->SW(); break;
            case SD: iset->SD(); break;
            case SQ: iset->SQ(); break;
            case SF1: iset->SF1(); break;
            case SF2: iset->SF2(); break;
            case PUSHB: iset->PUSHB(); break;
            case PUSHW: iset->PUSHW(); break;
            case PUSHD: iset->PUSHD(); break;
            case PUSHQ: iset->PUSHQ(); break;
            case PUSHF1: iset->PUSHF1(); break;
            case PUSHF2: iset->PUSHF2(); break;
            case POPB: iset->POPB(); break;
            case POPW: iset->POPW(); break;
            case POPD: iset->POPD(); break;
            case POPQ: iset->POPQ(); break;
            case POPF1: iset->POPF1(); break; //UNIMPL.
            case POPF2: iset->POPF2(); break; //UNIMPL.
            case MOV: iset->MOV(); break;
            case MOVF: iset->MOVF(); break;
            case MOVD: iset->MOVD(); break;
            case JMP: iset->JMP(); break;
            case JE: iset->JE(); break;
            case JNE: iset->JNE(); break;
            case SLT: iset->SLT(); break;
            case INT: iset->INT(); break;
            case DI: iset->DI(); break;
            case EI: iset->EI(); break;
            case HALT: iset->HALT(); break;
            case NOP: iset->NOP(); break;
            case AND: iset->AND(); break;
            case OR: iset->OR(); break;
            case XOR: iset->XOR(); break;
            case NOT: iset->NOT(); break;
            case BT: iset->BT(); break;
            case BS: iset->BS(); break;
            case SRA: iset->SRA(); break;
            case SRL: iset->SRL(); break;
            case SL: iset->SL(); break;
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
            default: throw std::runtime_error("VIRTUAL_MACHINE: invalid instruction.");
        }

        iset->debug_post();
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
