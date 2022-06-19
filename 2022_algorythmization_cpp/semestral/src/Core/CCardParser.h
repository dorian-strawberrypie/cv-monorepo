#include <memory>
#include <string>
#include <map>

#include "../Features/CCard.h"
#include "../Features/CCardCharacter.h"
#include "../Features/CCardAction.h"
#include "../Features/CEffectBuff.h"
#include "../Features/CEffectAttack.h"
#include "Reader.h"

#pragma once

/**
 * Contains definitions for parsing CCardCharacter and CCardAction, putting them
 * into a vector.
 */
class CCardParser {
public:
    using CreateItem = std::unique_ptr<CEffect>(*)(Reader&);
    /**
     * used in CCardReader::parse for CCardAction. Based on their member type (str)
     * determines whether card effect is CEffectAttack or CEffectBuff. Map then
     * contains definition for creating the instance.
     */
    const std::map<std::string, CreateItem> effect_types = {
            { CEffectAttack::type, CEffect::create<CEffectAttack> },
            { CEffectBuff::type, CEffect::create<CEffectBuff> },
    };


    std::vector<std::shared_ptr<CCardAction>> parse(const std::string& file, int & cardTypeCount);
    std::vector<shared_ptr<CCardCharacter>> parse(const std::string& file);
};

