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
        throw std::logic_error("\nMatrix.cpp Matrix::Matrix()>>> Invalid row or col quantity.\n");
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
        throw std::logic_error("\nMatrix.cpp setEntry(double, int, int)>>> Setting value at invalid index.\n");
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
        throw std::logic_error("\nMatrix.cpp Matrix::getEntry(int, int)>>> Getting value from invalid index.\n");
    }
}

double Matrix::getRow() const { return this->n; }

double Matrix::getCol() const { return this->m; }

void Matrix::print(int rooms, int precision) const
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
            std::cout << std::setw(p + rooms) << this->matrix[i][j];
        }
        std::cout << " |" << std::endl;
    }
    std::cout << std::endl;
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
        throw std::logic_error("\nMatrix.cpp row_interchange(int, int)>>> Invalid rows.\n");
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
        throw std::logic_error("\nMatrix.cpp row_scale(int, double)>>> Invalid row or factor.\n");
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
        throw std::logic_error("\nMatrix.cpp row_combine(int, double, int)>>> Invalid rows.\n");
    }
}

void Matrix::Gauss()
{
    int significant_ones = 0;
    for (int j = 0; j < this->m; j++)
    {
        for (int i = significant_ones; i < this->n; i++)
        {
            bool is_zero_col = true;
            for (int n = 0; n < this->n; n++)
            {
                if (this->matrix[i][j] == 0.0)
                {
                    for (int k = i; k < this->n - 1; k++)
                    {
                        this->row_interchange(k, k + 1);
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
                double factor = 1.0 / (this->matrix[i][j]);
                this->row_scale(i, factor);
                significant_ones++;
                for (int k = i + 1; k < this->n; k++)
                {
                    if (this->matrix[k][j] != 0.0)
                    {
                        factor = (-1) * (this->matrix[k][j]);
                        this->row_combine(i, factor, k);
                    }
                }
                break;
            }
        }
    }
}

void Matrix::Gauss_Jordan()
{
    this->Gauss();
    for (int i = this->n - 1; i >= 0; i--)
    {
        for (int j = 0; j < this->m; j++)
        {
            if (this->matrix[i][j] != 0)
            {
                double factor;
                for (int k = i; k > 0; k--)
                {
                    if (this->matrix[k - 1][j] != 0)
                    {
                        factor = (-1.0) * this->matrix[k - 1][j];
                        this->row_combine(i, factor, k - 1);
                    }
                }
                break;
            }
        }
    }
}

Matrix operator*(const Matrix &A, const Matrix &B)
{
    if (A.getCol() != B.getRow())
    {
        throw std::logic_error("\nMatrix.cpp Matrix operator*(Matrix, Matrix)>>> Cannot multiply the parameter matrices.\n");
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
        throw std::logic_error("\nMatrix.cpp Matrix operator+(Matrix, Matrix)>>> Cannot sum the parameter matrices.\n");
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
        throw std::logic_error("\nMatrix.cpp Matrix operator-(Matrix, Matrix)>>> Cannot subtract the parameter matrices.\n");
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

Matrix trans(const Matrix &M)
{
    Matrix T = M;
    for (int i = 0; i < T.getRow(); i++)
    {
        for (int j = 0; j < T.getCol(); j++)
        {
            T.setEntry(M.getEntry(j, i), i, j);
        }
    }
    return T;
}

Matrix gauss(const Matrix &M)
{
    Matrix G = M;
    int significant_ones = 0;
    for (int j = 0; j < G.getCol(); j++)
    {
        for (int i = significant_ones; i < G.getRow(); i++)
        {
            bool is_zero_col = true;
            for (int n = 0; n < G.getRow(); n++)
            {
                if (G.getEntry(i, j) == 0.0)
                {
                    for (int k = i; k < G.getRow() - 1; k++)
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
                double factor = 1.0 / (G.getEntry(i, j));
                G.row_scale(i, factor);
                significant_ones++;
                for (int k = i + 1; k < G.getRow(); k++)
                {
                    if (G.getEntry(k, j) != 0.0)
                    {
                        factor = (-1) * (G.getEntry(k, j));
                        G.row_combine(i, factor, k);
                    }
                }
                break;
            }
        }
    }
    return G;
}

Matrix gauss_jordan(const Matrix &M)
{
    Matrix GJ = gauss(M);
    for (int i = GJ.getRow() - 1; i >= 0; i--)
    {
        for (int j = 0; j < GJ.getCol(); j++)
        {
            if (GJ.getEntry(i, j) != 0)
            {
                double factor;
                for (int k = i; k > 0; k--)
                {
                    if (GJ.getEntry(k - 1, j) != 0)
                    {
                        factor = (-1.0) * GJ.getEntry(k - 1, j);
                        GJ.row_combine(i, factor, k - 1);
                    }
                }
                break;
            }
        }
    }
    return GJ;
}

double det(const Matrix &M)
{
    if (M.getRow() == M.getCol() && M.getRow() > 0)
    {
        double d = 1;
        Matrix G = M;
        int significant_ones = 0;
        for (int j = 0; j < G.getCol(); j++)
        {
            for (int i = significant_ones; i < G.getRow(); i++)
            {
                bool is_zero_col = true;
                for (int n = 0; n < G.getRow(); n++)
                {
                    if (G.getEntry(i, j) == 0.0)
                    {
                        for (int k = i; k < G.getRow() - 1; k++)
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
                    double factor = 1.0 / (G.getEntry(i, j));
                    G.row_scale(i, factor);
                    d /= factor;
                    significant_ones++;
                    for (int k = i + 1; k < G.getRow(); k++)
                    {
                        if (G.getEntry(k, j) != 0.0)
                        {
                            factor = (-1) * (G.getEntry(k, j));
                            G.row_combine(i, factor, k);
                        }
                    }
                    break;
                }
            }
        }
        for (int i = 0; i < G.getRow(); i++)
        {
            d *= G.getEntry(i, i);
        }
        return d;
    }
    else
    {
        throw std::logic_error("\nMatrix.cpp double det()>>> Invalid dimensions.\n");
    }
}

Matrix inv(const Matrix &A)
{
    if (A.getRow() == A.getCol() && A.getRow() > 0)
    {
        if (det(A) == 0)
        {
            throw std::logic_error("\nMatrix.cpp Matrix inverse()>>> Inverse does not exist.\n");
        }
        Matrix M(A.getRow(), 2 * A.getCol());
        for (int i = 0; i < A.getRow(); i++)
        {
            for (int j = 0; j < A.getCol(); j++)
            {
                M.setEntry(A.getEntry(i, j), i, j);
            }
            for (int j = A.getCol(); j < 2 * A.getCol(); j++)
            {
                if (i + A.getRow() == j)
                {
                    M.setEntry(1, i, j);
                }
            }
        }
        Matrix N = gauss_jordan(M);
        Matrix I(A.getRow(), A.getCol());
        for (int i = 0; i < A.getRow(); i++)
        {
            for (int j = 0; j < A.getCol(); j++)
            {
                I.setEntry(N.getEntry(i, j + A.getCol()), i, j);
            }
        }
        return I;
    }
    else
    {
        throw std::logic_error("\nMatrix.cpp Matrix inverse()>>> Invalid dimensions.\n");
    }
}
