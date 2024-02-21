#include <cs50.h>
#include <stdio.h>

// Function prototypes
int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}


// Prompt the user for input and return num of cents as int
int get_cents(void)
{
    int cents;
    do
    {
        // Promt user
        cents = get_int("Change owed: ");
    }
    // If negative num, re-prompt user for vaild entry
    while (cents < 0);
    return cents;
}

// Calculate the num of quarters and return as int
int calculate_quarters(int cents)
{
    // divide num of cents by 25 and return
    return cents / 25;
}

// Calculate the num of dimes and return as int
int calculate_dimes(int cents)
{
    // calculate remainder after dividing num of cents by 25
    // cents = cents % 25;
    return cents / 10;
}

// Calculate the num of nickles and return as int
int calculate_nickels(int cents)
{
    // calculate remainder after dividing num of cents by 25
    // cents = cents % 25 % 10;
    return cents / 5;
}

// Calculate the num of pennies and return as int
int calculate_pennies(int cents)
{
    // calculate remainder after dividing num of cents by 25,10, and 5
    // cents = cents % 25 % 10 % 5;
    return cents / 1;
}
