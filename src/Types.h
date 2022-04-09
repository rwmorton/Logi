#ifndef __LOGI_TYPES_H__
#define __LOGI_TYPES_H__

#define __LOGI_TESTS_ON__

//std includes
#include <ostream>

//TEMP
#include <iostream>
using std::cout;
using std::endl;

namespace Logi
{

const unsigned int MAGIC_NUMBER {57069};    //magic number to verify the bytecode format
const unsigned int HEADER_SIZE {26};        //header size for the bytecode format

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

enum Endian
{
    BIG = 0,
    LITTLE
};

//will be 8 bytes long for each type
//which is not an efficient use of space
//but I am opting to build a more "versatile"
//system
union TypeUnion
{
    Logi::S1 S1;
    Logi::U1 U1;
    Logi::S2 S2;
    Logi::U2 U2;
    Logi::S4 S4;
    Logi::U4 U4;
    Logi::S8 S8;
    Logi::U8 U8;
    Logi::F4 F4;
    Logi::F8 F8;
};

enum TypeTag
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
        TypeTag tag;
};

} //namespace Logi

#endif //__LOGI_TYPES_H__
