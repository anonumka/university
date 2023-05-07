//Вариант 3 задача на 100%
#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>

using namespace std;

int main()
{
    ofstream out ;
    out.open ("out.txt"); 

    char A[8][8]{
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'}
    };
    char crd[255];
    cout << "Enter coordinates: ";
    cin.getline(crd, 255);
    if (strlen(crd)!=2)
    {
        out << "Invalid coordinates.";
        return 0;
    }
    int k = 0;
    int l = crd[1] - '0';
    if (l > 8)
    {
        out << "Invalid coordinates.";
        return 0;
    }
    else
        l = abs(l-8);
    switch (crd[0])
	{
	case 'h':
		k = 7;
		break;
	case 'g':
		k = 6;
		break;
	case 'f':
		k = 5;
		break;
	case 'e':
		k = 4;
		break;
	case 'd':
		k = 3;
		break;
    case 'c':
		k = 2;
		break;
    case 'b':
		k = 1;
		break;
    case 'a':
		k = 0;
		break;
	default:
		cout << "Invalid coordinates.";
		return 0;
	}

    A[l][k] = 'K';
    if ((l-2>=0 && l-2<8) && k+1<8)
        A[l-2][k+1] = '*';
    if ((l-2>=0 && l-2<8) && k-1>=0)
        A[l-2][k-1] = '*';
    if ((l-1>=0 && l-1<8) && k+2<8)
        A[l-1][k+2] = '*';
    if ((l-1>=0 && l-1<8) && k-2>=0)
        A[l-1][k-2] = '*';
    if ((l+1>=0 && l+1<8) && k+2<8)
        A[l+1][k+2] = '*';
    if (l+1>=0 && l+1<8 && k-2>=0)
        A[l+1][k-2] = '*';
    if ((l+2<8 && l+2>=0) && k+1 < 8)
        A[l+2][k+1] = '*';
    if ((l+2<8 && l+2>=0) && k-1 >= 0)
        A[l+2][k-1] = '*';

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            out << " " << A[i][j] << " ";
        }
        out << '\n';
    }
    out.close();

    return 0;
}
