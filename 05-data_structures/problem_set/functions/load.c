#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICTIONARY "dictionaries/small"
// #define DICTIONARY "dictionaries/large"

// Represents a node in a hash table
typedef struct node
{
    char word[46];
    struct node *next;
}
node;

// function prototypes
bool load(const char *dictionary);
node *create(char *dict_word);
node *insert(node *head, char *dict_word);
bool find(node *head, int val);
void destroy(node *head);
bool unload(void);

int main(void)
{
    char *dictionary = DICTIONARY;
    load(dictionary);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    unsigned int word_count = 0;
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s\n", dictionary);
        return false;
    }

    // create word array with max word length
    char dict_word[46];

    // initialize head node
    node *head = NULL;

    // loop through all words in dictionary, keep count of words found, create linked list of all words
    while (fscanf(inptr, "%s", dict_word) != EOF)
    {
        if (word_count == 0)
        {
            head = create(dict_word);
        }
        else
        {
            head = insert(head, dict_word);
        }
        word_count++;
    }
    printf("%i words counted\n", word_count);

    // print words saved to linked list
    int node_count = 0;
    for (node *tmp = head; tmp != NULL; tmp = tmp->next)
    {
        printf("%s\n", tmp->word);
        node_count++;
    }
    printf("%i nodes counted\n", node_count);

    destroy(head);
    fclose(inptr);
    return true;
}

// create first node
node *create(char *dict_word)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("bad\n");
    }
    strcpy(n->word, dict_word);
    n->next = NULL;
    return n;
}

// insert a new node at beginning of linked list, returns pointer to next node
node *insert(node *head, char *dict_word)
{
    // use malloc to store a new node, check for NULL
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("bad\n");
    }
    // copy word into node
    strcpy(n->word, dict_word);
    n->next = head;
    return n;
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