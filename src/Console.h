#ifndef __LOGI_CONSOLE_H__
#define __LOGI_CONSOLE_H__

//std includes
#include <string>
#include <cstdio>

namespace Logi
{

//
// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
//
class Console
{
    public:
        static const std::string RED;
        static const std::string GREEN;
        static const std::string BLUE;
        static const std::string YELLOW;
        static const std::string MAGENTA;
        static const std::string CYAN;
        static const std::string RESET;
};

} //namespace Logi

#endif //__LOGI_CONSOLE_H__
