//Logi includes
#include "Bytecode.h"
#include "VirtualMachine.h"

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
        throw std::runtime_error("Could not load bytecode file."); //could not read file
    }

    //read in header
    in.read((char*)&magic,2);
    if(magic != (U2)Bytecode::MAGIC_NUMBER) throw std::runtime_error("Could not read valid magic number from the bytecode."); //not a valid magic number
    in.read((char*)&symbolTableSize,8);
    in.read((char*)&stringTableSize,8);
    in.read((char*)&bytecodeSize,8);
    if(bytecodeSize == 0) throw std::runtime_error("No bytecode to execute."); //no bytecode to execute

    //header looks good, continue.
    //set total size of the bytecode executable in bytes
    totalSize = bytecodeSize + (heapSize * 1024) + (stackSize * 1024);

    //get bytecode addresses
    U8 bytecodeStart = Bytecode::HEADER_SIZE + symbolTableSize + stringTableSize;
    U8 bytecodeEnd = (bytecodeStart + bytecodeSize) - 1;
    U8 bytecodeAddress = (bytecodeEnd - bytecodeStart) + 1;
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
    vm.registers.R($SS) = bytecodeSize + (stackSize * 1024) - 1;    //set stack start address
    vm.registers.R($TOP) = totalSize - 1;                           //set stack top address

    //load bytecode into RAM
    U1 byte {};
    unsigned int i {0};
    while(!in.eof())
    {
        byte = in.get();
        std::cout << std::showbase << std::hex << +byte << std::dec << ' ';
        (*vm.ram)(i++) = byte;
        in.peek(); //make sure we don't go past EOF
    }
    std::cout << std::dec << std::endl;

    //close the file stream
    in.close();

    //test
    std::cout << "stack size = " << stackSize << std::endl;
    std::cout << "heap size = " << heapSize << std::endl;
    std::cout << "bytecode size = " << bytecodeSize << std::endl;
    std::cout << "bytecode file = " << bytecodeFile << std::endl;
    std::cout << "total bytes allocated = " << totalSize << std::endl;
    std::cout << "number of bytes from bytecode allocated into ram = " << i << std::endl;
    std::cout << "bytecodeStart = " << bytecodeStart << std::endl;
    std::cout << "bytecodeEnd = " << bytecodeEnd << std::endl;
    std::cout << std::endl;
    //print the bytecode
    for(i=0; i<bytecodeSize; i++)
    {
        std::cout << std::showbase << std::hex << static_cast<U8>((*vm.ram)(i)) << ' ';
    }
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
