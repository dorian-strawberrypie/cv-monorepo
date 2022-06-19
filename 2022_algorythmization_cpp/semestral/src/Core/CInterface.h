/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#pragma once

#include <iostream>
using namespace std;

/**
 * CInterface contains methods for printing, processing input.
 * Each entity (each player) can use a different streams.
 * CInterface uses operator>> and operator<< for processing in/out.
 */
class CInterface {
private:
    istream & in;
    ostream & out;
public:

    CInterface ( istream & in, ostream & out );
    void print(const string& toPrint) const;
    void printNumberPretty(int number, int width) const;
    string processInput() const;
    bool processIntArg(int & arg) const;
    void clearIn() const;
    ostream & getOut() const;
    void wrongArg(const string& cmdName) const;
};
