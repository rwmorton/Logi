//Logi includes
#include "Bytecode.h"

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

Bytecode::Bytecode() : stack(Bytecode::DEFAULT_STACK_SIZE),heap(Bytecode::DEFAULT_HEAP_SIZE),bytecodeFile(Bytecode::DEFAULT_EXECUTABLE_FILE) {}
Bytecode::~Bytecode() {}

//load the bytecode from command line args
void Bytecode::load(int argc,char* argv[])
{
    parseArgs(argc,argv);

    //load the bytecode file

    //test
    std::cout << "stack = " << stack << std::endl;
    std::cout << "heap = " << heap << std::endl;
    std::cout << "bytecode file = " << bytecodeFile << std::endl;
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
            stack = std::stoul((*i).replace(0,3,std::string(""))); //replace first three characters of the argument
        }
        //heap arg?
        else if(Bytecode::checkFlag(c,'-',heapFlags,2))
        {
            //start of heap arg
            heap = std::stoul((*i).replace(0,3,std::string("")));
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
