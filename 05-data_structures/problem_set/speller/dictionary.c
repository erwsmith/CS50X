// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// function prototypes
bool load(const char *dictionary);
unsigned int hash(const char *str);
unsigned int size(void);
bool check(const char *str);
bool unload(void);

node *create(char *dict_word);
node *insert(int h, char *str);
void destroy(node *head);

// Number of buckets in hash table
const unsigned int N = 100;

// Hash table - every element in array is a pointer to a node
node *table[N];

// Hash table index
int hash_code;

char dict_word[46];
unsigned int word_count = 0;

bool load(const char *dictionary)
{
    // Open dictionary file if valid
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s\n", dictionary);
        return false;
    }

    // scan all words in dictionary file
    while (fscanf(inptr, "%s", dict_word) != EOF)
    {
        // hash word (get hash_code int)
        hash_code = hash(dict_word);

        // if table[hash_code] is empty, create a node there
        if (table[hash_code] == NULL)
        {
            table[hash_code] = create(dict_word);
        }
        // if table[hash_code] already has a node, insert a new node to start a linked list
        else
        {
            table[hash_code] = insert(hash_code, dict_word);
        }
        // track word count for size()
        word_count++;
    }
    fclose(inptr);
    return true;
}

// Hashes word to a number
unsigned int hash(const char *str)
{
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        sum += tolower(str[i]);
    }
    return sum % N;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        return word_count;
    }
    else
    {
        return 0;
    }
}

// Returns true if word is in dictionary, else false
bool check(const char *str)
{
    hash_code = hash(str);
    if (table[hash_code] != NULL)
    {
        for (node *tmp = table[hash_code]; tmp != NULL; tmp = tmp->next)
        {
            if (strcasecmp(tmp->word, str) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // iterate through hash table, freeing all nodes
    for (int i = 0; i < N; i++)
    {
        destroy(table[i]);
    }
    return true;
}

// delete and free all memory from linked list
void destroy(node *head)
{
    if (head == NULL)
    {
        return;
    }

    // recursive case
    destroy(head->next);

    // base case
    free(head);
}

// creates a new node
node *create(char *str)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("bad\n");
    }
    strcpy(n->word, str);
    n->next = NULL;
    return n;
}

// inserts a new node into existing linked list
node *insert(int h, char *str)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("bad\n");
    }
    strcpy(n->word, str);
    n->next = table[h];
    return n;
}