/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 20.05.2022
 */

#pragma once

#include <functional>
#include "CCommand.h"
#include "CGame.h"
#include "CInterface.h"

class CGame;
/**
 * each instance contains function to be executed in CGame loop by execute().
 */
class CCommandPlayer : public CCommand {
public:
    CCommandPlayer(std::string help, function<bool (CGame & game, const CInterface & iface)>  func);
    bool execute(CGame & game, const CInterface & iface);
private:
    function<bool (CGame & game, const CInterface & iface)> func;
};
