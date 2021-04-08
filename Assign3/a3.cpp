/**********************************************************
 ** Program: a3.cpp
 ** Author: Emily Becher
 **	Date: 2/14/21
 ** Inputs: length of trip, departure and arrival times, expenses for 
 	meals, travel, hotel, airfare, events
 ** Outputs: Instructions, expenses, reimbursements, and excess costs
 *********************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

void get_double(double &num, double min, double max, int dec_ap, string prompt);
void get_bool(bool &play, string prompt);
void update_total(double &expens, double &reimbs, double add_expens, double add_reimb);
void daily_fees(int days, int start, double &expens, double &reimbs, double daily_reimb, string prompt);
void taxi(int days, double &expens, double &reimbs);
void meal_fees(int days, double depart, double arrive, double &expens, double &reimbs);
void depart_fees(double depart, double &expens, double &reimbs);
void arrive_fees(double arrive, double &expens, double &reimbs);
void meal_reimb(int max_reimb, double cost, double &reimbs);
int ati(char c);
int atf(char c);
double stod(string str, int dec_ap);

int main() {
	/* Variables */
	bool play = true;
	double days = 0;
	double depart = 0;
	double arrive = 0;
	double airfare = 0;
	double event = 0;

	while(play) {
		/*Variables*/
		double expens = 0;
		double reimbs = 0;

		/*Opening Message */
		cout << endl << "This program calculates the expenses, reimbursements, " <<
			endl << "and excess costs of a business trip." << endl << endl;

		/* Get trip details */
		get_double(days, 1, 365, 1, "Enter the number of days in your trip: ");
		get_double(depart, 0, 23, 1, "Enter the hour of your departure time(0-23): ");
		get_double(arrive, 0, 23, 1, "Enter the hour of your return time(0-23): ");

		/*Get trip fees */
		get_double(airfare, 0, 1e100, 0, "Enter your airfare costs: $");
		get_double(event, 0, 1e100, 0, "Enter your event fees: $");

		update_total(expens, reimbs, airfare + event, airfare + event);

		taxi(days, expens, reimbs);

		daily_fees(days - 1, 1, expens, reimbs, 90, "Enter you hotel fees for each day");
		meal_fees(days, depart, arrive, expens, reimbs);

		/* Output */
		cout << endl << "Your total expenses are $" << expens << endl;
		cout << "Your total reimbursements are $" << reimbs << endl;
		cout << "Your personal costs are $" << expens - reimbs << endl;

		/* Again? */
		get_bool(play, "Would you like to play again? ");
	}

	return 0;
}


/**********************************************************
 ** Function: get_double
 ** Parameters: &num, min, max, dec_ap, prompt
 ** Pre-Conditions: double or int variable to fill
 ** Post-Conditions: fills variable with double within entered constraints
 	input of "." return 0
 ** Lines: 20
 *********************************************************/

