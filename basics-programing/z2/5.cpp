#include <iostream>

using namespace std;

int main()
{
    float a1,a2,b1,b2;
    string stop = "y";

    setlocale (LC_ALL, ".1251");

    while (stop == "y")
    {
        cout << "������� ������ ����������: ";
        cin >> a1 >> a2;
        cout << "������� ������ ����������: ";
        cin >> b1 >> b2;

        if ((a1 == b1) && (a2 == b2))
        {
            cout << "A ����� B";
        }

        else if ((a1 < a2) && (b1 < b2))
        {
            if (((a1 < b1) && (a2 < b2)) && (b1 < a2))
            {
                cout << "������ �����������";
            }
            else if (((a1 < b1) && (a2 < b2)) && (b1 > a2))
            {
                cout << "��� �����������";
            }
            else if ((a1 < b1) && (b2 < a2))
            {
                cout << "B ������ A";
            }
            else if ((b1 < a1) && (a2 < b2))
            {
                cout << "A ������ B";
            }
            else
            {
                cout << "��� �����������";
            }
        }

        else if ((a1 > a2) && (b1 > b2))
        {
            if (((a1 > b1) && (a2 > b2)) && (b1 > a2))
            {
                cout << "������ �����������";
            }
            else if (((a1 > b1) && (a2 > b2)) && (b1 < a2))
            {
                cout << "��� �����������";
            }
            else if ((a1 > b1) && (b2 > a2))
            {
                cout << "B ������ A";
            }
            else if ((b1 > a1) && (a2 > b2))
            {
                cout << "A ������ B";
            }
            else
            {
                cout << "��� �����������";
            }
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
        else
        {
            cout << "\n�� ����� �������� �����. ����������� y/n \n";
            cin >> stop;
        }
    }
}
