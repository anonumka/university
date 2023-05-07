#include <iostream>
#include <cmath>

using namespace std;

float f1(int x)
{
    return x+3.14;
}

float f2(int x)
{
    return pow((x*x+2), 1/2);
}

int main()
{
    int x;
    float y;
    cout << "¬ведите значение 'x': ";
    cin >> x;

    y = f1(x) + f1(x*x) + f2(x) + f2(x-1);
    cout << y;
    return 0;
}
