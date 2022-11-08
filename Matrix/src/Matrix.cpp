#include <iostream>
#include <iomanip>
#include "Matrix.h"

Matrix::Matrix(int row, int col)
{
    if (row >= 1 && col >= 1)
    {
        this->matrix = new double *[row];
        for (int i = 0; i < row; i++)
        {
            this->matrix[i] = new double[col];
            for (int j = 0; j < col; j++)
            {
                this->matrix[i][j] = 0.0;
            }
        }
        this->n = row;
        this->m = col;
    }
    else
    {
        const char *msg = "\nMatrix.cpp Matrix::Matrix()>>> Invalid row or col quantity.\n";
        throw msg;
    }
}

Matrix::Matrix(const Matrix &old)
{
    int row = old.n;
    int col = old.m;
    this->matrix = new double *[row];
    for (int i = 0; i < row; i++)
    {
        this->matrix[i] = new double[col];
        for (int j = 0; j < col; j++)
        {
            this->matrix[i][j] = old.matrix[i][j];
        }
    }
    this->n = row;
    this->m = col;
}

Matrix &Matrix::operator=(const Matrix &old)
{
    int row = old.n;
    int col = old.m;
    if (this->n == row && this->m == col)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                this->matrix[i][j] = old.matrix[i][j];
            }
        }
    }
    return *this;
}

bool Matrix::operator==(const Matrix &other)
{
    bool flag = true;
    int row = other.n;
    int col = other.m;
    if (this->n == row && this->m == col)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (this->matrix[i][j] != other.matrix[i][j])
                {
                    flag = false;
                    i = row;
                    break;
                }
            }
        }
    }
    else
    {
        flag = false;
    }
    return flag;
}

Matrix::~Matrix()
{
    for (int i = 0; i < this->n; i++)
    {
        delete[] this->matrix[i];
    }
    delete[] this->matrix;
    this->n = 0;
    this->m = 0;
}

void Matrix::setEntry(double value, int row, int col)
{
    if (this->n > row && row >= 0 && this->m > col && col >= 0)
    {
        this->matrix[row][col] = value;
    }
    else
    {
        const char *msg = "\nMatrix.cpp setEntry(double, int, int)>>> Setting value at invalid index.\n";
    }
}

double Matrix::getEntry(int row, int col) const
{
    if (this->n > row && row >= 0 && this->m > col && col >= 0)
    {
        return this->matrix[row][col];
    }
    else
    {
        const char *msg = "\nMatrix.cpp Matrix::getEntry(int, int)>>> Getting value from invalid index.\n";
        throw msg;
    }
}

double Matrix::getRow() const { return this->n; }

double Matrix::getCol() const { return this->m; }

void Matrix::print(int precision) const
{
    int p = precision;
    if (precision < 0)
    {
        p = 2;
    }
    std::cout << std::fixed << std::setprecision(p);
    std::cout << std::endl
              << std::endl;
    for (int i = 0; i < this->n; i++)
    {
        std::cout << " |";
        for (int j = 0; j < this->m; j++)
        {
            std::cout << std::setw(p + 8) << this->matrix[i][j];
        }
        std::cout << " |" << std::endl;
    }
    std::cout << std::endl;
}

Matrix operator*(const Matrix &A, const Matrix &B)
{
    if (A.getCol() != B.getRow())
    {
        const char *msg = "\nMatrix.cpp Matrix operator*(Matrix, Matrix)>>> Cannot multiply the parameter matrices.\n";
        throw msg;
    }
    else
    {
        Matrix C(A.getRow(), B.getCol());
        for (int i = 0; i < A.getRow(); i++)
        {
            for (int j = 0; j < B.getCol(); j++)
            {
                double cell = 0;
                for (int k = 0; k < A.getCol(); k++)
                {
                    cell += A.getEntry(i, k) * B.getEntry(k, j);
                }
                C.setEntry(cell, i, j);
            }
        }
        return C;
    }
}

Matrix operator+(const Matrix &A, const Matrix &B)
{
    if (A.getRow() != B.getRow() || A.getCol() != B.getCol())
    {
        const char *msg = "\nMatrix.cpp Matrix operator+(Matrix, Matrix)>>> Cannot sum the parameter matrices.\n";
        throw msg;
    }
    else
    {
        Matrix C(A.getRow(), B.getCol());
        for (int i = 0; i < A.getRow(); i++)
        {
            for (int j = 0; j < B.getCol(); j++)
            {
                C.setEntry(A.getEntry(i, j) + B.getEntry(i, j), i, j);
            }
        }
        return C;
    }
}

Matrix operator-(const Matrix &A, const Matrix &B)
{
    if (A.getRow() != B.getRow() || A.getCol() != B.getCol())
    {
        const char *msg = "\nMatrix.cpp Matrix operator-(Matrix, Matrix)>>> Cannot subtract the parameter matrices.\n";
        throw msg;
    }
    else
    {
        Matrix C(A.getRow(), B.getCol());
        for (int i = 0; i < A.getRow(); i++)
        {
            for (int j = 0; j < B.getCol(); j++)
            {
                C.setEntry(A.getEntry(i, j) - B.getEntry(i, j), i, j);
            }
        }
        return C;
    }
}

void Matrix::row_interchange(int row1, int row2)
{
    if (row1 <= this->n && row2 <= this->n)
    {
        double *temp = this->matrix[row1];
        this->matrix[row1] = this->matrix[row2];
        this->matrix[row2] = temp;
    }
    else
    {
        const char *msg = "\nMatrix.cpp row_interchange(int, int)>>> Invalid rows.\n";
        throw msg;
    }
}

