#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "utils.h"
#include "deck.h"
#include "side_pile.h"


using namespace std;
//structure to return what cards are played
struct resPair {
	int c1 = 0;
	int c2 = 0;
	int total() { return c1 + c2; }
};
//overall base class for players
class Player {
protected:
	//class variables for players that are private
	side_pile pile = side_pile();
	deck pDeck = deck();
	string name = "";
public:
	//public functions and variables
	int points = 0;
	int totCards() { return pile.getlength() + pDeck.getSize(); }
	void stock_deck(int card) { pDeck.enqueue(card); }
	virtual resPair play(Player& opp) { return resPair(); }
	virtual void create(int index) {}
	int peekDeck() { return pDeck.getSize(); }
	string getName() { return name; }

};
//derived clas of player called user
class User : public Player {
public:
	//public functions for users
	void create(int index) {
		name = input_s("Enter player " + to_string(index) + " name: ");
	}
	//play function for player
	resPair play(Player& opp) {
		string opp_name = opp.getName(); //print stats
		printf("%9s   %-9s\n", name.c_str(), opp_name.c_str());
		cout << "Deck Pile   Deck Pile" << endl;
		printf("%4i %4i   %4i    ?\n", pDeck.getSize(), pile.getlength(), opp.peekDeck());
		cout << endl;

		int card;
		if (pDeck.getSize() > 0) {
			card = pDeck.dequeue();
		}
		else {
			card = pile.play();
		}
		//code to print out the card drawn and give the user choices of what to do
		cout << "Drawing" << flush;
		this_thread::sleep_for(chrono::milliseconds(100)); //dramatic suspense
		cout << "." << flush;
		this_thread::sleep_for(chrono::milliseconds(100));
		cout << "." << flush;
		this_thread::sleep_for(chrono::milliseconds(100));
		cout << "." << flush;
		this_thread::sleep_for(chrono::milliseconds(100));
		cout << card << endl << endl;

		bool c1e = pile.getlength() < 5 && pDeck.getSize() > 0; //precomputes branch conditions to make logic more readable
		bool c2e = pile.getlength() > 0;

		if (c1e) cout << "1) Push card\n";
		else cout << "X) Push card X\n";
		if (c2e) cout << "2) Pull card\n";
		else cout << "X) Pull card X\n";
		cout << "3) Play Card" << endl;
		int choice;
		while (true) { //input handling. if the input is an x'd out option, it continues the loop to get a new input
			choice = bounded_input<int>("?: ", "choice", 0b1111, 1, 3);
			if (choice == 1 && !c1e) {
				if (pDeck.getSize() <= 0) {
					cout << "!! Deck empty, cant push card !!" << endl;
				}
				else if (pile.getlength() >= 5) {
					cout << "!! Pile full, cant push card !!" << endl;
				}
				continue;
			}
			if (choice == 2 && !c2e) {
				cout << "!! Pile empty, cant pull card !!" << endl;
				continue;
			}
			break;
		}
		//pushes to the side pile and plays a new card
		if (choice == 1) {
			pile.add(card);
			int new_card = pDeck.dequeue();

			cout << "Card pushed. Drawing new card" << flush;
			this_thread::sleep_for(chrono::milliseconds(50)); //dramatic suspense
			cout << "." << flush;
			this_thread::sleep_for(chrono::milliseconds(50));
			cout << "." << flush;
			this_thread::sleep_for(chrono::milliseconds(50));
			cout << "." << flush;
			this_thread::sleep_for(chrono::milliseconds(50));
			cout << new_card << endl;

			return { new_card };
		}
		//pulls a card from the pile and adds it to a respair
		if (choice == 2) {
			cout << "Card pulled. ";
			int new_card = pile.play();
			cout << card << endl;
			return { card,new_card };
		}
		return { card }; //plays the card if neither other option is picked


	}
};

class Computer : public Player {
public:
	void create(int index) {
		name = "Com" + to_string(index);
	}
	//runs the play function for the computer
	resPair play(Player& opp) {
		int card;
		//checking if it can play from queue
		if (pDeck.getSize() > 0) card = pDeck.dequeue();
		else card = pile.play();

		if (pDeck.getSize() == 0 && pile.getlength() > 0) {
			int new_card = pile.play();
			return { card,new_card };
		}
		//checking if it should pull a card from the pile
		if (card < 5) {
			if (pile.getlength() > 0) {
				int new_card = pile.play();
				return { card,new_card };
			}
			return { card };
		}
		//checking if it should push the card to the pile
		if (card < 9) {
			if (pile.getlength() < 5 && pDeck.getSize() > 0) {
				pile.add(card);
				int new_card = pDeck.dequeue();
				return { new_card };
			}
			return { card };
		}
		//plays the card if its a high card
		return { card };
	}
};

