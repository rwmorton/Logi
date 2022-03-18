#ifndef __LOGI_BYTECODE_H__
#define __LOGI_BYTECODE_H__

//Logi includes
#include "Types.h"
#include "RAM.h"

//std includes
#include <string>
#include <vector>

namespace Logi
{

/*
BYTECODE FILE SPEC

--------------
HEADER: 26 bytes long
16-bit magic number
64-bit value for size of symbol table (in bytes)
64-bit value for size of string table (in bytes)
64-bit value for size of bytecode section (in bytes)
--------------
SYMBOL TABLE
--------------
STRING TABLE
--------------

BYTECODE

--------------
*/

//
// options:
//      -h=XYZ      set heap size to XYZ * 1024 bytes
//      -s=XYZ      set stack size to XYZ * 1024 bytes
//      -d          start in debug mode
//

//
// Default values:
//      -s=DEFAULT_STACK_SIZE
//      -h=DEFAULT_HEAP_SIZE
//      DEFAULT_EXECUTABLE_FILE (name of the executable)
//

class VirtualMachine;

class Bytecode
{
    public:
        Bytecode();
        ~Bytecode();
        void load(int argc,char *argv[],VirtualMachine& vm);
    private:
        void parseArgs(int argc,char *argv[]);
        static const bool checkFlag(const char* currentChar,const char prefix,const char flags[],unsigned char numFlags);
        std::string bytecodeFile;                           //the bytecode file to execute
        U2 magic;                                           //magic number
        U8 heapSize;                                        //heap memory to allocate in KB (heap * 1024 bytes)
        U8 stackSize;                                       //stack memory to allocate in KB (stack * 1024 bytes)
        U8 symbolTableSize;                                 //size of the symbol table in the executable (in bytes)
        U8 stringTableSize;                                 //size of the string table in the executable (in bytes)
        U8 bytecodeSize;                                    //size of the bytecode in the executable (in bytes)
        U8 totalSize;                                       //total size of the bytecode executable (in bytes)
        static const unsigned int MAGIC_NUMBER;             //magic number to verify the bytecode format
        static const unsigned int HEADER_SIZE;              //header size for the bytecode format
        static const unsigned int DEFAULT_STACK_SIZE;       //default stack size if no size supplied
        static const unsigned int DEFAULT_HEAP_SIZE;        //default heap size if no size supplied
        static const std::string DEFAULT_EXECUTABLE_FILE;   //default executable file if none supplied
};

} //namespace Logi

#endif //__LOGI_BYTECODE_H__
