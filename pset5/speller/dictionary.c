// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <cs50.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 675;
int SIZE = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    string clone = malloc(strlen(word) + 1);
    strcpy(clone, word);

    for (int i = 0; i< strlen(clone); i++)
    {
        clone[i] = tolower(clone[i]);
    }

    unsigned int index = hash(clone);
    node *trav = table[index];

    while (true)
    {
        if (strcmp(trav->word, clone) == 0)
        {
            free(clone);
            return true;
            break;
        }
        else
        {
            if (trav->next == NULL)
            {
                free(clone);
                return false;
                break;
            }
            else
            {
                trav = trav->next;
            }
        }
    }
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash;
    char first_char = tolower(word[0]);
    int aindex = ((int) first_char) - 97;

    if ((int) word[1] == 0)
    {
        hash = aindex;
        return hash;
    }
    else
    {
        int bindex = ((int) word[1]) - 97;
        aindex = aindex * 26;

        hash = aindex + bindex;
        return hash;
    }
}

void set_NULL(void);
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        return false;
    }

    set_NULL();
    char buffer[LENGTH+1];
    while (fscanf(input, "%s", buffer) != EOF)
    {
        SIZE++;
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Unable to load into the hash table");
            break;
        }

        strcpy(n->word, buffer);

        unsigned int index = hash(n->word);
        if (table[index] == NULL)
        {
            n->next = NULL;
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
    }
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return SIZE;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i< N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}

//Setting all head pointers in table to NULL
void set_NULL(void)
{
    for (int i = 0; i< N; i++)
    {
    table[i] = NULL;
    }
}
