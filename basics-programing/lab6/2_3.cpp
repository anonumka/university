#include <iostream>
#include <cmath>

using namespace std;

double f (double x, double d)
{
    int8_t sign = 1;

    int i = 1;
    double res, result = 0, pow = x;
    unsigned long int fact = 1;

    while (true)
    {
        if (i != 1)
        {
            pow = pow * x * x;
            fact = fact * i * (i - 1);
            res = sign * (pow / fact);
        }

        else
            result = pow / fact;


        if ( fabs(res) >= d )
        {
            result += res;
            sign *= -1;
            i += 2;
        }

        else
        {
            return result;
        }

    }
}

int main ()
{
    setlocale (LC_ALL, ".1251");
    double x, d, res;

    cout << "¬ведите 'x': ";
    cin >> x;
    cout << "¬ведите 'd': ";
    cin >> d;

    if ( d < 0 )
        cout << "d не может быть отрицательным";
    else
        res = f(x, d);
        cout << res << endl;
        cout << sin( res ) << endl;
        cout << res - sin(res);

    return 0;
}

