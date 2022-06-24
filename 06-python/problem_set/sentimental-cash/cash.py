from cs50 import get_float
import math

# initialize c variable
c = -1

# get and validate user input
while c < 0:
    c = get_float("Change owed: ")

# initialize coin values to 0
q = d = n = p = 0

# get number of quarters and update change total
q = math.floor(c / .25)
c = round(c - (q * .25), 2)

# get number of dimes and update change total
d = math.floor(c / .1)
c = round(c - (d * .1), 2)

# get number of nickels and update change total
n = math.floor(c / .05)
c = round(c - (n * .05), 2)

# calculate pennies remaining
p = round(c * 100)

# sum up number of coins and print the result
coins = round(q + d + n + p)
print(coins)