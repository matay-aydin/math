# Convert integer string to binary string
def int2bin(integerStr):
    binary = ""
    integer = int(integerStr)
    negative = False  # Assume integer is positive
    if integer == 0:
        binary = "0"
    if integerStr[0] == "-":  # Check negativity
        negative = True
        integer *= -1
    while integer > 0:  # Decimal to binary
        binary = str(integer % 2) + binary
        integer //= 2
    if negative:  # Add minus if necessary
        binary = "-" + binary
    return binary


# Convert fraction string to binary string
def float2bin(fractionStr):
    binary = ""
    rem = float(fractionStr)
    if rem > 0:  # Put floating point
        binary = "."
    while rem > 0:
        rem *= 2
        if rem < 1:
            binary += "0"  # Bit
        else:
            binary += "1"  # Bit
            rem -= 1
    return binary


# Convert given decimal rational number to binary rational number
def rationalBin(rational):
    parts = str(float(rational)).split(".")
    integerPart = parts[0]
    floatPart = "0." + parts[1]
    binInt = int2bin(integerPart)
    binFloat = float2bin(floatPart)
    binary = binInt + binFloat
    return binary


# Run the algoritm over various cases
cases = [0.0, 0, 1, -5, "-5", 0.375, -0.375, 8.25, -8.25, 0.1, 5 / 8, -4097.125, 0.0625]
for case in cases:
    print(str(case).ljust(10), "is", rationalBin(case))
