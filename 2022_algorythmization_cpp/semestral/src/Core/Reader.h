/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 04.06.2022
 */

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

/**
 * reads file lines and separates them into 2 elements -
 * type and value, using Regex expressions, getline func.
 *
 */
class Reader {
public:
    struct Error : runtime_error {
        using runtime_error::runtime_error;
    };

    Reader(const string& file);

    void parse(const string& tag, string& v);

    bool try_parse(const string& tag, string& v);

    bool try_parse(const string& tag, int & v);

private:
    string line;
    ifstream inp;
};