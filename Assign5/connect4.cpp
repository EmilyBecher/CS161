/**********************************************************
** Program: text4.cpp
** Author: Emily Becher
** Date: 2/28/21
** Description: performs swap, flip, or frequency operation on an inputted string
** Inputs: c-string 1023 char, integers, strings
** Outputs: instructions and the changed string
**********************************************************/
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

void play_game(char** board, int rows, int cols, int mode, bool play);
void switch_player(int& player, int temp);
void print_board(char** board, int rows, int cols);
void reset_board(char** board, int rows, int cols);
int check_board(char** board, int rows, int cols, int mode);
int check_row(char** board, int rows, int cols, int mode);
int check_col(char** board, int rows, int cols, int mode);
int check_diag(char** board, int rows, int cols, int mode);
void results(int result, int mode);
void get_col(char** board, int rows, int cols, int player);
void get_bool(bool &play, string prompt);
void get_int(int &num, int min, int max, string prompt, string str);
int ati(char c);
int atf(char c);
int stod(string str);

int main(int argc, char *argv[]){
	/*Variables*/
	int mode = 0;
	int rows = 0;
	int cols = 0;
	bool play = 1;

	/*Get mode, rows, and cols*/
	if(argc != 4){//If there aren't four command line argumennts
		get_int(mode, 1, 2, "Enter number of players: ", "-bl.ah");
		get_int(rows, 4, 20, "Enter number of rows: ", "-bl.ah");
		get_int(cols, 4, 20, "Enter number of columns: ", "-bl.ah");
	}
	else {//If there are four command line arguments
		get_int(mode, 1, 2, "Enter number of players: ", argv[1]);
		get_int(rows, 4, 20, "Enter number of rows: ", argv[2]);
		get_int(cols, 4, 20, "Enter number of columns: ", argv[3]);
	}

	/*Allocate memory for game board*/
	char** arr = new char*[rows + 1];
	for(int i = 0; i < rows; i++){
		arr[i] = new char[cols];
	}

	play_game(arr, rows, cols, mode, play);

	/*Free game board memory*/
	for(int i = 0; i < rows; i++) {
		delete [] arr[i];
		arr[i] = NULL;
	}
	delete [] arr;
	arr = NULL;

	return 0;
}

/**********************************************************
 ** Function: play_game
 ** Parameters: char** arr, int rows, int cols, int mode, bool play
 ** Pre-Conditions: memory allocated for char array
 ** Post-Conditions: handles gameplay
 ** Lines: 19
 *********************************************************/

void play_game(char** arr, int rows, int cols, int mode, bool play) {
	cout << endl << "Welcome to Connect 4" << endl << endl;
	while(play){
		bool game = 1;
		int player = 1;
		int temp = 2;
		int result = 0;
		bool first = 1;
		if(mode == 1) {//If playing against computer
			temp = 0;
			get_bool(first, "Would you like to go first?: ");
			if(first == 0){//If computer goes first
				player = 0;
			}
		}
		reset_board(arr, rows, cols);
		while(game) {
			print_board(arr, rows, cols);
			get_col(arr, rows, cols, player);//gets move
			result = check_board(arr, rows, cols, mode);
			switch_player(player, temp);
			if(result != 0){
				game = 0;
			}
		}
		print_board(arr, rows, cols);
		results(result, mode);
		get_bool(play, "Would you like to play again?: ");
	}
	cout << "Thanks for playing" << endl;
}

/**********************************************************
 ** Function: switch_player
 ** Parameters: &player, int temp
 ** Pre-Conditions: player and temp are correct
 ** Post-Conditions: switch player to 1 or temp
 ** Lines: 4
 *********************************************************/

void switch_player(int& player, int temp) {
	if(player == 1) {
		player = temp;
	}
	else {
		player = 1;
	}
}

/**********************************************************
 ** Function: print_board
 ** Parameters: char** board, int rows, int cols
 ** Pre-Conditions: board points to initialized character array
 ** Post-Conditions: outputs board 
 ** Lines: 17
 *********************************************************/

void print_board(char** board, int rows, int cols) {
	/*Print column headers*/
	for(int i = 0; i < cols; i++) {
		if(i > 8) {
			cout << " " << i + 1 << " "; 
		}
		else {
			cout << "  " << i + 1 << " ";
		}
	}
	/*Print board*/
	cout << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i % 2 == 0 && j % 2 == 0)
				cout << "|\033[30;47m " << board[i][j] << " ";
			else if (i % 2 == 1 && j % 2 == 1)
				cout << "|\033[30;47m " << board[i][j] << " ";
			else
				cout << "|\033[0m " << board[i][j] << " ";
			cout << "\033[0m";
		}
		cout << endl;
	}
	cout << endl;
}

