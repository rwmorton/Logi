//Logi includes
#include "Types.h"

////TEMP
#include <iostream>

namespace Logi
{

//////////////////////////////////////////////
//////////////////// test ////////////////////

DerivedA::DerivedA(signed int v)
{
    value = std::any_cast<signed int>(v);
}

std::ostream& operator<<(std::ostream& out,DerivedA& dA)
{
    out << std::any_cast<signed int>(dA.value);
    return out;
}

DerivedB::DerivedB(unsigned int v)
{
    value = std::any_cast<unsigned int>(v);
}

std::ostream& operator<<(std::ostream& out,DerivedB& dB)
{
    out << std::any_cast<unsigned int>(dB.value);
    return out;
}

/////////////////////////// type ///////////////////////////

Type::Type(std::any value) : value(value) {}

Type::Type(const Type& type) : value(type.value) {}

Type& Type::operator=(const Type& type)
{
    this->value = type.value;
    return *this;
}

} //namespace Logi
