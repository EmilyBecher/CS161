#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;

int main() {

	/*Variables*/
	bool play = 1;

	/*Seed random number*/
	srand(time(NULL));

	/*Welcome*/
	cout << "Welcom to Password Creator!" << endl;

	/*Game loop*/
	while (play) {
		
		/*Variables*/
		bool letters = 0;
		bool uppercase = 0;
		bool lowercase  = 0;
		bool numbers = 0;
		int upper_num = 0;
		int lower_num = 0;
		int num_num = 0;
		int rand_num = 0;
		char rand_char;
		string password = "";

		/*Gets user preferences*/
		cout << endl << "In your password... " << endl;
		cout << "Do you want letters (0-no, 1-yes)? ";
		cin >> letters;
		if (letters) {	
			cout << "Do you want uppercase letters (0-no, 1-yes)? ";
			cin >> uppercase;
			if (uppercase) {
				cout << "How many uppercase letters? ";
				cin >> upper_num;
			}
			cout << "Do you want lowercase letters (0-no, 1-yes)? ";
			cin >> lowercase;
			if (lowercase) {
				cout << "How many lowercase letters? ";
				cin >> lower_num;
			}
		}
		cout << "Do you want numbers (0-no, 1-yes)? ";
		cin >> numbers;
		if (numbers) {
			cout << "How many numbers? ";
			cin >> num_num;
		}
		cout << endl;

		/*Creates Password*/
		for (int i = 0; i < upper_num; i++) {
			rand_num = rand() % 26 + 65;
			rand_char = rand_num;
			password.append(1, rand_char);	
		}
		for (int i = 0; i < lower_num; i++) {
			rand_num = rand() % 26 + 97;
			rand_char = rand_num;
			password.append(1, rand_char);	
		}
		for (int i = 0; i < num_num; i++) {
			rand_num = rand() % 10 + 48;
			rand_char = rand_num;
			password.append(1, rand_char);
		}

		/*Output*/
		if (password == "") {
			cout << "You did not create a password." << endl;
			cout << "Would you like to try again (0-no, 1-yes)? ";
			cin >> play;
		}
		else {
			cout << "Your random password is " << password << endl << endl;
			cout << "Would you like to create another password (0-no, 1-yes)? ";
			cin >> play;
		}
	}

	return 0;
}
