//Вариант 3 задание на 100%
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void my_task(std::istream &ist, std::ostream &ost)
{
    char line[255];
    char res[255];
    bool c;
    int len;
    int k;
    while (ist.getline(line, 255))
    {
        k = 0;
        memset(res, 0, 255);
        for (int i = 0; i < strlen(line); i++)
        {
            if (line[i] == 255)
                line[i] = 0;
            else if (line[i] == '\0')
                break;
            else
            {
                c = true;
                len = strlen(res);
                for (int j = 0; j < len; j++)
                    if (line[i] == res[j])
                        c = false;
                if (c)
                {
                    res[k] = line[i];
                    k++;
                }
            }
        }
        res[k] = '\0';
        ost << line << '\n' << res << '\n';
    }
}

int main()
{
    ifstream ist("in.txt", ios::in);
    ofstream ost("out.txt", ios::out);
    if (!ist.is_open())
    {
        cout << "Файл не найден!";
        return 0;
    }
    my_task(ist, ost);
    ost.close();

    return 0;
}
