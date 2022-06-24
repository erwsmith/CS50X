from cs50 import SQL

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

name = "Eric"
month = 10
day = 14

db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)