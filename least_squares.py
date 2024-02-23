from math import log


def matrixMult(A, B):
    if len(A[0]) != len(B):
        return []
    C = []
    for i in range(len(A)):
        C.append([])
        for j in range(len(B[0])):
            entry = 0
            for k in range(len(B)):
                entry += A[i][k] * B[k][j]
            C[i].append(entry)
    return C


def transpose(A):
    At = []
    for j in range(len(A[0])):
        At.append([])
        for i in range(len(A)):
            At[j].append(A[i][j])
    return At


def identity(size):
    I = []
    for i in range(size):
        I.append([])
        for j in range(size):
            if i == j:
                I[i].append(1)
            else:
                I[i].append(0)
    return I


# Elementary row operation
def rowScale(A, row, scale):
    if scale == 0:
        return
    for i in range(len(A[0])):
        A[row][i] *= scale


# Elementary row operation
def rowExchange(A, row1, row2):
    if row1 == row2:
        return
    for i in range(len(A[0])):
        temp = A[row1][i]
        A[row1][i] = A[row2][i]
        A[row2][i] = temp


# Elementary row operation
def rowCombine(A, rowSource, rowDest, scale):
    if rowSource == rowDest or scale == 0:
        return
    for i in range(len(A[0])):
        A[rowDest][i] += A[rowSource][i] * scale


# Return a copy of the given matrix
def copyMatrix(A):
    cA = []
    for i in range(len(A)):
        cA.append([])
        for j in range(len(A[0])):
            cA[i].append(A[i][j])
    return cA


# Create and return the inverse of the given square matrix
def inverse(A):
    if len(A) != len(A[0]):
        return []
    size = len(A)
    cA = copyMatrix(A)
    invA = identity(size)
    for i in range(size):  # Gaussian elimination
        pivot = cA[i][i]
        pivotRow = i
        for j in range(i, size):  # Partial pivoting
            if abs(cA[j][i]) > abs(pivot):
                pivot = cA[j][i]
                pivotRow = j
        rowExchange(cA, i, pivotRow)
        rowExchange(invA, i, pivotRow)
        if pivot == 0:  # Zero column
            print("Determinant is zero!")
            exit(1)
        rowScale(cA, i, 1 / pivot)
        rowScale(invA, i, 1 / pivot)
        for j in range(i, size):  # Forward elimination
            scale = (-1) * cA[j][i]
            rowCombine(cA, i, j, scale)
            rowCombine(invA, i, j, scale)
    for i in range(size - 1, -1, -1):  # Backward elimination
        for j in range(i, -1, -1):
            scale = (-1) * cA[j][i]
            rowCombine(cA, i, j, scale)
            rowCombine(invA, i, j, scale)
    return invA


# y values
Y = [
    [0.72],
    [1.63],
    [1.88],
    [3.39],
    [4.02],
    [3.89],
    [4.25],
    [3.99],
    [4.68],
    [5.03],
    [5.27],
    [4.82],
    [5.67],
    [5.95],
    [5.72],
    [6.01],
    [5.5],
    [6.41],
    [5.83],
    [6.33],
]

# Create X matrix for the line using given x values
Xl = [
    [1, 0.5],
    [1, 1],
    [1, 1.5],
    [1, 2],
    [1, 2.5],
    [1, 3],
    [1, 3.5],
    [1, 4],
    [1, 4.5],
    [1, 5],
    [1, 5.5],
    [1, 6],
    [1, 6.5],
    [1, 7],
    [1, 7.5],
    [1, 8],
    [1, 8.5],
    [1, 9],
    [1, 9.5],
    [1, 10],
]

# Create X matrix for the parabola using given x values
Xq = copyMatrix(Xl)
for i in range(len(Xq)):
    Xq[i].append(Xq[i][1] ** 2)

# Create X matrix for the logarithmic curve using given x values
Xln = copyMatrix(Xl)
for i in range(len(Xln)):
    Xln[i][1] = log(Xln[i][1])

# Coefficient matrices from least squares aprrox.
Al = matrixMult(
    inverse(matrixMult(transpose(Xl), Xl)), matrixMult(transpose(Xl), Y)
)  # line
Aq = matrixMult(
    inverse(matrixMult(transpose(Xq), Xq)), matrixMult(transpose(Xq), Y)
)  # parabola
Aln = matrixMult(
    inverse(matrixMult(transpose(Xln), Xln)), matrixMult(transpose(Xln), Y)
)  # logarithmic

"""
# Check outputs
print(matrixMult(transpose(Xl), Xl))
print(inverse(matrixMult(transpose(Xl), Xl)))
print(matrixMult(transpose(Xl), Y))
print(matrixMult(inverse(matrixMult(transpose(Xl), Xl)), matrixMult(transpose(Xl), Y)))
print("")
print(Xq)
print(matrixMult(transpose(Xq), Xq))
print(inverse(matrixMult(transpose(Xq), Xq)))
print(matrixMult(transpose(Xq), Y))
print(matrixMult(inverse(matrixMult(transpose(Xq), Xq)), matrixMult(transpose(Xq), Y)))
print("")
print(Xln)
print(matrixMult(transpose(Xln), Xln))
print(inverse(matrixMult(transpose(Xln), Xln)))
print(matrixMult(transpose(Xln), Y))
print(
    matrixMult(inverse(matrixMult(transpose(Xln), Xln)), matrixMult(transpose(Xln), Y))
)
"""

import matplotlib.pyplot as plt
from numpy import linspace

# Plot the given points
x = []
y = []
for i in range(len(Y)):
    y.append(Y[i][0])
    x.append(Xl[i][1])
plt.plot(x, y, "o")

axis_x = linspace(0.5, 11, 100)  # The interval for the approximated functions.

yl = Al[1][0] * axis_x + Al[0][0]
plt.plot(axis_x, yl, label="linear")

yq = Aq[2][0] * (axis_x**2) + Aq[1][0] * axis_x + Aq[0][0]
plt.plot(axis_x, yq, label="quadratic")

yln = []
for i in range(len(axis_x)):
    yln.append(Aln[1][0] * (log(axis_x[i])) + Aln[0][0])
plt.plot(axis_x, yln, label="logarithmic")

plt.title("Least Squares Approximation")
plt.xlabel("x-Axis")
plt.ylabel("y-Axis")
plt.legend(loc="upper left")
plt.show()