/*
THERE ARE BUGS IN THE CODE
*/
#include <iostream>

using namespace std;

int main(){

	int x = 3, y;

	y = x;
	cout << "x is set to: " << y << endl;

	//while again is true, prompt user for y value,
	//and output if it's >, < or = to x
	bool again = true;
	while(again){
	    	cout << "Please enter a number for y: ";
		cin >> y;
		if(x > y) {
			cout << "X is greater than Y" << endl;
			cout << "would you like to input another number? ";
			cin >> again;
		}
		else if(x < y) {
			cout << "X is less than Y" << endl;
			cout << "would you like to input another number? ";
			cin >> again;
		}
		else{
			cout << "X is equal to Y" << endl;
			cout << "would you like to input another number? ";
			cin >> again;
		}
	}

	//for loop, print out the value of x for 10 times
	for(x = 0; x < 10; x++)
		cout << x << endl;
	
	//compute and output factorial for num
	int num = 0;
	cout << "What number would you like to find the factorial for? ";
	cin >> num;
	for(int x = num; x > 1; x--)
		num *= (x -1);
	cout << num << endl;

	//conditionals
	char myAnswer;
	cout << "Are you enjoying cs161? (y or n) ";
	cin >> myAnswer;
	if(myAnswer == 'y')
		cout << "YAY" << endl;
	else
		cout << "YOU WILL SOON!" << endl;

	return 0;
}
