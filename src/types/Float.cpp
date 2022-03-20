//Logi includes
#include "Float.h"

namespace Logi
{

/////////////////////////// float ///////////////////////////

Float::Float()
{
    this->value.F4 = 0.0f;
    this->tag = TypeTag::F4_TAG;
}

Float::Float(const F4 value)
{
    this->value.F4 = value;
    this->tag = TypeTag::F4_TAG;
}

std::ostream& operator<<(std::ostream& out,Float& float_)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(float_.value.F4);
    out << std::dec;
    return out;
}

/////////////////////////// double ///////////////////////////

Double::Double()
{
    this->value.F8 = 0.0;
    this->tag = TypeTag::F8_TAG;
}

Double::Double(const F8 value)
{
    this->value.F8 = value;
    this->tag = TypeTag::F8_TAG;
}

std::ostream& operator<<(std::ostream& out,const Double& double_)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(double_.value.F8);
    out << std::dec;
    return out;
}

} //namespace Logi
