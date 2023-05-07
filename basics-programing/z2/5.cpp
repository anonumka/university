#include <iostream>

using namespace std;

int main()
{
    float a1,a2,b1,b2;
    string stop = "y";

    setlocale (LC_ALL, ".1251");

    while (stop == "y")
    {
        cout << "Введите первый промежуток: ";
        cin >> a1 >> a2;
        cout << "Введите второй промежуток: ";
        cin >> b1 >> b2;

        if ((a1 == b1) && (a2 == b2))
        {
            cout << "A равно B";
        }

        else if ((a1 < a2) && (b1 < b2))
        {
            if (((a1 < b1) && (a2 < b2)) && (b1 < a2))
            {
                cout << "Другое пересечение";
            }
            else if (((a1 < b1) && (a2 < b2)) && (b1 > a2))
            {
                cout << "Нет пересечений";
            }
            else if ((a1 < b1) && (b2 < a2))
            {
                cout << "B внутри A";
            }
            else if ((b1 < a1) && (a2 < b2))
            {
                cout << "A внутри B";
            }
            else
            {
                cout << "Нет пересечений";
            }
        }

        else if ((a1 > a2) && (b1 > b2))
        {
            if (((a1 > b1) && (a2 > b2)) && (b1 > a2))
            {
                cout << "Другое пересечение";
            }
            else if (((a1 > b1) && (a2 > b2)) && (b1 < a2))
            {
                cout << "Нет пересечений";
            }
            else if ((a1 > b1) && (b2 > a2))
            {
                cout << "B внутри A";
            }
            else if ((b1 > a1) && (a2 > b2))
            {
                cout << "A внутри B";
            }
            else
            {
                cout << "Нет пересечений";
            }
        }

        cout << "\nПродолжить? y/n \n";
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
            cout << "\nВы ввели неверный ответ. Используйте y/n \n";
            cin >> stop;
        }
    }
}
