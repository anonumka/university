#include <iostream>

using namespace std;

int main()
{
    float a,b,c,d,x;
    string stop = "y";

    setlocale (LC_ALL, ".1251");

    while (stop == "y")
    {
        cout << "������� �������� x: ";
        cin >> x;
        cout << "������� ������ ����������: ";
        cin >> a >> b;
        cout << "������� ������ ����������: ";
        cin >> c >> d;

        if (((abs(a) < x) && (abs(b) > x)) || ((abs(a) > x) && (abs(b) < x)))
        {
            cout << "�����������";
        }
        else if (((abs(c) < x) && (abs(d) > x)) || ((abs(c) > x) && (abs(d) < x)))
        {
            cout << "�����������";
        }
        else
        {
            cout << "�� �����������";
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
