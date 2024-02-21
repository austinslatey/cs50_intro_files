// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get the hash index for the word
    unsigned int index = hash(word);

    node *cursor = table[index];
    while (cursor != NULL)
    {
        // compare words case insensitivey
        if (strcasecmp(cursor->word, word) == 0)
        {
            // Word found in the dictionary
            return true;
        }
        // next node
        cursor = cursor->next;
    }
    // word not found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // initalize the hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Read words from the file and insert them into the hash table
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            // unable to allocate memory
            return false;
        }

        // copy the word to node
        strncpy(new_node->word, word, LENGTH + 1);

        // Hash the word to get the index in the hash table
        unsigned int index = hash(word);

        // insert the new node at start of linked list
        new_node->next = table[index];
        table[index] = new_node;
    }

    fclose(file);
    // loaded dictionary sucessfully
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;

    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            count++;
            cursor = cursor->next;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        table[i] = NULL;
    }
    // success unloading dictionary
    return true;
}
