//Logi includes
#include "Word.h"

namespace Logi
{

/////////////////////////// signed word ///////////////////////////

Word::Word()
{
    this->value.S2 = 0;
    this->tag = TypeTag::S2_TAG;
}

Word::Word(const S2 value)
{
    this->value.S2 = value;
    this->tag = TypeTag::S2_TAG;
}

std::ostream& operator<<(std::ostream& out,Word& word)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(word.value.S2);
    out << std::dec;
    return out;
}

/////////////////////////// unsigned word ///////////////////////////

UWord::UWord()
{
    this->value.U2 = 0;
    this->tag = TypeTag::U2_TAG;
}

UWord::UWord(const U2 value)
{
    this->value.U2 = value;
    this->tag = TypeTag::U2_TAG;
}

std::ostream& operator<<(std::ostream& out,const UWord& word)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(word.value.U2);
    out << std::dec;
    return out;
}

} //namespace Logi
