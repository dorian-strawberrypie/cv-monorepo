/**
* @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
* @date 05.05.2022
*/

#include "CEffect.h"

#include <utility>

CEffect::CEffect(Reader & r) {
    r.parse("target", target);
    if (target != "self" && target != "enemy")
        throw std::runtime_error("wrong target argument");
}


string CEffect::getTargetStr() const {
    return target;
}


string CEffect::printIfNotZero(const string& name, int attr, const string& end) const {
    if (attr == 0) return "";
    return " " + name + to_string(attr) + end;
}