void get_double(double &num, double min, double max, int dec_ap, string prompt) {
	string str;
	bool bad = 1;
	cout << prompt;
	while(bad) {
		getline(cin, str);
		for(int i = 0; i < str.length(); i++) {
			/* Checks for invalid characters */
			if(ati(str[i]) < 46 || ati(str[i]) > 57 || ati(str[i]) == 47) {
				cout << "Invalid input, try again: ";
				break;
			}
			/* All characters are valid */
			else if(i == str.length() - 1) {
				num = stod(str, dec_ap);
				/* Too many decimal points*/
				if(num == -1) { /* -1 is returned when more decimal points than expected appear */
					cout << "Invalid input, try again: ";
					break;
				}
				else if(num > max) {
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
 ** Function: get_bool
 ** Parameters: &play, prompt
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
 ** Function: update_total
 ** Parameters: &expens, &reimbs, add_expens, add_reimb
 ** Pre-Conditions: valid arguments
 ** Post-Conditions: update expens and reimbs
 ** Lines: 2
 *********************************************************/

void update_total(double &expens, double &reimbs, double add_expens, double add_reimb) {
	expens += add_expens;
	reimbs += add_reimb;
}

/**********************************************************
 ** Function: daily_fees
 ** Parameters: days, start, &expens, &reimbs, daily_reimb, prompt
 ** Pre-Conditions: start < days
 ** Post-Conditions: update expens and reimbs after looping through days
 ** Lines: 9
 *********************************************************/

void daily_fees(int days, int start, double &expens, double &reimbs, double daily_reimb, string prompt) {
	double fee = 0;
	cout << endl << prompt << endl;
	for(int i = start; i <= days; i++) {
		cout << "Day " << i;
		get_double(fee, 0, 1e100, 0, ": $");
		expens += fee;
		if(fee < daily_reimb) {
			reimbs += fee;
		}
		else {
			reimbs += daily_reimb;
		}
	}
}

/**********************************************************
 ** Function: taxi
 ** Parameters: days, &expens, &reimbs
 ** Pre-Conditions: valid arguments
 ** Post-Conditions: updates expens and reimbs with either taxi or rental inputs
 ** Lines: 7
 *********************************************************/

void taxi(int days, double &expens, double &reimbs) {
	bool taxi;
	double rental = 0;
	get_bool(taxi, "Did you travel by taxi during your trip? ");
	/* Taxi fees*/
	if(taxi){
		daily_fees(days, 1, expens, reimbs, 10, "Enter your taxi fees for each day");
	}
	/* Rental car fees*/
	else {
		get_double(rental, 0, 1e100, 0, "Enter your rental and gas fees: $");
		update_total(expens, reimbs, rental, rental);
		daily_fees(days, 1, expens, reimbs, 6, "Enter your parking fees for each day");
	}
}

/**********************************************************
 ** Function: meal_fees
 ** Parameters: days, depart, arrive, &expens, &reimbs
 ** Pre-Conditions: days > 0
 ** Post-Conditions: updates expens and reimbs with all meal fees
 ** Lines: 8
 *********************************************************/

void meal_fees(int days, double depart, double arrive, double &expens, double &reimbs) {
	cout << endl << "Departure day meal fees" << endl;
	depart_fees(depart, expens, reimbs);
	if(days > 2) { /* Days without departure or arrival */
		daily_fees(days - 1, 2, expens, reimbs, 9, "Enter your breakfast costs for each day");
		daily_fees(days - 1, 2, expens, reimbs, 12, "Enter your lunch costs for each day");
		daily_fees(days - 1, 2, expens, reimbs, 16, "Enter your dinner costs for each day");
	}
	cout << endl << "Return day meal fees" << endl;
	arrive_fees(arrive, expens, reimbs);
}

/**********************************************************
 ** Function: depart_fees
 ** Parameters: depart, &expens, &reimbs
 ** Pre-Conditions: valid arguments
 ** Post-Conditions: update expens and reimbs with departure day meal fees
 ** Lines: 12
 *********************************************************/

void depart_fees(double depart, double &expens, double &reimbs) {
	double meal = 0;
	if(depart < 7) {
		get_double(meal, 0, 1e100, 0, "Enter your breakfast cost: $");
		expens += meal;
		meal_reimb(9, meal, reimbs);
	}
	if(depart < 12) {
		get_double(meal, 0, 1e100, 0, "Enter your lunch cost: $");
		expens += meal;
		meal_reimb(12, meal, reimbs);
	}
	if(depart < 18) {
		get_double(meal, 0, 1e100, 0, "Enter your dinner cost: $");
		expens += meal;
		meal_reimb(16, meal, reimbs);
	}
}

/**********************************************************
 ** Function: arrive_fees
 ** Parameters: arrive, &expens, &reimbs
 ** Pre-Conditions: valid arguments
 ** Post-Conditions: update expens and reimbs with return day meal fees
 ** Lines: 12
 *********************************************************/

void arrive_fees(double arrive, double &expens, double &reimbs) {
	double meal = 0;
	if(arrive > 8) {
		get_double(meal, 0, 1e100, 0, "Enter your breakfast cost: $");
		expens += meal;
		meal_reimb(9, meal, reimbs);
	}
	if(arrive > 13) {
		get_double(meal, 0, 1e100, 0, "Enter your lunch cost: $");
		expens += meal;
		meal_reimb(12, meal, reimbs);
	}
	if(arrive > 19) {
		get_double(meal, 0, 1e100, 0, "Enter your dinner cost: $");
		expens += meal;
		meal_reimb(16, meal, reimbs);
	}
}

/**********************************************************
 ** Function: meal_reimb
 ** Parameters: max_reimb, cost, &reimbs
 ** Pre-Conditions: valid arguments
 ** Post-Conditions: update reimbs with meal reimbursements
 ** Lines: 4
 *********************************************************/

void meal_reimb(int max_reimb, double cost, double &reimbs) {
	if(cost < max_reimb) {
		reimbs += cost;
	}
	else {
		reimbs += max_reimb;
	}
}

/**********************************************************
 ** Function: ati
 ** Parameters: c
 ** Pre-Conditions: valid arguments
 ** Post-Conditions: change char c to ascii value
 ** Lines: 1
 *********************************************************/

int ati(char c) {
	return c;
}

/**********************************************************
 ** Function: atf
 ** Parameters: c
 ** Pre-Conditions: assumes char is a number
 ** Post-Conditions: switches data type from char to int
 ** Lines: 31 (one switch statement and any simplification wouldn't
 	help readability or function)
 *********************************************************/

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
 ** Parameters: str, dec_ap
 ** Pre-Conditions: str contains only characters 0-9 or .
 ** Post-Conditions: switches data type from str to double, input of "." returns 0
 ** Lines: 12
 *********************************************************/

double stod(string str, int dec_ap) {
	bool dec = 0;
	int dec_pl = 1;
	double num = 0;
	for(int i = 0; i < str.length(); i++) {
		if(ati(str[i]) == 46) {
			dec = 1;
			dec_ap++;
			if(dec_ap > 1){
				return -1;
			}
		}
		else if(dec) {
			num += (atf(str[i]) / pow(10,dec_pl));
			dec_pl++;
		}
		else {
			num = (num * 10) + atf(str[i]);
		}
	}
	return num;
}