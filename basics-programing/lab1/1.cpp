#include <iostream>
#include <clocale>
#include <cstdio>

using std::cout;

int main() {
	setlocale(LC_ALL, ".1251");
	cout << "Hello world!\n";
	printf("Hello world!\n");
	cout << "Привет Мир!\n";
	printf("Привет Мир!");
	return 0;
}