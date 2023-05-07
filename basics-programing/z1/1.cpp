#include <iostream>
#include <clocale>

using std::cin;
using std::cout;

int main() {
	setlocale(LC_ALL, ".1251");
	int a, b;
	cout << "Enter the first number: ";
	cin >> a; 
	cout << "Enter the second number: ";
	cin >> b;
	a += b;
	b = a - b;
	a -= b;
	cout << "The first number equal is " << a;
	cout << "The second number equal is " << b;
	return 0;
}