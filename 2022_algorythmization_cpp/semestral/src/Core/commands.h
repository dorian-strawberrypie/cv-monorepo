/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#pragma once

#include "CCommandApp.h"
#include "CCommandPlayer.h"

/**
 * @file commands.h
 * Contains all commands used in CGame and CApplication.
 * If CCommandGame returns false, won't move to next player.
 */

CCommandPlayer saveGame();

CCommandPlayer helpPl();

CCommandApp helpApp();

CCommandApp exitApp();

CCommandApp setPack();

CCommandApp startGame();

CCommandApp loadGame();

CCommandApp chooseMode();

CCommandApp showConfig();

CCommandPlayer quitGame();

CCommandPlayer playCard();

CCommandPlayer throwCard();
