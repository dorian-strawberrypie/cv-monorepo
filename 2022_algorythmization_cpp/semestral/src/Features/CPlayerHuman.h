/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 04.05.2022
 */

#pragma once

#include "../Core/CInterface.h"
#include "CPlayer.h"
/**
 * Turn is made by user command line input.
 */
class CPlayerHuman : public CPlayer {
public:
    explicit CPlayerHuman(const CInterface & iface);
    string turn() override;
private:
};
