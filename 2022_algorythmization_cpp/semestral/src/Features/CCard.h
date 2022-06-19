/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#pragma once

#include <string>
#include <iostream>
#include <memory>
#include "../Core/Reader.h"


using namespace std;
/**
 * virtual base class for CCardAction and CCardCharacter
 */
class CCard {
public:
    string name;

    explicit CCard(string name);

    explicit CCard(Reader& r);

    CCard(const CCard & other) = default;

    virtual ~CCard() = default;

    virtual string stringCard() const = 0;

    string stringName() const;

    const int CARDSTRWIDTH = 25;

};