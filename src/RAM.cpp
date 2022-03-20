//Logi includes
#include "RAM.h"
#include "Stream.h"

//std includes
#include <ostream>

namespace Logi
{

RAM::RAM() : _ram(nullptr),_bytes{0} {}

RAM::~RAM()
{
    if(this->_ram != nullptr) delete[] _ram;
}

//return the total number of bytes in the RAM
const U8 RAM::size() const
{
    return _bytes;
}

//get a pointer to RAM at given index
U1* RAM::at(const U8 index)
{
    return &_ram[index];
}

//get a pointer to the first byte of the RAM
U1* RAM::begin()
{
    return &_ram[0];
}

//get a pointer to the last byte of the RAM
U1* RAM::end()
{
    return &_ram[this->size()-1];
}

//does not include bounds error checking
void RAM::allocate(const U8 bytes)
{
    if(bytes == 0) throw std::runtime_error("cannot allocate RAM with zero bytes.");
    if(_ram) delete[] _ram;
    //allocate
    _ram = new U1[bytes]{};
    _bytes = bytes;
}

//get byte at index
U1& RAM::operator()(const unsigned int index)
{
    if(index >= _bytes) throw std::out_of_range("RAM index out of bounds.");
    return *(&_ram[index]);
}

std::ostream& operator<<(std::ostream& out,RAM& ram)
{
    out << std::showbase << std::hex;

    U8 length = ram.size();
    for(U8 i=0; i<length; i++)
    {
        out << static_cast<int>(ram(i));
        if(i < length-1) out << ' ';
    }

    out << std::dec;
    return out;
}

} //namespace Logi
