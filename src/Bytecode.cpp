//Logi includes
#include "Bytecode.h"
#include "VirtualMachine.h"
#include "Stream.h"

//std includes
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

namespace Logi
{

const unsigned int Bytecode::MAGIC_NUMBER {57069}; //0xDEED
const unsigned int Bytecode::HEADER_SIZE {26};
const unsigned int Bytecode::DEFAULT_STACK_SIZE {1};//{64};
const unsigned int Bytecode::DEFAULT_HEAP_SIZE {1};//{64};

const Flag Bytecode::STACK_FLAG(Bytecode::FlagID::STACK,{"-","sS"},1);
const Flag Bytecode::HEAP_FLAG(Bytecode::FlagID::HEAP,{"-","hH"},1);
const Flag Bytecode::DEBUG_FLAG(Bytecode::FlagID::DEBUG,{"-","dD"},0);

Bytecode::Bytecode(VirtualMachine& vm) :
    vm{vm},
    stackSize{Bytecode::DEFAULT_STACK_SIZE},
    heapSize{Bytecode::DEFAULT_HEAP_SIZE},
    debug{false}
{
    //populate flags
    addFlag(STACK_FLAG);
    addFlag(HEAP_FLAG);
    addFlag(DEBUG_FLAG);
}

Bytecode::~Bytecode() {}

//load the bytecode from command line args
void Bytecode::load(int argc,char* argv[])
{
    std::vector<Flag> flags = parseArgs(argc,argv);
    std::vector<Flag>::iterator flags_it = flags.begin();
    while(flags_it != flags.end())
    {
        switch(flags_it->getId())
        {
            case FlagID::STACK: stackSize = std::stoul(flags_it->arg(0));
            break;
            case FlagID::HEAP: heapSize = std::stoul(flags_it->arg(0));
            break;
            case FlagID::DEBUG: debug = true;
            break;
            default: throw std::runtime_error("BYTECODE: invalid flag id.");
        }

        ++flags_it;
    }

    //load the bytecode file
    std::ifstream in(filename,std::ios::in | std::ios::binary);
    if(!in.is_open())
    {
        throw std::runtime_error("BYTECODE: could not load file.");
    }

    //read in header
    in.read((char*)&magic,2);
    if(magic != Bytecode::MAGIC_NUMBER) throw std::runtime_error("BYTECODE: could not read valid magic number.");
    in.read((char*)&symbolTableSize,8);
    in.read((char*)&stringTableSize,8);
    in.read((char*)&bytecodeSize,8);
    if(bytecodeSize == 0) throw std::runtime_error("BYTECODE: nothing to execute.");

    //header looks good, continue.

    //is debug on? and do we have the neccessary data?
    if(debug == true && symbolTableSize > 0 && stringTableSize > 0)
    {
        loadDebugger(in);
    }

    //now load the bytecode
    loadBytecode(in);

    //all done, close the file stream
    in.close();
}

std::ostream& operator<<(std::ostream& out,const Bytecode& bytecode)
{
    out << std::dec << "BYTECODE:\n";
    out << std::setw(10) << std::setfill('-') << '\n';
    out << "filename = " << bytecode.filename << '\n';
    out << "stack size = " << bytecode.stackSize << " KB.\n";
    out << "heap size = " << bytecode.heapSize << " KB.\n";
    out << "bytecode size = " << bytecode.bytecodeSize << " bytes.\n";
    out << "total bytes allocated = " << bytecode.totalSize << " bytes.\n";
    out << std::showbase << std::hex;
    out << "bytecode start address = " << bytecode.bytecodeStartAddress << '\n';
    out << "bytecode end address = " << bytecode.bytecodeEndAddress << '\n' << std::dec;
    return out;
}

//load debug data
void Bytecode::loadDebugger(std::ifstream& in)
{
    DebugData* debugData = &vm.debugger.data;
    vm.debugOn = true; //set vm debugging to true

    //read table of contents
    in.read((char*)&debugData->contents.numGlobalVariables,4);     //read in the number of global variables
    in.read((char*)&debugData->contents.numProcedures,4);          //read in the number of procedures

    const U4 numGlobalVariables = debugData->contents.numGlobalVariables;
    const U4 numProcedures = debugData->contents.numProcedures;

    if(numGlobalVariables == 0 && numProcedures == 0)
    {
        throw std::runtime_error("BYTECODE: debug is on but no global variables and/or procedures to load.");
    }

    //if there are global variables
    if(numGlobalVariables > 0)
    {
        //allocate memory for global variable records
        debugData->globalVariables = new GlobalVariable[numGlobalVariables]{};

        //read in global variables
        GlobalVariable* g {nullptr};
        for(int i=0; i<numGlobalVariables; i++)
        {
            g = &debugData->globalVariables[i];
            in.read((char*)&g->text,8);
            in.read((char*)&g->type,1);
            in.read((char*)&g->len,8);
            in.read((char*)&g->size,8);
            in.read((char*)&g->offset,8);
            in.read((char*)&g->line,4);
        }
    }

    //if there are procedures
    if(numProcedures > 0)
    {
        //allocate memory for procedure records
        debugData->procedures = new Procedure[numProcedures];

        //read in procedures
        Procedure* p {nullptr};
        for(int i=0; i<numProcedures; i++)
        {
            p = &debugData->procedures[i];
            in.read((char*)&p->text,8);
            in.read((char*)&p->address,8);
            in.read((char*)&p->line,4);
            in.read((char*)&p->nRet,1);
            in.read((char*)&p->nArgs,1);
            in.read((char*)&p->nLocals,1);
            in.read((char*)&p->nLabels,2);

            //read ret
            if(p->nRet)
            {
                p->ret = new StackFrame{};
                readStackFrame(in,p->ret);
            }
            
            //if args, allocate and read in args
            if(p->nArgs > 0) p->args = new StackFrame[p->nArgs]{};
            for(int i=0; i<p->nArgs; i++)
            {
                readStackFrame(in,&p->args[i]);
            }

            //if locals, allocate and read in locals
            if(p->nLocals > 0) p->locals = new StackFrame[p->nLocals]{};
            for(int i=0; i<p->nLocals; i++)
            {
                readStackFrame(in,&p->locals[i]);
            }

            //if labels, allocate and read in labels
            if(p->nLabels > 0) p->labels = new Label[p->nLabels]{};
            for(int i=0; i<p->nLabels; i++)
            {
                in.read((char*)&p->labels[i].text,8);
                in.read((char*)&p->labels[i].address,8);
                in.read((char*)&p->labels[i].text,4);
            }
        }
    }

    //allocate memory for string table
    //and read it in.
    debugData->stringTable = new U1[stringTableSize]{};
    U1 byte;
    for(int i=0; i<stringTableSize; i++)
    {
        *(&debugData->stringTable[i]) = in.get();
    }
}

//load stack frame
void Bytecode::readStackFrame(std::ifstream& in,StackFrame* sf)
{
    in.read((char*)&sf->text,8);
    in.read((char*)&sf->fpOffset,4);
    in.read((char*)&sf->line,4);
}

//load bytecode data
void Bytecode::loadBytecode(std::ifstream& in)
{
    //set total size of the bytecode executable in bytes
    totalSize = bytecodeSize + (heapSize * 1024) + (stackSize * 1024);

    //get bytecode addresses
    bytecodeStartAddress = Bytecode::HEADER_SIZE + symbolTableSize + stringTableSize;
    bytecodeEndAddress = (bytecodeStartAddress + bytecodeSize) - 1;
    //
    //U8 freeBytes = getAvailableMemory();
    //
    //TODO - check we have enough free space
    //

    //allocate memory for the bytecode
    vm.ram->allocate(totalSize);

    //set up registers
    vm.registers.R($IP) = 0;                                        //set instruction pointer
    vm.registers.R($SP) = totalSize - 1;                            //set stack pointer
    vm.registers.R($FP) = 0;                                        //set frame pointer
    vm.registers.R($BE) = bytecodeSize - 1;                         //set bytecode end
    vm.registers.R($HS) = bytecodeSize;                             //set heap start address
    vm.registers.R($HE) = bytecodeSize + (heapSize * 1024) - 1;     //set heap end address
    vm.registers.R($SS) = bytecodeSize + (stackSize * 1024);        //set stack start address
    vm.registers.R($TOP) = totalSize - 1;                           //set stack top address

    //load bytecode into RAM
    U1 byte {};
    unsigned int i {0};
    while(!in.eof())
    {
        byte = in.get();
        (*vm.ram)(i++) = byte;
        in.peek(); //make sure we don't go past EOF
    }
}

} //namespace Logi