/**********************************************************
 ** Function: reset_board
 ** Parameters: char** board, int rows, int cols
 ** Pre-Conditions: memory is allocated for array
 ** Post-Conditions: all elements of array are set to spaces
 ** Lines: 3
 *********************************************************/

void reset_board(char** board, int rows, int cols) {
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			board[i][j] = ' ';
		}
	}
}

/**********************************************************
 ** Function: check_board
 ** Parameters: char** board, int rows, int cols, int mode
 ** Pre-Conditions: array with elements (' ', 'X', 'O') and mode (1, 2) passed in
 ** Post-Conditions: returns current board state
 ** Lines: 12
 *********************************************************/

int check_board(char** board, int rows, int cols, int mode) {
	int row, col, diag;
	row = check_row(board, rows, cols, mode);
	col = check_col(board, rows, cols, mode);
	diag = check_diag(board, rows, cols, mode);
	if(row == 1 || col == 1 || diag == 1) {//If any direction reports four X's
		return 1;
	}
	else if(row == 2 || col == 2 || diag == 2){//If any direction reports 4 O's in mode 2
		return 2;
	}
	else if(row == 3 || col == 3 || diag == 3) {//If any direction reports 4 O's in mode 1
		return 3;
	}
	else if(row == 4) {//If board is full
		return 4;
	}
	return 0;
}

/**********************************************************
 ** Function: check_row
 ** Parameters: char** board, int rows, int cols, int mode
 ** Pre-Conditions: array with elements (' ', 'X', 'O') and mode (1, 2) passed in
 ** Post-Conditions: returns if board is full or if someone won based on rows
 ** Lines: 20
 *********************************************************/

int check_row(char** board, int rows, int cols, int mode) {
	bool full = 1;
	char c = '0';
	int count = 1;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			if(board[i][j] == ' '){
				full = 0;
				c = ' ';
			}
			else if(board[i][j] == c){
				count++;
				if(count == 4 && c == 'X'){//4 X's 
					return 1;
				}
				else if(count == 4 && c == 'O' && mode == 1){//4 O's and mode 1
					return 3;
				}
				else if(count == 4 && c == 'O'){//4 O's and mode 2
					return 2;
				}
			}
			else {
				count = 1;
				c = board[i][j];
			}
		}
		if(full == 1 && i == rows - 1){//board full
			return 4;
		}
		c = 0;//count to zero when moving to next row
	}
	return 0;
}

/**********************************************************
 ** Function: check_col
 ** Parameters: char** board, int rows, int cols, int mode
 ** Pre-Conditions: array with elements (' ', 'X', 'O') and mode (1, 2) passed in
 ** Post-Conditions: returns if someone won based on columns
 ** Lines: 15
 *********************************************************/

int check_col(char** board, int rows, int cols, int mode) {
	char c = '0';
	int count = 1;
	for(int j = 0; j < cols; j++){//loop through columns
		for(int i = 0; i < rows; i++){//loop through rows
			if(board[i][j] != ' ' && board[i][j] == c){
				count++;
				if(count == 4 && c == 'X'){//4 X's
					return 1;
				}
				else if(count == 4 && c == 'O' && mode == 1){//4 O's and mode 1
					return 3;
				}
				else if(count == 4 && c == 'O'){//4 O's and mode 2
					return 2;
				}
			}
			else {
				count = 1;
				c = board[i][j];
			}
		}
		c = 0;//count to zero when moving to next column
	}
	return 0;
}

/**********************************************************
 ** Function: check_diag
 ** Parameters: char** board, int rows, int cols, int mode
 ** Pre-Conditions: array with elements (' ', 'X', 'O') and mode (1, 2) passed in
 ** Post-Conditions: returns if someone won diagonally
 ** Lines: 21, I think it's more clear to check both directions in the same function 
 			than to split into two functions
 *********************************************************/

int check_diag(char** board, int rows, int cols, int mode) {
	char c = '0';
	/*Check down right direction*/
	for(int i = 0; i < rows - 3; i++) {
		for(int j = 0; j < cols - 3; j++) {
			c = board[i][j];
			if(board[i+1][j+1] == c && board[i+2][j+2] == c && board[i+3][j+3] == c){
				if(c == 'X') {
					return 1;
				}
				else if(c == 'O' && mode == 1) {
					return 3;
				}
				else if(c == 'O') {
					return 2;
				}
			}
		}
	}
	/*Check down left direction*/
	for(int i = 3; i < rows; i++) {
		for(int j = 0; j < cols - 3; j++){
			c = board[i][j];
			if(board[i-1][j+1] == c && board[i-2][j+2] == c && board[i-3][j+3] == c) {
				if(c == 'X') {
					return 1;
				}
				else if(c == 'O' && mode == 1) {
					return 3;
				}
				else if(c == 'O') {
					return 2;
				}	
			}
		}
	}
	return 0;
}

