/**
 * @file
 * @author Jakub Dorian Charbulák <charbjak@fit.cvut.cz>
 * @date 05.05.2022
 */

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include "CApplication.h"
#include "CInterface.h"

bool launch(istream & in, ostream & out) {
    CInterface iface = CInterface(in, out);
    CApplication app(iface);
    app.run();
    return true;
}

void test();

/**
 * starts the game or runs tests
 * @return
 */
int main() {
    const bool testMode = false;
    std::cout << "Welcome to Duel Heroes!" << std::endl;
    if (testMode)
        test();
    else
        launch(std::cin, std::cout);
    return 0;
}

void test() {
    istringstream iss;
    ostringstream oss;

//     test commands
    iss.clear();
    iss.str("mode versus "
            "start "
            "throw 1 "
            "    \n\nplay 3 "
            "throw 7 "
            "  play 1 "
            "  \n\nplay 8 "
            "exit");
    assert(launch(iss, oss));
    cout << oss.str();
    oss.str("");

    cout << "--------------------------------------" << endl;

    // game logic, wrong input
    iss.clear();
    iss.str("start\nplay 8 play 1 play 8 asdf throw 2 exit ");
    assert(launch(iss, oss));
    cout << oss.str();
    oss.str("");

    cout << "--------------------------------------" << endl;

    //  input checking
    iss.clear();
    iss.str("xxxyyy\nstart\nxxxyyy\nquit\nexit");
    assert(launch(iss,oss));
    cout << oss.str();
    oss.str("");

    cout << "--------------------------------------" << endl;

    //  logic
    iss.clear();
    iss.str("mode ai\nmode versus exit");
    assert(launch(iss,oss));
    cout << oss.str();
    oss.str("");

    cout << "--------------------------------------" << endl;

    // choosing pack
    iss.clear();
    iss.str("mode ai\nsetpack character char2.txt\nsetpack action action2.txt\n start\n play 2\nexit");
    assert(launch(iss, oss));
    cout << oss.str();
    oss.str("");

    cout << "--------------------------------------" << endl;

    // SHOULD BE VALID pack
    iss.clear();
    iss.str("mode ai\nsetpack character corrupt1.txt\n start\n play 2\nexit");
    assert(launch(iss, oss));
    cout << oss.str();
    oss.str("");

    cout << "--------------------------------------" << endl;

    // invalid pack
    iss.clear();
    iss.str("mode versus \n setpack action corrupt1.txt\nexit");
    assert(launch(iss, oss));
    cout << oss.str();
    oss.str("");

    cout << "--------------------------------------" << endl;

    // invalid pack
    iss.clear();
    iss.str("mode versus \n setpack action corrupt2.txt\nexit");
    assert(launch(iss, oss));
    cout << oss.str();
    oss.str("");

    cout << "--------------------------------------" << endl;

    // invalid pack
    iss.clear();
    iss.str("mode versus \n setpack action corrupt3.txt\nexit");
    assert(launch(iss, oss));
    cout << oss.str();
    oss.str("");

    cout << "--------------------------------------" << endl;

    // loading a save
    iss.clear();
    iss.str("mode ai\nload sv1 \n play 2 \n throw 3\n exit");
    assert(launch(iss, oss));
    cout << oss.str();
    oss.str("");

    cout << "--------------------------------------" << endl;

    // invalid save
    iss.clear();
    iss.str("\nload asdf\n play 1\n exit\n");
    assert(launch(iss, oss));
    cout << oss.str();
    oss.str("");

    cout << "--------------------------------------" << endl;

}
