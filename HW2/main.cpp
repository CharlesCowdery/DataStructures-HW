#include <iostream>
#include "Game.h"
using namespace std;

int main() {
    float moneyCount = 0;
    int wheelSize = 0;
    cout << "Enter how much money you would like to start with: $";
    cin >> moneyCount;
    while (true) {
        cout << "choose the size of wheel youd like to play with [6-20]: " << flush;
        cin >> wheelSize;
        if (wheelSize < 6 || wheelSize > 20) cout << "Out of range." << endl;
        else break;
    }

    Wheel playerWheel;
    playerWheel.set_wheel_size(wheelSize);

    Wheel houseWheel;
    houseWheel.set_wheel_size(wheelSize);

    while (true){
        int wagerModification = 0;
        

        while (wagerModification < 1 || wagerModification > 3) {
            cout << "Would you like to modify your wager?\n[1] Double\n[2] Halve\n[3] Keep current wager";
            cin >> wagerModification;
            if (wagerModification >= 1 && wagerModification <= 3) {
                break;
            }
            else {
                cout << "Invalid response, enter only an integer between 1 and 3 (inclusive)." << endl;
            }
        }
        if (wagerModification == 2) {
            //house gets 1 chance
        }
        else if (wagerModification == 1 || wagerModification == 3) {
            //house gets 2 chances
        }

    }
    
}