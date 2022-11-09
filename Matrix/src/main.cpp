#include <iostream>
#include "Matrix.h"
using namespace std;

int main()
{
    Matrix A(3, 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i >= i)
            {
                A.setEntry(i + 3 * j + 1 + (i * 10) / 7.0 + (j * 10) / 7.0, i, j);
            }
        }
    }
    A.print(8, 8);
    double h = 5.6;
    cout << det(A) << "  " << h << endl;
    gauss(A).print();
    gauss_jordan(A).print();
    trans(A).print();
    A.Gauss_Jordan();
    A.print();
    cout << h << endl;
    try
    {
        Matrix I = inv(A);
        I.print();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
