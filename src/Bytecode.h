#ifndef __LOGI_BYTECODE_H__
#define __LOGI_BYTECODE_H__

//Logi includes
#include "Types.h"
#include "LoadFile.h"
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
class StackFrame;

class Bytecode : public LoadFile
{
    enum FlagID
    {
        STACK,
        HEAP,
        DEBUG
    };
    public:
        Bytecode(VirtualMachine& vm);
        ~Bytecode();
        void load(int argc,char *argv[]);
        //stream output
        friend std::ostream& operator<<(std::ostream& out,const Bytecode& bytecode);
    private:
        void loadDebugger(std::ifstream& in);
        void readStackFrame(std::ifstream& in,StackFrame* sf);
        void loadBytecode(std::ifstream& in);
        VirtualMachine& vm;                                 //reference to the VM
        U2 magic;                                           //magic number
        U8 heapSize;                                        //heap memory to allocate in KB (heap * 1024 bytes)
        U8 stackSize;                                       //stack memory to allocate in KB (stack * 1024 bytes)
        bool debug;                                         //start in debug mode?
        U8 symbolTableSize;                                 //size of the symbol table in the executable (in bytes)
        U8 stringTableSize;                                 //size of the string table in the executable (in bytes)
        U8 bytecodeSize;                                    //size of the bytecode in the executable (in bytes)
        U8 totalSize;                                       //total size of the bytecode executable (in bytes)
        U8 bytecodeStartAddress;
        U8 bytecodeEndAddress;
        static const unsigned int MAGIC_NUMBER;             //magic number to verify the bytecode format
        static const unsigned int HEADER_SIZE;              //header size for the bytecode format
        static const unsigned int DEFAULT_STACK_SIZE;       //default stack size if no size supplied
        static const unsigned int DEFAULT_HEAP_SIZE;        //default heap size if no size supplied
        //flags
        static const Flag STACK_FLAG;
        static const Flag HEAP_FLAG;
        static const Flag DEBUG_FLAG;
};

} //namespace Logi

#endif //__LOGI_BYTECODE_H__
