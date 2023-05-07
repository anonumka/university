//Вариант 9, задание на 100%
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double f(double x)
{
    return exp(x)-10*x;
}

int main ()
{

    setlocale (LC_ALL, ".1251");
    double a, b, h, x, y, res = 0;
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
        double y_tmp = 0;
        for (double tmp = a; tmp <= b; tmp+=h)
        {
            y_tmp = f(tmp);
            if ( ( abs(tmp) + abs(y_tmp) ) > res )
            {
                x = tmp;
                y = y_tmp;
                res = abs(tmp) + abs(y_tmp);
            }
        }
        for (a; a <= b; a+=h)
        {
            if ( a == x )
                cout << setw(10) << scientific << '(' << x << ", " << y << ')' << '*' << '\n';
            else
                cout << setw(10) << scientific << '(' << a << ", " << f(a) << ')' << '\n';
        }
    }
    return 0;
}