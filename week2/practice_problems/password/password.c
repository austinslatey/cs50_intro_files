// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_number = false;
    bool has_symbol = false;

    for (int i = 0; password[i] != '\0'; i++)
    {
        char c = password[i];

        if (isupper(c))
        {
            // set uppercase to true
            has_upper = true;

        }
        else if (islower(c))
        {
            // set lowercase to true
            has_lower = true;

        }
        else if (isdigit(c))
        {
            // set number to true
            has_number = true;

        }
        else if (ispunct(c))
        {
            // set symbols to true
            has_symbol = true;

        }
    }

    return has_upper && has_lower && has_number && has_symbol;

}