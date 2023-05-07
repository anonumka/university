// Вариант 9, задание на 100%
#include <iostream>
#include <cstring>

using namespace std;

char* space_adder(char* s1, char* s2)
{
    int c = 0;
    int len = strlen(s2);

    for (int i = 1; i < len; i++)
    {
        if (s1[i] >= 'A' && s1[i] <= 'Z')
        {
            s2[i + c] = ' ';
            c += 1;
        }
        else
            s2[i + c] = s1[i];
    }
    return s2;
}

int main()
{
    setlocale(LC_ALL, ".1251");
    char* s1 = new char[255];
    cout << "Enter string: ";
    cin.getline(s1, 255);
    bool begin = true;
    int j = strlen(s1);
    for (int i = 1; i < strlen(s1); i++)
    {
        if (s1[i] >= 'A' && s1[i] <= 'Z')
            j += 1;
    }

    char* s2 = new char[j];
    s2 = space_adder(s1, s2);
    cout << '\n' << "original string equal: " << s1 << endl;
    cout << "changed string equal: " << s2 << endl;

    return 0;
}
