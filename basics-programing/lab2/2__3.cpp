//Вариант 3 Работа на 100%
#include <iostream>
#include <clocale>

using std::cin;
using std::cout;

int main() {
	setlocale(LC_ALL, ".1251");
	float v1, v2, t1, t2;
	cout << "Enter the volume of the first water: ";
	cin >> v1;
	cout << "Enter the temperature of the first water: ";
	cin >> t1;
	cout << "Enter the volume of the second water: ";
	cin >> v2;
	cout << "Enter the temperature of the second water: ";
	cin >> t2;
	if ((v1 <= 0) || (v2 <= 0))
		cout << "Error!\nThe volume of water can't be negative or zero.";
	else if ((t1 > 100) || (t2 > 100))
		cout << "Error!\nThe temperature of water can't be more than 100 degrees.";
	else
		cout << "The volume of water equal is " << v1 + v2 << "\nThe temperature of mixture equal is " << (v1 * t1 + v2 * t2) / (v1 + v2);
	return 0;
}