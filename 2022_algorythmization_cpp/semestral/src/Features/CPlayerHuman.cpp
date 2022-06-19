/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#include "CPlayerHuman.h"

CPlayerHuman::CPlayerHuman(const CInterface & iface) : CPlayer(iface) {}

string CPlayerHuman::turn() {
    return iface.processInput();
}

