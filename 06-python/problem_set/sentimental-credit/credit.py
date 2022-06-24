'''
WRITTEN BY ERIC 29 APRIL 2022

Description from CS50X:
Most credit cards use an algorithm invented by Hans Peter Luhn of IBM.
According to Luhn’s algorithm, you can determine if a credit card
number is (syntactically) valid as follows:

Multiply every other digit by 2, starting with the number’s
second-to-last digit, and then add those products’ digits together.
Add the sum to the sum of the digits that weren’t multiplied by 2.
If the total’s last digit is 0 (or, put more formally, if the
total modulo 10 is congruent to 0), the number is valid!
// if number starts with: 34 or 37 and is 15-digits long, "AMEX"
// if starts with: 51, 52, 53, 54, or 55 and is 16-digits long, "MASTERCARD"
// if starts with: 4, and 13 digits long, "VISA"

'''
from cs50 import get_string
import math
import sys

n = get_string("Number: ")

if not (len(n) == 13 or len(n) == 15 or len(n) == 16):
    print("INVALID")
    sys.exit(1)
elif not (n.startswith("34") or n.startswith("37") or n.startswith("5") or n.startswith("4")):
    print("INVALID")
    sys.exit(1)
elif n.startswith("5") and not (0 < int(n[1]) < 6):
    print("INVALID")
    sys.exit(1)

# reverse order of number
n = n[::-1]

# initialize set lists
set1 = []
set2 = []

# get sum of (2 * every other digit) starting from second to last digit
for num in range(1, len(n), 2):
    x = int(n[num]) * 2
    if x > 9:
        set1.append(1)
        set1.append(x % 10)
    else:
        set1.append(x)

# get sum of second set
for num in range(0, len(n), 2):
    y = int(n[num])
    if y > 9:
        set2.append(1)
        set2.append(y % 10)
    else:
        set2.append(y)


z = str(sum(set1) + sum(set2))

if z[-1] != "0":
    print("INVALID")
    sys.exit(2)
else:
    # set number back to correct order
    n = n[::-1]
    # if number starts with: 34 or 37 and is 15-digits long, "AMEX"
    if (n.startswith("34") or n.startswith("37")) and len(n) == 15:
        print("AMEX")

    # if starts with: 51, 52, 53, 54, or 55 and is 16-digits long, "MASTERCARD"
    elif n.startswith("5") and (0 < int(n[1]) < 6) and len(n) == 16:
        print("MASTERCARD")

    # if starts with: 4, and 13 digits long, "VISA"
    elif (len(n) == 13 or len(n) == 16) and n.startswith("4"):
        print("VISA")
    else:
        print("lost")

