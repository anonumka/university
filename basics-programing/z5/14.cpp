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
    cout << "������� ���������� ������: ";
    cin >> N;
    cout << "������� �������� ���������� 'x': ";
    cin >> x;

    if (N > 0)
        cout << "P = " << ai(N, x) << '\n';
    else
        cout << "���������� ������ �� ����� ���� ������������� ��� ��������� ����\n";

    return 0;
}
