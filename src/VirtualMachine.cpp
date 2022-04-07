//Logi includes
#include "VirtualMachine.h"
#include "Debugger.h"
#include "Stream.h"
#include "Validator.h"

//std includes
#include <iostream>
#include <fstream>

namespace Logi
{

VirtualMachine::VirtualMachine() : executable(*this),debugger{*this},debugOn(false),registers{},ram{nullptr},validate{nullptr}
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
    executable.load(argc,argv);
    stream->string("VM: Bytecode executable loaded.\n");

    //validate the bytecode
    //validateBytecode();
    //stream->string("VM: bytecode passed validation!\n");
}

void VirtualMachine::run()
{
    stream->string("VM: running...\n");

    //////////////// TEMP!!!!!!
    // force debug on until I can build a proper executable
    debugOn = true;

    U8 debugIP;

    if(debugOn)
    {
        stream->string("Debugger started, enter command:\n");
    }

    while((*ram)(registers.R($IP)) != OpCode::HALT)
    {
        //is debugger on?
        if(debugOn)
        {
            debugger.read();
            debugIP = registers.R($IP); //save current $IP for debug
        }

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
            case ADD: iset->ADD(); break;
            case SUB: iset->SUB(); break;
            case MULT: iset->MULT(); break;
            case DIV: iset->DIV(); break;
            case CAST_IF: iset->CAST_IF(); break;
            case CAST_ID: iset->CAST_ID(); break;
            case CAST_FI: iset->CAST_FI(); break;
            case CAST_FD: iset->CAST_FD(); break;
            case CAST_DI: iset->CAST_DI(); break;
            case CAST_DF: iset->CAST_DF(); break;
            case FADD: iset->FADD(); break;
            case FSUB: iset->FSUB(); break;
            case FMULT: iset->FMULT(); break;
            case FDIV: iset->FDIV(); break;
            case FSLT: iset->FSLT(); break;
            case DADD: iset->DADD(); break;
            case DSUB: iset->DSUB(); break;
            case DMULT: iset->DMULT(); break;
            case DDIV: iset->DDIV(); break;
            case DSLT: iset->DSLT(); break;
            default: throw std::runtime_error("VIRTUAL_MACHINE: invalid instruction.");
        }

        std::ostream& out = stream->get();
        out << "\n\nR($IP) = " << static_cast<int>(registers.R($IP)) << "\n";
        out << "RAM[R($IP)) = " << static_cast<int>((*ram)($IP)) << "\n\n";
        out << static_cast<int>((*ram)(3)) << '\n';

        if(debugOn)
        {
            //print the last executed instruction
            debugger.instruction(debugIP);
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
