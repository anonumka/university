#include <iostream>
#include <cmath>

using namespace std;

 void sort(float arr[], int len, float x)
{
    float tmp;

    for (int i = 0; i < len; i++)
    {
        cout << "Enter " << i+1 << " element array:: ";
        cin >> arr[i];
        arr[i] = fabs(arr[i]);
    }

    for (int i = 0; i < len; i++)
    {
        for (int j = i+1; j < len; j++)
        {
            if (fabs(arr[i] - x) > fabs(arr[j] - x))
            {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }

}

int main ()
{
    setlocale (LC_ALL, ".1251");

    int len;
    float x;

    cout << "Enter length of array: ";
    cin >> len;
    cout << "Enter number with which elements array will be compare: ";
    cin >> x;

    if (len > 0)
    {
        float *arr = new float [len];
        float *dist = new float [len];

        sort(arr, len, x);

        cout << "dist[] = ";

        for (int i = 0; i < len; i++)
        {
            dist[i] = fabs(arr[i] - x);
            cout << dist[i] << ' ';
        }

        delete [] arr;
        delete [] dist;
    }
    else
        cout << "Lenght cant be zero or negative";

    return 0;
}
