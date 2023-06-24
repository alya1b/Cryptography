def extended_gcd(a, b):
    # Initial values
    x0, x1, y0, y1 = 1, 0, 0, 1
    steps = []

    while b != 0:
        quotient, remainder = divmod(a, b)
        steps.append((a, b, quotient, remainder, x0, y0))

        # Update values
        a, b = b, remainder
        x0, x1 = x1, x0 - quotient * x1
        y0, y1 = y1, y0 - quotient * y1

    return a, x0, y0, steps


# Get input from the user
a = int(input("Enter the first number (a): "))
b = int(input("Enter the second number (b): "))

# Call the extended_gcd function
gcd, x, y, steps = extended_gcd(a, b)

# Print the steps
print("Extended GCD steps:")
print("a\tb\tquotient\tremainder\tx\ty")
for step in steps:
    print("{}\t{}\t{}\t\t{}\t\t{}\t{}".format(*step))

# Print the results
print("\nExtended GCD of", a, "and", b, "is:", gcd)
print("x =", x)
print("y =", y)
