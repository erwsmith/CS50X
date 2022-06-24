import csv
from cs50 import get_string

# people = {
#     "Carter": "+-1617-495-1000",
#     "David": "+1-949-468-2750"
# }
# name = get_string("name: ")
# if name in people:
#     print(f"Number: {people[name]}")

name = get_string("Name: ")
number = get_string("Number: ")

# with the file open, do the following, then it closes the file automatically
with open("phonebook.csv", "a") as file:
    writer = csv.writer(file)
    writer.writerow([name, number])
