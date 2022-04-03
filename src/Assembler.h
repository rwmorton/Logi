#ifndef __LOGI_ASSEMBLER_H__
#define __LOGI_ASSEMBLER_H__

//Logi includes
#include "LoadFile.h"
#include "Types.h"

//std includes
#include <string>
#include <ostream>
#include <vector>

namespace Logi
{

class Assembler;

struct Token
{
    Token(const std::string& str) : str{str} {};
    std::string str;        //the token string
    U1 type;                //type of token
};

class Line
{
    friend class Assembler;
    public:
        Line(const U4 pos);
        friend std::ostream& operator<<(std::ostream& out,const Line& line);
    private:
        U4 pos;                         //line number in original source file
        std::vector<Token> tokens;
};

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
        void preProcessRaw();
        void tokenize(Line& line,const std::string& rawLine);
        bool omitDebug;
        unsigned short numErrors;
        bool createListing;
        std::string outputFile;
        std::vector<std::string> rawLines;              //vector containing all the raw lines from the ASM file
        std::vector<Line> tokenizedLines;               //vector containing all the tokens per line
        //static flags
        static const Flag DEBUG_FLAG;
        static const Flag ALLOW_ERRORS_FLAG;
        static const Flag CREATE_LISTING_FLAG;
        static const Flag OUTPUT_FILE_FLAG;
        static const std::string WHITESPACE;
        static const unsigned char SPACE;
        static const unsigned char COMMA;
        static const unsigned char EOL;
        static const unsigned char ASM_COMMENT;
};

} //namespace Logi

#endif //__LOGI_ASSEMBLER_H__
