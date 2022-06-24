import csv

titles = {}

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)

    # ignore first row in a csv reader:
    # next(reader)

    for row in reader:
        # strip leading and ending whitespace, uppercase all letters
        title = row["title"].strip().upper().replace(":", "").replace("-", " ")
        if title in titles:
            titles[title] += 1
        else:
            titles[title] = 1

for title in sorted(titles, key=lambda title: titles[title], reverse=True):
        print(title, titles[title])