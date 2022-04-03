#ifndef __LOGI_ASSEMBLER_H__
#define __LOGI_ASSEMBLER_H__

//Logi includes
#include "LoadFile.h"

//std includes
#include <string>

namespace Logi
{

class Assembler : public LoadFile
{
    enum FlagID
    {
        X = 0,
        Y,
        Z
    };
    public:
        Assembler();
        ~Assembler();
        void load(int argc,char *argv[]);
    private:
        //static flags
        //TEMP
        static const Flag X_FLAG;
        static const Flag Y_FLAG;
        static const Flag Z_FLAG;
};

} //namespace Logi

#endif //__LOGI_ASSEMBLER_H__
