/**
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 20.05.2022
 */
#include "CCommandApp.h"

#include <utility>

void CCommandApp::execute(CGame & game, CApplication & app, const CInterface & iface) {
    func(game, app, iface);
}

CCommandApp::CCommandApp(string help, std::function<void (CGame & game, CApplication & app, const CInterface & iface)>  func)
:CCommand(std::move(help)), func(std::move(func)){

}
