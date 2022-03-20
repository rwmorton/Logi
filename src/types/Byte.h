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
        Byte();
        explicit Byte(const S1 value);
        friend std::ostream& operator<<(std::ostream& out,Byte& byte);
};

//unsigned byte
class UByte : public Type
{
    public:
        UByte();
        explicit UByte(const U1 value);
        friend std::ostream& operator<<(std::ostream& out,const UByte& byte);
};

} //namespace Logi

#endif //__LOGI_BYTE_H__
