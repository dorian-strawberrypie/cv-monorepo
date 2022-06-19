/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#include "CCard.h"

CCard::CCard(string name):name(move(name)) {

}

CCard::CCard(Reader & r) {
    r.parse("name", name);
}

/**
 * prints card name with max width of CARDSTRWIDTH
 * @return
 */
string CCard::stringName() const {
    string ret = "name: ";
    auto nl = name.length();
    for (int i = 0; i < nl && i < CARDSTRWIDTH - 8; i++)
        ret += name[i];
    return ret + "\n";
}
