/**
 * @file CApplication.cpp
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#include "CApplication.h"

/**
 * Emplaces CCommandApp cmds to be used in CApplication input loop
 *
 * @param iface from main.cpp, to be used as interface in
 *      CPlayerHuman, CGame, output for CPlayerAI
 */
CApplication::CApplication(const CInterface & iface) : mainIface(iface), game(iface) {
    commands.emplace("exit", exitApp());
    commands.emplace("start", startGame());
    commands.emplace("mode", chooseMode());
    commands.emplace("setpack", setPack());
    commands.emplace("load", loadGame());
    commands.emplace("config", showConfig());
    commands.emplace("help", helpApp());

    iface.print("=====\nMENU\n=====");
    iface.print(strConfig());
    run();
}

/**
 * Contains Menu input loop, running until "exit" command executed.
 * Waits for user input, finds the command in commands and executes it.
 */
void CApplication::run() {
    while (running) {
        string cmdName = mainIface.processInput();
        auto it = commands.find(cmdName);
        if (it == commands.end()) {
            mainIface.print("wrong input, look zadani.txt for commands or try 'help'");
            mainIface.clearIn();
            continue;
        }
        it->second.execute(game, *this, mainIface);
    }
}

void CApplication::setRunning(bool isRunning) {
    running = isRunning;
}

string CApplication::strConfig() const {
    string ret;
    ret += "CURRENT CONFIGURATION:\n";
    ret += "mode: " + game.getMode() + '\n';
    ret += "action card pack: " + game.getActionLocation() + '\n';
    ret += "character card pack: " + game.getCharLocation() + '\n';
    return ret;
}

void CApplication::printHelps() {
    for (const auto & a : commands) {
        mainIface.print(a.second.getHelp());
    }
}
