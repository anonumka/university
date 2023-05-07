#include <iostream>
#include <clocale>

using std::cin;
using std::cout;

int main() {
	setlocale(LC_ALL, ".1251");
	int num_people, num_seats, num_buses = 0, num_free_seats = 0;
	cout << "Enter the count people: ";
	cin >> num_people;
	cout << "Enter the count places: ";
	cin >> num_seats;
	num_buses = ((num_people - 1) / num_seats + 1);
	num_free_seats = num_buses * num_seats - num_people;
	cout << "The number of buses need is " << num_buses;
	cout << "\nThe number of free seats is " << num_free_seats;
	return 0;
}