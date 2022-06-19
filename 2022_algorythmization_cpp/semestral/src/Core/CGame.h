/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#pragma once

#include <cstdlib>
#include <memory>
#include <map>
#include <string>

#include "CCommandPlayer.h"
#include "../Features/CPlayer.h"
#include "CCardParser.h"

using namespace std;
class CCommandPlayer;

/**
 * Holds "game" input loop for playing the game and handles
 * game mechanics - winning, number of cards in hand etc.
 * Each player's turn ends by throwing or playing a card.
 * Players can also exit the game, save the game etc.
 */
class CGame {
private:
    string charLocation = "examples/cardpacks/charpacks/char1.txt";
    vector<shared_ptr<CCardCharacter>> charactersPack;
    int totalActionCards;
    string actionLocation = "examples/cardpacks/actionpacks/action2.txt";
    vector<shared_ptr<CCardAction>> actionPack;

    shared_ptr<CPlayer> player1;
    shared_ptr<CPlayer> player2;
    map<string, CCommandPlayer> commands;
    bool running = false;
    string mode = "ai";
    const int GOLDWIN = 100;

public:
    explicit CGame(const CInterface & iface);
    void fillPlayerIfNull(shared_ptr<CPlayer> & player, const string  & type);
    void setRunning(bool isRunning);
    void setPlayer(int id, const shared_ptr<CPlayer> & player);
    shared_ptr<CPlayer> getIdlePlayer();
    shared_ptr<CCardAction> randomActionCard();
    void setMode(string modeName);
    void win(const string& winMessage);
    bool winHandler();
    void play();
    void init();
    shared_ptr<CPlayer> currentPlayer;
    static const int CARDCAP = 6;
    const string pathActionPack = "examples/cardpacks/actionpacks/";
    const string pathCharPack = "examples/cardpacks/charpacks/";
    const string pathSave = "examples/gamesaves/";
    CInterface mainInterface;

    void initPlayer(const shared_ptr<CPlayer> &player, int number);

    void printCurrentPlayerCards() const;

    void printPlayerChange() const;

    void printHelps();

    string getPlayerActionCardIdx(int pos, const shared_ptr<CPlayer> &player) const;

    string getCharInfo(const shared_ptr<CPlayer> &player) const;

    string getMode() const;

    string getCharLocation() const;

    string getActionLocation() const;

    void setCharCardFile(const string& filename);
    void setActionCardFile(const string& filename);

    shared_ptr<CCardAction> getCardFromPack(int idx);

    void parsePacks(CCardParser &c);
};
