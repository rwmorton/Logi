#ifndef __LOGI_LISTING_LINE_H__
#define __LOGI_LISTING_LINE_H__

//Logi includes
#include "Types.h"

//std includes
#include <string>
#include <vector>
#include <iomanip>

namespace Logi
{

struct ListingLine
{
    U4 line;
    std::string str;
    std::vector<U8> addrVec;
    bool instruction;
    U8 byte; //if an instruction, which byte it begins at
    //default constructor
    ListingLine() : instruction{false} {}
    //clear
    void clear()
    {
        str.clear();
        addrVec.clear();
    }
    //add to listing line
    void add(const std::string& appendStr) { str += appendStr; }
    void add(const U8 addr) { addrVec.push_back(addr); }
    //write listing line
    void write(std::ofstream& out,const int width)
    {
        int lineWidth = 16;
        int remWidth = width - lineWidth;

        std::setfill(' ');
        std::string lineStr {std::to_string(line) + ')'};
        if(instruction)
        {
            lineStr += '[';
            lineStr += std::to_string(byte);
            lineStr += ']';
        }
        out << std::left << std::setw(lineWidth) << lineStr;
        out << std::left << std::setw(width) << str;
        //construct address string
        std::vector<U8>::const_iterator i = addrVec.begin();
        while(i != addrVec.end())
        {
            std::string addrStr {'[' + std::to_string(*i) + ']'};
            out << addrStr;
            ++i;
        }
        out << '\n';
    }
    //operator overloads for sorting by line number
    const bool operator<(const ListingLine &ll)
    {
        return line < ll.line ? true : false;
    }
    const bool operator>(const ListingLine &ll)
    {
        return line > ll.line ? true : false;
    }
    const bool operator==(const ListingLine &ll)
    {
        return line == ll.line ? true : false;
    }
};

} //namespace Logi

#endif //__LOGI_LISTING_LINE_H__
