#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "utils.h"
#include "deck.h"
#include "side_pile.h"


using namespace std;

class Player {
protected:
	side_pile pile;
	deck pDeck;
	string name;
	int points = 0;
public:
	void stock_deck(int card) { pDeck.enqueue(card); }
	virtual int play(Player opp);
	virtual void create(int index);
	virtual int oppPeekDeck();
	string getName() { return name; }
	
};

class User : public Player {
public:
	int oppPeekDeck() {
		return pDeck.getSize();
	}
	void create(int index) {
		name = input_s("Enter player " + to_string(index) + " name");
	}
	int play(Player opp) {
		printf("%s9   %s9", name.c_str(), opp.getName().c_str());
		cout << "Deck Pile   Deck Pile" << endl;
		printf( "%i4 %i4    %i4    ?", pDeck.getSize(), pile.getlength(), opp.oppPeekDeck());
		int card = pDeck.dequeue();

		cout << "Drawing" << flush;
		this_thread::sleep_for(chrono::milliseconds(50)); //dramatic suspense
		cout << "." << flush;
		this_thread::sleep_for(chrono::milliseconds(50));
		cout << "." << flush;
		this_thread::sleep_for(chrono::milliseconds(50));
		cout << "." << flush;
		this_thread::sleep_for(chrono::milliseconds(50));
		cout << card << endl << endl;

		if (pile.getlength() < 5) cout << "1) Push card\n";
		else cout << "X Push card X\n";
		if (pile.getlength() > 0) cout << "2) Pull card\n";
		else cout << "X Pull card X\n";
		cout << "3) Play Card" << endl;
		int choice;
		while (true) {
			choice = bounded_input<int>("?: ", "choice", 0b1111, 1, 3);
			if (choice == 1 && pile.getlength() >= 5) {
				cout << "!! Deck full, cant push card !!" << endl;
				continue;
			}
			if (choice == 2 && pile.getlength() <= 0) {
				cout << "!! Deck empty, cant pull card !!" << endl;
				continue;
			}
		}
		if (choice == 1) {
			pile.add(card);
			int new_card = pDeck.dequeue();

			cout << "Card pushed. Drawing new card" << endl;
			this_thread::sleep_for(chrono::milliseconds(50)); //dramatic suspense
			cout << "." << flush;
			this_thread::sleep_for(chrono::milliseconds(50));
			cout << "." << flush;
			this_thread::sleep_for(chrono::milliseconds(50));
			cout << "." << flush;
			this_thread::sleep_for(chrono::milliseconds(50));
			cout << card << endl;
			
			cout << "Pulled a " << new_card << endl;
			return card;
		}
		if (choice == 2) {
			cout << "Card pulled. ";
			int new_card = pile.play(card);
			cout << card << endl;
			return card + new_card;
		}
		return card;


	}
};

class Computer : public Player {
public:
	void create(int index) {
		name = "Com" + to_string(index);
	}
	int play(Player opp) {
		int card = pDeck.dequeue();
		if (card < 5 && pile.getlength() > 0) {

		}
	}
};

int main() {
	Player ply;
	Player com;

	ply = User();
	ply.create(1);

	for (int i = 0; i < 52; i++) {
		ply.stock_deck(i % 13+1);
	}

	while (true) {
		ply.play(com);
	}
}