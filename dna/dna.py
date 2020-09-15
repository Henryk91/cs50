# DNA Comparison check pset 6
# use eg: python dna.py databases/large.csv sequences/6.txt
import csv
import sys


def main():

    if len(sys.argv) < 3:
        return 0

    check_dir = sys.argv[1]
    dna_dir = sys.argv[2]

    people_db = load_db(check_dir)

    strs_list = people_db.fieldnames

    str_counts = get_str_counts(dna_dir, strs_list)

    dna_match = check_db(check_dir, str_counts)
    if dna_match != '':
        print(dna_match)
    else:
        print("No match")


def get_str_counts(dna_dir, strs_list):
    # gets all str type counts from dna
    f = open(dna_dir, "r")
    file_content = f.read()
    content_length = len(file_content)

    strs_match_counter = [0] * len(strs_list)

    prev_match_index = 0
    prev_strs_list_index = 0
    streak_count = 0
    sequence_ind_prev = 0

    # iterate over every character chechking it against the strs list
    for i in range(content_length):
        match_index = single_str_check(file_content, i, strs_list)

        # if there was a match between character and strs item else no match
        if (match_index > 0):

            prev_in_range = len(strs_list[match_index]) == (i - sequence_ind_prev)

            if (prev_strs_list_index == match_index) & prev_in_range:
                streak_count += 1
                sequence_ind_prev = i
                prev_match_index = i
            else:
                # saving new high score
                if streak_count > strs_match_counter[prev_strs_list_index]:
                    strs_match_counter[prev_strs_list_index] = streak_count

                # reset variables
                streak_count = 1
                sequence_ind_prev = i
                prev_strs_list_index = match_index

    # adds new high score to counter array for save
    if streak_count > strs_match_counter[prev_strs_list_index]:
        strs_match_counter[prev_strs_list_index] = streak_count

    return strs_match_counter


def single_str_check(to_check_string, current_index, strs_list):

    # check for a str match at an index returns matching index
    # strs_match_counter = [0] * len(strs_list)
    match_found = ''
    match_found_index = 0

    for i, str_item in enumerate(strs_list):

        check_end = len(str_item) + current_index
        to_check = to_check_string[current_index: check_end]

        # check if characters match dna_str type
        if str_item == to_check:
            # strs_match_counter[i] += 1
            match_found_index = i
            break

    return match_found_index


def load_db(db_dir):
    # Open csv file
    reader = 'null'
    with open(db_dir, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        headers = reader.fieldnames

    return reader


# returns match from people csv
def check_db(db_dir, strs_count_list):
    # Open csv file
    strs_list_match = ''

    with open(db_dir, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        headers = reader.fieldnames
        strs_list = headers
        people = reader
        for row in reader:

            match_count = 0
            header_length = len(headers)

            # compare matches for each person
            for i in range(header_length):
                checking_str = headers[i]
                if checking_str != 'name':
                    checking_str_val = row[checking_str]

                    if int(checking_str_val) == int(strs_count_list[i]):
                        match_count += 1

            # header_length - 1 remove one of the first one being name
            if match_count == (header_length - 1):
                strs_list_match = row['name']
    return strs_list_match


main()