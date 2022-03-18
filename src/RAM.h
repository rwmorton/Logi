#ifndef __LOGI_RAM_H__
#define __LOGI_RAM_H__

//Logi includes
#include "Types.h"

//std includes
#include <ostream>

namespace Logi
{

class RAM
{
    public:
        RAM();
        ~RAM();
        const U8 size() const;
        const U1* begin() const;
        const U1* end() const;
        void allocate(const U8 bytes);
        U1& operator()(unsigned int index);
        //stream output
        friend void operator<<(RAM& ram,std::ostream& out);
    private:
        U1* _ram;       //the RAM itself
        U8 _bytes;      //number of bytes in RAM
};

} //namespace Logi

#endif //__LOGI_RAM_H__
