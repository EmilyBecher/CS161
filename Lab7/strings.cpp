/********************************************************
 ** Author: Emily Becher
 ** Date: 2/11/21
 ** Program: ask the user for a string, copy the string,
 ** 	     change ' ' in the copy into '_', get char
 ** 	     from user, count appearances of char in str
 ** Inputs: string and char
 ** Outputs: string, dashed string, appearance count
 ********************************************************/

#include <iostream>
#include <string>

using namespace std;

void get_string(string *str_to_store);
void set_replace_string(string copy_str, string *dash_str);
int get_search_replace(char c, string copy_str, string *dash_str);

int main() {
	/* Variables */
	string str;
	string dash;
	char c;
	int num = 0;

	get_string(&str);
	set_replace_string(str, &dash);

	cout << "Your string is now " << dash << endl;

	cout << endl << "Enter a character: ";
	cin >> c;
	num = get_search_replace(c, str, dash);

	cout << endl << "Your string is now " << dash << endl;
	cout << c << " appeared " << num << " times" << endl;

	return 0;
}

/**********************************************************
 ** Function: get_string
 ** Parameters: string *str_to_store
 ** Pre-Conditions:
 ** Post-Conditions: str is filled with user input
 *********************************************************/

void get_string(string *str_to_store) {
	cout << "Enter a string: ";
	getline(cin, *str_to_store);
}

/**********************************************************
 ** Function: set_replace_string
 ** Parameters: strings copy_str and *dash_str
 ** Pre-Conditions: copy_str has contents
 ** Post-Conditions: fills dash with str with dashes
 *********************************************************/

void set_replace_string(string copy_str, string *dash_str) {
	for(int i = 0; i < copy_str.length(); i++) {
		if(copy_str[i] != ' ') {
			copy_str.replace(i, 1, "_");
		}	
	}
	*dash_str = copy_str;
}

/**********************************************************
 ** Function: get_search_replace
 ** Parameters: char c, strings copy_str and *dash_str
 ** Pre-Conditions: c and copy_str have content
 ** Post-Conditions: dash is changed and num is returned
 *********************************************************/

int get_search_replace(char c, string copy_str, string *dash_str) {
	int num = 0;
	for(int i = 0; i < copy_str.length(); i++) {
		if(copy_str[i] == c) {
			num++;
			copy_str.replace(i, 1, 1, c);
		}
	}
	*dash_str = copy_str;
	return num;
}
