/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 20.05.2022
 */

#include "CCommandPlayer.h"

#include <utility>

bool CCommandPlayer::execute(CGame & game, const CInterface & iface) {
    return func(game, iface);
}

CCommandPlayer::CCommandPlayer(string help, std::function<bool (CGame & game, const CInterface & iface)>  func)
        :CCommand(std::move(help)), func(std::move(func)){

}
