#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double f (double x)
{
    static const double pi = acos(-1);
    double res = 0;

    res = sin(pi*x)*sin(pi*x);

    return res;
}

int main ()
{

    setlocale (LC_ALL, ".1251");

    double a, b, s, u = 0, fun, scale;

    cout << "Введите начало отрезка: ";
    cin >> a;
    cout << "Введите конец отрезка: ";
    cin >> b;
    cout << "Введите размер шага: ";
    cin >> s;
    cout << "Введите масштаб: ";
    cin >> scale;


    if (scale <= 0)
        cout << "Масштаб не может быть отрицательным";
    else if (b < a)
        cout << "Начало не может быть больше конца";
    else
    for (a; a < b; a+=s)
    {
        fun = f(a);
        cout << setw(2+int(fun*scale)) << "$(" << a << ", " << fun << ')' << '\n';
    }

    return 0;

}

