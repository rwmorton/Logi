#ifndef __LOGI_VIRTUAL_MACHINE_H__
#define __LOGI_VIRTUAL_MACHINE_H__

//Logi includes
#include "Debugger.h"
#include "Bytecode.h"
#include "Registers.h"
#include "RAM.h"
#include "InstructionSet.h"
#include "Stream.h"
#include "Validator.h"
#include "Transform.h"

//std includes
#include <ostream>

namespace Logi
{

/*
the basic execution environment which the virtual machine has at
its disposal consists of a memory address space and a collection
of 52 registers.
the memory address space is a contiguous series of bytes that
is dedicated as storage space for a single process.
the memory address space is broken into three segments: a text
segment, a heap and a stack.

there are 8 registers used to delimit the three segements:
$BE,$HS,$HE,$SS,$TOP and serve as address pointers $IP,$SP,$FP

there are 24 general purpose registers ($R1 - $R24)
10 general purpose single-precision registers ($F1 - $F10)
10 generate purpose double-precision registers ($D1 - $D10)

--------------------------------
TEXT SEGMENT
--------------------------------
=== $TOP - top of memory
===
=== $FP - frame pointer
===
=== $SP - stack pointer
===
===
=== $SS - stack start
--------------------------------
HEAP SEGMENT
--------------------------------
=== $HE - heap end
===
===
=== $HS - heap start
--------------------------------
STACK SEGMENT
--------------------------------
=== $BE - bytecode end
===
=== $IP - instruction pointer
===
=== address zero (0)
--------------------------------
*/

class Stream;
class Debugger;
class DebugPrinter;
class Validator;

class VirtualMachine
{
    friend class Stream;
    friend class Bytecode;
    friend class Debugger;
    friend class DebugPrinter;
    friend class InstructionSet;
    public:
        VirtualMachine();
        ~VirtualMachine();
        const Logi::RAM* RAM() const;
        void init(const int argc,const char* argv[]);
        void run();
        void shutdown();
        friend std::ostream& operator<<(std::ostream& out,const VirtualMachine& vm);
    private:
        void validateBytecode();
        Bytecode executable;
        bool debugOn;
        Debugger debugger;
        Registers registers;
        Logi::RAM* ram;
        InstructionSet* iset;
        Validator* validate;
        std::vector<std::string> commandLine;
        Stream* stream;
};

} //namespace Logi

#endif //__LOGI_VIRTUAL_MACHINE_H__
