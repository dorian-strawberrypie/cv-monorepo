/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 04.05.2022
 */

#include "CPlayer.h"

#include <utility>

CPlayer::CPlayer(const CInterface & iface) : iface(iface) {}

/**
 * Re-obtain one card in hand.
 * @param cardNum
 * @param newCard
 */
void CPlayer::reobtainCard(int cardNum, shared_ptr<CCardAction> newCard) {
    auto pos = cards.begin() + cardNum;
    if (pos == cards.end())
        cards.emplace(pos, std::move(newCard));
    else
        cards[cardNum] = newCard;
}

shared_ptr<CCardAction> CPlayer::getCard(int cardNum) const {
    if (cards.size() <= cardNum) return nullptr;
    return cards[cardNum];
}

shared_ptr<CCardCharacter> CPlayer::getCharacter() const {
    return character;
}

void CPlayer::setCharacter(const shared_ptr<CCardCharacter> & c) {
    character = c;
}
