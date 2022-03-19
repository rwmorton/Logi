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
        DWord();
        explicit DWord(const signed int value);
        friend std::ostream& operator<<(std::ostream& out,DWord& dword);
};

//unsigned dword - 4 bytes
class UDWord : public Type
{
    public:
        UDWord();
        explicit UDWord(const unsigned int value);
        friend std::ostream& operator<<(std::ostream& out,const UDWord& dword);
};

} //namespace Logi

#endif //__LOGI_DWORD_H__
