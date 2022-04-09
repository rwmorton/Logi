//Logi includes
#include "SymbolRepository.h"

//std includes
#include <iomanip>
#include <map>

namespace Logi
{

std::ostream& operator<<(std::ostream& out,const GlobalVariable& gv)
{
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

    return out;
}

std::ostream& operator<<(std::ostream& out,const StackFrame& sf)
{
    out << sf.line << '\t' << sf.text << '\t' << sf.fpOffset;

    return out;
}

std::ostream& operator<<(std::ostream& out,const Label& l)
{
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
