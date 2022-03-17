#ifndef __LOGI_VIRTUAL_MACHINE_H__
#define __LOGI_VIRTUAL_MACHINE_H__

//Logi includes
#include "Registers.h"
#include "RAM.h"

namespace Logi
{

class VirtualMachine
{
    friend class Stream;
    public:
        VirtualMachine();
        ~VirtualMachine();
        void init();
        void run();
        void shutdown();
    private:
        Registers registers;
        RAM* ram;
};

} //namespace Logi

#endif //__LOGI_VIRTUAL_MACHINE_H__
