//Logi includes
#include "VirtualMachine.h"

//std includes
#include <iostream>

namespace Logi
{

VirtualMachine::VirtualMachine() : registers{},ram{nullptr}
{
    ram = new Logi::RAM();
}

VirtualMachine::~VirtualMachine()
{
    if(ram != nullptr) delete ram;
}

const Logi::RAM* VirtualMachine::RAM() const
{
    return ram;
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
