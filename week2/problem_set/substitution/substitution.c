#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // accept single line cmd line arg
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // validate key: 26 alphabetical characters
    // key is invalid if === anything other than alphabetical characters
    string key = argv[1];
    int key_length = strlen(key);
    if (key_length != 26)
    {
        printf("Key must be 26 characters long.\n");
        return 1;
    }
    for (int i = 0; i < key_length; i++)
    {
        if(!isalpha(key[i]))
        {
            printf("Key can only contain alphabetical characters.\n");
            return 1;
        }
        for (int j = i + 1; j < key_length; j++)
        {
            if (key[i] == key[j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    // prompt user for a plaintext string
    string plaintext = get_string("plaintext: ");

    // encrypt plaintext
    int plain_length = strlen(plaintext);
    string ciphertext = plaintext;
    for (int i = 0; i < plain_length; i++)
    {
        if (isalpha(plaintext[i]))
        {
            int offset = isupper(plaintext[i]) ? 'A' : 'a';
            int j = toupper(plaintext[i]) - 'A';
            char ciphertext_char = isupper(plaintext[i]) ? toupper(key[j]) : tolower(key[j]);
            ciphertext_char -= offset - 'A';
            ciphertext[i] = isupper(plaintext[i]) ? toupper(ciphertext_char) : tolower(ciphertext_char);
        }
    }

    // print the plaintext and ciphertext
    printf("ciphertext: %s\n", ciphertext);

    // exit the program
    printf("\n");
    return 0;

    // must output `plaintext: ` and prompt user for a string using get_string
    // must output `ciphertext: ` followed by plaintext's ciphertext
        // each alphabetical char in plaintext substituted for ciphertext
    // after output, print a newline, return 0, and exit program

}