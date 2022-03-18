#ifndef __LOGI_STREAM_H__
#define __LOGI_STREAM_H__

//Logi includes
#include "Types.h"
#include "RAM.h"
#include "VirtualMachine.h"

//std includes
#include <ostream>
#include <string>

namespace Logi
{

//
// Stream is a singleton.
//
class Stream
{
    public:
        static Stream* getInstance();
        void set(const std::ostream* out);
        //stream methods
        void U_REG(const std::string& regStr,U8 reg) const;
        void S_REG(const std::string& regStr,U8 reg) const;
        void F_REG(const std::string& regStr,U8 reg) const;
        void D_REG(const std::string& regStr,U8 reg) const;
        //
        void U1(U1 byte) const;
        void U2(U2 word) const;
        void U4(U4 dword) const;
        void U8(U8 qword) const;
        //
        void S1(S1 byte) const;
        void S2(S2 word) const;
        void S4(S4 dword) const;
        void S8(S8 qword) const;
        //RAM stream methods
        void mem(const RAM* ram,Logi::U8 index) const;
        void bytes(const Logi::U1 bytes[],unsigned int length) const;
        //
        //VM stream methods
        void memSection(const VirtualMachine& vm,Logi::U8 address,Logi::U8 bytes) const;
        void allRAM(const VirtualMachine& vm) const;
        void basicRegisters(const VirtualMachine& vm) const;
        void generalRegisters(const VirtualMachine& vm) const;
        void floatRegisters(const VirtualMachine& vm) const;
        void doubleRegisters(const VirtualMachine& vm) const;
    private:
        Stream();
        static Stream* instance;
        std::ostream& out;
};

} //namespace Logi

#endif //__LOGI_STREAM_H__
