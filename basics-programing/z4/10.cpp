#include <iostream>

using namespace std;

int main ()
{
    int x;
    int x_max = -2147483648;

    setlocale (LC_ALL, ".1251");

    cout << "������� 'x': ";
    cin >> x;

    string cont = "y";
    while (cont != "n")
    {
        while (x > x_max)
        {
            cout << x << "\n";
            x_max = x;
            cout << "������� ��������� �������� 'x': ";
            cin >> x;
            if (x < x_max)
                cout << "�������� ��������� ������, ��� ����������\n";

        }

        x = 0; x_max = 0;

        cout << "\n������ ����������? y/n \n";
        cin >> cont;
        if (cont == "n")
            break;
        else if (cont != "y")
            cout << "\n������� ������� �����: ";
    }


    return 0;
}
