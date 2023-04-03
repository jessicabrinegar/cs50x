import math


def main():
    creditNum = get_creditNum()
    length = get_length(creditNum)
    validity = is_card_valid(creditNum)
    if validity:
        get_card_type(creditNum, length)
    else:
        print("INVALID")


def get_creditNum():
    while True:
        try:
            creditNum = int(input("Number: "))
            return creditNum
        except ValueError:
            print("Please type a number.")


def get_length(creditNum):
    # Returns number of digits (the length)
    digits = int(math.log10(creditNum)) + 1
    return digits


def get_card_type(creditNum, length):
    if is_mc_valid(creditNum, length):
        print("MASTERCARD")
    elif is_amex_valid(creditNum, length):
        print("AMEX")
    elif is_visa_valid(creditNum, length):
        print("VISA")
    else:
        print("INVALID")


def is_mc_valid(creditNum, length):
    first_two_digits = int(str(creditNum)[:2])
    if length == 16 and (first_two_digits > 50 and first_two_digits < 56):
        return True
    else:
        return False


def is_amex_valid(creditNum, length):
    first_two_digits = int(str(creditNum)[:2])
    if length == 15 and (first_two_digits == 34 or first_two_digits == 37):
        return True
    else:
        return False


def is_visa_valid(creditNum, length):
    first_digit = int(str(creditNum)[:1])
    if first_digit == 4 and (length == 13 or length == 16):
        return True
    else:
        return False


def multiply_and_sum(creditNum):
    sumOfDigits = 0
    digitMultiplied = int(2 * (creditNum % 10))
    while (digitMultiplied != 0):
        sumOfDigits += digitMultiplied % 10
        digitMultiplied = int(digitMultiplied / 10)
    return sumOfDigits


def sum_every_other_digit(creditNum):
    # Describes if the current digit should be used, or if it should be skipped
    useCurrentDigit = False
    # Keep track of the summation
    sum = 0
    while creditNum > 0:
        # If useCurrentDigit is true
        if useCurrentDigit:
            # Add the digit (or sum of digits) to the sum
            sum += multiply_and_sum(creditNum)
        # Switch the bool value of the useCurrentDigit variable
        useCurrentDigit = not useCurrentDigit
        # Divide creditNum by 10 (removing the last digit)
        creditNum = int(creditNum / 10)
    return sum


def sum_remaining_digits(creditNum):
    # Flip it to where it starts with the last digit instead of the second-to-last one
    useCurrentDigit = True
    sum = 0
    while creditNum > 0:
        if (useCurrentDigit):
            # Returns the digit and adds it to the sum
            sum += creditNum % 10
        # Switch the bool value of the useCurrentDigit variable
        useCurrentDigit = not useCurrentDigit
        creditNum = int(creditNum / 10)
    return sum


def is_card_valid(creditNum):
    # Sum that were multiplied
    sumOne = sum_every_other_digit(creditNum)
    # Sum that weren't multiplied
    sumTwo = sum_remaining_digits(creditNum)
    totalSum = sumOne + sumTwo
    bool = (totalSum % 10) == 0
    return bool


main()