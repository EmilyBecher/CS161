#include <iostream>
#include <cstdlib>

using namespace std;

void towers(int disks, int **b, int from, int to, int spar, int c);
void print_board(int **b, int c);

int main(int argc, char** argv) {
	int disks = 0;

	//cout << "Enter a positive number: ";
	//cin >> disks;

	disks = atoi(argv[1]);

	int **b = NULL;
	b = new int*[disks];
	for(int i = 0; i < disks; i++){
		b[i] = new int[3];
		b[i][0] = i + 1;
		b[i][1] = 0;
		b[i][2] = 0;
	}

	print_board(b, disks);
	towers(disks, b, 1, 2, 3, disks);

	for(int i = 0; i < disks; i++)
		delete [] b[i];
	delete [] b;

	return 0;
}

void towers(int disks, int **b, int from, int to, int spare, int c){
	int temp = 0;
	if(disks >= 1) {
		towers(disks - 1, b, from, spare, to, c);
		//move disk
		for(int i = 0; i < c; i++){
			if(b[i][from - 1] > 0) {
				temp = b[i][from - 1];
				b[i][from - 1] = 0;
				break;
			}
		}
		for(int i = c - 1; i >= 0; i--){
			if(b[i][to - 1] == 0) {
				b[i][to - 1] = temp;
				break;
			}
		}
		print_board(b, c);
		towers(disks - 1, b, spare, to, from, c);
	}
}

void print_board(int **b, int c){
	for(int i = 0; i < c; i++){
		for(int j = 0; j < 3; j++){
			cout << b[i][j] << " ";
		}
		cout << endl;
	}
	cout << "---------" << endl;
}