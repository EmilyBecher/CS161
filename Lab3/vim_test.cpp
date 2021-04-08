#include <iostream>

using namespace std;

int main() {

    bool like = 0;

    cout << "Do you like vi as an editor?(0-1): ";
	cin >> like;

    if (like) 
	cout << "You love vi!" << endl;
    else
	cout << "You hate vi!" << endl;

    return 0;
}
