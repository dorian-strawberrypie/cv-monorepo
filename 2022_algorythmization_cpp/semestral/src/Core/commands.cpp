/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#include "commands.h"
#include "CApplication.h"
#include "../Features/CPlayerAI.h"
#include "../Features/CPlayerHuman.h"

CCommandApp exitApp() {
    return CCommandApp {
        "exit - exit the app",
        [](CGame & game, CApplication & app, const CInterface & iface) {app.setRunning(false);}
    };
}

CCommandApp startGame() {
    return CCommandApp {
        "start - start the game",
        [](CGame & game, CApplication & app, const CInterface & iface) {
            game.play();
            app.setRunning(false);
        }
    };
}

/**
 * loads relevant CGame info from semestral/examples/gamesaves/filename
 * throws an exception if  CGame::CARDCAP was modified or if ifs failed
 * @return true if file could be opened, false otherwise
 */
CCommandApp loadGame() {
    return CCommandApp {
            "load <filename> - saves file into /examples/gamesaves/ under filename",
            [](CGame & game, CApplication & app, const CInterface & iface) {
                string filename = iface.processInput();

                ifstream ifs(game.pathSave + filename);
                if (ifs.fail()) {
                    iface.wrongArg("load");
                    return false;
                }
                try {
                    string input;
                    ifs >> input; game.setCharCardFile(input);
                    ifs >> input; game.setActionCardFile(input);
                    ifs >> input; game.setMode(input);

                    shared_ptr<CPlayer> player1 = make_shared<CPlayerHuman>(iface), player2;
                    game.setPlayer(1, player1);
                    if (input == "versus")
                        player2 = make_shared<CPlayerHuman>(iface);
                    else if (input == "ai")
                        player2 = make_shared<CPlayerAI>(iface.getOut());
                    else
                        throw runtime_error("savefile corrupted (mode)");

                    game.setPlayer(2, player2);

                    ifs >> input; game.currentPlayer = stoi(input) == 1 ? player1 : player2;
                    auto idlePlayer = game.getIdlePlayer();

                    CCardParser c;
                    game.parsePacks(c);

                    int mH, h, s, sG, m, mG, g, gG, shield;
                    ifs >> input >> mH >> h >> s >> sG >> m >> mG >> g >> gG >> shield;
                    game.currentPlayer->setCharacter(make_shared<CCardCharacter>(input, mH, h, s, sG, m, mG, g, gG, shield));
                    ifs >> input >> mH >> h >> s >> sG >> m >> mG >> g >> gG >> shield;
                    idlePlayer->setCharacter(make_shared<CCardCharacter>(input, mH, h, s, sG, m, mG, g, gG, shield));

                    int oldCARDCAP;
                    ifs >> oldCARDCAP;
                    if (oldCARDCAP != CGame::CARDCAP) throw runtime_error("savefile corrupted (CARDCAP changed)");
                    int idx;
                    for (int i = 0; i < CGame::CARDCAP; i++) {
                        ifs >> idx;
                        game.currentPlayer->reobtainCard(i, game.getCardFromPack(idx));
                    }
                    for (int i = 0; i < CGame::CARDCAP; i++) {
                        ifs >> idx;
                        idlePlayer->reobtainCard(i, game.getCardFromPack(idx));
                    }
                    if (ifs.fail())
                        throw runtime_error("saveFile corrupted");
                }
                catch (...) {
                    ifs.close();
                    iface.print("unable to load from save");
                    return false;
                }
                ifs.close();
                game.play();
                app.setRunning(false);
                return true;
            }
    };
}

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

/**
 * saves relevant CGame info to semestral/examples/gamesaves/filename
 * @return false, so that the player who executed "save" cmd continues turn
 */
CCommandPlayer saveGame() {
    return CCommandPlayer {
            "save <filename> - saves game as examples/gamesaves/filename",
            [](CGame & game, const CInterface & iface) {
                string filename = iface.processInput();


                ofstream ofs(game.pathSave + filename, ios::trunc);
                if (ofs.fail()) {
                    iface.wrongArg("save");
                    return false;
                }
                string charPackName = split(game.getCharLocation(), '/').back();
                string actionPackName = split(game.getActionLocation(), '/').back();

                auto idlePlayer = game.getIdlePlayer();
                ofs <<
                        charPackName << "\n" <<
                        actionPackName << "\n" <<
                        game.getMode() << "\n" <<
                        game.currentPlayer->playerNumber << "\n" <<
                        game.getCharInfo(game.currentPlayer) << "\n" <<
                        game.getCharInfo(idlePlayer) << "\n" <<
                        to_string(CGame::CARDCAP) << "\n";
                for (int i = 0; i < CGame::CARDCAP; i++)
                    ofs << game.getPlayerActionCardIdx(i, game.currentPlayer) << "\n";
                for (int i = 0; i < CGame::CARDCAP; i++)
                    ofs << game.getPlayerActionCardIdx(i, idlePlayer) << endl;

                ofs.close();
                return false;
            }
    };
}


