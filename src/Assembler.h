#ifndef __LOGI_ASSEMBLER_H__
#define __LOGI_ASSEMBLER_H__

//Logi includes
#include "LoadFile.h"

//std includes
#include <string>
#include <ostream>

namespace Logi
{

class Assembler : public LoadFile
{
    enum FlagID
    {
        DEBUG = 0,
        ALLOW_ERRORS,
        CREATE_LISTING,
        OUTPUT_FILE
    };
    public:
        Assembler();
        ~Assembler();
        void load(int argc,char *argv[]);
        friend std::ostream& operator<<(std::ostream& out,const Assembler& asmb);
    private:
        bool omitDebug;
        unsigned short numErrors;
        bool createListing;
        std::string outputFile;
        //static flags
        static const Flag DEBUG_FLAG;
        static const Flag ALLOW_ERRORS_FLAG;
        static const Flag CREATE_LISTING_FLAG;
        static const Flag OUTPUT_FILE_FLAG;
};

} //namespace Logi

#endif //__LOGI_ASSEMBLER_H__
