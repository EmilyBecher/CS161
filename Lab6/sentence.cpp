#include <iostream>
#include <string>

using namespace std;

void get_sentence(string *sentence);

int main() {
	string sentence;

	get_sentence(&sentence);
	cout << sentence << endl;

	return 0; 
}

void get_sentence(string *sentence) {
	cout << "Enter a sentence: ";
	getline(cin, *sentence);

}