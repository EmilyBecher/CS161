#include <iostream>
#include <cstring>
#include <string>

using namespace std;

void get_string(char* str);
void word_arr(int size, string* words);

int main() {
	char str[1024];
	int size = 0;
	string* words;

	get_string(str);

	cout << "How many words?: ";
	cin >> size;
	cin.ignore(1024, '\n');
	//string words[size];
	words = new string[size];
	word_arr(size, words);

	cout << str << endl;
	for(int i = 0; i < size; i++){
		cout << words[i] << endl;
	}

	delete [] words;
	words = NULL;

	return 0;
}

void get_string(char* str) {
	cout << "Enter a string: ";
	cin.getline(str, 1024, '\n');
	if (cin.fail()) {
		cin.ignore(1024, '\n');
		cin.clear();
	}
}

void word_arr(int size, string* words){
	for(int i = 0; i < size; i++){
		cout << "Enter word " << i + 1 << ": ";
		getline(cin, words[i]);
	}
}