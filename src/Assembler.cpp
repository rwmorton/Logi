//Logi includes
#include "Assembler.h"

//std includes
#include <fstream>
#include <sstream>
#include <iomanip>

namespace Logi
{

Line::Line(const U4 pos) : pos{pos} {}

std::vector<Token>::const_iterator Line::token_iter() const
{
    return tokens.begin();
}

std::ostream& operator<<(std::ostream& out,const Line& line)
{
    out << line.pos << ": ";
    std::vector<Token>::const_iterator i = line.tokens.begin();
    while(i != line.tokens.end())
    {
        
        out << (*i)() << " (" << i->str << ')';

        switch(i->type)
        {
            case CHAR_CONSTANT:
            {
                out << ", char_val = " << i->val.S8_val;
            }
            break;
            case INTEGER_CONSTANT:
            {
                out << ", int_val = " << i->val.S8_val;
            }
            break;
            case FLOAT_CONSTANT:
            {
                out << ", float_val = " << i->val.F8_val;
            }
            break;
        }

        ++i;
        if(i != line.tokens.end()) out << ", ";
    }
    return out;
}

const Flag Assembler::DEBUG_FLAG(Assembler::FlagID::DEBUG,{"-","dD"},0);
const Flag Assembler::ALLOW_ERRORS_FLAG(Assembler::FlagID::ALLOW_ERRORS,{"-","eE"},1);
const Flag Assembler::CREATE_LISTING_FLAG(Assembler::FlagID::CREATE_LISTING,{"-","lL"},0);
const Flag Assembler::OUTPUT_FILE_FLAG(Assembler::FlagID::OUTPUT_FILE,{"-","oO"},1);

const std::string Assembler::WHITESPACE {" \n\r\t"};
const unsigned char Assembler::SPACE {' '};
const unsigned char Assembler::COMMA {','};
const unsigned char Assembler::EOL {'\0'};
const unsigned char Assembler::ASM_COMMENT {'#'};

const std::vector<std::string> Assembler::ASMIdentifierStrings
{
    ".GB",".GW",".GD",".GQ",
    ".PB",".PE",
    ".PR",".PA",".PV",".PL"
};

const std::vector<std::string> Token::TokenTypeStrings
{
    "inst",
    "dir",
    "id",
    "int_reg",
    "flt_reg",
    "dbl_reg",
    "char_const",
    "int_const",
    "flt_const",
    "BAD_TOKEN"
};

Assembler::Assembler() : omitDebug{false}, numErrors{0}, createListing{false}
{
    addFlag(DEBUG_FLAG);
    addFlag(ALLOW_ERRORS_FLAG);
    addFlag(CREATE_LISTING_FLAG);
    addFlag(OUTPUT_FILE_FLAG);
}

Assembler::~Assembler() {}

//
// Load ASM file from command line args
//
void Assembler::load(const int argc,const char* argv[])
{
    std::vector<Flag> flags = parseArgs(argc,argv);

    std::vector<Flag>::iterator flags_it = flags.begin();
    while(flags_it != flags.end())
    {
        switch(flags_it->getId())
        {
            case Assembler::FlagID::DEBUG: omitDebug = true;
            break;
            case Assembler::FlagID::ALLOW_ERRORS: numErrors = std::stoi(flags_it->arg(0));
            break;
            case Assembler::FlagID::CREATE_LISTING:
            {
                createListing = true;
                listingFilename = filename + ".LST";
            }
            break;
            case Assembler::FlagID::OUTPUT_FILE: outputFile = flags_it->arg(0);
            break;
            default: throw std::runtime_error("ASSEMBLER: invalid flag id.");
        }

        ++flags_it;
    }

    //load the asm file
    std::ifstream in(filename,std::ios::in | std::ios::binary);
    if(!in.is_open())
    {
        throw std::runtime_error("ASSEMBLER: could not load file.");
    }
    
    std::string line{};
    int lineCount{0};

    while(std::getline(in,line))
    {
        rawLines.push_back(line);
    }

    //all done, close the file stream
    in.close();

    //remove whitespace, comments etc.
    //and generate preliminary tokens.
    preProcessRaw();

    //assign correct identity to each token
    //and check for logical errors etc.
    identifyTokens();

    //build the symbol repository
    buildSymbolRepository();

    //resolve symbol addresses
    resolveAddresses();

    //finally, build the bytecode
    buildBytecode();

    //do we need to build a listing file?
    if(createListing)
    {
        std::ofstream listingFile(listingFilename,std::ios::out);

        if(!listingFile.is_open())
        {
            std::string errorStr {"ASSEMBLER: could not open listing file ("};
            errorStr += listingFilename;
            errorStr += ") for writing.";
            throw std::runtime_error(errorStr);
        }

        //get the bytecode listing lines vector
        std::vector<ListingLine> bytecodeListingLines = bytecodeLoader.getListingLines();

        //merge the two vectors, sorting by line number
        std::vector<ListingLine> mergedListingLines;
        std::merge
        (
            listingLines.begin(),listingLines.end(),
            bytecodeListingLines.begin(),bytecodeListingLines.end(),
            std::back_inserter(mergedListingLines)
        );

        //get the largest string in the vector
        std::vector<ListingLine>::iterator i = mergedListingLines.begin();
        int largestLine {0};
        while(i != mergedListingLines.end())
        {
            if(largestLine < i->str.length()) largestLine = i->str.length();
            ++i;
        }

        //now write the listing lines
        largestLine += 10; //give a little extra space
        i = mergedListingLines.begin();
        while(i != mergedListingLines.end())
        {
            i->write(listingFile,largestLine);

            ++i;
        }

        //now write the symbol table and string tables
        listingFile << symbolRepository << '\n';

        //finally close the listing file
        listingFile.close();
    }
}

std::ostream& operator<<(std::ostream& out,const Assembler& asmb)
{
    out << std::dec << "ASSEMBLER:\n";
    out << std::setw(11) << std::setfill('-') << '\n';
    out << "filename = " << asmb.filename << '\n';
    out << "allow num errors = " << asmb.numErrors << '\n';
    out << "omit debug? ";
    asmb.omitDebug ? out << "yes\n" : out << "no\n";
    out << "creating listing file? ";
    asmb.createListing ? out << "yes (" << asmb.listingFilename << ")\n" : out << "no\n";
    out << "output file? ";
    asmb.outputFile.length() == 0 ? out << "no\n" : out << asmb.outputFile << '\n';

    /*
    //TEMP
    out << "\nRAW LINES:\n";
    out << std::setw(11) << std::setfill('-') << '\n';
    std::vector<std::string>::const_iterator i = asmb.rawLines.begin();
    while(i != asmb.rawLines.end())
    {
        out << *i;
        ++i;
        if(i != asmb.rawLines.end()) out << '\n';
    }

    out << "\nTOKENIZED LINES:\n";
    out << std::setw(17) << std::setfill('-') << '\n';
    std::vector<Line>::const_iterator j = asmb.tokenizedLines.begin();
    while(j != asmb.tokenizedLines.end())
    {
        out << *j;
        ++j;
        if(j != asmb.tokenizedLines.end()) out << '\n';
    }
    */

    out << "\nSYMBOL REPOSITORY:\n";
    out << std::setw(19) << std::setfill('-') << '\n';
    out << asmb.symbolRepository;

    out << "\nBYTECODE:\n";
    out << std::setw(10) << std::setfill('-') << '\n';
    out << asmb.bytecodeLoader;

    return out;
}

//
// Do pre-processing of the vector of raw lines
// which creates a vector of Lines which have all relevant
// information such as the tokens and line number etc.
// This will be the first stage of token generation and will
// require further refinement.
//
// The vector of raw lines is cleared after this.
//
void Assembler::preProcessRaw()
{
    std::vector<std::string>::iterator i = rawLines.begin();
    unsigned int count {0}; //keep track of line count in file
    while(i != rawLines.end())
    {
        //strip leading/trailing whitespace
        i->erase(0,i->find_first_not_of(WHITESPACE));
        i->erase(i->find_last_not_of(WHITESPACE)+1);

        if(i->length() != 0 && i->at(0) != ASM_COMMENT)
        {
            //save line number and
            //split the line into tokens.
            Line line{count};
            tokenizePreProcess(line,*i);
            tokenizedLines.push_back(line);
        }
        ++i;

        count++;
    }

    rawLines.clear(); //clear all the raw lines
}

//
// Split line into tokens, removing commas, whitespace etc.
// These will be the "raw" tokens and will require further processing.
//
void Assembler::tokenizePreProcess(Line& line,const std::string& rawLine)
{
    int i {0};
    std::string tokenStr {};
    char c;
    while(i < rawLine.length())
    {
        c = rawLine.at(i);
        switch(c)
        {
            case SPACE:
            case COMMA:
            {
                //save the token if not empty (in case of extra spaces/commas)
                if(tokenStr.length() > 0)
                {
                    line.tokens.push_back({tokenStr,line});
                }
                tokenStr.clear();
            }
            break;
            case ASM_COMMENT:
            {
                //save token if not empty (once at comment anything to end of line is discarded)
                if(tokenStr.length() > 0)
                {
                    line.tokens.push_back({tokenStr,line});
                }
                tokenStr.clear();
                return;
            }
            break;
            default:
            {
                tokenStr.push_back(rawLine.at(i));
            }
            break;
        }

        i++;
    }

    line.tokens.push_back({tokenStr,line}); //save final token
}

//
// Save bytecode executable.
//
void Assembler::save()
{
    if(!outputFile.length()) throw std::runtime_error("ASSEMBLER: no output file to save the bytecode executable to.");

    std::ofstream out(outputFile,std::ios::out | std::ios::binary);
    if(!out.is_open())
    {
        std::string errorStr = {"ASSEMBLER: could not open file ("};
        errorStr += outputFile;
        errorStr += ").";
        throw std::runtime_error(errorStr);
    }

    // write the header
    const SymbolTable symbolTable = symbolRepository.getSymbolTable();
    const U8 symbolTableSize = symbolTable.size();
    const U8 stringTableSize = symbolRepository.stringTableSize();
    const U8 bytecodeSize = bytecodeLoader.getBytecode().size();
    //
    out.write((const char*)&MAGIC_NUMBER,sizeof(Logi::U2));
    out.write((const char*)&symbolTableSize,sizeof(Logi::U8));
    out.write((const char*)&stringTableSize,sizeof(Logi::U8));
    out.write((const char*)&bytecodeSize,sizeof(Logi::U8));

    // write the symbol table
    symbolTable.write(out);

    // write the string table
    const std::vector<std::string> stringTable = symbolRepository.getStringTable();
    std::vector<std::string>::const_iterator i = stringTable.begin();

    int totalBytes {0};
    int totalLines {0};

    while(i != stringTable.end())
    {
        out.write(i->c_str(),i->length() + 1); //+1 makes out write the null-character '\0'

        totalBytes += i->length() + 1;
        totalLines++;

        ++i;
    }

    // write the bytecode
    bytecodeLoader.write(out);

    // all done, close file
    out.close();
}

const ASMIdentifier Assembler::FIRST_ASM_ID {ASMIdentifier::GB};

//
// Get ASM identifier from string.
//
const ASMIdentifier Assembler::ASMIdentifier_fromStr(const std::string& str)
{
    std::vector<std::string>::const_iterator i = ASMIdentifierStrings.begin();
    int index = FIRST_ASM_ID;
    while(i != ASMIdentifierStrings.end())
    {
        if(*i == str) return (ASMIdentifier)index;
        ++i;
        index++;
    }

    return ASMIdentifier::BAD_ID;
}

} //namespace Logi
