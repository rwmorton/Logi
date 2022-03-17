#ifndef __LOGI_VIRTUAL_MACHINE_H__
#define __LOGI_VIRTUAL_MACHINE_H__

//Logi includes
#include "Registers.h"
#include "RAM.h"

//std includes
#include <memory>

namespace Logi
{

class VirtualMachine
{
    public:
        VirtualMachine();
    private:
        static const Registers registers;
        std::unique_ptr<RAM> ram;
};

} //namespace Logi

#endif //__LOGI_VIRTUAL_MACHINE_H__
