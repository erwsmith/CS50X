#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];
candidate winner_list[MAX];
candidate temp;

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    int false_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes ++;
            return true;
        }
        else
        {
            false_count ++;
        }
    }

    if (false_count == candidate_count)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    string votes_leader = "Votes uncounted";
    int n = candidate_count;

    // Implement Bubble Sort on candidates by number of votes, descending:
    // repeat n-1 times
    for (int i = 0; i < n - 1; i++)
    {
        // for j from 0 to n - 2
        for (int j = 0; j <= n - 2; j++)
        {
            // if candidates[j] and candidates[j+1] are out of order
            if (candidates[j].votes < candidates[j + 1].votes)
            {
                // swap j and j+1
                temp = candidates[j];
                candidates[j] = candidates[j + 1];
                candidates[j + 1] = temp;
            }
        }
    }

    // save initial winner
    winner_list[0] = candidates[0];

    // check for ties, starting with winner
    for (int i = 0; i < n - 1; i++)
    {
        if (candidates[i].votes == candidates[i + 1].votes)
        {
            winner_list[i + 1] = candidates[i + 1];
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (winner_list[i].name != NULL)
        {
            printf("%s\n", winner_list[i].name);
        }
    }
    return;
}