//Logi includes
#include "Types.h"

//
// reduce horrible boilerplate.
// TODO: revisit this down the line and see if there is
// a more elegant option using std::variant or something similar.
//
#define RETURN_ASSIGN_TO(OP) \
{ \
    switch(tag) \
    { \
        case S1_TAG: value.S1 OP type.value.S1; break; \
        case U1_TAG: value.U1 OP type.value.U1; break; \
        case S2_TAG: value.S2 OP type.value.S2; break; \
        case U2_TAG: value.U2 OP type.value.U2; break; \
        case S4_TAG: value.S4 OP type.value.S4; break; \
        case U4_TAG: value.U4 OP type.value.U4; break; \
        case S8_TAG: value.S8 OP type.value.S8; break; \
        case U8_TAG: value.U8 OP type.value.U8; break; \
        case F4_TAG: value.F4 OP type.value.F4; break; \
        case F8_TAG: value.F8 OP type.value.F8; break; \
        default: throw std::runtime_error("Incorrect type tag!"); \
    } \
    return *this; \
} \

#define RETURN_X_OP_Y(OP) \
{ \
    Type result; \
    switch(tag) \
    { \
        case S1_TAG: result.value.S1 = (value.S1 OP type.value.S1); \
        case U1_TAG: result.value.U1 = (value.U1 OP type.value.U1); \
        case S2_TAG: result.value.S2 = (value.S2 OP type.value.S2); \
        case U2_TAG: result.value.U2 = (value.U2 OP type.value.U2); \
        case S4_TAG: result.value.S4 = (value.S4 OP type.value.S4); \
        case U4_TAG: result.value.U4 = (value.U4 OP type.value.U4); \
        case S8_TAG: result.value.S8 = (value.S8 OP type.value.S8); \
        case U8_TAG: result.value.U8 = (value.U8 OP type.value.U8); \
        case F4_TAG: result.value.F4 = (value.F4 OP type.value.F4); \
        case F8_TAG: result.value.F8 = (value.F8 OP type.value.F8); \
        default: throw std::runtime_error("Incorrect type tag!"); \
    } \
    return result; \
} \

