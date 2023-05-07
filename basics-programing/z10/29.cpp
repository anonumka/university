#include <iostream>
#include <cstring>

using namespace std;

void strip(char *s, const char *chars)
{
    bool cont = true;
    for (int i = strlen(s) - 1; i >= 0; i--)
	{
		cont = false;
		for (int j = 0; j < strlen(chars); j++)
		{
			if (s[i] == chars[j])
			{
				s[i] = 0;
				cont = true;
				break;
			}
		}
		if (!cont)
			break;
	}
    for (int i = 0; i < strlen(s); i++)
	{
		cont = false;
		for (int j = 0; j < strlen(chars); j++)
		{
			if (s[i] == chars[j])
			{
				for (int k = 0; k < strlen(s); k++)
					s[k] = s[k + 1];
				cont = true;
				i = -1;
				break;
			}
		}
		if (!cont)
			break;
	}
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

    strip(s, chars);
    cout << '\n' << "String equal: " << s << endl;

    return 0;
}