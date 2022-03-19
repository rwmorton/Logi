//Logi includes
#include "Float.h"

namespace Logi
{

/////////////////////////// float ///////////////////////////

Float::Float(float value) : Type(std::any_cast<float>(value)) {}

std::ostream& operator<<(std::ostream& out,Float& float_)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(std::any_cast<float>(float_.value));
    out << std::dec;
    return out;
}

/////////////////////////// double ///////////////////////////

Double::Double(double value) : Type(std::any_cast<double>(value)) {}

std::ostream& operator<<(std::ostream& out,Double& double_)
{
    out << std::showbase << std::hex;
    out << static_cast<CAST_TO>(std::any_cast<double>(double_.value));
    out << std::dec;
    return out;
}

} //namespace Logi
