#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void rev_lines(std::istream &ist, std::ostream &ost)
{
    char buf[255];
    int c = 0;
    while ( ist.getline(buf, 255) )
        c++;
    memset(buf, 0, 255);
	char buf2[c-1][255];
    ist.clear();
	ist.seekg(ios_base::beg);
    int i = 0;
    while ( ist.getline(buf2[i], 255) )
        i++;
    for (; i > 0; i--)
        ost << buf2[i - 1] << endl;
}

int main ()
{
    ifstream ist("in2.txt", ios::in);
    ofstream ost("out2.txt", ios::out);

    if (!ist.is_open())
    {
        cout << "Read error!";
        return 0;
    }

    rev_lines(ist, ost);
    cout << "The program has finished executing.";
    ist.close();
    ost.close();
    return 0;
}
