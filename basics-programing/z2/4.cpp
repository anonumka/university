#include <iostream>

using namespace std;

int main()
{
    float a,b,c,d,x;
    string stop = "y";

    setlocale (LC_ALL, ".1251");

    while (stop == "y")
    {
        cout << "Введите значение x: ";
        cin >> x;
        cout << "Введите первый промежуток: ";
        cin >> a >> b;
        cout << "Введите второй промежуток: ";
        cin >> c >> d;

        if (((abs(a) < x) && (abs(b) > x)) || ((abs(a) > x) && (abs(b) < x)))
        {
            cout << "Принадлежит";
        }
        else if (((abs(c) < x) && (abs(d) > x)) || ((abs(c) > x) && (abs(d) < x)))
        {
            cout << "Принадлежит";
        }
        else
        {
            cout << "Не принадлежит";
        }

        cout << "\nПродолжить? y/n \n";
        cin >> stop;
        if ((stop == "n") || (stop == "no"))
        {
            stop == "n";
        }
        else if ((stop == "y") || (stop == "yes"))
        {
            stop == "y";
        }
    }
}
