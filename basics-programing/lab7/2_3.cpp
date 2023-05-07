#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double f(double x)
{
    return cos(2*x)*x+2*x-1;
}

int main ()
{

    setlocale (LC_ALL, ".1251");

    double a, b, h, res, res_prev;

    cout << "Введите начало отрезка: ";
    cin >> a;
    cout << "Введите конец отрезка: ";
    cin >> b;
    cout << "Введите ширину шага: ";
    cin >> h;

    if (b < a)
        cout << "Конец отрезка меньше, чем начало отрезка";
    else if (h <= 0)
        cout << "Длина шага не может быть отрицательным или положительным";
    else if (a + h > b)
        cout << "Сумма первого шага и начала отрезка не может быть больше, чем конец отрезка";
    else
    {
        res = f(a+h);
        res_prev = f(a);
        a+=h;
        for (a; a<=b; a+=h)
            {
                if ( ( res_prev < res ) && ( f(a+h) < res ) )
                    cout << setw(10) << scientific << res << '*' << '\n';
                else
                    cout << setw(10) << scientific << res << '\n';
                res_prev = res;
                res = f(a+h);
            }
    }

    return 0;

}

