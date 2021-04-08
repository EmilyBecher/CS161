#include <iostream>

using namespace std;

int fib_iter(int n);
int fib_recurs(int n);

int main() {
	int n = 0;

	cout << "Enter a positive integer: ";
	cin >> n;

	cout << "The " << n << " number in the fibonacci series is " << fib_iter(n) << endl;
	cout << "The " << n << " number in the fibonacci series is " << fib_recurs(n) << endl;

	return 0;
}

int fib_iter(int n) {
	int Fn = 0;
	int a = 0;
	int b = 1;
	for(int i = 0; i < n - 1; i++) {
		Fn = a + b;
		a = b;
		b = Fn;
	}
	if(n == 1)
		return 1;
	return Fn;
}

int fib_recurs(int n) {
	if(n == 0)
		return 0;
	if(n == 1)
		return 1;
	return fib_recurs(n - 1) + fib_recurs(n - 2);
}