//Logi includes
#include "../Assembler.h"

namespace Logi
{

//
// For each line check whether it is a directive or an
// instruction and load as appropriate.
//
void Assembler::buildSymbolRepository()
{
    std::vector<Line>::const_iterator line = tokenizedLines.begin();

    while(line != tokenizedLines.end())
    {
        switch(line->type)
        {
            case DIRECTIVE: loadDirective(line); break;
            case INSTRUCTION:
            {
                std::vector<Token>::const_iterator token_it = line->tokens.begin();
                loadInstruction(token_it);
            }
            break;
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

    switch(Assembler::ASMIdentifier_fromStr(token_it->str))
    {
        case PB: loadProcedure(line_it); break;
        case GB:
        case GW:
        case GD:
        case GQ:
        {
            loadGlobalVariable(token_it);
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
// Load global variable from token iterator.
//
void Assembler::loadGlobalVariable(std::vector<Token>::const_iterator& line_it)
{
    //
}

//
// Load procedure from Line iterator. Note that a
// procedure cannot contain another procedure.
//
void Assembler::loadProcedure(std::vector<Line>::const_iterator& line_it)
{
    bool firstLoad = true;
    while(line_it != tokenizedLines.end())
    {
        std::vector<Token>::const_iterator token_it = line_it->tokens.begin();
        switch(Assembler::ASMIdentifier_fromStr(token_it->str))
        {
            case PR: loadProcedureReturn(token_it); break;
            case PA: loadProcedureArgument(token_it); break;
            case PV: loadProcedureLocalVariable(token_it); break;
            case PL: loadProcedureLabel(token_it); break;
            case PE:
            {
                //end of procedure.
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
                    errorStr += " is not part of a valid procedure.";
                    throw std::runtime_error(errorStr);
                }

                firstLoad = false;;
            }
            break;
            default:
            {
                //must have an instruction
                //within the procedure.
                loadInstruction(token_it);
            }
            break;
        }

        ++line_it;
    }
}

//
// Load procedure return from token iterator.
//
void Assembler::loadProcedureReturn(std::vector<Token>::const_iterator& token_it)
{
    //
}

//
// Load procedure argument from token iterator.
//
void Assembler::loadProcedureArgument(std::vector<Token>::const_iterator& token_it)
{
    //
}

//
// Load procedure local variable from token iterator.
//
void Assembler::loadProcedureLocalVariable(std::vector<Token>::const_iterator& token_it)
{
    //
}

//
// Load procedure label from token iterator.
//
void Assembler::loadProcedureLabel(std::vector<Token>::const_iterator& token_it)
{
    //
}

//
// Load instruction from token iterator.
//
void Assembler::loadInstruction(std::vector<Token>::const_iterator& token_it)
{
    //
}

} //namespace Logi