namespace Logi
{

Type::Type() : tag(NO_TAG) {}

Type::Type(const Type& copy) : value(copy.value) {}

Type& Type::operator=(const Type& type)
{
    this->value = type.value;
    return *this;
}

Type& Type::operator++()
{
    switch(tag)
    {
        case S1_TAG: value.S1 += 1; break;
        case U1_TAG: value.U1 += 1; break;
        case S2_TAG: value.S2 += 1; break;
        case U2_TAG: value.U2 += 1; break;
        case S4_TAG: value.S4 += 1; break;
        case U4_TAG: value.U4 += 1; break;
        case S8_TAG: value.S8 += 1; break;
        case U8_TAG: value.U8 += 1; break;
        case F4_TAG: value.F4 += 1; break;
        case F8_TAG: value.F8 += 1; break;
        default: throw std::runtime_error("Incorrect type tag!");
    }
    return *this;
}

Type Type::operator++(int)
{
    Type result;
    switch(tag)
    {
        case S1_TAG: result.tag = S1_TAG; result.value.S1 = ++value.S1; break;
        case U1_TAG: result.tag = U1_TAG; result.value.U1 = ++value.U1; break;
        case S2_TAG: result.tag = S2_TAG; result.value.S2 = ++value.S2; break;
        case U2_TAG: result.tag = U2_TAG; result.value.U2 = ++value.U2; break;
        case S4_TAG: result.tag = S4_TAG; result.value.S4 = ++value.S4; break;
        case U4_TAG: result.tag = U4_TAG; result.value.U4 = ++value.U4; break;
        case S8_TAG: result.tag = S8_TAG; result.value.S8 = ++value.S8; break;
        case U8_TAG: result.tag = U8_TAG; result.value.U8 = ++value.U8; break;
        case F4_TAG: result.tag = F4_TAG; result.value.F4 = ++value.F4; break;
        case F8_TAG: result.tag = F8_TAG; result.value.F8 = ++value.F8; break;
        default: throw std::runtime_error("Incorrect type tag!");
    }
    return result;
}

Type& Type::operator--()
{
    switch(tag)
    {
        case S1_TAG: value.S1 -= 1; break;
        case U1_TAG: value.U1 -= 1; break;
        case S2_TAG: value.S2 -= 1; break;
        case U2_TAG: value.U2 -= 1; break;
        case S4_TAG: value.S4 -= 1; break;
        case U4_TAG: value.U4 -= 1; break;
        case S8_TAG: value.S8 -= 1; break;
        case U8_TAG: value.U8 -= 1; break;
        case F4_TAG: value.F4 -= 1; break;
        case F8_TAG: value.F8 -= 1; break;
        default: throw std::runtime_error("Incorrect type tag!");
    }
    return *this;
}

Type Type::operator--(int)
{
    Type result;
    switch(tag)
    {
        case S1_TAG: result.tag = S1_TAG; result.value.S1 = --value.S1; break;
        case U1_TAG: result.tag = U1_TAG; result.value.U1 = --value.U1; break;
        case S2_TAG: result.tag = S2_TAG; result.value.S2 = --value.S2; break;
        case U2_TAG: result.tag = U2_TAG; result.value.U2 = --value.U2; break;
        case S4_TAG: result.tag = S4_TAG; result.value.S4 = --value.S4; break;
        case U4_TAG: result.tag = U4_TAG; result.value.U4 = --value.U4; break;
        case S8_TAG: result.tag = S8_TAG; result.value.S8 = --value.S8; break;
        case U8_TAG: result.tag = U8_TAG; result.value.U8 = --value.U8; break;
        case F4_TAG: result.tag = F4_TAG; result.value.F4 = --value.F4; break;
        case F8_TAG: result.tag = F8_TAG; result.value.F8 = --value.F8; break;
        default: throw std::runtime_error("Incorrect type tag!");
    }
    return result;
}

const Type Type::operator+(const Type& type) const { RETURN_X_OP_Y(+); }
Type& Type::operator+=(const Type& type) { RETURN_ASSIGN_TO(+=) }
const Type Type::operator-(const Type& type) const { RETURN_X_OP_Y(-) }
Type& Type::operator-=(const Type& type) { RETURN_ASSIGN_TO(-=) }
const Type Type::operator*(const Type& type) const { RETURN_X_OP_Y(*) }
Type& Type::operator*=(const Type& type) { RETURN_ASSIGN_TO(*=) }
const Type Type::operator/(const Type& type) const { RETURN_X_OP_Y(/); }
Type& Type::operator/=(const Type& type) { RETURN_ASSIGN_TO(/=) }

std::ostream& operator<<(std::ostream& out,const Type& type)
{
    out << std::showbase << std::hex;
    switch(type.tag)
    {
        case S1_TAG: out << static_cast<CAST_TO>(type.value.U1); break;
        case U1_TAG: out << static_cast<CAST_TO>(type.value.S1); break;
        case S2_TAG: out << static_cast<CAST_TO>(type.value.U2); break;
        case U2_TAG: out << static_cast<CAST_TO>(type.value.S2); break;
        case S4_TAG: out << static_cast<CAST_TO>(type.value.U4); break;
        case U4_TAG: out << static_cast<CAST_TO>(type.value.S4); break;
        case S8_TAG: out << static_cast<CAST_TO>(type.value.U8); break;
        case U8_TAG: out << static_cast<CAST_TO>(type.value.S8); break;
        case F4_TAG: out << static_cast<CAST_TO>(type.value.F4); break;
        case F8_TAG: out << static_cast<CAST_TO>(type.value.F8); break;
        default: throw std::runtime_error("Incorrect type tag!");
    }
    out << std::dec;
    return out;
}

} //namespace Logi
