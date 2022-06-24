import sys
from cs50 import get_string

# sys.argv[] looks at the command line arguments
# use command-line argument entered after 'python name.py'
# command line entry: 'python name.py Eric' returns 'hello, my name is Eric'

# sys.exit() leaves the interpreter (exits the whole program)

if len(sys.argv) > 1:
    sys.exit("Usage python hello.py")

name = get_string("What is your name? ")

print("hello,", name)
print()