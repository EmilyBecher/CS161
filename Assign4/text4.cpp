/**********************************************************
** Program: text4.cpp
** Author: Emily Becher
** Date: 2/28/21
** Description: performs swap, flip, or frequency operation on an inputted string
** Inputs: c-string 1023 char, integers, strings
** Outputs: instructions and the changed string
**********************************************************/
#include <iostream>
#include <string.h>
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>

using namespace std;

void swap(char* str);
void flip(char* str);
void freq(char* str);
int compare(char* str, string word);
void get_input(char* str);
void get_int(int &num, int min, int max, string prompt);
void get_letter(char &c, string prompt);
void get_words(string* &arr, int num);
void to_lower(char* str);
void print_ops();
int ati(char c);
int atf(char c);
int stod(string str);


int main(){
	/*Variables*/
	char str[1024];
	int op = 0;

	cout << endl << "Welcome to Text Surgeon!" << endl << endl;

	/*Get user's string*/
	get_input(str);

	/*Perform Operations*/
	while(op != 4){
		print_ops();
		get_int(op, 1, 4, "Enter the number of the operation you want performed: ");
		cout << endl;

		if (op == 1){
			swap(str);
		}
		else if(op == 2){
			flip(str);
		}
		else if(op == 3) {
			freq(str);
		}
	}

	cout << "Thank you for using Text Surgeon!" << endl;

	return 0;
}

/**********************************************************
** Function: swap
** Description: replaces first letter with second
** Parameters: char* str
** Pre-Conditions: a string was inputted in main
** Post-Conditions: prints string with replaced letter and doesn't change string in main
**********************************************************/

void swap(char* str){
	char c1, c2, c3;
	/*Get letters*/
	get_letter(c1, "Enter letter to be replaced: ");
	get_letter(c2, "Enter letter to be inserted: ");

	/*Print string with c1 replaced*/
	cout << endl;
	for(int i = 0; i < strlen(str); i++){
		if(str[i] == c1){
			cout << c2;
		}
		else if(ati(str[i]) == ati(c1) - 32){
			c3 = ati(c2) - 32;
			cout << c3;
		}
		else {
			cout << str[i];
		}
	}
	cout << endl;
}

/**********************************************************
** Function: flip
** Description: reverse the string
** Parameters: char* str
** Pre-Conditions: a string was inputted in main
** Post-Conditions: prints reversed string without changing it in main
**********************************************************/

void flip(char* str){
	char* copy = NULL;

	/*Copies and flips str*/
	copy = new char[strlen(str) + 1];
	for(int i = 0; i < strlen(str); i++){
		copy[i] = str[strlen(str) - i - 1];
	}
	copy[strlen(str)] = '\n';

	/*Outputs copy*/
	for(int i = 0; i < strlen(copy); i++){
		cout << copy[i];
	}

	delete [] copy;
	copy = NULL;
}

/**********************************************************
** Function: freq
** Description: gets a user selected number of words and outputs how many times they appear
** Parameters: char* str
** Pre-Conditions: a string was inputted in main
** Post-Conditions: prints appearances of each user provided word
**********************************************************/

void freq(char* str){
	int num = 0;
	get_int(num, 1, 20, "Enter the number of words you'd like to count: ");
	string* words = NULL;
	get_words(words, num);
	cout << endl;
	int count[num];
	ofstream output;
	output.open ("out.txt");
	for(int i = 0; i < num; i++){
		count[i] = compare(str, words[i]);
		output << words[i] << " appears " << count[i] << " times." << endl;
	}
	
	output.close();

	delete [] words;
	words = NULL;
}

/**********************************************************
** Function: compare
** Description: compares a c-string to a string object
** Parameters: char* str, string word
** Pre-Conditions: has a c-style string and string object
** Post-Conditions: returns the number of time word is in str
**********************************************************/

int compare(char* str, string word){
	int count = 0;
	char* lower = &word[0];
	to_lower(lower);

	char* copy = NULL;
	copy = new char[strlen(str) + 1];
	for(int i = 0; i < strlen(str); i++){
		copy[i] = str[i];
	}
	copy[strlen(str)] = '\n';

	to_lower(copy);
	for(int i = 0; i < strlen(copy) - strlen(lower) + 1; i++){
		for(int j = 0; j < strlen(lower); j++){
			if(copy[i + j] == lower[j]) {
				if(j == strlen(lower) - 1){
					count++;
				}
			}
			else{
				break;
			}
		}
	}

	delete [] copy;
	copy = NULL;

	return count;
}

/**********************************************************
** Function: get_input
** Description: gets a string from file
** Parameters: char* str
** Pre-Conditions: there is memory allocated and the text in given file is under 1024 chars
** Post-Conditions: string in main is populated
**********************************************************/

