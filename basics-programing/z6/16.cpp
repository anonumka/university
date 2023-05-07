#include <iostream>
#include <iomanip>

using namespace std;

double f (double x)
{
    return 2*x*x - 3*x + 1;
}

int main ()
{
    setlocale (LC_ALL, ".1251");

    double a, b, s;

    cout << "Введите начало отрезка: ";
    cin >> a;
    cout << "Введите конец отрезка: ";
    cin >> b;
    cout << "Введите размер шага: ";
    cin >> s;

    if (a > b)
        cout << "Точка начала не может быть больше, чем точка конца";
    else if ( s+a > b )
        cout << "Сумма шага и начала не может быть больше, чем точка конца";
    else
    {
        for (a; a < b; a+=s)
        {
            cout << setw(10) << fixed << a << ' ';
            cout << setw(15) << scientific << f(a) << '\n';
        }

        return 0;
    }

}
