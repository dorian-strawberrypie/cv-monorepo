/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 04.05.2022
 */

#pragma once

#include <memory>
#include <vector>
#include "../Core/CInterface.h"
#include "CCardCharacter.h"
#include "CCardAction.h"
class CCardAction;

/**
 * virtual base class for AI and Human players
 */
class CPlayer {

protected:
    explicit CPlayer(const CInterface & iface);
public:
    CInterface iface;
    int playerNumber;
    virtual string turn() = 0;
    void reobtainCard(int cardNum, shared_ptr<CCardAction> newCard);
    shared_ptr<CCardAction> getCard(int cardNum) const;
    shared_ptr<CCardCharacter> getCharacter() const;
    void setCharacter(const shared_ptr<CCardCharacter> & c);
protected:
    vector<shared_ptr<CCardAction>> cards;
    shared_ptr<CCardCharacter> character;
};
