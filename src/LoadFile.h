#ifndef __LOGI_LOAD_FILE_H__
#define __LOGI_LOAD_FILE_H__

//std includes
#include <string>
#include <vector>

namespace Logi
{

class LoadFile;

//
// Flag has a series of options for characters.
// First string in the vector is all the possible
// individual characters that begin the flag, second
// (if any) is all the possible individual characters
// in the second character of the argument and so forth.
//
// args, if any, then follow. args are stored as strings,
// the client is expected to do the neccessary type casts.
//
class Flag
{
    friend class LoadFile;
    public:
        Flag(const int id,const std::vector<std::string>& opts,unsigned short expectedArgs=0);
        Flag(const Flag& flag);
        const int getId() const;
        std::string arg(unsigned short index) const;
        const bool check(const std::string& flag);
        Flag& addArg(const std::string &arg);
        void loadArgs(std::vector<std::string>::iterator& it);
        const bool operator==(const Flag& flag) const;
    private:
        int id;                             //flag ID
        std::vector<std::string> opts;      //flag options
        unsigned short expectedArgs;        //number of expected arguments
        std::vector<std::string> args;      //all args (saved as strings)
};

class LoadFile
{
    public:
        virtual ~LoadFile();
        LoadFile& addFlag(const Flag& flag);
        virtual void load(int argc,char *argv[]) = 0;
    protected:
        std::vector<Flag> parseArgs(int argc,char* argv[]);
        static const bool checkFlag(const char* currentChar,const char prefix,const char flags[],unsigned char numFlags);
        std::string filename;
        std::vector<Flag> addedFlags;
        std::vector<Flag> parsedFlags;
};

} //namespace Logi

#endif //__LOGI_LOAD_FILE_H__
