#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "utils.h"
#include "deck.h"
#include "side_pile.h"


using namespace std;

struct resPair {
	int c1 = 0;
	int c2 = 0;
};

class Player {
protected:
	side_pile pile;
	deck pDeck;
	string name;
	int points = 0;
public:
	int totCards() { return pile.getlength() + pDeck.getSize(); }
	void stock_deck(int card) { pDeck.enqueue(card); }
	virtual resPair play(Player opp);
	virtual void create(int index);
	int peekDeck() { return pDeck.getSize(); }
	string getName() { return name; }
	
};
class User : public Player {
public:
	void create(int index) {
		name = input_s("Enter player " + to_string(index) + " name");
	}
	resPair play(Player opp) {
		printf("%s9   %s9", name.c_str(), opp.getName().c_str());
		cout << "Deck Pile   Deck Pile" << endl;
		printf( "%i4 %i4    %i4    ?", pDeck.getSize(), pile.getlength(), opp.peekDeck());
		int card;
		if (pDeck.getSize() > 0) {
			card = pDeck.dequeue();
		}
		else {
			card = pile.play();
		}

		cout << "Drawing" << flush;
		this_thread::sleep_for(chrono::milliseconds(50)); //dramatic suspense
		cout << "." << flush;
		this_thread::sleep_for(chrono::milliseconds(50));
		cout << "." << flush;
		this_thread::sleep_for(chrono::milliseconds(50));
		cout << "." << flush;
		this_thread::sleep_for(chrono::milliseconds(50));
		cout << card << endl << endl;

		bool c1e = pile.getlength() < 5 && pDeck.getSize() > 0;
		bool c2e = pile.getlength() > 0;

		if (c1e) cout << "1) Push card\n";
		else cout << "X Push card X\n";
		if (c2e) cout << "2) Pull card\n";
		else cout << "X Pull card X\n";
		cout << "3) Play Card" << endl;
		int choice;
		while (true) {
			choice = bounded_input<int>("?: ", "choice", 0b1111, 1, 3);
			if (choice == 1 && !c1e) {
				if (pDeck.getSize() <= 0) {
					cout << "!! Deck empty, cant push card !!" << endl;
				} else if (pile.getlength() >= 5) {
					cout << "!! Pile full, cant push card !!" << endl;
				}
				continue;
			}
			if (choice == 2 && !c2e) {
				cout << "!! Pile empty, cant pull card !!" << endl;
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
			return {new_card};
		}
		if (choice == 2) {
			cout << "Card pulled. ";
			int new_card = pile.play();
			cout << card << endl;
			return { card,new_card };
		}
		return { card };


	}
};

class Computer : public Player {
public:
	void create(int index) {
		name = "Com" + to_string(index);
	}
	resPair play(Player opp) {
		int card;
		if (pDeck.getSize() > 0) card = pDeck.dequeue();
		else card = pile.play();

		if (pDeck.getSize() == 0 && pile.getlength() > 0) {
			int new_card = pile.play();
			return { card,new_card };
		}
		if (card < 5 ) {
			if (pile.getlength() > 0) {
				int new_card = pile.play();
				return { card,new_card };
			}
			return { card };
		}
		if (card < 9) {
			if (pile.getlength() < 5 && pDeck.getSize()>0) {
				pile.add(card);
				int new_card = pDeck.dequeue();
				return { new_card };
			}
			return { card };
		}
		return { card };
	}
};

int main() {
	Player ply;
	Player com;
	int play_type;
	int num_rounds;
	int player_wins = 0;
	bool infinity = false;
	

	ply = User();
	ply.create(1);

	for (int i = 0; i < 52; i++) {
		ply.stock_deck(i % 13+1);
	}
	cout<<"would you like to play until empty(1) or for a number of rounds(2)?"<<endl;
	cin >> play_type;
	if(play_type==1){
		infinity = true;
		while ((ply.totCards()>0&&com.totCards()>0)) {
			resPair com_card;
			resPair ply_card;
			ply_card = ply.play(com);
			com_card = com.play(ply);
			cout << "the computer played a total card value of: " << com_card.c1 + com_card.c2;
			cout << " You played a card value of : " << ply_card.c1+ply_card.c2 << endl;
			if ((ply_card.c1+ply_card.c2) > (com_card.c1+com_card.c2)) {
				cout << "congrats you won!" << endl << "adding cards to your deck!" << endl;
				ply.stock_deck(ply_card.c1);
					if (ply_card.c2 != 0) {
						ply.stock_deck(ply_card.c2);
					
					}
					ply.stock_deck(com_card.c2);
					if (com_card.c2 != 0) {
						ply.stock_deck(com_card.c2);

					}
			
			}
			else {
				cout << "womp womp you lost :(" << endl << "adding cards to computer deck!" << endl;
				com.stock_deck(ply_card.c1);
				if (ply_card.c2 != 0) {
					ply.stock_deck(ply_card.c2);

				}
				com.stock_deck(com_card.c2);
				if (com_card.c2 != 0) {
					com.stock_deck(com_card.c2);

				}
			
			
			}
		
		}
	
	}
	else {
		while (true) {
			ply.play(com);
		}
	}
}