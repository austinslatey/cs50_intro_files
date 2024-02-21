#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // prompt user for credit card
    long long card_number;

    do
    {
        card_number = get_long("Number:  ");
    }
    while (card_number < 1);

    // check if the card num is valid to find card company numeric issued card
    int sum = 0, digits = 0;
    long long temp = card_number;

    // loop through the card nums digits from right to left
    while (temp > 0)
    {
        // if even digit position, add digit to sum
        if (digits % 2 == 0)
        {
            sum += temp % 10;
        }
        else
        {
            // if odd digit position, double digit and add the sum of its digits to sum
            int digit = 2 * (temp % 10);
            sum += digit / 10 + digit % 10;
        }

        // move to next digit
        temp /= 10;

        // increment digit position
        digits++;
    }

    // American, Express, MasterCard, or Visa
    // if sum of digits is a multiple of 10, card number is potentially valid
    if (sum % 10 == 0)
    {
        // Amex starts with 34 || 37
        if ((card_number >= 340000000000000 && card_number < 350000000000000) || (card_number >= 370000000000000 &&
                card_number < 380000000000000))
        {
            printf("AMEX\n");
        }
        // Mastercard starts with 51-55
        else if (card_number >= 5100000000000000 && card_number < 5600000000000000)
        {
            printf("MASTERCARD\n");
        }
        // Visacard numbers start with 4
        else if ((card_number >= 4000000000000000 && card_number < 5000000000000000) || (card_number >= 4000000000000 &&
                 card_number < 5000000000000))
        {
            printf("VISA\n");
        }
        else
        {
            // if card does not match pattern return invalid to user
            printf("INVALID\n");
        }
    }
    else
    {
        // if sum of digits !== a multiple of 10, card is invalid
        printf("INVALID\n");
    }
}