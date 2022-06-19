/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 04.05.2022
 */

#include <sstream>
#include "CInterface.h"

CInterface::CInterface(std::istream & in, std::ostream & out) : in(in), out(out) {}

string CInterface::processInput() const {
    string command;
    in >> command;
    return command;
}

bool CInterface::processIntArg(int & arg) const {
    string s = processInput();
    istringstream iss(s);
    iss >> arg;
    return !iss.fail();
}

void CInterface::print(const string& toPrint) const {
    out << toPrint << endl;
}

void CInterface::printNumberPretty(int number, int width) const {
    string str = "+";
    for (int i = 0; i < width - 2; i ++)
        str += "-";
    str += "+\n| " + to_string(number);
    for (int i = 0; i < width - 4; i ++)
        str += " ";
    str += "|\n+";
    for (int i = 0; i < width - 2; i ++)
        str += "-";
    str += "+";

    print(str);
}

void CInterface::clearIn() const {
    in.clear();
}

ostream & CInterface::getOut() const {
    return out;
}
void CInterface::wrongArg(const string& cmdName) const {
    out << "wrong arguments, see zadani.txt for' " << cmdName + "',  or try 'help'" << endl;
    clearIn();
}

