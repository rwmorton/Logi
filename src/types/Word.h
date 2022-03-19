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
        Word();
        explicit Word(const signed short value);
        friend std::ostream& operator<<(std::ostream& out,Word& word);
};

//unsigned word - 2 bytes
class UWord : public Type
{
    public:
        UWord();
        explicit UWord(const unsigned short value);
        friend std::ostream& operator<<(std::ostream& out,const UWord& word);
};

} //namespace Logi

#endif //__LOGI_WORD_H__
