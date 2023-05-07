#include <iostream>

using namespace std;

void print_rect(int x, int y, int sx, int sy)
{
    for (int i = 0; i < y; i++)
    {
        cout << "\n";
    }

    if (y >= 0)
    {
        for (int i = 0; i < sy; i++)
        {
            for (int j = 0; j < x; j++)
            {
                cout << " ";
            }

            if (x >= 0)
            {
                for (int j = 0; j < sx; j++)
                {
                    cout << "@";
                }
            }
            else
            {
                for (int j = 0; j < sx+x; j++)
                {
                    cout << "@";
                }
            }
            cout << "\n";
        }
    }


    else
    {
        for (int i = 0; i < sy+y; i++)
        {
            for (int j = 0; j < x; j++)
            {
                cout << " ";
            }

            if (x >= 0)
            {
                for (int j = 0; j < sx; j++)
                {
                    cout << "@";
                }
            }
            else
            {
                for (int j = 0; j < sx+x; j++)
                {
                    cout << "@";
                }
            }
            cout << "\n";
        }
    }


}

int main ()
{
    setlocale(LC_ALL, ".1251");

    int64_t x = 0;
    int64_t y = 0;
    int64_t sx = 0;
    int64_t sy = 0;

    cout << "¬ведите отступ по оси 'x': ";
    cin >> x;
    cout << "¬ведите отступ по оси 'y': ";
    cin >> y;
    cout << "¬ведите отступ по оси 'sx': ";
    cin >> sx;
    cout << "¬ведите отступ по оси 'sy': ";
    cin >> sy;

    print_rect(x, y, sx, sy);

    return 0;
}
