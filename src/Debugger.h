#ifndef __LOGI_DEBUGGER_H__
#define __LOGI_DEBUGGER_H__

//Logi includes
#include "Types.h"
#include "Bytecode.h"
#include "SymbolRepository.h"

//std includes
#include <string>
#include <vector>

namespace Logi
{

struct DebugData
{
    struct Contents contents;
    struct GlobalVariable* globalVariables {nullptr};
    struct Procedure* procedures {nullptr};
    U1* stringTable;
};

class VirtualMachine;
class Stream;

class Debugger
{
    friend class Bytecode;
    public:
        Debugger(VirtualMachine& vm);
        ~Debugger();
        void read();
        void instruction(const U8 address) const;
    private:
        void badCommand(const std::string& command) const;
        void splitArgs(const std::string& line,std::vector<std::string>& args) const;
        void help() const;
        void bytecode() const;
        void dump(const U8 start,const U8 stop) const;
        void search(const U8 start,const U8 stop,const std::string& str) const;
        void symbol(const std::string& str) const;
        void procedure() const;
        void basicRegisters() const;
        void intRegisters() const;
        void floatRegisters() const;
        void doubleRegisters() const;
        const bool checkRange(const U8 start,const U8 stop) const;
        VirtualMachine& vm;     //reference to the VM
        Stream* stream;
        DebugData data;
};

} //namespace Logi

#endif //__LOGI_DEBUGGER_H__
