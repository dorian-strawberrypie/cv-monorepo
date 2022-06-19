/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#pragma once

#include <string>

class CCommand {
protected:
    explicit CCommand(std::string help);
    std::string help;
public:
    std::string getHelp() const;
};
