//Logi includes
#include "Debugger.h"

namespace Logi
{

Debugger::~Debugger()
{
    //free all global variables
    if(data.globalVariables != nullptr)
    {
        delete[] data.globalVariables;
    }

    //free all procedures and associated
    //ret, arg, local and labels
    if(data.procedures != nullptr)
    {
        if(data.procedures->nRet != 0) delete data.procedures->ret;
        if(data.procedures->nArgs != 0) delete[] data.procedures->args;
        if(data.procedures->nLocals != 0) delete[] data.procedures->locals;
        if(data.procedures->nLabels != 0) delete[] data.procedures->labels;
        delete[] data.procedures;
    }
}

} //namespace Logi
