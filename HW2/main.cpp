#include <iostream>
#include "Game.h"
using namespace std;

int main() {
    int moneyCount = 0;
    cout << "Enter how much money you would like to start with: $";
    cin >> moneyCount;

    while (true){
        int wagerModification = 0;
        cout << "Would you like to modify your wager?\n[1] Double\n[2] Halve\n[3] Keep current wager";
        cin >> wagerModification;

        while (wagerModification < 1 || wagerModification > 3) {
            if (wagerModification == 2){
                //house gets 1 chance
            } else if (wagerModification == 1 || wagerModification == 3) {
                //house gets 2 chances
            } else {
                cout << "Invalid response, enter only an integer. Would you like to modify your wager?\n[1] Double\n[2] Halve\n[3] Keep current wager";
                cin >> wagerModification;
            }
        }

    }
}

Wheel playerWheel;
playerWheel.set_wheel_size(); //enter wherever we get that

Wheel houseWheel;
houseWheel.set_wheel_size(); //enter wherever we get 
