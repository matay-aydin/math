#include <iostream>
#include "Matrix.h"
using namespace std;

int main()
{
    Matrix A(3, 3);
    Matrix B(3, 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i >= j)
            {
                A.setEntry(i + j + 1, i, j);
                // B.setEntry(5, i, j);
            }
        }
    }
    // A.print();
    // A.gauss().print();
    // A.gauss_jordan().print();
    Matrix I = A.inverse();
    // B.print();
    // cout << B.det() << endl;
    return 0;
}