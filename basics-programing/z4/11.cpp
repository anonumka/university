#include <iostream>

using namespace std;

void print_diag(int s)
{
    for (int i = 0; i < s; i++)
    {
        for (int j = 0; j < i; j++)
        {
            cout << " ";
        }
        cout << "*\n";
    }
}

int main ()
{
    setlocale(LC_ALL, ".1251");

    int64_t s = 0;
    cout << "������� ���������� ���������: ";
    cin >> s;

    if (s > 0)
        print_diag(s);
    else
        cout << "��������� ����� ������ ��� ����� ����.";

    return 0;
}
