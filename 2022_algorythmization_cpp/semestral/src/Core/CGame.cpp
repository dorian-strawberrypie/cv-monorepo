/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#include "CGame.h"

#include <utility>
#include "commands.h"
#include "../Features/CPlayerHuman.h"
#include "../Features/CPlayerAI.h"
#include "CCardParser.h"

CGame::CGame(const CInterface & iface) : mainInterface(iface) {}


/**
 * Tries to load card packs, throws exception if unable, emplaces commands for
 *      CGame loop, allocates players if not already and initializes them.
 */
void CGame::init() {
    srand(time(nullptr));
    try {
        CCardParser c;
        parsePacks(c);
        if (actionPack.size() < CARDCAP || charactersPack.empty())
            throw runtime_error("not enough cards in packs");
    }
    catch (const exception & e) {
        mainInterface.print(e.what());
        mainInterface.print("exiting, repair card packs and try again.");
        return;
    }
    running = true;
    commands.emplace("exit", quitGame());
    commands.emplace("throw", throwCard());
    commands.emplace("play", playCard());
    commands.emplace("save", saveGame());
    commands.emplace("help", helpPl());

    if (mode == "versus") {
        fillPlayerIfNull(player1, "human");
        fillPlayerIfNull(player2, "human");
    }
    else {
        fillPlayerIfNull(player1, "human");
        fillPlayerIfNull(player2, "ai");
    }
    initPlayer(player1, 1);
    initPlayer(player2, 2);
    currentPlayer = currentPlayer ? currentPlayer : player1;

    mainInterface.print("========\nGAME START\n========");
}

void CGame::parsePacks(CCardParser &c) {
    if (actionPack.empty())
        actionPack = c.parse(actionLocation, totalActionCards);
    if (charactersPack.empty())
        charactersPack = c.parse(charLocation);
}

/**
 * Sets player number, allocates CCardCharacter if not already,
 *      same with playing cards.
 * @param player pointer to be initialized
 * @param number player number
 */
void CGame::initPlayer(const shared_ptr<CPlayer>& player, int number) {
    player->playerNumber = number;
    if (!player->getCharacter()) {
        auto randChar = charactersPack[rand() % charactersPack.size()];
        auto newChar = make_shared<CCardCharacter>(*randChar);
        player->setCharacter(newChar);
    }
    for (int i = 0; i < CARDCAP; i++) {
        if (player->getCard(i)) continue;
        player->reobtainCard(i, randomActionCard());
    }
}

/**
 * Holds game input loop.
 * Calls game and player initialization,
 * processes input in while loop,
 * calls printing, handles game mechanic
 */
void CGame::play() {
    init();
    if (currentPlayer)
        printPlayerChange();
    while (running) { // while hasWon either
        string cmdName = currentPlayer->turn();
        auto it = commands.find(cmdName);
        if (it == commands.end()) {
           currentPlayer->iface.print("wrong input, look zadani.txt for commands or try 'help'");
            mainInterface.print("PLAYER " + to_string(currentPlayer->playerNumber) + ":");
           currentPlayer->iface.clearIn();
           continue;
        }

        if (!it->second.execute(*this, currentPlayer->iface)) {
            continue;
        }
        winHandler();
        if (!running) break;
        currentPlayer->getCharacter()->updateChar();
        currentPlayer = getIdlePlayer();
        currentPlayer->getCharacter()->normalizeAttrs();
        printPlayerChange();
    }
}
void CGame::setRunning(bool isRunning) {
    running = isRunning;
}

void CGame::setMode(string modeName) {
    this->mode = std::move(modeName);
}

void CGame::setPlayer(int id, const shared_ptr<CPlayer> & player) {
    if (id == 1) player1 = player;
    else if (id == 2) player2 = player;
}

shared_ptr<CPlayer> CGame::getIdlePlayer() {
    return player1 == currentPlayer ? player2 : player1;
}

void CGame::fillPlayerIfNull(shared_ptr<CPlayer> & player, const string  & type) {
    if (player != nullptr)
        return;
    if (type == "human") player = make_shared<CPlayerHuman>(mainInterface);
    else player = make_shared<CPlayerAI>(mainInterface.getOut());
}

void CGame::win(const string& winMessage) {
    running = false;
    mainInterface.print("Player " + to_string(currentPlayer->playerNumber) + " won by " + winMessage);
}

/**
 * Holds definitions of players winning.
 * @return
 */
bool CGame::winHandler() {
    if (currentPlayer->getCharacter()->getGold() >= GOLDWIN) {
        win("having over 100g!");
        return true;
    }
    if (getIdlePlayer()->getCharacter()->getHealth() <= 0) {
        win("killing the opponent!");
        return true;
    }
    return false;
}

shared_ptr<CCardAction> CGame::randomActionCard() {
    auto randomCard =  actionPack[rand() % actionPack.size()];
    return randomCard;
}


void CGame::printCurrentPlayerCards() const {
    for (int i = 0; i < CARDCAP; i++) {
        int width = 25;
        currentPlayer->iface.printNumberPretty(i + 1, width);
        currentPlayer->iface.print(currentPlayer->getCard(i)->stringCard());
        string delim = "+";
        for (int j = 0; j < width - 2; j++)
            delim += "-";
        currentPlayer->iface.print(delim + "+\n");
    }
}

void CGame::printPlayerChange() const {
    mainInterface.print("\nPLAYER " + to_string(currentPlayer->playerNumber) + ":");
    mainInterface.print(currentPlayer->getCharacter()->stringCard());
    mainInterface.print("your cards:\n");
    printCurrentPlayerCards();
}


string CGame::getCharLocation() const {
    return charLocation;
}

string CGame::getActionLocation() const {
    return actionLocation;
}

string CGame::getMode() const {
    return mode;
}

string CGame::getCharInfo(const shared_ptr<CPlayer>& player) const {
    auto character = player->getCharacter();
    ostringstream oss;
    oss << character->getName() << "\n" <<
            character->getMaxHealth() << "\n" <<
            character->getHealth() << "\n" <<
            character->getStamina() << "\n" <<
            character->getStaminaGain() << "\n" <<
            character->getMana() << "\n" <<
            character->getManaGain() << "\n" <<
            character->getGold() << "\n" <<
            character->getGoldGain() << "\n" <<
            character->getShield();
    return oss.str();
}

string CGame::getPlayerActionCardIdx(int pos, const shared_ptr<CPlayer>& player) const {
    auto iter = std::find(actionPack.begin(), actionPack.end(), player->getCard(pos));
    size_t idx = iter - actionPack.begin();
    return to_string(idx);
}

void CGame::setCharCardFile(const string& filename) {
    charLocation = pathCharPack + filename;
}

void CGame::setActionCardFile(const string& filename) {
    actionLocation =  pathActionPack + filename;
}

shared_ptr<CCardAction> CGame::getCardFromPack(int idx) {
    return actionPack.at(idx);
}

void CGame::printHelps() {
    for (const auto & a : commands) {
        mainInterface.print(a.second.getHelp());
    }
}
