//Logi includes
#include "SymbolRepository.h"

//std includes
#include <iomanip>

namespace Logi
{

std::ostream& operator<<(std::ostream& out,const GlobalVariable& gv)
{
    out << "GLOBAL VARIABLE:\n";
    out << std::setw(17) << std::setfill('-') << '\n';
    out << "text: " << gv.text << '\n';
    out << "line: " << gv.line << '\n';
    out << "type: ";
    switch(gv.type)
    {
        case BYTE: out << "BYTE\n"; break;
        case WORD: out << "WORD\n"; break;
        case DWORD: out << "DWORD\n"; break;
        case QWORD: out << "QWORD\n"; break;
        default:
        {
            throw std::runtime_error("SYMBOL_REPOSITORY: not a valid global variable type.");
        }
    }
    if(gv.len > 1) out << "array count: " << gv.len << '\n';
    out << "size: " << gv.size << '\n';
    out << "offset: " << gv.offset << '\n';

    return out;
}

std::ostream& operator<<(std::ostream& out,const StackFrame& sf)
{
    out << "STACK FRAME:\n";
    out << std::setw(13) << std::setfill('-') << '\n';
    out << "text: " << sf.text << '\n';
    out << "FP offset: " << sf.fpOffset << '\n';
    out << "line: " << sf.line << '\n';

    return out;
}

std::ostream& operator<<(std::ostream& out,const Label& l)
{
    out << "LABEL:\n";
    out << std::setw(7) << std::setfill('-') << '\n';
    out << "text: " << l.text << '\n';
    out << "address: " << l.address << '\n';
    out << "line: " << l.line << '\n';

    return out;
}

std::ostream& operator<<(std::ostream& out,const Procedure& p)
{
    out << "PROCEDURE:\n";
    out << std::setw(11) << std::setfill('-') << '\n';
    out << "text: " << p.text << '\n';
    out <<"line: " << p.line << '\n';
    out <<"address: " << p.address << '\n';
    //output return
    out << "\nRETURN:\n";
    out << std::setw(8) << std::setfill('-') << '\n';
    if(p.retVal == ProcedureReturn::VOID) out << "VOID\n";
    else out << p.ret << '\n';
    //output arguments
    out << "ARGUMENTS:\n";
    out << std::setw(11) << std::setfill('-') << '\n';
    std::vector<StackFrame>::const_iterator i = p.args.begin();
    while(i != p.args.end())
    {
        out << *i << '\n';
        ++i;
    }
    //output locals
    out << "LOCALS:\n";
    out << std::setw(8) << std::setfill('-') << '\n';
    i = p.locals.begin();
    while(i != p.locals.end())
    {
        out << *i << '\n';
        ++i;
    }
    //output labels
    out << "LABELS:\n";
    out << std::setw(8) << std::setfill('-') << '\n';
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
    globalVariables.push_back(gv);
}

void SymbolTable::addProcedure(const Procedure& proc)
{
    procedures.push_back(proc);
}

std::ostream& operator<<(std::ostream& out,const SymbolTable& st)
{
    //output global variables
    out << "\nGLOBAL VARIABLES:\n";
    out << std::setw(18) << std::setfill('-') << '\n';

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

SymbolTable& SymbolRepository::getSymbolTable()
{
    return symbolTable;
}

std::ostream& operator<<(std::ostream& out,const SymbolRepository& sr)
{
    // output the symbol table contents.
    out << "\nSYMBOL TABLE:\n";
    out << std::setw(14) << std::setfill('-') << '\n';
    out << sr.symbolTable << '\n';
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
