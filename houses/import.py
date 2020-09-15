# Import csv into sqllite db
import cs50 as cs
from cs50 import SQL
import csv
import sys

db_location = 'sqlite:///students.db'


def main():

    if len(sys.argv) == 3:
        print("Wrong number of args. Should be 2 you gave", len(sys.argv))
        return 0

    check_dir = sys.argv[1]

    load_db(check_dir)


def load_db(db_dir):
    # Open csv file and load data in db

    students_db = SQL(db_location)
    reader = 'null'
    with open(db_dir, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        # itterate over csv rows
        for row in reader:
            split_name = parse_name(row['name'])
            insert_in_db(split_name, row['house'], row['birth'], students_db)


def parse_name(name):
    # split name into array for first middle and last
    name_count = name.count(' ')

    # initialise split_name
    split_name = [None, None, None]
    if name_count == 1:
        split = name.split(' ')
        split_name = [split[0], 'NULL', split[1]]
    else:
        split_name = name.split(' ')
    return split_name


def insert_in_db(name_arr, house, birth, db):
    # insert student into database
    query = ''
    # check if student has middle name
    if name_arr[1] == 'NULL':
        query = ("INSERT INTO students (first, last, house, birth) VALUES ('" +
                 name_arr[0] + "','" + name_arr[2] + "','" + house + "'," + birth + ")")
    else:
        query = ("INSERT INTO students (first, middle, last, house, birth) VALUES ('" +
                 name_arr[0] + "','" + name_arr[1] + "','" + name_arr[2] + "','" + house + "'," + birth + ")")

    db.execute(query)


main()