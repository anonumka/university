#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "������� ����������� �����: "
    cin >> n;

    if (n <= 0)
        cout << "������� ������������� �����";
    else
    {
        for (int i = 1; i <= n; i++)
        {
           cout << i << '\n';
        }

        cout << '\n';

        int i = 0;

        while (i != n)
        {
            cout << i+1 << '\n';
            i++;
        }

        cout << '\n';
        i = 0;

        while (true == true)
        {
            cout << i+1 << '\n';
            i++;
            if ( i == n )
                break;
        }
    }

    return 0;
}
