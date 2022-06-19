//
// Created by jakub on 6/4/2022.
//

#include "../Features/CCardAction.h"
#include "../Features/CCardCharacter.h"
#include "../Features/CCard.h"
#include <regex>
#include <memory>
#include <map>
#include "Reader.h"


Reader::Reader(const string& file) : inp(file) {
    if (inp.fail())
        throw runtime_error("could not open file: " + file);
}

/**
 * Gets expected tag, puts value into v (for mandatory arguments).
 * @param tag if matches, proceeds to load value
 * @param v value
 */
void Reader::parse(const string& tag, string& v) {
    if (!try_parse(tag, v)) throw Error("");
}

/**
 * Tries parsing value by tag (for optional arguments)
 * @param tag if matches, proceeds to load value
 * @param v value
 * @return success, throws exception if stoi failed
 */
bool Reader::try_parse(const string& tag, int & v) {
    string num;
    if (!try_parse(tag, num)) return false;
    v = stoi(num);
    return true;
}

/**
 * Tries parsing value by tag (for optional arguments).
 * Reads line, tries matching it to "tag value;" format.
 * @param tag if matches, proceeds to load value
 * @param v value
 * @return true for success, false otherwise.
 */
bool Reader::try_parse(const string& tag, string& v) {
    if (line.empty()) getline(inp, line, ';');

    regex re(R"(\s*(\S+)\s*(.*?)\s*)");
    smatch m;

    if (!regex_match(line, m, re) || tag != m[1])
        return false;

    v = m[2];
    line = "";

    return true;
}
