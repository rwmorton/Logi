#ifndef __LOGI_RAM_H__
#define __LOGI_RAM_H__

//Logi includes
#include "Types.h"

namespace Logi
{

class RAM
{
    friend class Stream;
    friend class Bytecode;
    public:
        RAM();
        ~RAM();
        const U8 size() const;
        const U1* begin() const;
        const U1* end() const;
        void allocate(const U8 bytes);
        U1& operator()(unsigned int index);
        void dump() const;
    private:
        U1* _ram;       //the RAM itself
        U8 _bytes;      //number of bytes in RAM
};

} //namespace Logi

#endif //__LOGI_RAM_H__
