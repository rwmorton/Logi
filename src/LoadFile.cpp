//Logi includes
#include "LoadFile.h"

//std includes
#include <stdexcept>

namespace Logi
{

Flag::Flag
(
    const int id,const std::vector<std::string>& opts,unsigned short expectedArgs
)   : id{id}, opts{opts}, expectedArgs{expectedArgs} {}

Flag::Flag(const Flag& flag)
{
    id = flag.id;
    opts = flag.opts;
    expectedArgs = flag.expectedArgs;
    args = flag.args;
}

const int Flag::getId() const
{
    return id;
}

std::string Flag::arg(unsigned short index) const
{
    if(index >= args.size()) throw std::runtime_error("FLAG: argument index out of range.");
    return args.at(index);
}

//
// Check whether the flag exists.
//
const bool Flag::check(const std::string& flag)
{
    //check that the length of the flag options
    //matches the number of characters in the flag
    if(opts.size() != flag.length()) return false;
    
    //we have a possible match
    std::vector<std::string>::iterator it = opts.begin();

    //check each option
    int i = 0;
    while(it != opts.end())
    {
        bool match = false;
        for(int j=0; j<(*it).length(); j++)
        {
            //if any character is matched set true
            if((*it).at(j) == flag.at(i))
            {
                match = true;
                break;
            }
        }

        if(!match) return false;

        i++;
        ++it;
    }
    
    return true;
}

Flag& Flag::addArg(const std::string &arg)
{
    if(args.size() >= expectedArgs) throw std::runtime_error("FLAG: received more arguments than expected.");
    args.push_back(arg);
    return *this;
}

//
// Loads arguments starting from the flag position itself.
// Expects the iterator to be within range.
//
void Flag::loadArgs(std::vector<std::string>::iterator& it)
{
    int i = 0;
    while(i < expectedArgs)
    {
        ++it; //next arg

        //if argument is an empty string throw error
        if(it->length() == 0) throw std::runtime_error("FLAG: cannot load empty argument.");

        args.push_back(*it);
        i++;
    }
}

const bool Flag::operator==(const Flag& flag) const
{
    return id == flag.id;
}

LoadFile::~LoadFile() {}

LoadFile& LoadFile::addFlag(const Flag& flag)
{
    addedFlags.push_back(flag);
    return *this;
}

std::vector<Flag> LoadFile::parseArgs(int argc,char* argv[])
{
    //get all the command line args
    std::vector<std::string> args;
    for(int i=0; i<argc; i++) args.push_back(argv[i]);

    //first arg is the executable
    //name so skip this one.
    std::vector<std::string>::iterator args_it = args.begin();
    ++args_it;

    std::vector<std::string> noMatch{};

    while(args_it != args.end())
    {
        //check for matching flags
        std::vector<Flag>::iterator addedFlags_it = addedFlags.begin();
        bool match = false;
        while(addedFlags_it != addedFlags.end())
        {
            //check for a match
            if(addedFlags_it->check(*args_it))
            {
                match = true;

                //save this flag
                Flag flag(*addedFlags_it);

                //remove this flag from the
                //list of added flags.
                addedFlags_it = addedFlags.erase(addedFlags_it);

                //load arguments, if any
                if(flag.expectedArgs > 0)
                {
                    //load the arguments.
                    //note that loadArgs begins
                    //from the flag position itself.
                    flag.loadArgs(args_it);
                }

                //then save flag to the list of parsed flags
                parsedFlags.push_back(flag);
            }
            else
            {
                ++addedFlags_it;
            }
        }

        if(!match)
        {
            //no match against flags, save this.
            noMatch.push_back(*args_it);
            ++addedFlags_it;
        }

        ++args_it;
    }

    //at this point we should expect to have received only
    //a single no match argument, which should be the filename
    if(noMatch.size() != 1)
    {
        throw std::runtime_error("LOAD_FILE: incorrect command line args, either received no filename or invalid arguments.");
    }
    else
    {
        filename = noMatch.at(0);
    }

    return parsedFlags;
}

const bool LoadFile::checkFlag(const char* currentChar,const char prefix,const char flags[],unsigned char numFlags)
{
    for(int i=0; i<numFlags; i++)
    {
        if(*currentChar == prefix && *(currentChar+1) == flags[i]) return true;
    }
    return false;
}

} //namespace Logi
