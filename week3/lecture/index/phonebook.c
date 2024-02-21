#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    person people[2];

    // define name and number of person
    people[0].name = "carter";
    people[0].number = "651-123-1423";

    people[1].name = "david";
    people[1].number = "651-222-2212";

    // prompt user for name
    string name = get_string("Name: ");

    // iterate through people array and list number with "found" message
    for (int i = 0; i < 2; i++)
    {
        if (strcmp(people[i].name, name) == 0)
        {
            printf("Found %s\n", people[i].number);
            return 0;
        }
    }

    // error not found
    printf("Not found\n");
    return 1;
}