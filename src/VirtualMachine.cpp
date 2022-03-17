//Logi includes
#include "VirtualMachine.h"

//std includes
#include <iostream>

namespace Logi
{

VirtualMachine::VirtualMachine() : registers{},ram{nullptr}
{
    //
}

VirtualMachine::~VirtualMachine()
{
    if(ram != nullptr) delete ram;
}

void VirtualMachine::init()
{
    //
}

void VirtualMachine::run()
{
    //
}

void VirtualMachine::shutdown()
{
    //
}

} //namespace Logi
