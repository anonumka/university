#include <iostream>
#include <cstring>

using namespace std;

void rstrip(char *s, const char *chars)
{
    bool cont = true;

    do
    {
        for (int i = strlen(s) - 1; i >= 0; i--)
        {
            cont = false;
            for (int j = 0; j < strlen(chars); j++)
            {
                if (s[i] == chars[j])
                {
                    s[i] = 0;
                    cont = true;
                }

            }
        }
    } while (cont);

}

int main ()
{
    setlocale (LC_ALL, ".1251");

    char* s = new char[255];
    cout << "Enter string: ";
    cin.getline(s, 255);
    char* chars = new char[255];
    cout << "Enter symbols: ";
    cin.getline(chars, 255);

    rstrip(s, chars);
    cout << '\n' << "String equal: " << s << endl;

    return 0;
}
