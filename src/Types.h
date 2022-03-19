#ifndef __LOGI_TYPES_H__
#define __LOGI_TYPES_H__

//std includes
#include <ostream>

namespace Logi
{

using S1 = signed char;
using S2 = signed short;
using S4 = signed int;
using S8 = signed long long;

using U1 = unsigned char;
using U2 = unsigned short;
using U4 = unsigned int;
using U8 = unsigned long long;

using F4 = float;
using F8 = double;

using CAST_TO = U8;

//will be 8 bytes long for each type
//which is not an efficient use of space
//but I am opting to build a more "versatile"
//system
union TypeUnion
{
    signed char S1;
    unsigned char U1;
    signed short S2;
    unsigned short U2;
    signed int S4;
    unsigned int U4;
    signed long long S8;
    unsigned long long U8;
    float F4;
    double F8;
};

enum TypeUnionTag
{
    S1_TAG = 0,
    U1_TAG,
    S2_TAG,
    U2_TAG,
    S4_TAG,
    U4_TAG,
    S8_TAG,
    U8_TAG,
    F4_TAG,
    F8_TAG,
    NO_TAG
};

class Type
{
    public:
        Type();
        Type(const Type& copy);
        virtual ~Type() {}
        virtual Type& operator=(const Type& type);

        virtual Type& operator++(); //prefix
        virtual Type operator++(int); //postfix

        virtual Type& operator--(); //prefix
        virtual Type operator--(int); //postfix

        virtual const Type operator+(const Type& type) const;
        virtual Type& operator+=(const Type& type);
        virtual const Type operator-(const Type& type) const;
        virtual Type& operator-=(const Type& type);
        virtual const Type operator*(const Type& type) const;
        virtual Type& operator*=(const Type& type);
        //no check for divizion by zero!
        virtual const Type operator/(const Type& type) const;
        virtual Type& operator/=(const Type& type);
        //stream output
        friend std::ostream& operator<<(std::ostream& out,const Type& type);
    protected:
        TypeUnion value;
        TypeUnionTag tag;
};

} //namespace Logi

#endif //__LOGI_TYPES_H__
