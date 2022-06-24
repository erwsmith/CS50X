#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <strings.h>
#include "dictionary.h"

#define DICTIONARY "dictionaries/small"
// #define DICTIONARY "dictionaries/large"

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// unsigned int hash(char *str);
unsigned int hash(const char *str);
bool load(const char *dictionary);
node *create(char *dict_word);
node *insert(int h, char *str);

const unsigned int N = 1;
unsigned int word_count = 0;
node *table[N];
int hash_code;
char dict_word[46];
node *head = NULL;

int main(void)
{
    char *dictionary = DICTIONARY;
    load(dictionary);

    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
            {
                printf("%s\n", tmp->word);
            }
        }
    }
    return 0;
}

bool load(const char *dictionary)
{
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s\n", dictionary);
        return false;
    }

    while (fscanf(inptr, "%s", dict_word) != EOF)
    {
        hash_code = hash(dict_word);

        // if table[hash_code] is empty
        if (table[hash_code] == NULL)
        {
            table[hash_code] = create(dict_word);
        }
        // if table[hash_code] already has a node
        else
        {
            table[hash_code] = insert(hash_code, dict_word);
        }
        word_count++;
    }
    return true;
}

unsigned int hash(const char *str)
{
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        sum += str[i];
    }
    return sum % N;
}

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