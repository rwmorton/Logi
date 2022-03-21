//Logi includes
#include "RAM.h"
#include "Stream.h"

//std includes
#include <ostream>

namespace Logi
{

RAM::RAM() : _ram(nullptr),_numBytes{0},_currentByte{0} {}

RAM::~RAM()
{
    if(this->_ram != nullptr) delete[] _ram;
}

//return the total number of bytes in the RAM
const U8 RAM::size() const
{
    return _numBytes;
}

//get a pointer to RAM at given index
U1* RAM::at(const U8 index)
{
    if(index >= _numBytes) throw std::runtime_error("RAM: cannot get byte - out of range!");
    _currentByte = index;
    return &_ram[index];
}

//get a pointer to the next byte of the RAM
U1* RAM::next()
{
    if(++_currentByte >= _numBytes) throw std::runtime_error("RAM: cannot get next byte - out of range!");
    return &_ram[_currentByte];
}

//get a pointer to the previous byte of the RAM
U1* RAM::prev()
{
    if(_currentByte-1 < 0) throw std::runtime_error("RAM: cannot get previous byte - out of range!");
    return &_ram[--_currentByte];
}

//get a pointer to the first byte of the RAM
U1* RAM::begin()
{
    _currentByte = 0;
    return &_ram[0];
}

//get a pointer to the last byte of the RAM
U1* RAM::end()
{
    _currentByte = _numBytes - 1;
    return &_ram[_currentByte];
}

//does not include bounds error checking
void RAM::allocate(const U8 bytes)
{
    if(bytes == 0) throw std::runtime_error("RAM: cannot allocate RAM with zero bytes.");
    if(_ram) delete[] _ram;
    //allocate
    _ram = new U1[bytes]{};
    _numBytes = bytes;
}

//get byte at index
U1& RAM::operator()(const unsigned int index)
{
    //Stream::getInstance()->string("RAM::operator() : index = ").U8(index).endl();

    if(index >= _numBytes) throw std::out_of_range("RAM: index out of bounds.");
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
