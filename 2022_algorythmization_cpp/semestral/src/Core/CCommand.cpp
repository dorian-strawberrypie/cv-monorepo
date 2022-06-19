/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#include "CCommand.h"

using namespace std;

CCommand::CCommand(std::string help) : help(help) {}
std::string CCommand::getHelp() const {
    return help;
}
