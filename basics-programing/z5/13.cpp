#include <iostream>

using namespace std;

double ai(int N)
{
    double s = 0;
    for ( double i = 1; i <= N; i++ )
    {
        s += ( i / ( i+1 ) );
    }
    return s;
}

int main ()
{
    setlocale (LC_ALL, ".1251");

    int N;
    cout << "¬ведите количество циклов: ";
    cin >> N;

    if ( N > 0 )
        cout << "S = " << ai(N) << '\n';
    else
        cout << " оличество циклов не может быть отрицательным или равн€тьс€ нулю\n";

    return 0;
}
