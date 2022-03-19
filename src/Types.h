#ifndef __LOGI_TYPES_H__
#define __LOGI_TYPES_H__

//std includes
#include <ostream>
#include <any>

namespace Logi
{

typedef signed char S1;
typedef signed short S2;
typedef signed int S4;
typedef signed long long S8;

typedef unsigned char U1;
typedef unsigned short U2;
typedef unsigned int U4;
typedef unsigned long long U8;

typedef float F4;
typedef double F8;

///////////////////////////////////////////////////////////////////
//test
class Base
{
    public:
        virtual ~Base() {}
    protected:
        std::any value;
};

class DerivedA : public Base
{
    public:
        DerivedA(signed int v);
        friend std::ostream& operator<<(std::ostream& out,DerivedA& dA);
};

class DerivedB : public Base
{
    public:
        DerivedB(unsigned int v);
        friend std::ostream& operator<<(std::ostream& out,DerivedB& dB);
};
///////////////////////////////////////////////////////////////////

typedef signed long long CAST_TO;

class Type
{
    public:
        Type(std::any value);
        Type(const Type& type);
        virtual ~Type() {}
        Type& operator=(const Type& type);
    protected:
        std::any value;
};

} //namespace Logi

#endif //__LOGI_TYPES_H__
