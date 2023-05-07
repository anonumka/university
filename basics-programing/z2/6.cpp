#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    float a, b, c, D, x1, x2;
    string stop = "y";

    setlocale (LC_ALL, ".1251");

    while (stop == "y")
    {
        cout << "Введите значение 'a': ";
        cin >> a;
        cout << "Введите значение 'b': ";
        cin >> b;
        cout << "Введите значение 'c': ";
        cin >> c;

        D = b*b - 4*a*c;
        if (D > 0)
        {
            x1 = (-b+sqrt(D)) / (2*a);
            x2 = (-b-sqrt(D)) / (2*a);
            cout << "Корни: х1 = " << x1 << ", x2 = " << x2;
        }
        else if (D == 0)
        {
            x1 = -b/(2*a);
            cout << "Корень выражения равен " << x1;
        }
        else
        {
            cout << "Корней для выражения нет.";
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
