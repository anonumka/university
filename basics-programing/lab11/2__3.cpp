// Вариант 3, задание на 100%
#include <iostream>
#include <cstring>

using namespace std;

void* dots(char* s1, char* s2)
{
    int c = 0;
    int len = strlen(s1);


    for (int i = 0; i < len; i++)
    {
        if (s1[i] != '.')
        {
            s2[i+c] = s1[i];
        }

        else
        {
            s2[i+c] = '.';
            s2[i+c+1] = '.';
            s2[i+c+2] = '.';
            c += 2;
        }
    }
}

int main ()
{
    setlocale (LC_ALL, ".1251");

    char* s1 = new char[255];
    cout << "Enter string: ";
    cin.getline(s1, 255);

    int j = 0;
    for (int i = 0; i < strlen(s1); i++)
    {
        if (s1[i] == '.')
            j+=3;
        else
            j++;
    }

    char* s2 = new char[j];

    dots(s1, s2);
    cout << '\n' << "original string equal: " << s1 << endl;
    cout << "changed string equal: " << s2 << endl;

    return 0;
}
