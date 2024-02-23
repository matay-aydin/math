from math import log


def newton(f, df, x0, iterations):
    ns = []
    xn = x0
    while iterations > 0:
        fxn = f(xn)
        dfxn = df(xn)
        ns.append((xn, fxn, dfxn))
        if dfxn == 0:
            print("Divide by zero!")
            exit(1)
        else:
            xn = xn - (fxn / dfxn)
        iterations -= 1
    return ns


def secant(f, x0, x1, iterations):
    xn_minus_1 = x0
    xn = x1
    ns = [(xn_minus_1, f(xn_minus_1))]
    while iterations > 0:
        fxn = f(xn)
        fxn_minus_1 = f(xn_minus_1)
        ns.append((xn, fxn))
        if fxn_minus_1 - fxn == 0:
            print("Divide by zero!")
            exit(1)
        else:
            xn_plus_1 = xn - ((fxn * (xn_minus_1 - xn)) / (fxn_minus_1 - fxn))
        xn_minus_1 = xn
        xn = xn_plus_1
        iterations -= 1
    return ns


def errBtwIters(iterateTupleList):
    err = []
    for i in range(len(iterateTupleList) - 1):
        err.append(abs(iterateTupleList[i + 1][0] - iterateTupleList[i][0]))
    return err


def errEstimate(root, iterateTupleList):
    err = []
    for i in range(len(iterateTupleList) - 1):
        err.append(abs(root - iterateTupleList[i][0]))
    return err


def newtonConvRate(errEst):
    rate = []
    for i in range(1, len(errEst) - 1):
        if errEst[i] == 0 or errEst[i + 1] == 0:
            continue
        num = log(errEst[i + 1] / errEst[i])
        denom = log(errEst[i] / errEst[i - 1])
        rate.append(num / denom)
    return rate


def func(x):
    return 4 * log(x) - x


def funcPrime(x):
    if x == 0:
        print("Divide by zero!")
        exit(1)
    return 4 / x - 1


newtonList = newton(func, funcPrime, 1, 7)
newtonErrorList = errBtwIters(newtonList)
secantList = secant(func, 1, 2, 7)
secantErrorList = errBtwIters(secantList)
newtonErrEstimateList = errEstimate(1.4296118247255556, newtonList)
secantErrEstimateList = errEstimate(1.4296118247255556, secantList)
newtonConvRateList = newtonConvRate(newtonErrEstimateList)

print("Newton:")
print("n", "xn".rjust(25, " "), "f(xn)".rjust(25, " "), "f'(xn)".rjust(25, " "))
for i in range(len(newtonList)):
    print(
        i,
        str(newtonList[i][0]).rjust(25, " "),
        str(newtonList[i][1]).rjust(25, " "),
        str(newtonList[i][2]).rjust(25, " "),
    )
print(" ")

print("Secant:")
print("n", "xn".rjust(25, " "), "f(xn)".rjust(25, " "))
for i in range(len(secantList)):
    print(i, str(secantList[i][0]).rjust(25, " "), str(secantList[i][1]).rjust(25, " "))
print(" ")

print("Newton:")
print("|xn - xn-1|")
for e in newtonErrorList:
    print(str(e).ljust(25, " "))
print(" ")

print("Secant:")
print("|xn - xn-1|")
for e in secantErrorList:
    print(str(e).ljust(25, " "))
print(" ")
# for e in newtonErrEstimateList:
#    print(e)
# for e in secantErrEstimateList:
#    print(e)
# for r in newtonConvRateList:
#    print(r)
