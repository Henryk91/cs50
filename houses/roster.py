# Checks sqllite db for House students
import cs50 as cs
from cs50 import SQL
import csv
import sys

db_location = 'sqlite:///students.db'


def main():

    if len(sys.argv) == 3:
        print("Wrong number of args. Should be 2 you gave", len(sys.argv))
        return 0

    check_house = sys.argv[1]
    check_for_house_in_db(check_house)


def check_for_house_in_db(house):
    # Check for student by house in database

    # query to get students by house name
    query = "SELECT * FROM students WHERE house='" + house + "' ORDER by last, first"
    db = SQL(db_location)
    students = db.execute(query)

    # Itterate over db return values
    for student in students:
        if student['middle'] == None:
            to_print = student['first'] + " " + student['last'] + ", born " + str(student['birth'])
            print(to_print)
        else:
            to_print = student['first'] + " " + student['middle'] + " " + student['last'] + ", born " + str(student['birth'])
            print(to_print)


main()