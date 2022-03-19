#ifndef __LOGI_WORD_H__
#define __LOGI_WORD_H__

//Logi includes
#include "../Types.h"

namespace Logi
{

//signed word - 2 bytes
class Word : public Type
{
    public:
        explicit Word(signed short value);
        friend std::ostream& operator<<(std::ostream& out,Word& word);
};

//unsigned word - 2 bytes
class UWord : public Type
{
    public:
        explicit UWord(unsigned short value);
        friend std::ostream& operator<<(std::ostream& out,UWord& word);
};

} //namespace Logi

#endif //__LOGI_WORD_H__
