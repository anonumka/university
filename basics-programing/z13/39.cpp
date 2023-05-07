#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void wrap_text(std::istream &ist, std::ostream &ost, int max_line_len)
{
    char buf[255];
    int c = 1;
    int len;
    while (ist.getline(buf, 255))
    {
        len = strlen(buf);
        for (int i = 0; i < len; i++)
        {
            if ( c-1 == max_line_len )
            {
                ost << endl;
                c = 1;
            }
            ost << buf[i]; 
            c++;
        }
        ost << endl;
        c = 1;
    }
}

int main ()
{
    ifstream ist("in3.txt", ios::in);
    ofstream ost("out3.txt", ios::out);

    if (!ist.is_open())
    {
        cout << "Read error!";
        return 0;
    }

    int len;
    cout << "Enter max line len: ";
    cin >> len;
    if (len <= 0)
    {
        cout << "Lenght can't be negative or zero!";
        return 0;
    }

    wrap_text(ist, ost, len);
    cout << "The program has finished executing.";
    ist.close();
    ost.close();
    return 0;
}
