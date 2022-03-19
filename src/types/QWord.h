#ifndef __LOGI_QWORD_H__
#define __LOGI_QWORD_H__

//Logi includes
#include "../Types.h"

namespace Logi
{

//signed qword - 8 bytes
class QWord : public Type
{
    public:
        explicit QWord(signed long long value);
        friend std::ostream& operator<<(std::ostream& out,QWord& qword);
};

//unsigned qword - 8 bytes
class UQWord : public Type
{
    public:
        explicit UQWord(unsigned long long value);
        friend std::ostream& operator<<(std::ostream& out,UQWord& qword);
        unsigned long long value;
};

} //namespace Logi

#endif //__LOGI_QWORD_H__
