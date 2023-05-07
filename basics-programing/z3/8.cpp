#include <iostream>
#include <cmath>

using namespace std;

float dist(float x1, float y1, float x2, float y2)
{
    float x,y;
    x = (x1-x2)*(x1-x2);
    y = (y1-y2)*(y1-y2);
    return sqrt(x+y);
}

int main()
{
    setlocale(LC_ALL, ".1251");

    string cont = "y";

    while (cont != "n")
    {
        setlocale(LC_ALL, ".1251");
        float x1 = 0,y1 = 0,x2 = 0,y2 = 0;

        if (cont == "y")
        {
            cout << "������� �������� ���������� '�1': ";
            cin >> x1;
            cout << "������� �������� ���������� 'y1': ";
            cin >> y1;
            cout << "������� �������� ���������� '�2': ";
            cin >> x2;
            cout << "������� �������� ���������� 'y2': ";
            cin >> y2;
            cout.precision(4);
            cout << "d = " << dist(x1,y1,x2,y2);
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

