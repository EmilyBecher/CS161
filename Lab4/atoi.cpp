#include <iostream>

using namespace std;

int atoi(char character);
char itoa(int decimal);

int main() {

	/*Variables*/
    	char character;
	int decimal;

	/*atoi*/
	cout << "Enter a character: ";
	cin >> character;
	cout << "Your character in decimal is " << atoi(character) << endl;

	/*itoa*/
	cout << "Enter a number: ";
	cin >> decimal;
	cout << "The character is " << itoa(decimal) << endl;

	return 0;
}

int atoi(char character) {

	return character;
}

char itoa(int decimal) {

	return decimal;
}
