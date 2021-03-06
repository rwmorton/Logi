//Logi includes
#include "Debugger.h"
#include "VirtualMachine.h"
#include "Console.h"

//std includes
#include <iostream>
#include <istream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <cmath>

namespace Logi
{

Debugger::Debugger(VirtualMachine& vm) : vm{vm}, print{vm}
{
    stream = Stream::getInstance();
}

Debugger::~Debugger() {}

void Debugger::read()
{
    while(true)
    {
        std::string debugLine{};
        std::getline(std::cin,debugLine);

        if(debugLine.size() == 0)
        {
            badCommand("input empty command, try again.");
        }
        else
        {
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

                    //quit debug mode and return control back to run()
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
                    dump(std::stoull(args[1]),std::stoull(args[2]));
                }
                break;
                //string do not contain whitespace
                case 's':
                case 'S':
                {
                    std::vector<std::string> args{};
                    splitArgs(debugLine,args);

                    if(args.size() != 4)
                    {
                        badCommand(debugLine);
                        break;
                    }

                    //search string
                    search(std::stoull(args[1]),std::stoull(args[2]),args[3]);
                }
                break;
                //symbols do not contain whitespace
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
                    symbol(args[1]);
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
                            //print basic registers
                            case 'b':
                            {
                                basicRegisters();
                            }
                            break;
                            //print int registers
                            case 'i':
                            {
                                intRegisters();
                            }
                            break;
                            //print float registers
                            case 'f':
                            {
                                floatRegisters();
                            }
                            break;
                            //print double registers
                            case 'd':
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
                    //simply return to run(), which
                    //then returns back to the debugger
                    return;
                }
                break;
                default:
                {
                    badCommand(debugLine);
                }
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
    helpString += "r/R{b}:\t\t\tdispay basic registers.\n";
    helpString += "r/R{i}:\t\t\tdispay integer registers.\n";
    helpString += "r/R{f}:\t\t\tdispay float registers.\n";
    helpString += "r/R{d}:\t\t\tdispay double registers.\n";
    helpString += "s/S start stop string:\tsearch memory range [start,stop] for [string].\n";
    helpString += "t/T:\t\t\ttrace through next instruction.\n";
    
    stream->string(helpString);
}

void Debugger::Debugger::bytecode() const
{
    std::ostream& out = stream->get();
    out << '\n' << vm.executable << '\n';
}

void Debugger::dump(const U8 start,const U8 stop) const
{
    if(checkRange(start,stop))
    {
        std::ostream& out = stream->get();

        std::string str {"MEMORY DUMP ["};
        str += std::to_string(start);
        str += ',';
        str += std::to_string(stop);
        str += "]:";

        out << '\n' << str << '\n';
        out << std::right << std::setw(str.length()+1) << std::setfill('-') << '\n';

        //get positions for console color
        Bytecode& exe = vm.executable;
        U8 bytecodeSize = exe.bytecodeSize;
        U8 heapSize = exe.heapSize * 1024;
        U8 stackSize = exe.stackSize * 1024;
        U8 bytecodeEnd = bytecodeSize-1;        // use bytecodeSize because bytecodeEndAddress includes the header
        U8 heapEnd = bytecodeEnd + heapSize;    // offset by size of heap in bytes
        U8 stackEnd = heapEnd + stackSize;      // offset by size of stack in bytes

        //print for reference
        out << "RAM (" << vm.executable.totalSize << "): [";
        out << Console::CYAN << "BYTECODE";
        out << Console::RESET << " (" << bytecodeSize << ")], [";
        out << Console::GREEN << "HEAP";
        out << Console::RESET << " (" << heapSize << ")], [";
        out << Console::BLUE << "STACK";
        out << Console::RESET << " (" << stackSize << ")]\n";
        out << Console::YELLOW << "$IP = " << vm.registers.R($IP) << '\n';
        out << Console::YELLOW << "$SP = " << vm.registers.R($SP) << '\n';
        out << Console::RED << "$TOP = " << vm.registers.R($TOP) << '\n';
        out << Console::RESET << '\n';

        for(U8 i=start; i<=stop; i++)
        {
            //differentiate between bytecode, heap and stack sections
            if(i <= bytecodeEnd) out << Console::CYAN;
            else if(i <= heapEnd) out << Console::GREEN;
            else if(i <= stackEnd ) out << Console::BLUE;

            //print $IP, $SP and $TOP
            if(i == vm.registers.R($SP) || i == vm.registers.R($IP)) out << Console::YELLOW;
            if(i == vm.registers.R($TOP)) out << Console::RED;

            stream->U1((*vm.ram)(i));
            if(i < stop) out << ' ';
        }
        out << '\n';
    } //else, checkRange will print appropriate message.

    //reset console color
    stream->get() << Console::RESET;
}

//
// TODO: not sure if working properly, need some actual data to test.
//
void Debugger::search(const U8 start,const U8 stop,const std::string& str) const
{
    if(checkRange(start,stop))
    {
        std::ostream& out = stream->get();
        out << std::dec;
        out << "\nSEARCHING FOR STRING [" << str << "] IN RANGE [" << start << "," << stop << "]:\n";
        out << std::right << std::setw(70) << std::setfill('-') << '\n';
        
        bool match = false;
        U8 address{};

        for(int i=start; i<=stop; i++)
        {
            if((*vm.ram)(i) == str.at(0))
            {
                //does the whole string match what is in RAM?
                if(i + str.length() > stop)
                {
                    out << "\n\nTERMINATED: search goes out of bounds.\n";
                    return;
                }
                else
                {
                    for(int j=i; j<str.length(); j++)
                    {
                        if((*vm.ram)(j) != str.at(j))
                        {
                            match = false;
                            break;
                        }
                        match = true;
                        address = (*vm.ram)(i);
                        out << "MATCHED AT ADDRESS: " << address << '\n';
                        return;
                    }
                }
            }
        }
        out << '\n';
    } //else, checkRange will print appropriate message.
}

void Debugger::symbol(const std::string& str) const
{
    std::ostream& out = stream->get();
    out << std::dec;
    out << "\nSEARCHING FOR SYMBOL [" << str << "]:\n";
    out << std::right << std::setw(30) << std::setfill('-') << '\n';
    //
    throw std::runtime_error("DEBUGGER: symbol() unimplemented."); //need more data to do this.
}

void Debugger::procedure() const
{
    throw std::runtime_error("DEBUGGER: procedure() unimplemented.");
}

void Debugger::basicRegisters() const
{
    std::ostream& out = stream->get();
    out << std::dec << "\nBASIC REGISTERS:\n";
    out << std::right << std::setw(17) << std::setfill('-') << '\n';
    for(int i=$IP; i<=$TOP; i++)
    {
        out << std::dec << vm.registers.R_str((RegisterCodes)i) << ":\t" << std::showbase << std::hex << vm.registers.R((RegisterCodes)i) << '\n';
    }
    out << std::dec << '\n';
}

void Debugger::intRegisters() const
{
    std::ostream& out = stream->get();
    out << std::dec << "\nINTEGER REGISTERS:\n";
    out << std::right << std::setw(19) << std::setfill('-') << '\n';
    for(int i=$R1; i<=$R24; i++)
    {
        out << std::dec << vm.registers.R_str((RegisterCodes)i) << ":\t" << std::showbase << std::hex << vm.registers.R((RegisterCodes)i) << '\n';
    }
    out << std::dec << '\n';
}

void Debugger::floatRegisters() const
{
    std::ostream& out = stream->get();
    out << std::dec << "\nFLOAT REGISTERS:\n";
    out << std::right << std::setw(17) << std::setfill('-') << '\n';
    for(int i=$F1; i<=$F10; i++)
    {
        out << std::dec << vm.registers.RF_str((FloatRegisterCodes)i) << ":\t" << std::showbase << std::hex << vm.registers.RF((FloatRegisterCodes)i) << '\n';
    }
    out << std::dec << '\n';
}

void Debugger::doubleRegisters() const
{
    std::ostream& out = stream->get();
    out << std::dec << "\nDOUBLE REGISTERS:\n";
    out << std::right << std::setw(18) << std::setfill('-') << '\n';

    for(int i=$D1; i<=$D10; i++)
    {
        out << std::dec << vm.registers.RD_str((DoubleRegisterCodes)i) << ":\t" << std::showbase << std::hex << vm.registers.RD((DoubleRegisterCodes)i) << '\n';
    }
    out << std::dec << '\n';
}

const bool Debugger::checkRange(const U8 start,const U8 stop) const
{
    std::ostream& out = stream->get();
    out << std::dec;
    std::string badInput = "Bad input to dump: ";

    if(start > stop)
    {
        out << badInput << "start > stop.\n";
        return false;
    }

    if(start > vm.registers.R($TOP))
    {
        out << badInput << "start > $TOP.\n";
        return false;
    }

    if(stop > vm.registers.R($TOP))
    {
        out << badInput << "stop > $TOP.\n";
        return false;
    }

    return true;
}

} //namespace Logi
