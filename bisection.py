def bisection(a, epsilon):
    isNegative = False  # flag
    if a < 0:
        isNegative = True
        a *= -1
    c = [0, a + 1]  # interval that certainly contains the root
    root = pow(a, 0.2)  # store the value for later use
    x = (c[0] + c[1]) / 2  # estimation
    while abs(root - x) > epsilon:  # error check
        if root < x:
            c[1] = x
        else:
            c[0] = x
        x = (c[0] + c[1]) / 2  # update estimation
    if isNegative:
        x *= -1
    return x


# Examples
print("Fifth root of -1025 is approximately", bisection(-1025, 0.00001))
print("Fifth root of 0.7 is approximately", bisection(0.7, 0.00001))
