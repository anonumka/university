#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    float a, b, c, D, x1, x2;
    string stop = "y";

    setlocale (LC_ALL, ".1251");

    while (stop == "y")
    {
        cout << "������� �������� 'a': ";
        cin >> a;
        cout << "������� �������� 'b': ";
        cin >> b;
        cout << "������� �������� 'c': ";
        cin >> c;

        D = b*b - 4*a*c;
        if (D > 0)
        {
            x1 = (-b+sqrt(D)) / (2*a);
            x2 = (-b-sqrt(D)) / (2*a);
            cout << "�����: �1 = " << x1 << ", x2 = " << x2;
        }
        else if (D == 0)
        {
            x1 = -b/(2*a);
            cout << "������ ��������� ����� " << x1;
        }
        else
        {
            cout << "������ ��� ��������� ���.";
        }

        cout << "\n����������? y/n \n";
        cin >> stop;
        if ((stop == "n") || (stop == "no"))
        {
            stop == "n";
        }
        else if ((stop == "y") || (stop == "yes"))
        {
            stop == "y";
        }
    }
}
