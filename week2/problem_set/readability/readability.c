#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


float compute_index(string text);

int main(void)
{

    // prompt user for a string of text using get_string
    string text = get_string("Text: ");
    // count number of letters in text
    float index = compute_index(text);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", round(index));
    }

}

float compute_index(string text)
{
    int letter_count = 0;
    int word_count = 1;
    int sentence_count = 0;
    // iterate through the text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];

        // assume that any lower or uppercase char
        if (isalpha(c))
        {
            letter_count++;
        }
        // any sequence of characters seperated by spaces
        else if (c == ' ')
        {
            word_count++;
        }
        // any occurance of any '. ! ?'
        else if (c == '.' || c == '!' || c == '?')
        {
            sentence_count++;
        }
    }

    // compute the avg num of letters per 100 words
    float L = (float)letter_count / (float)word_count * 100.0;

    // compute the avg num of sentences per 100 words
    float S = (float)sentence_count / (float)word_count * 100.0;

    // compute the Coleman-Liau
    float index = 0.0588 * L - 0.296 * S - 15.8;

    return index;
}