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
        out.write(str.c_str(),str.length());

        //format nicely
        out << std::setw(width - str.length()) << std::setfill(' ') << '\t';

        std::vector<U8>::const_iterator i = addrVec.begin();
        while(i != addrVec.end())
        {
            std::string addrStr {'[' + std::to_string(*i) + ']'};
            out.write(addrStr.c_str(),addrStr.length());
            ++i;
        }

        //all done
        out.put('\n');
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
