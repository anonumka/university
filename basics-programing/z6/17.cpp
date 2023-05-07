#include <iostream>
#include <iomanip>

using namespace std;

double f (double x)
{
    return 5*x+2;
}

int main ()
{
    setlocale (LC_ALL, ".1251");

    double a, b, s, tmp_a;
    cout << "Введите начало диапазона чисел 'a': ";
    cin >> a;
    cout << "Введите конец диапазона чисел 'b': ";
    cin >> b;
    cout << "Введите длину шага 's': ";
    cin >> s;

    if (a > b)
        cout << "Точка начала не может быть больше, чем точка конца";
    else if ( s+a > b )
        cout << "Сумма шага и начала не может быть больше, чем точка конца";
    else
    {
        tmp_a = a;

        for (a; a < b; a+=s)
        {
            cout << setw(15) << setfill(' ') << fixed << setprecision(3) << a << " ";
        }

        a = tmp_a;

        cout << '\n';

        for (a; a < b; a+=s)
        {
            cout << setw(15) << scientific << setprecision(5) << f(a) << " ";
        }
    }

    return 0;
}

