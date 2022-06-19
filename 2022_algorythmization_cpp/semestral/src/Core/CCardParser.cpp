#include <vector>

#include "CCardParser.h"

/**
 * Reads playing action cards from file. Reads card count, calls card ctor where
 *  rest of params will be loaded. Then it reads 0..* CEffect instances - card effects
 * @param file
 * @param cardTypeCount
 * @return vector of smart pointers to CCardAction instances, loaded from a file.
 */
std::vector<std::shared_ptr<CCardAction>> CCardParser::parse(const std::string& file, int & cardTypeCount) {
    Reader r(file);
    std::vector<std::shared_ptr<CCardAction>> ret;

    int count;
    while (r.try_parse("count", count)) {
        cardTypeCount ++;
        auto a = make_shared<CCardAction>(r);
        for (int i = 0; i < count; i++)
            ret.push_back(a);

        std::string effect;
        while (r.try_parse("effect", effect)) {
            if (!effect_types.count(effect)) throw Reader::Error("wrong effect name");
            a->addEffect(effect_types.at(effect)(r));
        }
    }

    return ret;
}

/**
 * Reads character cards from file.
 * @param file
 * @return vector of smart pointers to CCardCharacter
 */
vector<shared_ptr<CCardCharacter>> CCardParser::parse(const std::string& file) {
    Reader r(file);
    vector<shared_ptr<CCardCharacter>> ret;

    string name;
    while (r.try_parse("name", name)) {
        ret.push_back(make_shared<CCardCharacter>(name, r));
    }

    return ret;
}

