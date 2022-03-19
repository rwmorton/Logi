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
        QWord();
        explicit QWord(const signed long long value);
        friend std::ostream& operator<<(std::ostream& out,QWord& qword);
};

//unsigned qword - 8 bytes
class UQWord : public Type
{
    public:
        UQWord();
        explicit UQWord(const unsigned long long value);
        friend std::ostream& operator<<(std::ostream& out,const UQWord& qword);
};

} //namespace Logi

#endif //__LOGI_QWORD_H__
