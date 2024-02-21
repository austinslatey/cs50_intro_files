#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

// function prototype calc_hours
float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    // get weeks from user input
    int weeks = get_int("Number of weeks taking CS50: ");
    // calculate amount of hours
    int hours[weeks];
    // iterate through weeks to print hour amount to usr
    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    // get user's output preference
    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    // print result
    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{
    // init var to calculate total hours
    int total_hours = 0;

    // iterate through the hours array and add up all the hours
    for (int i = 0; i < weeks; i++)
    {
        total_hours += hours[i];
    }

    // if user requests total num of hours,
    if (output == 'T')
    {
        return total_hours;
    }
    // average hours per week, calculate, and return
    else if (output == 'A')
    {
        // calculate, and return
        return (float)total_hours / weeks;
    }
    else if (output == 'B')
    {
        float average_hours = (float)total_hours / weeks;
        printf("Total hours: %.1f\nAverage hours per week:  %.1f\n" , (float)total_hours, average_hours);
        return -1.0;
    }
    else
    {
        // Invalid
        printf("Invalid input\n");
        return -1.0;
    }
}