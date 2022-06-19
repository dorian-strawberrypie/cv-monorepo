/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#pragma once

#include "CCard.h"
#include "CEffect.h"
#include <vector>

class CEffect;
class CPlayer;
/**
 * Vector cardEffects stores all card effects.
 * Used to check whether this card can be played,
 * to use the effects on target, to load effects into *this.
 */
class CCardAction : public CCard {
private:
    vector<std::shared_ptr<CEffect>> cardEffects;
public:
    explicit CCardAction(Reader & r);
    string stringCard() const override;
    void addEffect(const std::shared_ptr<CEffect> & effect);
    bool action(const shared_ptr<CPlayer>& current, const shared_ptr<CPlayer>& idle);
    bool canPlayCard(const shared_ptr<CCardCharacter>& character) const;
    void getAttrVector(vector<int> & cumulativeEffects) const;
};
