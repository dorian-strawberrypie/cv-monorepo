/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#pragma once

#include "CEffect.h"

/**
 * Attack effect of \class CCardAction
 * damage is calculated by params. base damage, critical chance, whether eff.
 *      ignores shield and critical damage
 */
class CEffectAttack : public CEffect {
public:
    explicit CEffectAttack(Reader & r);
    void apply(shared_ptr<CPlayer> target) override;
    bool hasSufficientAttr(const shared_ptr<CCardCharacter>& character) const override;
    static inline const std::string type = "attack";
    string stringEffect() const override;
    void addEffectsCumulative(vector<int> &cumulativeEffects) const override;

private:
    int damage{};
    int criticalChance{};
    int criticalDamage{};

    bool ignoresShield{};
};