int main() {
	//intializing stuff
	srand(time(NULL));
	User ply;
	Computer com;
	int play_type;
	int num_rounds;
	int player_wins = 0;
	bool infinity = false;


	ply = User();
	ply.create(1);

	com = Computer();
	com.create(1);

	// godawful code to allow for deck randomization
	// creates 13 seperate values marking how many of a card is left in the deck
	int choices[13];
	for (int i = 0; i < 13; i++) {
		for (int k = 0; k < 4; k++) {
			choices[i] = 4;
		}
	}
	//dispensing cards
	for (int i = 0; i < 26; i++) {
		while (true) {
			int sel = rand() % 13;
			if (choices[sel] == 0) continue;
			ply.stock_deck(sel + 1);
			break;
		}
	}
	for (int i = 0; i < 26; i++) {
		while (true) {
			int sel = rand() % 13;
			if (choices[sel] == 0) continue;
			com.stock_deck(sel + 1);
			break;
		}
	}

	cout << "Choose game type:\n1) until empty\n2) for a number of rounds" << endl;
	play_type = bounded_input<int>("Selection? ", "selection", 0b1111, 1, 2);

	int r_max; //maximum rounds
	int rounds = 0;//current round
	if (play_type == 1) {
		r_max = -1;
	}
	else {
		r_max = bounded_input<int>("Enter round count: ", "count", 0b1100, 0);
	}
	//runs until one of the player runs out of of cards or until the max runs are completed(if selected)
	while ((ply.totCards() > 0 && com.totCards() > 0) && rounds != r_max) {
		resPair com_card;
		resPair ply_card;
		cout << endl;
		if (r_max > 0) {//print round header. shows points if its round based
			printf("Round %i: [%3i:%-3i]", rounds, ply.points, com.points);
		}
		else {
			printf("Round %i: ", rounds);
		}
		cout << endl;
		//card playing. runs player UI and computer AI
		ply_card = ply.play(com);
		com_card = com.play(ply);

		//scordcard
		cout << endl;
		printf("%16s  %-15s\n", ply.getName().c_str(), com.getName().c_str());

		//what follows is an abomination of string formatting that really should have just been done with printf
		//not fit for human consumption
		stringstream out;
		out << "       ";
		if (ply_card.c2 != 0) out << setw(2) << right << ply_card.c2 << "+" << left << setw(2) << ply_card.c1 << " ";
		else out << "      ";
		out << setw(2) << right << ply_card.total() << " vs " << left << setw(2) << com_card.total() << " ";
		if (com_card.c2 != 0) out << setw(2) << right << com_card.c1 << "+" << left << setw(2) << com_card.c2;
		cout << out.str() << endl;
		cout << left;

		if ((ply_card.c1 + ply_card.c2) > (com_card.c1 + com_card.c2)) {//checks if player won
			cout << "        congrats you won!" << endl << "   adding cards to your deck!" << endl;

			ply.stock_deck(ply_card.c1);
			ply.stock_deck(com_card.c1);
			if (ply_card.c2 != 0) {
				ply.stock_deck(ply_card.c2);

			}
			if (com_card.c2 != 0) {
				ply.stock_deck(com_card.c2);
			}
			ply.points++;

		}
		else {//runs if the player lost
			cout << "       womp womp you lost :(" << endl << "   adding cards to computer deck!" << endl;

			com.stock_deck(ply_card.c1);
			com.stock_deck(com_card.c1);
			if (ply_card.c2 != 0) {
				com.stock_deck(ply_card.c2);

			}
			if (com_card.c2 != 0) {
				com.stock_deck(com_card.c2);

			}
			com.points++;

		}
		cout << endl;
		rounds++;

	}
	int winner = ply.totCards() - com.totCards();
	//cout << "Game over!" << endl;
	//int winner = ply.peekDeck() > 0 - com.peekDeck() > 0;
	//if (r_max > 0) winner = ply.points > com.points - ply.points < com.points;
	if (winner < 0) {
		cout << "Womp Womp you lose :(" << endl;
	}
	if (winner == 0) {
		cout << "Its a tie!" << endl;
	}
	if (winner > 0) {
		cout << "You win!" << endl;
	}

	input_s("press enter to exit.");
	return 1;
}
