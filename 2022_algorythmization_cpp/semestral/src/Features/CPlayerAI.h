/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 04.05.2022
 */

#pragma once

#include <sstream>
#include <utility>
#include "CPlayer.h"

/**
 * turn realised by computing points for each card, that the computer holds
 * has own stringstream for interface input and cmd line for output
 */

class CPlayerAI : public CPlayer {
private:
    string decideTurn();
    stringstream ss;
    /**
     * for storing a command and computing it's weight - command with the
     *      highest weight will be executed by the computer.
     */
    struct action {
        action(string cmd, int cardNum, const shared_ptr<CCardCharacter> & self, const shared_ptr<CCardAction> & card);
        string commandName;
        double weight;

        int cardNumber;
        int sign;
        shared_ptr<CCardAction> card;

        double evaluateCard( const shared_ptr<CCardCharacter> & self);
        int setMin(int value, int min);
    };
public:
    CInterface ifaceInit(ostream & os);
    CPlayerAI(ostream & os);
    string turn() override;
};
