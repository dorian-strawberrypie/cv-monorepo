/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#pragma once

#include "CEffect.h"
/**
 * Buff/debuff effect of CActionCard
 * changes target's health, stamina, staminaGain, mana, manaGain, gold, goldGain, shield
 */
class CEffectBuff : public CEffect {
public:
    explicit CEffectBuff(Reader & r);
    void apply(shared_ptr<CPlayer> target) override;
    bool hasSufficientAttr(const shared_ptr<CCardCharacter>& character) const override;
    static inline const std::string type = "buff";
    string stringEffect() const override;
    void addEffectsCumulative(vector<int> &cumulativeEffects) const override;

private:
    int health{}, stamina{}, staminaGain{}, mana{}, manaGain{}, gold{}, goldGain{}, shield{};
};
