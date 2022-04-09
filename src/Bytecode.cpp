//Logi includes
#include "Bytecode.h"
#include "VirtualMachine.h"
#include "Stream.h"

//std includes
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

//TEMP
using std::cout;
using std::endl;

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
void Bytecode::load(const int argc,const char* argv[])
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
        std::string errorStr {"BYTECODE: could not load file ("};
        errorStr += filename;
        errorStr += ')';
        throw std::runtime_error(errorStr);
    }

    //read in header
    in.read((char*)&magic,2);
    if(magic != Bytecode::MAGIC_NUMBER) throw std::runtime_error("BYTECODE: could not read valid magic number.");
    in.read((char*)&symbolTableSize,8);
    in.read((char*)&stringTableSize,8);
    in.read((char*)&bytecodeSize,8);
    if(bytecodeSize == 0) throw std::runtime_error("BYTECODE: nothing to execute.");

    //header looks good, continue.

    //is debug on?
    if(debug == true)
    {
        loadDebugger(in);
    }
    else
    {
        //skip ahead
        int skipBy = symbolTableSize + stringTableSize + Bytecode::HEADER_SIZE;
        in.seekg(skipBy);
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
        //throw std::runtime_error("BYTECODE: debug is on but no global variables and/or procedures to load.");
        Stream::getInstance()->string("BYTECODE (WARNING): no global variables or procedures available for the debugger.\n");
    }

    //if there are global variables
    if(numGlobalVariables > 0)
    {
        for(int i=0; i<numGlobalVariables; i++)
        {
            GlobalVariable g;
            GlobalVariable::read(g,in); //read in from file
            debugData->globalVariables.push_back(g); // and save

            cout << g << endl;
        }
    }

    //if there are procedures
    if(numProcedures > 0)
    {
        for(int i=0; i<numProcedures; i++)
        {
            Procedure p;
            Procedure::read(p,in); //read in from file
            debugData->procedures.push_back(p); //and save

            cout << p << endl;
        }
    }

    //read in string table
    int byteCount {0};
    while(byteCount < stringTableSize)
    {
        std::string line {};
        std::getline(in,line,'\0');
        debugData->stringTable.push_back(line);

        byteCount += line.length() + 1;
    }
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
