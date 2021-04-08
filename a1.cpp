/*****************************************
 * Program: a1.cpp
 * Author: Emily Becher
 * Date: 1/17/21
 * Description: A text adventure game where the user tries to escape a dangerous situation.
 * Input: Takes user inputs using the data types: int, char, float, and string.
 * Output: Prints the story that the user follows and the users name (string).
 ****************************************/

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int main() {

	/*Variables*/
	int path = 0;
	char dir;
	float dist = 0;
	char bh;
	char cs;
	char fr;
	float speed = 0;
	float endurance = 0;
	char el;
	int seq = 0;
	int num = 0;
	string name;
	bool good = false;

	/*Get Random Number*/
	srand(time(NULL));
	num = rand() % 5 + 1;
	
	/*Game Beginning*/
	cout << "Welcome! What is your name? ";
	cin >> name;
	cout << endl;
	cout << "You awake in the woods in front of a strange building. ";
	cout << "Would you like to head into the woods(1) or enter the building(2): ";
	cin >> path;
	cout << endl;
	if (path > 1) {		/*chooses building*/
		cout << "When you enter the building the door locks behind you ";
		cout << "and wakes a monster that was sleeping in the corner. ";
		cout << "Would you like to fight(f) or run(r): ";
		cin >> fr;
		cout << endl;
		if (num == 1) {		/*random effect*/
			if (fr == 'f') {	/*switch to run*/
				fr = 'r';
				cout << "You realize you can't hurt the monster ";
				cout << "and decide to run." << endl;
			}
			else {		/*switch to fight*/
				fr = 'f';
				cout << "You try to run, but the monster gets ";
				cout << "in your path forcing you to fight." << endl;
			}
		}
		cout << "How fast can you run in mph: ";
		cin >> speed;
		cout << "How many minutes could you maintain that speed: ";
		cin >> endurance;
		cout << endl;
		if ((int) (speed * endurance) % 2 == 1) {	/*success path*/
			if (fr == 'f') {
				cout << "You defeat the monster. ";
			}
			else {
				cout << "You slip through a narrow doorway that the ";
				cout << "monster can't follow into a back room. ";
			}
			cout << "Would you like explore(e) or leave(l): ";
			cin >> el;
			cout << endl;
			if (el == 'e') {	/*explorer ending*/
				cout << "You find a portal and become a great explorer."
					 << endl;
				good = true;
			}
			else {		/*leave ending*/
				cout << "You follow a road that takes you to a ";
				cout << "highway where you get help. ";
				cout << "You make it safely back to your home." << endl;
				good = true;
			}	
		}
		else {		/*fail path*/
			cout << "You can't get away from the monster and have one chance";
			cout << " to make it through a door with a puzzle lock. " << endl;
			cout << "The door reads 1, 1, 2, 3, 5... "; 
			cout << "What's the next number is the sequence: ";
			cin >> seq;
			cout << endl;
			if (seq == 8) {		/*correct ending*/
				cout << "Door clicks open and you follow a road to ";
				cout << "someone who helps you return home" << endl;
				good = true;
			}
			else {		/*incorrect ending*/
				cout << "The door reads that the input was incorrect ";
				cout << "and before you can enter another number ";
				cout << "the monster is on you." << endl;
				good = false;
			}
		}
	}
	else {		/*enters woods*/
		cout << "You wander through the woods for a while, ";
		cout << "but you've lost your bearings. ";
		cout << "What direction do you head in (n, e, s, or w): ";
		cin >> dir;
		cout << "How many miles can you make it in an hour: ";
		cin >> dist;
		cout << endl;
		if (dist > 10) {	/*make distance less than 10*/
			dist = (int)  dist % 10;
		}
		if (num == 1) {		/*slowed down*/
			cout << "You are slowed when you tweak your ankle." << endl;
			dist = dist / 2;
		}
		if (dist > 3 && dir != 'w') {		/*travels far enough*/
			cout << "You made good distance. ";
			cout << "You can see a building and hear a highway. ";
			cout << "Do you head toward the building(b) or highway(h): ";
			cin >> bh;
			cout << endl;
			if (bh == 'h') {	/*highway ending*/
				cout << "A passing driver helps you get home." << endl;
				good = true;
			}
			else {		/*building ending*/
				cout << "As you approach you are electrocuted by ";
				cout << " the building defenses." << endl;
				good = false;
			}
		}
		else {		/*doesn't travel far enough*/
			cout << "The sky darkens and you have yet to find anything ";
			cout << "Continue(c) traveling or build a shelter(s): ";
			cin >> cs;
			cout << endl;
			if (cs == 'c') {	/*continue ending*/
				cout << "In the dark you trip and fall to your death."
					 << endl;
				good = false;
			}
			else {		/*shelter ending*/
				cout << "You find help the next morning." << endl;
				good = true;
			}
		}	
	}
	if (good == true) { 	/*good end message*/
		cout << "Well played " << name << "!" << endl;
	}
	else {		/*bad end message*/
		cout << "Better luck next time " << name << "." << endl;
	}

	return 0;
}
