# Credit card check pset 6
import cs50 as cs


def main():
    number = get_card_num("Number: ")

    if luhn_check(number):
        company_check(number)
    else:
        print("INVALID")

# Prompt user for card number


def get_card_num(prompt):

    while True:
        n = cs.get_string(prompt)
        if (len(n) >= 0) & (len(n) <= 16):
            break
        else:
            break

    return n
# Luhn’s algorithm check


def luhn_check(number):
    num_len = len(number)
    if num_len < 13 or num_len > 16:
        return

    add = 0
    non_multiples = 0
    isfirst = False

    # Iterate digits in reverse order
    for i in range(num_len - 1, -1, -1):

        if isfirst:
            ind_num = int(number[i])
            sum_of = (ind_num * 2)
            if sum_of > 9:
                string_sum = str(sum_of)
                add += int(string_sum[0])
                add += int(string_sum[1])
            else:
                add += sum_of

            # Change toggle
            isfirst = False
        else:
            # add every other number together
            ind_num = int(number[i])
            non_multiples += ind_num
            isfirst = True

    total = str(non_multiples + add)

    # first digit shoule be a 0
    if total[1] == '0':
        return True
    return False

# Check which company makes this card


def company_check(number):
    # first and second character
    char_1 = str(number[0])
    char_2 = str(number[1])

    # Check card type
    if (char_1 == '3') & (len(number) == 15) & (char_2 == '4' or char_2 == '7'):
        print("AMEX")
    elif ((char_1 == '5') & (int(char_2) < 6)) & (len(number) == 16):
        print("MASTERCARD")
    elif (len(number) == 16 or len(number) == 13) & (char_1 == '4'):
        print("VIZA")


main()