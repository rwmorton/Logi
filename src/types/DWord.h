#ifndef __LOGI_DWORD_H__
#define __LOGI_DWORD_H__

//Logi includes
#include "../Types.h"

namespace Logi
{

//signed dword - 4 bytes
class DWord : public Type
{
    public:
        explicit DWord(signed int value);
        friend std::ostream& operator<<(std::ostream& out,DWord& dword);
};

//unsigned dword - 4 bytes
class UDWord : public Type
{
    public:
        explicit UDWord(unsigned int value);
        friend std::ostream& operator<<(std::ostream& out,UDWord& dword);
};

} //namespace Logi

#endif //__LOGI_DWORD_H__
