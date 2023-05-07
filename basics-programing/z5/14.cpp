#include <iostream>

using namespace std;

double ai(int N, double x)
{
    double p = 1, res = 1;
    for ( int i = 1; i <= N; i++ )
    {
        for ( int j = 1; j <= i; j++ )
        {
            res*=x;
        }

        p *= res*2;

        res = 1;
    }
    return p;
}

int main ()
{
    setlocale (LC_ALL, ".1251");

    int N;
    double x;
    cout << "¬ведите количество циклов: ";
    cin >> N;
    cout << "¬ведите значение переменной 'x': ";
    cin >> x;

    if (N > 0)
        cout << "P = " << ai(N, x) << '\n';
    else
        cout << " оличество циклов не может быть отрицательным или равн€тьс€ нулю\n";

    return 0;
}
