#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

node *create(int val);
node *insert(node *head, int val);
bool find(node* head, int val);
void destroy(node *head);

int main(void)
{
    // list of size 0
    node *head = NULL;

    // create first node
    head = create(9);

    // insert nodes into list
    for (int i = 8; i >= 0 ; i--)
    {
        head = insert(head, i);
    }

    // print numbers
    int node_count = 0;
    for (node *tmp = head; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
        node_count++;
    }
    printf("%i nodes counted\n", node_count);

    // search linked list for a particular value
    int value = -1;
    bool exists = find(head, value);
    if (exists)
    {
        printf("%i found\n", value);
    }
    else
    {
        printf("%i was not found\n", value);
    }

    // free list
    destroy(head);

    return 0;
}

node *create(int val)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("bad\n");
    }
    n->number = val;
    n->next = NULL;
    return n;
}
// insert a new node at beginning of linked list,
// returns pointer to next node
node *insert(node* head, int val)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        printf("bad\n");
    }
    n->number = val;
    n->next = head;
    return n;
}

bool find(node* head, int val)
{
    for (node *trav = head; trav != NULL; trav = trav->next)
    {
        if (trav->number == val)
        {
            return true;
        }
    }
    return false;
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