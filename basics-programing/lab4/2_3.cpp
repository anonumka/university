//Variant 3

#include <iostream>
#include <cmath>

using namespace std;

float f1(float x)
{
    return exp(x) - 2.3 * pow(10, 5);
}

float f2(float x)
{
    return pow(3*x+2, 1/5);
}

int main()
{
    setlocale(LC_ALL, ".1251");
    float x;


    cout << "Enter 'x': ";
    cin >> x;
    cout << "y = " << f1(x)+f2(x);


    return 0;
}


