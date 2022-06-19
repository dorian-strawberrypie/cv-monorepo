/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#include "CCardAction.h"

CCardAction::CCardAction(Reader & r) : CCard(r) {

}

void CCardAction::addEffect(const std::shared_ptr<CEffect> & effect) {
    cardEffects.push_back(effect);
}

/**
 * Finds whether a character has enough attr to use the card.
 * @param character
 * @return
 */
bool CCardAction::canPlayCard(const shared_ptr<CCardCharacter>& character) const {
    for (const auto & eff : cardEffects) {
        if (eff->getTargetStr() != "self")
            continue;
        if (!eff->hasSufficientAttr(character))
            return false;
    }
    return true;
}

/**
 * Check whether can be played by player and then applies each CEffect.
 * @param current
 * @param idle
 * @return success
 */
bool CCardAction::action(const shared_ptr<CPlayer>& current, const shared_ptr<CPlayer>& idle) {
    if (!canPlayCard(current->getCharacter()))
        return false;
    for (const auto & eff : cardEffects) {
        auto & target = eff->getTargetStr() == "self" ? current : idle;
        eff->apply(target);
    }
    return true;
}

string CCardAction::stringCard() const {
    string ret;
    ret += stringName();
    for (const auto& e : cardEffects) {
        ret += e->stringEffect();
    }
    return ret;
}

/**
 * returns cumulative (sum of target and self effect of):
 * health, damage, criticalDamage, criticalChance, stamina, sGain, mana, manaGain, gold, goldGain, shield
 */
void CCardAction::getAttrVector(vector<int> & cumulativeEffects) const {
    for (const auto& eff : cardEffects) {
        eff->addEffectsCumulative(cumulativeEffects);
    }
}
