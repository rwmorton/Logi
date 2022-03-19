#ifndef __LOGI_BYTE_H__
#define __LOGI_BYTE_H__

//Logi includes
#include "../Types.h"

namespace Logi
{

//signed byte
class Byte : public Type
{
    public:
        explicit Byte(signed char value);
        friend std::ostream& operator<<(std::ostream& out,Byte& byte);
};

//unsigned byte
class UByte : public Type
{
    public:
        explicit UByte(unsigned char value);
        friend std::ostream& operator<<(std::ostream& out,UByte& byte);
};

} //namespace Logi

#endif //__LOGI_BYTE_H__
