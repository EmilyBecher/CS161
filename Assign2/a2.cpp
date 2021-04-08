/****************************************************************
 * Program: a2.cpp
 * Author: Emily Becher
 * Date: 1/31/2021
 * Description: Plays a game a 21 with 1-4 players
 * Inputs: number of players, initial funds, bets, continue drawing, continue playing
 * Outputs: information about what's happening in the game
 * **************************************************************/
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

/*Prototypes*/
int hand(int player);
int deal(int max);
int fun(int scores[4]);

int main() {

	/*Variables*/
    	int players = 0;
	bool play = 1;
	float bank[4] = {0, 0, 0, 0};

	/*Welcome*/
	cout << "Welcome! You are playing 21!" << endl << endl;

	/*Number of Players*/
	while (players < 1 || players > 4) {
		cout << "How many players (1-4): ";
		cin >> players;
		if (cin.fail() || players < 1 || players > 4) {
			cin.clear();
			cin.ignore(80,'\n');
			cout << "Invalid input." << endl;
		}
	}
	cout << endl;

	/*Initial Bank*/
	for (int i = 0; i < players; i++) {
		while (bank[i] <= 0) {
			cout << "How much money does player " << i + 1 << " have?: ";
			cin >> bank[i];
			if (cin.fail()) {
				cin.clear();
				cin.ignore(80,'\n');
				cout << "Invalid input." << endl;
			}
		    else if (bank[i] <= 0) {
				cout << "You need to start with money." << endl;
			}
		}
	}
	cout << endl;

	/*Game Play*/
	while (play){

	    	/*Variables*/
		float bet[4] = {0, 0, 0, 0};
		int score[4] = {0, 0, 0, 0};
		bool dealer = 0;
		int dhand = 0;
		int best = 0;
		bool bust = 0;

	    	/*Get bets*/
		cout << "How much do you bet that you can beat the dealer?" << endl;
		for (int i = 0; i < players; i++) {
			if (bank[i] > 0) {
		    		while (bet[i] <= 0 || bet[i] > bank[i]) {
					cout << "Player " << i + 1 << " bet: ";
					cin >> bet[i];
					if (cin.fail()) {
						cin.clear();
						cin.ignore(80,'\n');
						cout << "Invalid input." << endl;
					}
					else if (bet[i] <= 0) {
						cout << "You have to bet something." << endl;
					}
					else if (bet[i] > bank[i]) {
						cout << "You don't have that much money." << endl;
					}
				}
			}
			else {
				cout << "Player " << i + 1 << " is skipped." << endl;
			}
		}
		cout << endl;

		/*Play hand*/
		for (int i = 0; i < players; i++) {
		    	if (bank[i] > 0) {
				score[i] = hand(i + 1);
				if (score[i] == 21) {
					cout << "You win!" << endl;
					bank[i] += bet[i];
				}
				else if (score[i] > 21) {
					cout << "Bust! You lose!" << endl;
					bank[i] -= bet[i];
				}
				else {
					dealer = 1;
				}
				cout << endl;
			}
		}



		/*Dealer's Turn*/
		if (dealer) {
		    	best = fun(score);
			dhand = deal(best);
			if (dhand > 21) {
				bust = 1;
			}
			cout << endl;
		}

		/*Compare Scores*/
		for (int i = 0; i < players; i++) {
			if (score[i] < 21 && bank[i] > 0) {
				if (score[i] > dhand || bust) {
					cout << "Player " << i + 1 << " beat the dealer" << endl;
					bank[i] += bet[i];
				}
				else if (score[i] < dhand && !bust) {
					cout << "The dealer beat player " << i + 1 << endl;
					bank[i] -= bet[i];
				}
				else {
					cout << "Player " << i + 1 << " tied the dealer" << endl;
				}
			}
		}
		cout << endl;

		/*Print Scores*/
		for (int i = 0; i < players; i++) {
			cout << "Player " << i + 1 << "'s balance is " << bank[i] << endl;
		}
		cout << endl;
		/*Continue?*/
		if (bank[0] + bank[1] + bank[2] + bank[3] > 0) {
			while (true) {
		    		cout << "Another hand? (0-no, 1-yes): ";
		    		cin >> play;
		    		if (cin.fail()) {
					cin.clear();
					cin.ignore(80,'\n');
					cout << "Invalid input." << endl;
		    		}		
		    		else {
					break;
		    		}
			}
		}
		else {
			cout << "All the players are out of money." << endl;
			play = 0;
		}
		cout << endl;	
	}		

	cout << "Thanks for playing!" << endl;
	return 0;
}

/****************************************************************
 * Function: hand
 * Description: plays a hand for the user 
 * Parameters: int player_num
 * Pre-Conditions: input is an integer
 * Post-Conditions: returned the score of the hand
 * **************************************************************/

int hand(int player_num) {
	
    	int score = 0;
	bool again = 1;

	srand(time(NULL));
	cout << "Player " << player_num << endl;

	while(again) {
		int card = rand() % 11 + 1;
		score += card;
		cout << "Your card is a " << card << endl;
		cout << "Your current score is " << score << endl;
		if (score < 21) {
			while (true) {
		    		cout << "Another card? (0-no, 1-yes): ";
		    		cin >> again;
		    		if (cin.fail()) {
					cin.clear();
					cin.ignore(80,'\n');
					cout << "Invalid input." << endl;
		    		}
		    		else {
					break;
		    		}
			}
		}
		else {
			again = 0;
		}		
	}
	return score;
}

/****************************************************************
 * Function: deal
 * Description: plays a hand for the dealer
 * Parameters: int best
 * Pre-Conditions: input is an integer
 * Post-Conditions: returns the score of the dealer's hand
 * **************************************************************/

int deal(int best) {

    	int card = 0;
    	int score = 0;   	
    	srand(time(NULL));

    	if (best > 16) {
    		best = 16;
    	}

	do {
		card = rand() % 11 + 1;
		score += card;
		cout << "The dealer got a " << card << endl;
	}while(score <= best);

	cout << "The dealer's score is " << score << endl;
    	return score;
}

/****************************************************************
 * Function: fun 
 * Description: finds the best score of the players
 * Parameters: int score[]
 * Pre-Condition: input is an integer array
 * Post-Condition: returns the best score out of the users' hands
 * **************************************************************/

int fun(int score[4]) {

    	int best = 0;    

    	for(int i = 0; i < 4; i++){
	    	if (score[i] < 21) {
			if (best < score[i]) {
	    			best = score[i];
			}
		}	
    	}

  	return best;
}
