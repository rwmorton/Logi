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
        explicit Float(float value);
        friend std::ostream& operator<<(std::ostream& out,Float& float_);
};

//double-precision float - 8 bytes
class Double : public Type
{
    public:
        explicit Double(double value);
        friend std::ostream& operator<<(std::ostream& out,Double& double_);
};

} //namespace Logi

#endif //__LOGI_FLOAT_H__
