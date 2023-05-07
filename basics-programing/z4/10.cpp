#include <iostream>

using namespace std;

int main ()
{
    int x;
    int x_max = -2147483648;

    setlocale (LC_ALL, ".1251");

    cout << "Введите 'x': ";
    cin >> x;

    string cont = "y";
    while (cont != "n")
    {
        while (x > x_max)
        {
            cout << x << "\n";
            x_max = x;
            cout << "Введите следующее значение 'x': ";
            cin >> x;
            if (x < x_max)
                cout << "Значение оказалось меньше, чем предыдущее\n";

        }

        x = 0; x_max = 0;

        cout << "\nХотите продолжить? y/n \n";
        cin >> cont;
        if (cont == "n")
            break;
        else if (cont != "y")
            cout << "\nНеверно введена буква: ";
    }


    return 0;
}
