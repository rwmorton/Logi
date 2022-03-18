//Logi includes
#include "VirtualMachine.h"
#include "Stream.h"

//std includes
#include <iostream>

namespace Logi
{

VirtualMachine::VirtualMachine() : registers{},ram{nullptr}
{
    ram = new Logi::RAM();
    stream = Stream::getInstance();
}

VirtualMachine::~VirtualMachine()
{
    if(ram != nullptr) delete ram;
}

const Logi::RAM* VirtualMachine::RAM() const
{
    return ram;
}

void VirtualMachine::init(int argc,char* argv[])
{
    stream->string("VM: Initializing virtual machine...").endl();
    stream->string("VM: Loading bytecode executable...").endl();
    //load the bytecode
    executable.load(argc,argv,*this);

    stream->string("VM: Bytecode executable loaded.").endl();

    executable.dump();
    registers.dump();
    ram->dump();
}

void VirtualMachine::run()
{
    stream->string("VM: running...").endl();

    //
}

void VirtualMachine::shutdown()
{
    stream->string("VM: shutting down...").endl();
}

} //namespace Logi
