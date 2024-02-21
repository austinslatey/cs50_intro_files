from cs50 import get_string

card_number = get_string("Number: ")

# Multiply every other digit by 2, starting from the second-to-last digit
doubled_digits = [int(digit) * 2 for digit in card_number[-2::-2]]

# Sum the digits of the doubled products and the remaining digits
total = sum([digit // 10 + digit % 10 for digit in doubled_digits]) + sum([int(digit) for digit in card_number[-1::-2]])

# Check the card's validity and determine the card type
if total % 10 == 0:
    if len(card_number) == 15 and card_number[:2] in ["34", "37"]:
        print("AMEX")
    elif len(card_number) == 16 and card_number[:2] in ["51", "52", "53", "54", "55"]:
        print("MASTERCARD")
    elif len(card_number) in [13,16] and card_number[0] == "4":
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