void get_input(char* str){
	char file[100];
	bool bad = 1;

	ifstream x(file);
	cout << "Enter filename: ";

	while(bad){
		cin.getline(file, 100, '\n');
		if(file[strlen(file)-4] == '.' && file[strlen(file)-3] == 't' && file[strlen(file)-2] == 'x' && file[strlen(file)-1] == 't'){
			x.open(file);
			if(x)
				bad = 0;
			else
				cout << "File not found. Try again: ";
		}
		else
			cout << "Enter a .txt file: ";
	}

	x.getline(str, 1023, '\n');	
}

/**********************************************************
** Function: get_int
** Description: gets an integer between given min and max
** Parameters: int &num, int min, int max, string prompt
** Pre-Conditions: there is memory allocated for num
** Post-Conditions: num is populated with integer
**********************************************************/

void get_int(int &num, int min, int max, string prompt) {
	string str;
	bool bad = 1;
	cout << prompt;
	while(bad) {
		getline(cin, str);
		for(int i = 0; i < str.length(); i++) {
			/* Checks for invalid characters */
			if(ati(str[i]) < 48 || ati(str[i]) > 57) {
				cout << "Invalid input, try again: ";
				break;
			}
			/* All characters are valid */
			else if(i == str.length() - 1) {
				num = stod(str);
				if(num > max) {
					cout << "Enter a number of at most " << max << ": ";
					break;
				}
				else if(num < min) {
					cout << "Enter a number of at least " << min << ": ";
					break;
				}
				/* Valid input*/
				else {
					bad = 0;
				}
			}
		}
	}
}

/**********************************************************
** Function: get_letter
** Description: gets a letter and makes it lowercase
** Parameters: char &c, string prompt
** Pre-Conditions: memory allocated for c
** Post-Conditions: c is populated with a lowercase letter
**********************************************************/

void get_letter(char &c, string prompt){
	char str[21];
	bool bad = 1;
	cout << prompt;
	while(bad) {
		cin.getline(str, 20, '\n');
		if(strlen(str) == 1){
			to_lower(str);
			c = str[0];
			if(ati(c) < 123 && ati(c) > 96){
				bad = 0;
			}
			else {
				cout << "Enter a letter: ";
			}
		}
		else {
			cout << "Enter one letter: ";
			cin.clear();
		}
	}
}

/**********************************************************
** Function: get_words
** Description: gets words from user and stores them in an array on the heap
** Parameters: string* &arr, int num
** Pre-Conditions: user has entered the number of words
** Post-Conditions: creates and populates string array
**********************************************************/

void get_words(string* &arr, int num){
	arr = new string[num];
	for(int i = 0; i < num; i++){
		bool bad = 1;
		cout << "Enter word " << i + 1 << ": ";
		while(bad) {
			getline(cin, arr[i]);
			if(arr[i].length() < 20){
				bad = 0;
			}
			else{
				cout << "Enter a shorter string: ";
			}
		}
	}
}

/**********************************************************
** Function: to_lower
** Description: switches a c-style string to lowercase
** Parameters: char* str
** Pre-Conditions: there is a string to be changed
** Post-Conditions: there are no uppercase letters in the string
**********************************************************/

void to_lower(char* str) {
	for(int i = 0; i < strlen(str); i++){
		if(ati(str[i]) > 64 && ati(str[i] < 91)){
			str[i] = ati(str[i]) + 32;
		}
	}
}

/**********************************************************
** Function: print_ops
** Description: prints the available operations
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: prints options
**********************************************************/

void print_ops() {
	cout << endl;
	cout << "The operations available are" << endl;
	cout << "1. Swap two letters" << endl;
	cout << "2. Reverse the string" << endl;
	cout << "3. Search for words in the string" << endl;
	cout << "4. Quit" << endl;
}

/**********************************************************
** Function: ati
** Description: switches char to int (ascii value)
** Parameters: char c
** Pre-Conditions: a character is passed in
** Post-Conditions: returns ascii value
**********************************************************/

int ati(char c) {
	return c;
}

/**********************************************************
** Function: atf
** Description: switches char to int (9 to 9)
** Parameters: char c
** Pre-Conditions: a character 0-9 is passed in
** Post-Conditions: num is an int
** Lines: 31 (shortening wouldn't help readability or function)
**********************************************************/

int atf(char c) {
	int num = 0;
	switch(c) {
		case '1': 
			num = 1;
			break;
		case '2':
			num = 2;
			break;
		case '3': 
			num = 3;
			break;
		case '4':
			num = 4;
			break;
		case '5': 
			num = 5;
			break;
		case '6':
			num = 6;
			break;
		case '7': 
			num = 7;
			break;
		case '8':
			num = 8;
			break;
		case '9': 
			num = 9;
			break;
		defaut:
			break;
	}
	return num;
}

/**********************************************************
** Function: stod
** Description: converts string of a number into int
** Parameters:string str
** Pre-Conditions: all characters in the string are numbers
** Post-Conditions: num is an int
**********************************************************/

int stod(string str) {
	int num = 0;
	for(int i = 0; i < str.length(); i++) {
			num = (num * 10) + atf(str[i]);
	}
	return num;
}