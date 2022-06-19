/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#pragma once

#include <utility>
#include <string>
#include "CInterface.h"
#include "CGame.h"
#include "CCommandApp.h"
#include "commands.h"

using namespace std;
/**
 * @class CApplication
 * Holds "menu" input loop for configuring game.
 * Enables starting game, exiting the app, choosing game mode,
 *      showing config, loading game from save
 */
class CApplication {
public:

    explicit CApplication(const CInterface & iface);
    void run();
    void setRunning(bool isRunning);

    bool running = true;
    CInterface mainIface;

    string strConfig() const;
    void printHelps();

private:
    CGame game;
    map<string, CCommandApp> commands;

};
