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

//get a pointer to the first byte of the RAM
const U1* RAM::begin() const
{
    return &_ram[0];
}

//get a pointer to the last byte of the RAM
const U1* RAM::end() const
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
U1& RAM::operator()(unsigned int index)
{
    if(index >= _bytes) throw std::out_of_range("RAM index out of bounds.");
    return *(&_ram[index]);
}

//dump RAM info to stream
void RAM::dump() const
{
    const Stream* stream = Stream::getInstance();
    stream->string("---------------").endl();
    stream->string("RAM dump").endl();
    stream->string("---------------").endl();
    stream->bytes(begin(),size()).endl();
}

} //namespace Logi
