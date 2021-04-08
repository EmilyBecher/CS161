#include <iostream>
#include <string>

using namespace std;

void get_sentence(string s);

int main() {
	string sentence;

	//sentence = get_sentence();
	//cout << get_sentence() << endl;

	//cout << "Enter a sentence: ";
	//getline(cin, sentence);
	get_sentence(sentence);

	cout << sentence << endl;

	return 0;
}

/**********************************************************
 * Function: get_sentence
 * Parameters: none
 * Pre-Conditions: 
 * Post-Conditions:
 * ********************************************************/

void get_sentence(string s) {
    	//string input;
	cout << "Enter a sentence: ";
	getline(cin, s);
	//cout << input << endl;

	//cout << s << endl;

	return;
}
