import sys
from cs50 import get_int

# initialize n
n = 0

# get height of pyramid from user, validate user input
while n < 1 or n > 8:
    n = get_int("Height: ")

# print n rows, decrementing from n to 0
for row in range(n, 0, -1):
    # print spaces
    print(f" " * (row - 1), end="")
    # print hashes
    print("#" * (n - row + 1), end="")
    # print gap
    print(f"  ", end="")
    # print hashes and new line
    print("#" * (n - row + 1), end="")
    print()
