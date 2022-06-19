/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#include "CPlayerAI.h"
#include "../Core/CGame.h"

CPlayerAI::CPlayerAI(ostream & os) : CPlayer(ifaceInit(os)) {

}

CInterface CPlayerAI::ifaceInit(ostream & os) {
    CInterface c(ss, os);
    return c;
}

string CPlayerAI::turn() {
    ss.str("");
    ss.clear();
    ss << decideTurn();
    string ret = iface.processInput();
    return ret;
}

/**
 * Fill vector of actions with every possible action,
 * compute the action's weight in action ctor,
 * sort the vector by weights descending,
 * choose the first action that can be played,
 * @return command, eg. "play 3"
 */
string CPlayerAI::decideTurn() {
    vector<action> actions;
    for (int i = 0; i < CGame::CARDCAP; i++) {
        actions.emplace_back("play", i+1, character,cards[i]);
        actions.emplace_back("throw", i+1, character, cards[i]);
    }
    std::sort(actions.begin(), actions.end(),
              [](const action & a, const action & b) -> bool
    {
        return a.weight > b.weight;
    });
    for (const auto& a : actions) {
            if (!a.card->canPlayCard(character))
                continue;
            return a.commandName + " " + to_string(a.cardNumber);
    }
    return "throw 1";
}

/**
 * Computes weight of the action.
 * @param cmd "play" or "throw"
 * @param cardNum
 * @param self
 * @param card evaluated card
 */
CPlayerAI::action::action(string cmd, int cardNum,
                          const shared_ptr<CCardCharacter> & self, const shared_ptr<CCardAction> & card)
                            : commandName(std::move(cmd)), cardNumber(cardNum), card(card) {
    sign = commandName == "throw" ? -1 : 1;
    weight = evaluateCard(self) * sign;
}

/**
 * @briref Computes points (also weight) of a CCardAction. The computer
 * will use the card with the most points, if he has sufficient
 * attributes for it (mana, gold, etc..).
 *
 * @details every +effectAttr = +1 point, exceptions:
 * points for health =
 * playerMaxHealth / setMin(playerHealth, 1) * healingEffect
 * points for damage =
 * - (damage + (criticalDamage * criticalChance)) * 2
 *
 * @param self computer's CCardCharacter instance
 * @return points (also weight)
 */
double CPlayerAI::action::evaluateCard(const shared_ptr<CCardCharacter> & self) {
    double points = 0;

    vector<int> attrVector(11, 0);
    card->getAttrVector(attrVector);
    for (size_t i = 4; i < attrVector.size(); i++)
        points += attrVector[i];
    points += (double(self->getMaxHealth()) / setMin(self->getHealth(), 1)) * attrVector[0];
    points += (attrVector[1] + (attrVector[2] * attrVector[3])) * 2;
    return points;
}

/**
 * @param value value to normalize
 * @param min minimum acceptable value
 * @return normalized value to a minimum of min
 */
int CPlayerAI::action::setMin(int value, int min) {
    return value < min ? min : value;
}
