//Logi includes
#include "SymbolRepository.h"

//std includes
#include <iomanip>

namespace Logi
{

const std::vector<std::string> GlobalVariable::GVTypeStrings
{
    "BYTE","WORD","DWORD","QWORD"
};

std::ostream& operator<<(std::ostream& out,const GlobalVariable& gv)
{
    out << "GLOBAL VARIABLE:\n";
    out << std::setw(17) << std::setfill('-') << '\n';
    out << "text:\t" << gv.text << '\n';
    out << "line:\t" << gv.line << '\n';
    out << "type:\t" << GlobalVariable::GVTypeStrings.at(gv.type) << '\n';
    if(gv.len > 0) out << "array count: \t" << gv.len << '\n';
    out << "size:\t" << gv.size << '\n';
    out << "offset:\t" << gv.offset << '\n';

    return out;
}

std::ostream& operator<<(std::ostream& out,const StackFrame& sf)
{
    out << "STACK FRAME:\n";
    out << std::setw(13) << std::setfill('-') << '\n';
    out << "text:\t" << sf.text << '\n';
    out << "FP offset:\t" << sf.fpOffset << '\n';
    out << "line:\t" << sf.line << '\n';

    return out;
}

std::ostream& operator<<(std::ostream& out,const Label& l)
{
    out << "LABEL:\n";
    out << std::setw(7) << std::setfill('-') << '\n';
    out << "text:\t" << l.text << '\n';
    out << "address:\t" << l.address << '\n';
    out << "line:\t" << l.line << '\n';

    return out;
}

std::ostream& operator<<(std::ostream& out,const Procedure& p)
{
    out << "PROCEDURE:\n";
    out << std::setw(11) << std::setfill('-') << '\n';
    out << "text:\t" << p.text << '\n';
    out << "line:\t" << p.line << '\n';
    out << "address:\t" << p.address << '\n';
    //output return
    out << "RETURN:\n";
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
    i = p.labels.begin();
    while(i != p.labels.end())
    {
        out << *i << '\n';
        ++i;
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
    out << "\nSYMBOL TABLE:\n";
    out << std::setw(14) << std::setfill('-') << '\n';
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

void SymbolRepository::addIdentifier(const std::string& id)
{
    stringVector.push_back(id);
}

std::ostream& operator<<(std::ostream& out,const SymbolRepository& sr)
{
    //
    // output the string vector contents.
    //
    out << "\nSTRING VECTOR:\n";
    out << std::setw(15) << std::setfill('-') << '\n';
    std::vector<std::string>::const_iterator i = sr.stringVector.begin();
    while(i != sr.stringVector.end())
    {
        out << *i << '\n';
        ++i;
    }

    return out;
}

} //namespace Logi
