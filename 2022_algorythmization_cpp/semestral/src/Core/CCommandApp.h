/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 20.05.2022
 */

#pragma once

#include <utility>
#include <cstdio>
#include <functional>
#include "CInterface.h"
#include "CCommand.h"

class CGame;
class CApplication;
/**
 * Each instance contains function to be executed in CApplication.
 */
class CCommandApp : public CCommand {
public:
    CCommandApp(std::string help, function<void (CGame & game, CApplication & app, const CInterface & iface)>  func);
    void execute(CGame & game, CApplication & app, const CInterface & iface);
private:
    function<void (CGame & game, CApplication & app, const CInterface & iface)> func;
};
