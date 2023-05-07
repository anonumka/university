#include <iostream>

using namespace std;

int find_most_frequent(int a, int b, int c, int d)
{
    int sum = 0;
    sum = a+b+c+d;
    if (sum == 2)
    {
        return -1;
    }
    else if (sum > 2)
        return 1;
    else if (sum < 2)
        return 0;
}

int main()
{
    setlocale(LC_ALL, ".1251");

    string cont = "y";
    while (cont != "n")
    {
        if (cont == "y")
        {
            int a = 0, b = 0,c = 0, d = 0;
            cout << "Требуется вводить числа 0 или 1\n";
            cout << "Введите значение переменной 'a': ";
            cin >> a;
            if (( a != 0 ) && ( a != 1 )) {
                cout << "Введено некорректное число.";
                return 0;
            }
            cout << "Введите значение переменной 'b': ";
            cin >> b;
            if (( b != 0 ) && ( b != 1 )) {
                cout << "Введено некорректное число.";
                return 0;
            }
            cout << "Введите значение переменной 'c': ";
            cin >> c;
            if (( c != 0 ) && ( c != 1 )) {
                cout << "Введено некорректное число.";
                return 0;
            }
            cout << "Введите значение переменной 'd': ";
            cin >> d;
            if (( d != 0 ) && ( d != 1 )) {
                cout << "Введено некорректное число.";
                return 0;
            }
            cout << "Чаще всего встречается: " << find_most_frequent(a,b,c,d);
        }

        cout << "\nХотите продолжить? y/n \n";
        cin >> cont;
        if (cont == "n")
            break;
        else if (cont != "y")
            cout << "\nНеверно введена буква: ";
    }
    return 0;
}
