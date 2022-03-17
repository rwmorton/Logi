//Logi includes
#include "RAM.h"

namespace Logi
{

RAM::RAM() : _ram(nullptr) {}

RAM::~RAM()
{
    if(this->_ram != nullptr) delete _ram;
}

} //namespace Logi
