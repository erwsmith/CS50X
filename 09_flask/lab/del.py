from cs50 import SQL

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")
id = 9
db.execute("DELETE FROM birthdays where id =?", id)