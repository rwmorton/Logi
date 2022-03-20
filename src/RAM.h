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
        U1* at(const U8 index);
        U1* begin();
        U1* end();
        void allocate(const U8 bytes);
        U1& operator()(const unsigned int index);
        //stream output
        friend std::ostream& operator<<(std::ostream& out,RAM& ram);
    private:
        U1* _ram;       //the RAM itself
        U8 _bytes;      //number of bytes in RAM
};

} //namespace Logi

#endif //__LOGI_RAM_H__
