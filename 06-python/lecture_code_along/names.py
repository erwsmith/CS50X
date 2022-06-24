import sys

names = ["Bill", "Charlie", "Fred", "George", "Ron"]

if "Ron" in names:
    print("found")
    sys.exit(0)
    
print("not found")
sys.exit(1)