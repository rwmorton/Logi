//Logi includes
#include "Debugger.h"
#include "VirtualMachine.h"

//std includes
#include <iostream>
#include <istream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

namespace Logi
{

Debugger::Debugger(VirtualMachine& vm) : vm{vm}
{
    stream = Stream::getInstance();
}

Debugger::~Debugger()
{
    //free all global variables
    if(data.globalVariables != nullptr)
    {
        delete[] data.globalVariables;
    }

    //free all procedures and associated
    //ret, arg, local and labels
    if(data.procedures != nullptr)
    {
        if(data.procedures->ret != nullptr) delete data.procedures->ret;
        if(data.procedures->args != nullptr) delete[] data.procedures->args;
        if(data.procedures->locals != nullptr) delete[] data.procedures->locals;
        if(data.procedures->labels != nullptr) delete[] data.procedures->labels;
        delete[] data.procedures;
    }
}

void Debugger::read()
{
    while(true)
    {
        std::cout << "enter debug command: ";

        std::string debugLine{};
        std::getline(std::cin,debugLine);

        switch(debugLine.at(0))
        {
            case '?':
            case 'h':
            case 'H':
            {
                debugLine.size() == 1 ? help() : badCommand(debugLine);
            }
            break;
            case 'q':
            case 'Q':
            {
                if(debugLine.size() > 1)
                {
                    badCommand(debugLine);
                    break;
                }

                //quit debug mode and return control back to vm.run()
                vm.debugOn = false;
                return;
            }
            break;
            case 'f':
            case 'F':
            {
                if(debugLine.size() > 1)
                {
                    badCommand(debugLine);
                    break;
                }

                //executable information
                bytecode();
            }
            break;
            case 'd':
            case 'D':
            {
                std::vector<std::string> args{};
                splitArgs(debugLine,args);

                if(args.size() != 3)
                {
                    badCommand(debugLine);
                    break;
                }

                //dump memory
                dump();
            }
            break;
            case 's':
            case 'S':
            {
                std::vector<std::string> args{};
                splitArgs(debugLine,args);

                if(args.size() != 3)
                {
                    badCommand(debugLine);
                    break;
                }

                //search string
                search();
            }
            break;
            case 'l':
            case 'L':
            {
                std::vector<std::string> args{};
                splitArgs(debugLine,args);

                if(args.size() != 2)
                {
                    badCommand(debugLine);
                    break;
                }

                //symbol lookup
                symbol();
            }
            break;
            case 'p':
            case 'P':
            {
                if(debugLine.size() != 1)
                {
                    badCommand(debugLine);
                    break;
                }

                //procedure display
                procedure();
            }
            break;
            case 'r':
            case 'R':
            {
                if(debugLine.size() != 2)
                {
                    badCommand(debugLine);
                    break;
                }
                else
                {
                    switch(debugLine.at(1))
                    {
                        //print in registers
                        case 'i':
                        case 'I':
                        {
                            intRegisters();
                        }
                        break;
                        //print float registers
                        case 'f':
                        case 'F':
                        {
                            floatRegisters();
                        }
                        break;
                        //print double registers
                        case 'd':
                        case 'D':
                        {
                            doubleRegisters();
                        }
                        break;
                        default:
                        {
                            badCommand(debugLine);
                        }
                    }
                }

                //RX - register display (Ri,Rf,Rd)
            }
            break;
            case 't':
            case 'T':
            {
                if(debugLine.size() != 1)
                {
                    badCommand(debugLine);
                    break;
                }

                //trace
                trace();
            }
            break;
            default:
            {
                badCommand(debugLine);
            }
        }
    }
}

void Debugger::badCommand(const std::string& command) const
{
    std::string outStr {"DEBUGGER: bad command ["};
    outStr += command;
    outStr += "].\n";
    stream->string(outStr);
}

void Debugger::Debugger::splitArgs(const std::string& line,std::vector<std::string>& args) const
{
    std::istringstream iss(line);
    std::copy(std::istream_iterator<std::string>(iss),std::istream_iterator<std::string>(),std::back_inserter(args));
}

void Debugger::Debugger::help() const
{
    std::string helpString(70,'-');
    helpString += "\nDEBUG COMMAND HELP:\n";
    helpString += "?/h/H:\t\t\tdisplay this help screen.\n";
    helpString += "d/D start stop:\t\tdump memory in the range [start,stop].\n";
    helpString += "f/F:\t\t\tdisplay executable file information.\n";
    helpString += "l/L string:\t\tquery meta-data for a program identifier [string].\n";
    helpString += "q/Q:\t\t\texit debug mode and return to production mode.\n";
    helpString += "r/R{i}:\t\t\tdispay integer registers.\n";
    helpString += "r/R{f}:\t\t\tdispay float registers.\n";
    helpString += "r/R{d}:\t\t\tdispay double registers.\n";
    helpString += "s/S start stop string:\tsearch memory range [start,stop] for [string].\n";
    helpString += "t/T:\t\t\ttrace through next instruction.\n";
    
    stream->string(helpString);
}

void Debugger::Debugger::bytecode() const
{
    //
}

void Debugger::dump() const
{
    //
}

void Debugger::search() const
{
    //
}

void Debugger::symbol() const
{
    //
}

void Debugger::procedure() const
{
    //
}

void Debugger::intRegisters() const
{
    //
}

void Debugger::floatRegisters() const
{
    //
}

void Debugger::doubleRegisters() const
{
    //
}

void Debugger::trace() const
{
    //
}

} //namespace Logi
