#include <iostream>

using namespace std;

float min_or_max(float a, float b, float c)
{
    if (a > 0.5) if ( b > c ) return b; else return c;
    else if (b > c) return c; else return b;
}

int main()
{
    setlocale(LC_ALL, ".1251");

    string cont = "y";

    while (cont != "n")
    {
        setlocale(LC_ALL, ".1251");
        if (cont == "y")
        {
            float a,b,c;
            cout << "������� ���������� 'a': ";
            cin >> a;
            cout << "������� ���������� 'b': ";
            cin >> b;
            cout << "������� ���������� 'c': ";
            cin >> c;
            cout << min_or_max(a,b,c);
        }

        cout << "\n������ ����������? y/n \n";
        cin >> cont;
        if (cont == "n")
            break;
        else if (cont != "y")
            cout << "\n������� ������� �����: ";
    }

    return 0;
}


