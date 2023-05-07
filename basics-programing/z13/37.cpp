#include <iostream>
#include <fstream>

using namespace std;

void join(const char *sep, std::istream &ist, std::ostream &ost)
{
    char buf[255];
	bool first_string = true;
	while (ist >> buf)
	{
		if (!first_string)
		    ost << sep;
		else
		    first_string = false;
		ost << buf;
	}
}

int main ()
{
    ifstream ist("in1.txt", ios::in);
    ofstream ost("out1.txt", ios::out);

    if (!ist.is_open())
    {
        cout << "Read error!";
        return 0;
    }

    char* sep = new char[255];
    cout << "Enter string-chars: ";
    cin.getline(sep, 255);

    join(sep, ist, ost);
    cout << "The program has finished executing.";

    delete [] sep;
    ist.close();
    ost.close();
    return 0;
}
