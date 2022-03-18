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
        //general stream methods
        const Stream& string(const std::string& str) const;
        const Stream& endl() const;
        //registers
        const Stream& U_REG(const std::string& regStr,U8 reg) const;
        const Stream& S_REG(const std::string& regStr,U8 reg) const;
        const Stream& F_REG(const std::string& regStr,U8 reg) const;
        const Stream& D_REG(const std::string& regStr,U8 reg) const;
        //unsigned types
        const Stream& U1(U1 byte) const;
        const Stream& U2(U2 word) const;
        const Stream& U4(U4 dword) const;
        const Stream& U8(U8 qword) const;
        //signed types
        const Stream& S1(S1 byte) const;
        const Stream& S2(S2 word) const;
        const Stream& S4(S4 dword) const;
        const Stream& S8(S8 qword) const;
        //floating point types
        const Stream& F4(F4 float_) const;
        const Stream& F8(F8 double_) const;
        //stream bytes
        const Stream& bytes(const Logi::U1 bytes[],unsigned int length) const;
    private:
        Stream();
        static Stream* instance;
        std::ostream& out;
};

} //namespace Logi

#endif //__LOGI_STREAM_H__