/**
 * Enables to choose between "versus" - two player mode
 *         and "ai" - vs. computer mode
 * @return true if type is "ai" or "versus"
 */
CCommandApp chooseMode() {
    return CCommandApp{
            "mode <type> - type: 'versus'/'ai', sets whether you play 2p or with computer",
            [](CGame &game, CApplication &app, const CInterface &iface) {
                shared_ptr<CPlayer> player1, player2;
                string type;
                type = iface.processInput();
                if (type != "ai" && type != "versus") {
                    iface.wrongArg("mode");
                    return;
                }
                game.setMode(type);

                return;
            }
    };
}

CCommandApp showConfig() {
    return CCommandApp{
            "config - shows how is the game configured",
            [](CGame &game, CApplication &app, const CInterface &iface) {
                iface.print(app.strConfig());
            }
    };
}

/**
 * Sets card packs file locations to be used in game.
 * @return
 */
CCommandApp setPack() {
    return CCommandApp{
            "setpack <type> <filename> - type: 'action'/'character', filename must\n"
            "be in corresponding folder of /examples/cardpacks/",
            [](CGame &game, CApplication &app, const CInterface &iface) {
                string type, filename;
                type = iface.processInput();
                filename = iface.processInput();
                if (type != "action" && type != "character") {
                    iface.wrongArg("setpack");
                    return;
                }
                if (type == "action")
                    game.setActionCardFile(filename);
                else
                    game.setCharCardFile(filename);

                return;
            }
    };
}

CCommandPlayer quitGame() {
    return CCommandPlayer {
            "exit - exit the app",
            [](CGame & game, const CInterface & iface) {game.setRunning(false); return true;}
    };
}

/**
 * Plays card of current player choice.
 * Gets cardNumebr parameter from @param iface of current player,
 * gets enemy player,
 * finds whether current player has enough mana, stamina and gold to play the card,
 * calls playedCard->action(), to apply the card effects,
 * gives current player a new random card.
 * @return false if wrong input, true otherwise
 */
CCommandPlayer playCard() {
    return CCommandPlayer {
            "play <number> - plays a card of number, must be within CARDCAP",
        [](CGame & game, const CInterface & iface) {
            int cardNumber;
            if (!iface.processIntArg(cardNumber) || cardNumber < 1 || cardNumber > CGame::CARDCAP) {
                iface.wrongArg("play");
                return false;
            }

            auto playedCard = game.currentPlayer->getCard(cardNumber - 1);
            shared_ptr<CPlayer> enemy = game.getIdlePlayer();
            if (!playedCard->action(game.currentPlayer, enemy)) {
                iface.print("INSUFFICIENT MANA/STAMINA/GOLD");
                return false;
            }
            iface.print("playing card number " + to_string(cardNumber));

            game.currentPlayer->reobtainCard(cardNumber - 1, game.randomActionCard());

            return true;
        }
    };
}

/**
 * calls reobtainCard() to replace the card that the player wants to throw away
 * @return true if valid input, false otherwise
 */
CCommandPlayer throwCard() {
    return CCommandPlayer {
            "throw <number> - throws away a card of number, must be within CARDCAP",
            [](CGame & game, const CInterface & iface) {
                int cardNumber;
                if (!iface.processIntArg(cardNumber) || cardNumber < 1 || cardNumber > CGame::CARDCAP) {
                    iface.wrongArg("throw");
                    return false;
                }
                string message = "throwing away card " + to_string(cardNumber);
                iface.print(message);

                game.currentPlayer->reobtainCard(cardNumber - 1, game.randomActionCard());

                return true;
            }
    };
}

CCommandPlayer helpPl() {
    return CCommandPlayer {
            "help - shows all available commands",
            [](CGame & game, const CInterface & iface) {
                game.printHelps();

                return false;
            }
    };
}

CCommandApp helpApp() {
    return CCommandApp{
            "help - shows all available commands",
            [](CGame &game, CApplication &app, const CInterface &iface) {
                app.printHelps();
                return;
            }
    };
}
