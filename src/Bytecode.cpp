//Logi includes
#include "Bytecode.h"
#include "VirtualMachine.h"
#include "Stream.h"

//std includes
#include <iostream>
#include <vector>
#include <fstream>

namespace Logi
{

const unsigned int Bytecode::MAGIC_NUMBER {57069}; //0xDEED
const unsigned int Bytecode::HEADER_SIZE {26};
const unsigned int Bytecode::DEFAULT_STACK_SIZE {64};
const unsigned int Bytecode::DEFAULT_HEAP_SIZE {64};
const std::string Bytecode::DEFAULT_EXECUTABLE_FILE {"bytecode.RUN"};

Bytecode::Bytecode() : stackSize(Bytecode::DEFAULT_STACK_SIZE),heapSize(Bytecode::DEFAULT_HEAP_SIZE),bytecodeFile(Bytecode::DEFAULT_EXECUTABLE_FILE) {}
Bytecode::~Bytecode() {}

//load the bytecode from command line args
void Bytecode::load(int argc,char* argv[],VirtualMachine& vm)
{
    parseArgs(argc,argv);

    //load the bytecode file
    std::ifstream in(bytecodeFile,std::ios::in | std::ios::binary);
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
    //set total size of the bytecode executable in bytes
    
    //////////////////////////////////////////////////////////////////////////
    // TEMP!!! FOR DEBUGGING, DON'T OUTPUT HEAP AND STACK * 1024
    //
    totalSize = bytecodeSize + 1000; //add just enough to avoid out of bounds errors
    //
    //////////////////////////////////////////////////////////////////////////
    //                  UNCOMMENT WHEN ABOVE DELETED
    //totalSize = bytecodeSize + (heapSize * 1024) + (stackSize * 1024);
    //
    //////////////////////////////////////////////////////////////////////////

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

    //close the file stream
    in.close();
}

std::ostream& operator<<(std::ostream& out,const Bytecode& bytecode)
{
    out << "stack size = " << bytecode.stackSize << " KB." << std::endl;
    out << "heap size = " << bytecode.heapSize << " KB."  << std::endl;
    out << "bytecode size = " << bytecode.bytecodeSize << " bytes." << std::endl;
    out << "total bytes allocated = " << bytecode.totalSize << " bytes." << std::endl;
    out << std::showbase << std::hex;
    out << "bytecode start address = " << bytecode.bytecodeStartAddress << std::endl;
    out << "bytecode end address = " << bytecode.bytecodeEndAddress << std::endl;
    out << std::dec;
    return out;
}

//parse the command line args
void Bytecode::parseArgs(int argc,char* argv[])
{
    std::vector<std::string> args;
    for(int i=0; i<argc; i++) args.push_back(argv[i]);

    std::vector<std::string>::iterator i = args.begin();
    ++i; //skip the first argument

    const char stackFlags[]{'s','S'};
    const char heapFlags[]{'h','H'};

    while(i != args.end())
    {
        char* c = &(*i)[0]; //get first character of current argument

        //stack arg?
        if(Bytecode::checkFlag(c,'-',stackFlags,2))
        {
            //start of stack arg
            stackSize = std::stoul((*i).replace(0,3,std::string(""))); //replace first three characters of the argument
        }
        //heap arg?
        else if(Bytecode::checkFlag(c,'-',heapFlags,2))
        {
            //start of heap arg
            heapSize = std::stoul((*i).replace(0,3,std::string("")));
        }
        else
        {
            //should then be the bytecode file itself
            bytecodeFile = std::string(*i);
        }

        ++i; //next arg
    }
}

//assumes bounds checks have been done first
const bool Bytecode::checkFlag(const char* currentChar,const char prefix,const char flags[],unsigned char numFlags)
{
    for(int i=0; i<numFlags; i++)
    {
        if(*currentChar == prefix && *(currentChar+1) == flags[i]) return true;
    }
    return false;
}

} //namespace Logi
