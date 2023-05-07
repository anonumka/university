#include <iostream>
#include <cstring>

using namespace std;

std::size_t join(char *s_out, std::size_t len, const char * const *s_in, std::size_t n_in, const char *sep)
{
    int c = 0;
    int sep_len = strlen(sep);
    for (size_t i = 0; i < n_in; i++)
    {
        for (size_t j = 0; j < strlen(s_in[i]) && c < len; j++, c++)
        {
            s_out[c] = s_in[i][j];
        }
        for (size_t k = 0; k < sep_len && c < len && i != n_in - 1; k++)
        {
            s_out[c] = sep[k];
            c++;
        }
    }
    s_out[c] = '\0';
    return c;
}

int main ()
{
    setlocale (LC_ALL, ".1251");

    int n_in;
    cout << "Enter amount string: ";
    cin >> n_in;

    char** s_in = new char* [n_in];
	for (size_t i = 0; i < n_in; i++)
	{
		s_in[i] = new char[255];
	}
	cin.get();
	cout << endl << "Enter array: " << endl;

	for (size_t i = 0; i < n_in; i++) 
	{
		cout << "Enter string #" << i + 1 << endl;
		cin.getline(s_in[i], 255);
	}

    char* sep = new char[255];
    cout << "Enter string-chars: ";
    cin.getline(sep, 255);

    int len;
    cout << "Enter lenght: ";
    cin >> len;
    char* s_out = new char[len];

    size_t ef_len = join(s_out, len, s_in, n_in, sep);

    cout << "\nChanged string: " << s_out << "\nEffective lenght of string: " << ef_len;

    return 0;
}