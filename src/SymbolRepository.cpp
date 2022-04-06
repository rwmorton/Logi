//Logi includes
#include "SymbolRepository.h"

//std includes
#include <iomanip>
#include <map>

//TEMP
#include <iostream>
using std::cout;
using std::endl;

namespace Logi
{

std::ostream& operator<<(std::ostream& out,const GlobalVariable& gv)
{
    //out << "GLOBAL VARIABLE:\n";
    //out << std::setw(50) << std::setfill('-') << '\n';
    
    /*out << "text: " << gv.text << '\n';
    out << "line: " << gv.line << '\n';
    out << "type: ";*/

    //out << "line\ttext\ttype\tlen\tsize\toffset\n";

    out << gv.line << '\t' << gv.text << '\t';

    switch(gv.type)
    {
        case BYTE: out << "BYTE\t"; break;
        case WORD: out << "WORD\t"; break;
        case DWORD: out << "DWORD\t"; break;
        case QWORD: out << "QWORD\t"; break;
        default:
        {
            throw std::runtime_error("SYMBOL_REPOSITORY: not a valid global variable type.");
        }
    }

    out << gv.len << '\t' << gv.size << '\t' << gv.offset;

    //if(gv.len > 1) out << "array count: " << gv.len << '\n';
    //out << "size: " << gv.size << '\n';
    //out << "offset: " << gv.offset << '\n';

    return out;
}

std::ostream& operator<<(std::ostream& out,const StackFrame& sf)
{
    /*out << "STACK FRAME:\n";
    out << std::setw(13) << std::setfill('-') << '\n';
    out << "text: " << sf.text << '\n';
    out << "FP offset: " << sf.fpOffset << '\n';
    out << "line: " << sf.line << '\n';*/

    out << sf.line << '\t' << sf.text << '\t' << sf.fpOffset;

    return out;
}

std::ostream& operator<<(std::ostream& out,const Label& l)
{
    /*out << "LABEL:\n";
    out << std::setw(7) << std::setfill('-') << '\n';
    out << "text: " << l.text << '\n';
    out << "address: " << l.address << '\n';
    out << "line: " << l.line << '\n';*/

    out << l.text << '\t' << l.line << '\t' << l.address;

    return out;
}

std::ostream& operator<<(std::ostream& out,const Procedure& p)
{
    const int W = 24;
    out << "PROCEDURE:\n";
    out << std::setw(W) << std::setfill('-') << '\n';
    out << "line\ttext\taddress\n";
    out << std::setw(W) << std::setfill('-') << '\n';
    out << p.line << '\t' << p.text << '\t' << p.address << '\n';

    /*out << "text: " << p.text << '\n';
    out <<"line: " << p.line << '\n';
    out <<"address: " << p.address << '\n';*/

    //output return
    out << "\nRETURN:\n";
    out << std::setw(W) << std::setfill('-') << '\n';
    out << "line\ttext\taddress\n";
    out << std::setw(W) << std::setfill('-') << '\n';
    if(p.retVal == ProcedureReturn::VOID) out << "VOID\n";
    else out << p.ret << '\n';
    //output arguments
    out << "\nARGUMENTS:\n";
    out << std::setw(W) << std::setfill('-') << '\n';
    out << "line\ttext\taddress\n";
    out << std::setw(W) << std::setfill('-') << '\n';
    std::vector<StackFrame>::const_iterator i = p.args.begin();
    while(i != p.args.end())
    {
        out << *i << '\n';
        ++i;
    }
    //output locals
    out << "\nLOCALS:\n";
    out << std::setw(W) << std::setfill('-') << '\n';
    out << "line\ttext\taddress\n";
    out << std::setw(W) << std::setfill('-') << '\n';
    i = p.locals.begin();
    while(i != p.locals.end())
    {
        out << *i << '\n';
        ++i;
    }
    //output labels
    out << "\nLABELS:\n";
    out << std::setw(W) << std::setfill('-') << '\n';
    out << "line\ttext\taddress\n";
    out << std::setw(W) << std::setfill('-') << '\n';
    std::vector<Label>::const_iterator j = p.labels.begin();
    while(j != p.labels.end())
    {
        out << *j << '\n';
        ++j;
    }

    out << std::setw(W) << std::setfill('-') << '\n';

    return out;
}

void SymbolTable::addGlobalVariable(const GlobalVariable& gv)
{
    int index = globalVariables.size();
    globalVariables.push_back(gv);
    addressablesMap.insert(std::pair<int,Addressable*>(gv.text,&globalVariables.at(index)));
}

void SymbolTable::addProcedure(const Procedure& proc)
{
    int index = procedures.size();
    procedures.push_back(proc);
    addressablesMap.insert(std::pair<int,Addressable*>(proc.text,&procedures.at(index)));
}

void SymbolTable::addLabel(const Label& label)
{
    int index = labels.size();
    labels.push_back(label);
    addressablesMap.insert(std::pair<int,Addressable*>(label.text,&labels.at(index)));
}

std::ostream& operator<<(std::ostream& out,const SymbolTable& st)
{
    const int W = 48;
    //output global variables
    out << "\nGLOBAL VARIABLES:\n";
    out << std::setw(W) << std::setfill('-') << '\n';
    out << "line\ttext\ttype\tlen\tsize\toffset\n";
    out << std::setw(W) << std::setfill('-') << '\n';

    std::vector<GlobalVariable>::const_iterator iv = st.globalVariables.begin();
    while(iv != st.globalVariables.end())
    {
        out << *iv << '\n';
        ++iv;
    }
    //output procedures
    out << "\nPROCEDURES:\n";
    out << std::setw(12) << std::setfill('-') << '\n';
    
    std::vector<Procedure>::const_iterator ip = st.procedures.begin();
    while(ip != st.procedures.end())
    {
        out << *ip << '\n';
        ++ip;
    }

    return out;
}

const U8 SymbolRepository::addIdentifier(const std::string& id)
{
    stringTable.push_back(id);
    return stringTable.size()-1;
}

const std::string& SymbolRepository::getIdentifier(const int index) const
{
    if(index < 0 || index >= stringTable.size()) throw std::runtime_error("SYMBOL_REPOSITORY: index into string table is out of range.");
    return stringTable.at(index);
}

const int SymbolRepository::getIdentifier(const std::string& id) const
{
    std::vector<std::string>::const_iterator i = stringTable.begin();
    int index {0};
    while(i != stringTable.end())
    {
        if(*i == id) return index;
        ++i;
        index++;
    }

    throw std::runtime_error("SYMBOL_REPOSITORY: no match for identifier found in string table.");
}

void SymbolRepository::addLabelAddr(const std::string& id,const U8 addr)
{
    symbolMap.insert(std::pair<std::string,const U8>(id,addr));
}

const U8 SymbolRepository::getAddress(const std::string& id) const
{
    return symbolMap.find(id)->second;
}

SymbolTable& SymbolRepository::getSymbolTable()
{
    return symbolTable;
}

const int SymbolRepository::indexInStringTable(const std::string& id) const
{
    std::vector<std::string>::const_iterator i = stringTable.begin();
    int index {0};
    while(i != stringTable.end())
    {
        if(*i == id) return index;

        ++i;
        index++;
    }

    std::string errorStr = {"SYMBOL_REPOSITORY: no match to string ("};
    errorStr += id;
    errorStr += ')';
    throw std::runtime_error(errorStr);
}

std::ostream& operator<<(std::ostream& out,const SymbolRepository& sr)
{
    // output the symbol table contents.
    out << "\nSYMBOL TABLE:\n";
    out << std::setw(14) << std::setfill('-') << '\n';
    out << sr.symbolTable;
    // output the string table contents.
    out << "\nSTRING TABLE:\n";
    out << std::setw(14) << std::setfill('-') << '\n';
    std::vector<std::string>::const_iterator i = sr.stringTable.begin();
    while(i != sr.stringTable.end())
    {
        out << *i << '\n';
        ++i;
    }

    return out;
}

} //namespace Logi
