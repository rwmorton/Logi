//Logi includes
#include "../Assembler.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Logi
{

//
// For each line check whether it is a directive or an
// instruction and load as appropriate.
//
void Assembler::buildSymbolRepository()
{
    std::vector<Line>::const_iterator line = tokenizedLines.begin();

    //init global variable address tracker
    globalVariableOffset = 0;
    
    //initialize bytecode loader (skip loading bytecode)
    bytecodeLoader.init(&symbolRepository,true,true);

    while(line != tokenizedLines.end())
    {
        switch(line->type)
        {
            case DIRECTIVE: loadDirective(line); break;
            case INSTRUCTION: loadInstruction(*line); break;
            default:
            {
                std::string errorStr {"ASSEMBLER: not a valid instruction or directive (line: "};
                errorStr += std::to_string(line->pos);
                errorStr += ").";
                throw std::runtime_error(errorStr);
            }
        }

        ++line;
    }
}

//
// Resolve all addresses from the symbol repository stage.
//
void Assembler::resolveAddresses()
{
    //resolve addresses
    std::map<std::string,U8>::const_iterator i = bytecodeLoader.getAddressesToResolve().begin();
    while(i != bytecodeLoader.getAddressesToResolve().end())
    {
        //find address of this identifier
        S8 addr = static_cast<S8>(symbolRepository.getAddress(i->first));

        //get the addressable itself (an identifier)
        const int index = symbolRepository.indexInStringTable(i->first);
        Addressable* addressable = symbolRepository.getSymbolTable().getAddressable(index);

        addressable->address = addr; //set to correct address

        cout << "resolving address of identifier (" << i->first;
        cout << ") to the correct address (" << addr << ") at byte (" << i->second << ")" << endl;

        ++i;
    }
}

//
// Now the  symbol repository has been built
// generate the bytecode from assembler.
//
void Assembler::buildBytecode()
{
    std::vector<Line>::const_iterator line = tokenizedLines.begin();

    //initialize bytecode loader, this time load bytecode.
    bytecodeLoader.init(&symbolRepository,false,false);

    while(line != tokenizedLines.end())
    {
        switch(line->type)
        {
            case DIRECTIVE: break;
            case INSTRUCTION: loadInstruction(*line); break;
            default:
            {
                std::string errorStr {"ASSEMBLER: not a valid instruction or directive (line: "};
                errorStr += std::to_string(line->pos);
                errorStr += ").";
                throw std::runtime_error(errorStr);
            }
        }

        ++line;
    }

    //no further need for the vector of tokenized lines
    tokenizedLines.clear();
}

//
// Load directive from given line iterator.
// This is because directives e.g. .PB can
// span multiple lines until termination at .PE.
//
// Some directives out of scope are invalid, eg. .PL
// is not valid unless it is within the scope of .PB
//
void Assembler::loadDirective(std::vector<Line>::const_iterator& line_it)
{
    std::vector<Token>::const_iterator token_it = line_it->tokens.begin();

    //check directive
    switch(Assembler::ASMIdentifier_fromStr(token_it->str))
    {
        case PB:
        {
            loadProcedure(line_it);
        }
        break;
        case GB:
        case GW:
        case GD:
        case GQ:
        {
            loadGlobalVariable(*line_it);
        }
        break;
        default:
        {
                std::string errorStr {"ASSEMBLER: not a valid directive (line: "};
                errorStr += std::to_string(line_it->pos);
                errorStr += ").";
                throw std::runtime_error(errorStr);
        }
    }
}

//
// Load global variable from line (so we can see whether an array or not).
//
void Assembler::loadGlobalVariable(const Line& line)
{
    GlobalVariable g;
    g.line = line.pos; //save line in source code that this variable is declared

    std::vector<Token>::const_iterator token_it = line.tokens.begin();

    //set type of variable
    ASMIdentifier id = Assembler::ASMIdentifier_fromStr(token_it->str);

    switch(id)
    {
        case GB: g.type = BYTE; break;
        case GW: g.type = WORD; break;
        case GD: g.type = DWORD; break;
        case GQ: g.type = QWORD; break;
        default:
        {
            throw std::runtime_error("ASSEMBLER: not a valid global variable directive"); //this should never happen
        }
    }

    //move onto next token
    ++token_it;
    std::string gvStr = token_it->str;
    g.text = symbolRepository.addIdentifier(gvStr); //save identifier to stringTable

    //is this an array?
    if(line.tokens.size() == 3)
    {
        //yes, is an array
        ++token_it;
        g.len = token_it->val.S8_val;
    }
    else g.len = 1; //not an array

    //set total size in bytes
    g.size = g.len * g.type;

    //set offset
    globalVariableOffset -= g.size;
    g.offset = globalVariableOffset;

    //keep track of this for address resolution
    g.address = static_cast<S8>(globalVariableOffset);

    symbolRepository.getSymbolTable().addGlobalVariable(g);
    symbolRepository.addLabelAddr(gvStr,g.address);

    //write to listing file
    if(createListing)
    {
        std::string lstStr{};

        switch(id)
        {
            case PB: lstStr += ".PB "; break;
            case GB: lstStr += ".GB "; break;
            case GW: lstStr += ".GW "; break;
            case GD: lstStr += ".GD "; break;
            case GQ: lstStr += ".GQ "; break;
        }
        
        lstStr += gvStr;

        if(g.len > 1)
        {
            lstStr += ' ';
            lstStr += std::to_string(g.len);
        }

        //save the listing line
        ListingLine ll;
        ll.line = g.line;
        ll.str = lstStr;
        listingLines.push_back(ll);
    }
}

//
// Load procedure from Line iterator. Note that a
// procedure cannot contain another procedure.
//
void Assembler::loadProcedure(std::vector<Line>::const_iterator& line_it)
{
    Procedure proc;
    proc.line = line_it->pos; //save line in source file
    std::string procStr = line_it->tokens.at(1).str;
    proc.text = symbolRepository.addIdentifier(procStr);
    U8 procByteBegin = bytecodeLoader.getCurrentByte();
    proc.retVal = ProcedureReturn::VOID; //default value

    //create listing file
    if(createListing)
    {
        std::string lstStr {".PB "};
        lstStr += procStr;

        //save the listing line
        ListingLine ll;
        ll.line = proc.line;
        ll.str = lstStr;
        listingLines.push_back(ll);        
    }

    //get next line
    ++line_it;

    bool firstLoad = true;
    bool retLoad = false;
    bool firstInst = true;

    while(line_it != tokenizedLines.end())
    {
        switch(Assembler::ASMIdentifier_fromStr(line_it->tokens.at(0).str))
        {
            case PR:
            {
                //if we have already loaded a procedure retval
                //then this is an error as a procedure can only
                //have one retval.
                if(retLoad)
                {
                    std::string errorStr {"ASSEMBLER: line "};
                    errorStr += std::to_string(line_it->pos);
                    errorStr += " : cannot have more than one .PR directive.";
                    throw std::runtime_error(errorStr);
                }
                retLoad = true;
                proc.retVal = ProcedureReturn::VALUE;
                loadProcedureReturn(proc,*line_it);
            }
            break;
            case PA: loadProcedureArgument(proc,*line_it); break;
            case PV: loadProcedureLocalVariable(proc,*line_it); break;
            case PL: loadProcedureLabel(proc,*line_it); break;
            case PE:
            {
                //end of procedure.
                //save procedure
                symbolRepository.getSymbolTable().addProcedure(proc);
                //create listing
                if(createListing)
                {
                    //save the listing line
                    std::string lstStr {".PE"};
                    ListingLine ll;
                    ll.line = line_it->pos;
                    ll.str = lstStr;
                    listingLines.push_back(ll);
                }
                //and return
                return;
            }
            break;
            case PB:
            {
                //if this is not the initial loading of .PB
                //then this is an error as a procedure
                //cannot contain another procedure.
                if(!firstLoad)
                {
                    std::string errorStr {"ASSEMBLER: line "};
                    errorStr += std::to_string(line_it->pos);
                    errorStr += " : is not part of a valid procedure.";
                    throw std::runtime_error(errorStr);
                }

                firstLoad = false;
            }
            break;
            default:
            {
                //must be an instruction
                //within the procedure.

                //if the first instruction
                if(firstInst)
                {
                    //then we assign it as the address
                    //of the procedure.
                    proc.address = static_cast<S8>(bytecodeLoader.getCurrentByte());
                    firstInst = false;

                    //save to the symbol map
                    //note: will always resolve to the correct address
                    symbolRepository.addLabelAddr(procStr,proc.address);
                }

                loadInstruction(*line_it);
            }
            break;
        }

        ++line_it;
    }
}

//
// Load stack frame from given line.
//
void Assembler::loadStackFrame(StackFrame& stackFrame,const Line& line)
{
    stackFrame.line = line.pos; //save line position in source code

    std::vector<Token>::const_iterator token_it = line.tokens.begin();

    //move onto next token
    ++token_it;
    std::string sfStr {token_it->str};
    stackFrame.text = symbolRepository.addIdentifier(sfStr); //save identifier to string table

    //move onto next token
    ++token_it;
    //and get the offset
    stackFrame.fpOffset = token_it->val.S8_val;

    //create listing
    if(createListing)
    {
        std::string lstStr {sfStr};
        lstStr += ' ';
        lstStr += std::to_string(stackFrame.fpOffset);
        
        //update the current listing line
        ListingLine& ll = listingLines.back();
        ll.add(lstStr);
    }
}

//
// Load procedure return from line.
//
void Assembler::loadProcedureReturn(Procedure& proc,const Line& line)
{
    //create listing
    if(createListing)
    {
        std::string lstStr {".PR "};
        
        //save the listing line
        ListingLine ll;
        ll.line = line.pos;
        ll.str = lstStr;
        listingLines.push_back(ll);
    }

    loadStackFrame(proc.ret,line);
}

//
// Load procedure argument from line.
//
void Assembler::loadProcedureArgument(Procedure& proc,const Line& line)
{
    //create listing
    if(createListing)
    {
        std::string lstStr {".PA "};
        
        //save the listing line
        ListingLine ll;
        ll.line = line.pos;
        ll.str = lstStr;
        listingLines.push_back(ll);
    }

    StackFrame arg;
    loadStackFrame(arg,line);
    proc.args.push_back(arg);
}

//
// Load procedure local variable from line.
//
void Assembler::loadProcedureLocalVariable(Procedure& proc,const Line& line)
{
    //create listing
    if(createListing)
    {
        std::string lstStr {".PV "};
        
        //save the listing line
        ListingLine ll;
        ll.line = line.pos;
        ll.str = lstStr;
        listingLines.push_back(ll);
    }

    StackFrame local;
    loadStackFrame(local,line);
    proc.locals.push_back(local);
}

//
// Load procedure label from line iterator (so we can get access to next instruction).
//
void Assembler::loadProcedureLabel(Procedure& proc,const Line& line)
{
    Label label;
    label.line = line.pos;
    std::string labelStr = line.tokens.at(1).str;
    label.text = symbolRepository.addIdentifier(labelStr); //save identifier to string table

    //label address is the instruction immediately after this line
    label.address = static_cast<S8>(bytecodeLoader.getCurrentByte());

    //add to the symbol map
    symbolRepository.addLabelAddr(line.tokens.at(1).str,label.address);

    //save label
    symbolRepository.getSymbolTable().addLabel(label);
    proc.labels.push_back(label);

    //create listing
    if(createListing)
    {
        std::string lstStr {".PL "};
        lstStr += labelStr;
        
        //save the listing line
        ListingLine ll;
        ll.line = line.pos;
        ll.str = lstStr;
        listingLines.push_back(ll);
    }
}

//
// Load instruction from line.
//
void Assembler::loadInstruction(const Line& line)
{
    bytecodeLoader.load(line);
}

} //namespace Logi
