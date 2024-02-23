import matplotlib.pyplot as plt
from math import ceil
from math import floor


class LagrangeInterpol:
    # Constructor
    def __init__(self, x, y):
        self.x = x  # x coordinates of data points
        self.y = y  # y coordinates of data points

    # Evaluate j-th basis polynomial
    def _basis(self, xi, j):
        result = 1.0
        for m in range(len(self.x)):
            if m != j:  # Skip j
                result *= (xi - self.x[m]) / (self.x[j] - self.x[m])
        return result

    # Evaluate the interpolant polynomial at xi
    def interpolant(self, xi):
        result = 0.0
        for j in range(len(self.x)):
            result += y[j] * self._basis(xi, j)
        return result

    # Plot the interpolated polynomial
    def plotCurve(self):
        xi = [
            x / 100 for x in range(100 * floor(min(self.x)), 100 * ceil(max(self.x)))
        ]  # x interval
        yi = [self.interpolant(x) for x in xi]  # y values sampled from the polinomial

        plt.plot(xi, yi, label="Interpolated Polynomial")  # Plot the polynomial
        plt.scatter(self.x, self.y, color="green", label="Abscissae")  # Plot abscissae
        plt.xlabel("x")
        plt.ylabel("y")
        plt.title("Lagrange Interpolation")
        plt.legend()
        plt.grid(True)
        plt.show()


if __name__ == "__main__":
    x = [-1.2, 0.3, 1.1]
    y = [-5.76, -5.61, -3.69]
    lp = LagrangeInterpol(x, y)
    lp.plotCurve()
