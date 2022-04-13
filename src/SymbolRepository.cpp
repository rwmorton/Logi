//Logi includes
#include "SymbolRepository.h"

//std includes
#include <iomanip>
#include <map>

namespace Logi
{

//set width for formatting stream output
const int W {8};

std::ostream& operator<<(std::ostream& out,const GlobalVariable& gv)
{
    out << std::left << std::setfill(' ');
    out << std::setw(W) << gv.line;
    out << std::setw(W) << gv.text;

    out << std::setw(W);
    switch(gv.type)
    {
        case BYTE: out << "BYTE"; break;
        case WORD: out << "WORD"; break;
        case DWORD: out << "DWORD"; break;
        case QWORD: out << "QWORD"; break;
        default:
        {
            throw std::runtime_error("SYMBOL_REPOSITORY: not a valid global variable type.");
        }
    }

    out << std::setw(W) << gv.len;
    out << std::setw(W) << gv.size;
    out << std::setw(W) << gv.offset;

    return out;
}

std::ostream& operator<<(std::ostream& out,const StackFrame& sf)
{
    out << std::left << std::setfill(' ');
    out << std::setw(W) << sf.line;
    out << std::setw(W) << sf.text;
    out << std::setw(W) << sf.fpOffset;

    return out;
}

std::ostream& operator<<(std::ostream& out,const Label& l)
{
    out << std::left << std::setfill(' ');
    out << std::setw(W) << l.text;
    out << std::setw(W) << l.line;
    out << std::setw(W) << l.address;

    return out;
}

std::ostream& operator<<(std::ostream& out,const Procedure& p)
{
    out << "PROCEDURE:\n";
    out << std::right << std::setw(W*3) << std::setfill('-') << '\n';
    out << std::left << std::setfill(' ');
    out << std::setw(W) << "line";
    out << std::setw(W) << "text";
    out << std::setw(W) << "address" << '\n';
    out << std::right << std::setw(W*3) << std::setfill('-') << '\n';
    out << std::left << std::setfill(' ');
    out << std::setw(W) << p.line;
    out << std::setw(W) << p.text;
    out << std::setw(W) << p.address << '\n';

    //output return
    out << std::right << "\nRETURN:\n";
    out << std::right << std::setw(W*3) << std::setfill('-') << '\n';
    out << std::left << std::setfill(' ');
    out << std::setw(W) << "line";
    out << std::setw(W) << "text";
    out << std::setw(W) << "address" << '\n';
    out << std::right << std::setw(W*3) << std::setfill('-') << '\n';
    out << std::left << std::setfill(' ');
    out << std::setw(W) << p.line;
    out << std::setw(W) << p.text;
    out << std::setw(W) << p.address << '\n';
    if(p.retVal == ProcedureReturn::VOID) out << "VOID\n";
    else out << p.ret << '\n';

    //output arguments
    out << std::right << "\nARGUMENTS:\n";
    out << std::right << std::setw(W*3) << std::setfill('-') << '\n';
    out << std::left << std::setfill(' ');
    out << std::setw(W) << "line";
    out << std::setw(W) << "text";
    out << std::setw(W) << "address" << '\n';
    out << std::right << std::setw(W*3) << std::setfill('-') << '\n';
    out << std::left << std::setfill(' ');
    out << std::setw(W) << p.line;
    out << std::setw(W) << p.text;
    out << std::setw(W) << p.address << '\n';
    std::vector<StackFrame>::const_iterator i = p.args.begin();
    while(i != p.args.end())
    {
        out << *i << '\n';
        ++i;
    }
    //output locals
    out << std::right << "\nLOCALS:\n";
    out << std::right << std::setw(W*3) << std::setfill('-') << '\n';
    out << std::left << std::setfill(' ');
    out << std::setw(W) << "line";
    out << std::setw(W) << "text";
    out << std::setw(W) << "address" << '\n';
    out << std::right << std::setw(W*3) << std::setfill('-') << '\n';
    out << std::left << std::setfill(' ');
    out << std::setw(W) << p.line;
    out << std::setw(W) << p.text;
    out << std::setw(W) << p.address << '\n';
    i = p.locals.begin();
    while(i != p.locals.end())
    {
        out << *i << '\n';
        ++i;
    }
    //output labels
    out << std::right << "\nLABELS:\n";
    out << std::right << std::setw(W*3) << std::setfill('-') << '\n';
    out << std::left << std::setfill(' ');
    out << std::setw(W) << "line";
    out << std::setw(W) << "text";
    out << std::setw(W) << "address" << '\n';
    out << std::right << std::setw(W*3) << std::setfill('-') << '\n';
    out << std::left << std::setfill(' ');
    out << std::setw(W) << p.line;
    out << std::setw(W) << p.text;
    out << std::setw(W) << p.address << '\n';
    std::vector<Label>::const_iterator j = p.labels.begin();
    while(j != p.labels.end())
    {
        out << *j << '\n';
        ++j;
    }

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

Addressable* SymbolTable::getAddressable(const int index)
{
    return addressablesMap.find(index)->second;
}

//
// Get size of symbol table
//
const U8 SymbolTable::size() const
{
    U8 gvSize = globalVariables.size() * GLOBAL_VARIABLE_SIZE;
    U8 procSize {8}; //initialize to 8 bytes for the TOC
    std::vector<Procedure>::const_iterator p = procedures.begin();
    while(p != procedures.end())
    {
        U8 totalStackFrames = p->args.size() + p->locals.size();
        U8 totalLabels = p->labels.size();
        procSize += BASE_PROCEDURE_SIZE;
        procSize += totalStackFrames * STACK_FRAME_SIZE;
        procSize += totalLabels * LABEL_SIZE;
        ++p;
    }

    U8 totalSize = gvSize + procSize;
    return totalSize;
}

//
// Write the symbol table to file.
//
void SymbolTable::write(std::ofstream& out) const
{
    //write table of contents - 8 bytes long
    //which is two DWORDS specifying the number
    //of global variable records and the number
    //of procedure records.
    const U4 numGlobalVariables = globalVariables.size();
    const U4 numProcedures = procedures.size();
    out.write((const char*)&numGlobalVariables,sizeof(Logi::U4));
    out.write((const char*)&numProcedures,sizeof(Logi::U4));

    //write global variables
    std::vector<GlobalVariable>::const_iterator gv_it = globalVariables.begin();
    while(gv_it != globalVariables.end())
    {
        gv_it->write(out);
        ++gv_it;
    }

    int procSize {0};

    //write procedures
    std::vector<Procedure>::const_iterator p_it = procedures.begin();
    while(p_it != procedures.end())
    {
        p_it->write(out);

        procSize += p_it->size();

        ++p_it;
    }
}

std::ostream& operator<<(std::ostream& out,const SymbolTable& st)
{
    //output global variables
    out << std::right << "\nGLOBAL VARIABLES:\n";
    out << std::setw(W*6) << std::setfill('-') << '\n';
    out << std::left << std::setfill(' ');
    out << std::setw(W) << "line";
    out << std::setw(W) << "text";
    out << std::setw(W) << "type";
    out << std::setw(W) << "len";
    out << std::setw(W) << "size";
    out << std::setw(W) << "offset" << '\n';
    out << std::right << std::setw(W*6) << std::setfill('-') << '\n';

    std::vector<GlobalVariable>::const_iterator iv = st.globalVariables.begin();
    while(iv != st.globalVariables.end())
    {
        out << *iv << '\n';
        ++iv;
    }
    //output procedures
    out << "\nPROCEDURES:\n";
    out << std::right << std::setw(12) << std::setfill('-') << '\n';
    
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

std::vector<std::string>& SymbolRepository::getStringTable()
{
    return stringTable;
}

//
// Get total size of the string table in bytes.
// For each string we add a byte for the null-
// termination character '\0' so we can read
// the string in with std::getline(...)
//
const int SymbolRepository::stringTableSize() const
{
    int size {0};

    std::vector<std::string>::const_iterator i = stringTable.begin();

    while(i != stringTable.end())
    {
        size += i->length();
        ++i;
    }

    //now add all the null-termination characters
    size += stringTable.size();

    return size;
}

std::ostream& operator<<(std::ostream& out,const SymbolRepository& sr)
{
    // output the symbol table contents.
    out << "\nSYMBOL TABLE:\n";
    out << std::right << std::setw(14) << std::setfill('-') << '\n';
    out << sr.symbolTable;
    // output the string table contents.
    out << "\nSTRING TABLE:\n";
    out << std::right << std::setw(14) << std::setfill('-') << '\n';
    std::vector<std::string>::const_iterator i = sr.stringTable.begin();
    while(i != sr.stringTable.end())
    {
        out << *i << '\n';
        ++i;
    }

    return out;
}

} //namespace Logi
