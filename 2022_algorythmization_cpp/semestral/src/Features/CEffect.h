/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#pragma once

#include "CPlayer.h"

class CPlayer;

/**
 * virtual base class for CEffectBuff and CEffectAttack
 */
class CEffect {
public:

    explicit CEffect(Reader  & r);

    virtual ~CEffect() = default;

    template < typename I >
    static std::unique_ptr<CEffect> create(Reader& r) {
        return make_unique<I>(r);
    }

    virtual void apply(shared_ptr<CPlayer> target) = 0;

    virtual bool hasSufficientAttr(const shared_ptr<CCardCharacter>& character) const = 0;

    virtual string stringEffect() const = 0;

    string getTargetStr() const;

    virtual void addEffectsCumulative(vector<int>& cumulativeEffects) const = 0;

protected:
    string printIfNotZero(const string& name, int attr, const string& end) const;

    string target; // self/enemy

};
