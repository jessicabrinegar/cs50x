// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 51;
// Global variable to track how many words in dictionary
int counter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashValue = hash(word);
    node *ptr = table[hashValue];

    while (ptr != NULL)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }

        ptr = ptr->next;

    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Ensure this fx is case insensitive
    // Output should be numerical index between 0 & N-1 inclusive
    // Can take value % N if hash value is greater than N
    int tracker = 0;
    for (int i = 0; i < 2; i++)
    {
        if (isalpha(word[i]) != 0)
        {
            int num = toupper(word[i]) - 'A';
            tracker += num;
        }
    }
    // return toupper(word[0]) - 'A';
    return tracker;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Read words from the dictionary one at a time (word, a char array to read the word into)
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for a new node, ensuring you have the memory available
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // Copy the word into the new node
        strcpy(n->word, word);

        // Get the hash value from the hash function, storing it as index
        int index = hash(word);

        // Set the new node's next pointer to what the hash table's index is pointing to
        if (table[index] == NULL)
        {
            n->next = NULL;
        }
        else
        {
            n->next = table[index];
        }

        // Set the hash table's index to be pointing to the newly created node
        table[index] = n;

        // Keep track of how many words are read (for size fx)
        counter += 1;

    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
// Free any memory allocated in load
// Use valgrind to check if this was done correctly (valgrind ./speller texts/cat.txt)
bool unload(void)
{
    // TODO
    node *tmp;
    node *cursor;
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            cursor = table[i];
            while (cursor != NULL)
            {
                tmp = cursor;
                cursor = cursor->next;
                free(tmp);
            }
        }

    }
    return true;
}