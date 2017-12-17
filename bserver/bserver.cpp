#include "../stdafx.h"
#include "setup.h"
#include "sign.h"

int main() {
    using namespace std;
    string command;
    for ( ; ; ) {
        cout << "Wprowadź polecenie (`setup`, `sign` albo `exit`)" << endl;
        cin >> command;
        if (command == "exit") break;
        else if (command == "setup") setup();
        else if (command == "sign") sign();
    }
    return 0;
}
