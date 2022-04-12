#ifndef __LOGI_ASSEMBLER_H__
#define __LOGI_ASSEMBLER_H__

//Logi includes
#include "LoadFile.h"
#include "Types.h"
#include "Registers.h"
#include "SymbolRepository.h"
#include "BytecodeFromASM.h"
#include "ListingLine.h"

//std includes
#include <string>
#include <ostream>
#include <vector>

namespace Logi
{

class Assembler;
class ValidateASM;
class Line;

/*
Token types are:

instruction (e.g. MOV, POP etc.)
directive (e.g. .PB)
identifier (e.g. function names etc.)
integer register (e.g. $R5)
float register (e.g. $F2)
double register (e.g $D7)
character constant enclosed in single quotes (e.g. 'x')
integer constant (e.g. 123)
floating-point constant (e.g. 0.3141e2)
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

/*
DIRECTIVE   IDENTIFIER  NUM ELS IF ARRAY
.G(B,W,D,Q) identifier  [integer]
.PB         idenfitier
.PR         identifier  +integer
.PA         identifier  +integer
.PV         identifier  -integer
.PL         identifier
.PE
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
    INSTRUCTION = 0,
    DIRECTIVE,
    IDENTIFIER,             // (a-z,A-Z,_,.,?,@) -> (a-z,A-Z,_,.,?,@,0-9)
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

union TokenVal
{
    S8 S8_val;          //register bytecode val, char val, integer const
    F8 F8_val;          //floating point val
};

//
// A single atomic portion of the assembly code.
//
struct Token
{
    public:
        Token(const std::string& str,const Line& line) : str{str} {};
        const std::string& operator()() const { return TokenTypeStrings.at(type); }
        std::string str;        //the token string
        TokenType type;         //type of token
        TokenVal val;           //token value
    private:
        static const std::vector<std::string> TokenTypeStrings;
};

//
// A line consists of one or more tokens making up a logical statement.
//
class Line
{
    friend class Assembler;
    friend class ValidateASM;
    public:
        Line(const U4 pos);
        const U4 getPos() const { return pos; }
        std::vector<Token>::const_iterator token_iter() const;
        friend std::ostream& operator<<(std::ostream& out,const Line& line);
    private:
        TokenType type;                 //type of token the line begins with
        U4 pos;                         //line number in original source file
        std::vector<Token> tokens;
};

//
// The assembler itself, loads a file containing assembly code
// and transforms it into a SymbolRepository and a bytecode
// executable which is then written to file.
//
class Assembler : public LoadFile
{
    friend class ValidateASM;
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
        void load(const int argc,const char *argv[]);
        void save();
        friend std::ostream& operator<<(std::ostream& out,const Assembler& asmb);
    private:
        //from load:
        //step 1
        void preProcessRaw();
        //step 2 (from preProcessRaw)
        void tokenizePreProcess(Line& line,const std::string& rawLine);
        //step 3
        void identifyTokens();
        const bool checkOpCodes(ValidateASM& validator);
        void checkASMIds(ValidateASM& validator);
        //step 4
        void buildSymbolRepository();
        //set 5
        void resolveAddresses();
        //step 6
        void buildBytecode();
        //step 7
        void writeListing();
        //
        void loadDirective(std::vector<Line>::const_iterator& line_it);
        void loadGlobalVariable(const Line& line);
        void loadProcedure(std::vector<Line>::const_iterator& line_it);
        void loadStackFrame(StackFrame& stackFrame,const Line& line);
        void loadProcedureReturn(Procedure& proc,const Line& line);
        void loadProcedureArgument(Procedure& proc,const Line& line);
        void loadProcedureLocalVariable(Procedure& proc,const Line& line);
        void loadProcedureLabel(Procedure& proc,const Line& line);
        void loadInstruction(const Line& line);
        //
        static const ASMIdentifier ASMIdentifier_fromStr(const std::string& str);
        //data
        bool omitDebug;
        unsigned short numErrors;
        bool createListing;
        std::vector<ListingLine> listingLines;
        std::string listingFilename;
        std::string outputFile;
        std::vector<std::string> rawLines;              //vector containing all the raw lines from the ASM file
        std::vector<Line> tokenizedLines;               //vector containing all the tokens per line
        SymbolRepository symbolRepository;              //the symbol repository
        BytecodeFromASM bytecodeLoader;                 //interface for loading instructions on a per line basis
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