void Matrix::row_scale(int row, double factor)
{
    if (row <= this->n && factor != 0)
    {
        for (int j = 0; j < this->m; j++)
        {
            this->matrix[row][j] *= factor;
        }
    }
    else
    {
        const char *msg = "\nMatrix.cpp row_scale(int, double)>>> Invalid row or factor.\n";
        throw msg;
    }
}

void Matrix::row_combine(int source_row, double factor, int row)
{
    if (source_row <= this->n && row <= this->m && source_row != row)
    {
        for (int j = 0; j < this->m; j++)
        {
            this->matrix[row][j] += this->matrix[source_row][j] * factor;
        }
    }
    else
    {
        const char *msg = "\nMatrix.cpp row_combine(int, double, int)>>> Invalid rows.\n";
        throw msg;
    }
}

Matrix Matrix::t()
{
    Matrix T(this->m, this->n);
    for (int i = 0; i < T.n; i++)
    {
        for (int j = 0; j < T.m; j++)
        {
            T.matrix[i][j] = this->matrix[j][i];
        }
    }
    return T;
}

Matrix Matrix::gauss()
{
    Matrix G = *this;
    int significant_ones = 0;
    for (int j = 0; j < G.m; j++)
    {
        for (int i = significant_ones; i < G.n; i++)
        {
            bool is_zero_col = true;
            for (int n = 0; n < G.n; n++)
            {
                if (G.matrix[i][j] == 0.0)
                {
                    for (int k = i; k < G.n - 1; k++)
                    {
                        G.row_interchange(k, k + 1);
                    }
                }
                else
                {
                    is_zero_col = false;
                    break;
                }
            }
            if (!is_zero_col)
            {
                double factor = 1.0 / (G.matrix[i][j]);
                G.row_scale(i, factor);
                significant_ones++;
                for (int k = i + 1; k < G.n; k++)
                {
                    if (G.matrix[k][j] != 0.0)
                    {
                        factor = (-1) * (G.matrix[k][j]);
                        G.row_combine(i, factor, k);
                    }
                }
                break;
            }
        }
    }
    return G;
}

Matrix Matrix::gauss_jordan()
{
    Matrix GJ = this->gauss();
    for (int i = GJ.n - 1; i >= 0; i--)
    {
        for (int j = 0; j < GJ.m; j++)
        {
            if (GJ.matrix[i][j] != 0)
            {
                double factor;
                for (int k = i; k > 0; k--)
                {
                    if (GJ.matrix[k - 1][j] != 0)
                    {
                        factor = (-1.0) * GJ.matrix[k - 1][j];
                        GJ.row_combine(i, factor, k - 1);
                    }
                }
                break;
            }
        }
    }
    return GJ;
}

double Matrix::det()
{
    if (this->n == this->m && this->n > 0)
    {
        double d = 1;
        Matrix G = *this;
        int significant_ones = 0;
        for (int j = 0; j < G.m; j++)
        {
            for (int i = significant_ones; i < G.n; i++)
            {
                bool is_zero_col = true;
                for (int n = 0; n < G.n; n++)
                {
                    if (G.matrix[i][j] == 0.0)
                    {
                        for (int k = i; k < G.n - 1; k++)
                        {
                            G.row_interchange(k, k + 1);
                        }
                        d *= (-1);
                    }
                    else
                    {
                        is_zero_col = false;
                        break;
                    }
                }
                if (!is_zero_col)
                {
                    double factor = 1.0 / (G.matrix[i][j]);
                    G.row_scale(i, factor);
                    d /= factor;
                    significant_ones++;
                    for (int k = i + 1; k < G.n; k++)
                    {
                        if (G.matrix[k][j] != 0.0)
                        {
                            factor = (-1) * (G.matrix[k][j]);
                            G.row_combine(i, factor, k);
                        }
                    }
                    break;
                }
            }
        }
        for (int i = 0; i < G.n; i++)
        {
            d *= G.matrix[i][i];
        }
        return d;
    }
    else
    {
        const char *msg = "\nMatrix.cpp double det()>>> Invalid dimensions.\n";
        throw msg;
    }
}

Matrix Matrix::inverse()
{
    if (this->n == this->m && this->n > 0)
    {
        Matrix M(this->n, 2 * this->m);
        for (int i = 0; i < this->n; i++)
        {
            for (int j = 0; j < this->m; j++)
            {
                M.matrix[i][j] = this->matrix[i][j];
            }
            for (int j = this->m; j < 2 * this->m; j++)
            {
                if (i + this->n == j)
                {
                    M.matrix[i][j] = 1;
                }
            }
        }
        bool hasZeroRow;
        for (int i = 0; i < this->n; i++)
        {
            hasZeroRow = true;
            for (int j = 0; j < this->m; j++)
            {
                if (M.matrix[i][j] != 0)
                {
                    hasZeroRow = false;
                    break;
                }
            }
            if (hasZeroRow)
            {
                const char *msg = "\nMatrix.cpp Matrix inverse()>>> Inverse does not exist.\n";
                throw msg;
            }
        }
        Matrix N = M.gauss_jordan();
        Matrix I(this->n, this->m);
        for (int i = 0; i < this->n; i++)
        {
            for (int j = 0; j < this->m; j++)
            {
                I.matrix[i][j] = N.matrix[i][j + this->m];
            }
        }
        return I;
    }
    else
    {
        const char *msg = "\nMatrix.cpp Matrix inverse()>>> Invalid dimensions.\n";
        throw msg;
    }
}