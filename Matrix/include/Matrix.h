#ifndef _MATRIX
#define _MATRIX

class Matrix
{
public:
    Matrix(int row = 1, int col = 1);
    Matrix(const Matrix &old);
    ~Matrix();
    void setEntry(double value, int row, int col);
    double getEntry(int row, int col) const;
    double getRow() const;
    double getCol() const;
    void print(int precision = 2) const;
    void row_interchange(int row1, int row2);
    void row_scale(int row, double factor);
    void row_combine(int source_row, double factor, int row);
    Matrix t();
    Matrix gauss();
    Matrix gauss_jordan();
    double det();
    Matrix inverse();

private:
    int n;
    int m;
    double **matrix;

    Matrix &operator=(const Matrix &old);
    bool operator==(const Matrix &other);
    friend Matrix operator*(const Matrix &A, const Matrix &B);
    friend Matrix operator+(const Matrix &A, const Matrix &B);
    friend Matrix operator-(const Matrix &A, const Matrix &B);
};

#endif