/**********************************************************
 ** Function: results
 ** Parameters: int results, int mode
 ** Pre-Conditions: result is between 1 and 4 and mode is between 1 and 2
 ** Post-Conditions: Outputs result
 ** Lines: 10
 *********************************************************/

void results(int result, int mode) {
	if(result == 1 && mode == 2){
		cout << "Player 1 wins!" << endl;
	}
	else if(result == 1 && mode == 1){
		cout << "You win!" << endl;
	}
	else if(result == 2){
		cout << "Player 2 wins!" << endl;
	}
	else if(result == 3){
		cout << "You lose!" << endl;
	}
	else {
		cout << "You tied!" << endl;
	}
}

/**********************************************************
 ** Function: get_col
 ** Parameters: char** board, int rows, int cols, int player
 ** Pre-Conditions: initialized board and player is between 0 and 2 
 ** Post-Conditions: gets valid move and makes move
 ** Lines: 19
 *********************************************************/

void get_col(char** board, int rows, int cols, int player) {
	srand(time(NULL));
	bool bad = 1;
	int move = 0;
	char c = 'O';
	if(player == 1){
		c = 'X';
	}
	else if(player == 0){
		cout << "Computer's move" << endl;
	}
	while(bad) {
		if(player == 0){
			move = rand() % cols + 1;//Computer plays randomnly
		}
		else if(player == 1){
			get_int(move, 1, cols, "Enter Player 1's move: ", "-bl.ah");
		}
		else {
			get_int(move, 1, cols, "Enter Player 2's move: ", "-bl.ah");
		}
		for(int i = rows - 1; i >= 0; i--){
			if(board[i][move - 1] == ' '){//If space is empty
				board[i][move - 1] = c;//make move
				bad = 0;
				break;
			}
		}
		if(bad && player != 0) {//only output message for user
			cout << "That column is full." << endl;
		}
	}
}

/**********************************************************
 ** Function: get_bool
 ** Parameters: bool &play, string prompt
 ** Pre-Conditions: boolean variable to fill
 ** Post-Conditions: converts y, Y, 1 or n, N, 0 into bool value
 ** Lines: 13
 *********************************************************/

void get_bool(bool &play, string prompt) {
	string str;
	bool bad = 1;
	cout << prompt;
	while(bad) {
		getline(cin, str);
		if(str.length() != 1) {
			cout << "Enter y or n: ";
		}
		/* True cases*/
		else if(str == "y" || str == "Y" || str == "1") {
			play = 1;
			bad = 0;
		}
		/* False cases*/
		else if(str == "n" || str == "N" || str == "0") {
			play = 0;
			bad = 0;
		}
		else {
			cout << "Enter y or n: ";
		}
	}
}

/**********************************************************
 ** Function: get_int
 ** Parameters: int &num, int min, int max, string prompt, string str
 ** Pre-Conditions: int to fill and user didn't enter -bl.ah in cmd line
 ** Post-Conditions: fills num with int within given min and max
 ** Lines: 22, I think it's better to keep this as one function
 *********************************************************/

void get_int(int &num, int min, int max, string prompt, string str) {
	bool bad = 1;
	if(str == "-bl.ah") {
		cout << prompt;
	}
	while(bad) {
		if(str == "-bl.ah") {
			getline(cin, str);
		}
		for(int i = 0; i < str.length(); i++) {
			/* Checks for invalid characters */
			if(ati(str[i]) < 48 || ati(str[i]) > 57) {
				cout << "Invalid input, try again: ";
				str = "-bl.ah";
				break;
			}
			/* All characters are valid */
			else if(i == str.length() - 1) {
				num = stod(str);
				str = "-bl.ah";
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
					break;
				}
			}
		}
	}
}

/**********************************************************
** Function: ati
** Parameters: char c
** Pre-Conditions: a character is passed in
** Post-Conditions: returns ascii value
** Lines: 1
**********************************************************/

int ati(char c) {
	return c;
}

/**********************************************************
** Function: atf
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
** Parameters:string str
** Pre-Conditions: all characters in the string are numbers
** Post-Conditions: num is an int
** Lines: 3
**********************************************************/

int stod(string str) {
	int num = 0;
	for(int i = 0; i < str.length(); i++) {
			num = (num * 10) + atf(str[i]);
	}
	return num;
}