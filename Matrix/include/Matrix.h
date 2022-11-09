#ifndef _MATRIX
#define _MATRIX

class Matrix
{
public:
    Matrix(int row = 1, int col = 1);
    Matrix(const Matrix &old);
    Matrix &operator=(const Matrix &old);
    bool operator==(const Matrix &other);
    ~Matrix();
    void setEntry(double value, int row, int col);
    double getEntry(int row, int col) const;
    double getRow() const;
    double getCol() const;
    /// @brief Prints Matrix to terminal
    /// @param rooms Space allocated for entries of Matrix
    /// @param precision Number of digits after floating point
    void print(int rooms = 8, int precision = 2) const;
    void row_interchange(int row1, int row2);
    void row_scale(int row, double factor);
    void row_combine(int source_row, double factor, int row);
    /// @brief Converts Matrix to row echelon form
    void Gauss();
    /// @brief Converts Matrix to reduced row echelon form
    void Gauss_Jordan();

private:
    int n;
    int m;
    double **matrix;

    /// @brief Performs matrix multiplication on matrices
    /// @return Matrix has value A*B
    friend Matrix operator*(const Matrix &A, const Matrix &B);
    /// @brief Performs matrix addition
    /// @return Matrix has value A+B
    friend Matrix operator+(const Matrix &A, const Matrix &B);
    /// @brief Performs matrix subtraction
    /// @return Matrix has value A-B
    friend Matrix operator-(const Matrix &A, const Matrix &B);
    /// @brief Copies the given matrix, and takes the transpose of the copy
    /// @return Transpose Matrix
    friend Matrix trans(const Matrix &);
    /// @brief Copies the given matrix, and converts the copy into row echelon form
    /// @return REF Matrix
    friend Matrix gauss(const Matrix &);
    /// @brief Copies the given matrix, and converts the copy into reduced row echelon form
    /// @return RREF Matrix
    friend Matrix gauss_jordan(const Matrix &);
    /// @brief Calculates the determinant of the given matrix
    /// @return Determinant
    friend double det(const Matrix &);
    /// @brief Copies the given matrix, and takes the inverse of the copy matrix
    /// @return Inverse Matrix
    friend Matrix inv(const Matrix &);
};

#endif
