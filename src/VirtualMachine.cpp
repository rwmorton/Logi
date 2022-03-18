//Logi includes
#include "VirtualMachine.h"
#include "Stream.h"

//std includes
#include <iostream>
#include <fstream>

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

void VirtualMachine::init(int argc,char* argv[])
{
    Stream* stream = Stream::getInstance();
    stream->string("VM: Initializing virtual machine...").endl();
    stream->string("VM: Loading bytecode executable...").endl();
    //load the bytecode
    executable.load(argc,argv,*this);

    stream->string("VM: Bytecode executable loaded.").endl();
}

void VirtualMachine::run()
{
    Stream* stream = Stream::getInstance();
    stream->string("VM: running...").endl();

    //this->registers << std::cout;
    this->executable << std::cout;
    //(*this->ram) << std::cout;

    std::ofstream ramDump("RAM_DUMP.BIN",std::ios::binary | std::ios::out);
    (*this->ram) << ramDump;
    ramDump.close();
}

void VirtualMachine::shutdown()
{
    Stream* stream = Stream::getInstance();
    stream->string("VM: shutting down...").endl();
}

void operator<<(VirtualMachine& vm,std::ostream& out)
{
    vm.executable << out;
    out << std::endl;
    vm.registers << out;
    out << std::endl;
    (*vm.ram) << out;
    out << std::endl;
}

} //namespace Logi
