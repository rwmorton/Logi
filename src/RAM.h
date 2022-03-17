#ifndef __LOGI_RAM_H__
#define __LOGI_RAM_H__

//Logi includes
#include "Types.h"

//std includes
#include <memory>

namespace Logi
{

class RAM
{
    friend class Stream;
    public:
        RAM();
        ~RAM();
    private:
        U1* _ram;
};

} //namespace Logi

#endif //__LOGI_RAM_H__
