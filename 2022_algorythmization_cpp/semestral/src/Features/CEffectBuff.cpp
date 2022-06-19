/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#include "CEffectBuff.h"

CEffectBuff::CEffectBuff(Reader &r) : CEffect(r) {
    r.try_parse("health", health);
    r.try_parse("stamina", stamina);
    r.try_parse("staminaGain", staminaGain);
    r.try_parse("mana", mana);
    r.try_parse("manaGain", manaGain);
    r.try_parse("gold", gold);
    r.try_parse("goldGain", goldGain);
    r.try_parse("shield", shield);
}

/**
 * target gains/loses attributes according to effect values.
 * @param target
 */
void CEffectBuff::apply(shared_ptr<CPlayer> target) {
    target->getCharacter()->addChange(health, stamina, staminaGain, mana,
                                     manaGain, gold, goldGain, shield);
}

string CEffectBuff::stringEffect() const {
    string ret = getTargetStr() + "\n";
    ret += printIfNotZero("health: ",health, "\n");
    ret += printIfNotZero("stamina: ",stamina, "\n");
    ret += printIfNotZero("staminaGain: ",staminaGain, "\n");
    ret += printIfNotZero("mana: ",mana, "\n");
    ret += printIfNotZero("manaGain: ",manaGain, "\n");
    ret += printIfNotZero("gold: ",gold, "\n");
    ret += printIfNotZero("goldGain: ",goldGain, "\n");
    ret += printIfNotZero("shield: ",shield, "\n");

    return ret;
}

/**
 * Check whether character can use a card with
 * their remaining stamina, mana and gold.
 * @param character
 * @return true if can, false otherwise
 */
bool CEffectBuff::hasSufficientAttr(const shared_ptr<CCardCharacter>& character) const {
    if (stamina + character->getStamina() < 0 ||
            mana + character->getMana() < 0 ||
            gold + character->getGold() < 0)
        return false;

    return true;
}

/**
 * Used for CPlayerAI to get effect attributes.
 * Modifies cumulativeEffects with card attributes.
 * @param cumulativeEffects
 */
void CEffectBuff::addEffectsCumulative(vector<int> &cumulativeEffects) const {
    int sign = target == "self" ? 1 : -1;
    cumulativeEffects[0] += sign * health;
    cumulativeEffects[4] += sign * stamina;
    cumulativeEffects[5] += sign * staminaGain;
    cumulativeEffects[6] += sign * mana;
    cumulativeEffects[7] += sign * manaGain;
    cumulativeEffects[8] += sign * gold;
    cumulativeEffects[9] += sign * goldGain;
    cumulativeEffects[10] += sign * shield;
}
