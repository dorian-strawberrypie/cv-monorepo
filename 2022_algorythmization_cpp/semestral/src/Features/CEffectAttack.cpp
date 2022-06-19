/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#include "CEffectAttack.h"

CEffectAttack::CEffectAttack(Reader &r) : CEffect(r) {
    r.try_parse("damage", damage);
    r.try_parse("criticalChance", criticalChance);
    r.try_parse("criticalDamage", criticalDamage);
    r.try_parse("ignoresShield", reinterpret_cast<int &>(ignoresShield));
}

/**
 * @brief Target gets damage based on their shield and whether this attack
 * ignores it, whether it has critical chance and based on damage.
 *
 * @details Computes whether attack will be critical, based on chance.
 * Applies the damage if ignores shield. If not, the result damage
 * will take points from shield first, then health.
 *
 * @param target
 */
void CEffectAttack::apply(shared_ptr<CPlayer> target) {
    auto character = target->getCharacter();
    int resDamage = damage;

    bool isCritical = rand() % 100 + 1 < criticalChance;
    if (isCritical)
        resDamage = criticalDamage;

    if (ignoresShield) {
        character->addChange(-resDamage, 0);
    }
    else {
        int shield = character->getShield();
        int shieldDamage, healthDamage;
        shieldDamage = resDamage > shield ? shield : resDamage;
        healthDamage = resDamage > shield ? resDamage - shield : 0;
        character->addChange(-healthDamage, -shieldDamage);
    }
}

/**
 * Ensures that in case of playing a self-hurting card, player
 * can't use it if his health is not sufficient.
 * @param character
 * @return
 */
bool CEffectAttack::hasSufficientAttr(const shared_ptr<CCardCharacter>& character) const {
    if (damage - character->getHealth() < 0)
        return false;

    return true;
}

string CEffectAttack::stringEffect() const {
    string ret = getTargetStr() + "\n";
    ret += printIfNotZero("damage: ",damage, "\n");
    ret += printIfNotZero("criticalChance: ",criticalChance, "%\n");
    ret += printIfNotZero("criticalDamage: ",criticalDamage, "\n");
    if (ignoresShield) ret += "ignores shield\n";

    return ret;
}

/**
 * Used for CPlayerAI to get effect attributes.
 * Modifies cumulativeEffects with card attributes.
 * @param cumulativeEffects
 */
void CEffectAttack::addEffectsCumulative(vector<int>& cumulativeEffects) const {
    int sign = target == "self" ? -1 : 1;
    cumulativeEffects[1] += sign * damage;
    cumulativeEffects[2] += sign * criticalDamage;
    cumulativeEffects[3] += criticalChance;
}
