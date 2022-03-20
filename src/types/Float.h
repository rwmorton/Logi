#ifndef __LOGI_FLOAT_H__
#define __LOGI_FLOAT_H__

//Logi includes
#include "../Types.h"

namespace Logi
{

//single-precision float - 4 bytes
class Float : public Type
{
    public:
        Float();
        explicit Float(const F4 value);
        friend std::ostream& operator<<(std::ostream& out,Float& float_);
};

//double-precision float - 8 bytes
class Double : public Type
{
    public:
        Double();
        explicit Double(const F8 value);
        friend std::ostream& operator<<(std::ostream& out,const Double& double_);
};

} //namespace Logi

#endif //__LOGI_FLOAT_H__
