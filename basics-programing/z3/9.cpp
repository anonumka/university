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
            cout << "Введите переменную 'a': ";
            cin >> a;
            cout << "Введите переменную 'b': ";
            cin >> b;
            cout << "Введите переменную 'c': ";
            cin >> c;
            cout << min_or_max(a,b,c);
        }

        cout << "\nХотите продолжить? y/n \n";
        cin >> cont;
        if (cont == "n")
            break;
        else if (cont != "y")
            cout << "\nНеверно введена буква: ";
    }

    return 0;
}


