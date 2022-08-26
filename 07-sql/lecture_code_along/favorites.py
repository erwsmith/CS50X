from cs50 import SQL

# open favorites.db file
db = SQL("sqlite:///favorites.db")

# ask user for title they want to search for
title = input("Title: ").strip()

# get list of rows 
rows = db.execute("SELECT COUNT(*) AS counter FROM favorites WHERE title LIKE ?", title)

row = rows[0]

print(row["counter"])