#ifndef __LOGI_ASSEMBLER_H__
#define __LOGI_ASSEMBLER_H__

//Logi includes
#include "LoadFile.h"
#include "Types.h"
#include "Registers.h"

//std includes
#include <string>
#include <ostream>
#include <vector>

namespace Logi
{

class Assembler;

/*
Token types are:

identifiers (eg. instructions like MOV, function names etc.)
integer registers (e.g. $R5)
float registers (e.g. $F2)
double registers (e.g $D7)
character constants enclosed in single quotes (e.g. 'x')
integer constants (e.g. 123)
floating-point constants (e.g. 0.3141e2)
*/

/*
                                        |-> (e|E) [+|-] digits
                                        |
                    |-> NZ [digits] --->|-> .digits
                    |                   |
float constant ---->|                   |-> .digits (e|E) [+|-] digits
                    |
                    |
                    |       |-> .digits
                    |       |
                    |-> 0 ->|
                            |
                            |-> .digits (e|E) [+|-] digits
*/

enum ASMIdentifier
{
    GB = 0,     // global variable (byte)
    GW,         // global variable (word)
    GD,         // global variable (double word)
    GQ,         // global variable (quad word})
    PB,         // beginning of procedure
    PE,         // end of procedure
    PR,         // procedure return val
    PA,         // procedure argument
    PV,         // procedure local variable
    PL,         // procedure label
    BAD_ID
};

enum TokenType
{
    IDENTIFIER = 0,         // (a-z,A-Z,_,.,?,@) -> (a-z,A-Z,_,.,?,@,0-9)
    INTEGER_REGISTER,       // $R[1-24]
    FLOAT_REGISTER,         // $F[1-10]
    DOUBLE_REGISTER,        // $D[1-10]
    CHAR_CONSTANT,          // 'ASCII char'
    INTEGER_CONSTANT,       // [+|-](1-9) -> (0-9)
    // elements in brackets are optional
    // elements in parentheses are mandatory
    // vertical bar represents logical OR
    // 'NZ' represents a single decimal digit in the range 1-9
    // digits represent a series of one or more decimal digits in range 1-9
    // [+|-] NZ [digits] (e|E) [+|-] digits (e.g. 622e-8)
    // [+|-] NZ [digits] .digits [(e|E) [+|-] digits] (e.g. -1.34)
    // [+|-] 0.digits [(e|E) [+|-] digits] (e.g. 0.41e+11)
    FLOAT_CONSTANT,         // see 3 forms above
    BAD_TOKEN
};

class Line;

struct Token
{
    Token(const std::string& str,const Line& line) : str{str} {};
    std::string str;        //the token string
    TokenType type;         //type of token
    union Val
    {
        S8 val;             //register bytecode val, char val, integer const
        F8 fval;            //floating point val
    };
};

//
// A line consists of one or more tokens making up a logical statement.
//
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
        void tokenizePreProcess(Line& line,const std::string& rawLine);
        void assignTokenIds();
        //
        //checks
        //if checks fail a runtime error is thrown.
        //
        const bool checkOpCodes(Line& line,Token& token);
        void checkASMIds(Line& line,Token& token);
        static void checkTokenCount(const Line& line,const int expectedCount);
        static void checkTokenCountWithinRange(const Line& line,const int start,const int end);
        static const RegisterCodes checkIntRegister(const std::string& str);
        static const FloatRegisterCodes checkFloatRegister(const std::string& str);
        static const DoubleRegisterCodes checkDoubleRegister(const std::string& str);
        static const ASMIdentifier ASMIdentifier_fromStr(const std::string& str);
        //data
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
        static const ASMIdentifier FIRST_ASM_ID;
        static const std::vector<std::string> ASMIdentifierStrings;
};

} //namespace Logi

#endif //__LOGI_ASSEMBLER_H__
