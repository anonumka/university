#include <iostream>

using namespace std;

int ai(int N)
{
    int s = 0, tmp_i = 1;
    for ( int i = 1; i <= N; i++ )
    {
        tmp_i *= (-1);

        if ( tmp_i < 0 )
            s -= ( i );
        else
            s += ( i );

    }
    return s;
}

int main ()
{
    setlocale (LC_ALL, ".1251");

    int N;
    cout << "¬ведите количество циклов: ";
    cin >> N;

    if (N > 0)
        cout << "S = " << ai(N) << '\n';
    else
        cout << " оличество циклов не может быть отрицательным или равн€тьс€ нулю\n";

    return 0;
}

