/**********************************************************
** Program: fractal.cpp
** Author: Emily Becher
** Date: 2/28/21
** Description: prints the given fractal
** Inputs: integers for the longest line and column offset
** Outputs: fractal where the longest line is n
**********************************************************/

#include <iostream>

using namespace std;

void pattern(int n, int col);

int main() {
	int n = 0;
	int col = 0;

	cout << "Enter n: ";
	cin >> n;

	cout << "Enter col: ";
	cin >> col;

	pattern(n, col);

	return 0;
}

/**********************************************************
** Function: pattern
** Description: prints the fractal
** Parameters: int n and int col
** Pre-Conditions: n is a positive odd number and col is a positive number
** Post-Conditions: the pattern is printed
**********************************************************/

void pattern(int n, int col) {
	if(n < 0)
		return;
	
	pattern(n - 2, col + 1);

	for(int i = 0; i < col; i++)
		cout << "  ";
	for(int i = 0; i < n; i++)
		cout << "* ";
	cout << endl;

	pattern(n - 2, col + 1);
}