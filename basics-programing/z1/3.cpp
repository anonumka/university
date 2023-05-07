#include <iostream>
#include <clocale>

using std::cin;
using std::cout;

int main() {
	setlocale(LC_ALL, ".1251");
	int d = 0;
	double x;
	cout << "Enter number: ";
	cin >> x;
	x -= int(x);
	d = x * 10.0;
	if (d < 0)
		d *= -1;
	cout << "Answer is " << d;
	return 0;
}