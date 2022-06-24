#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
// see 8:30 in walkthu vid for explanation and visualization
int preferences[MAX][MAX];

// locked[i][j] means candidate i is locked in over candidate j
bool locked[MAX][MAX];

// Each pair has a winner, loser
// int for the candidate's index
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle_check(int origin, int end);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();

    // // test record_preferences()
    // printf("\npreferences\n");
    // for (int i = 0; i < candidate_count; i++)
    // {
    //     for (int j = 0; j < candidate_count; j++)
    //     {
    //         {
    //             printf("[%i][%i]: %i\t", i, j, preferences[i][j]);
    //         }
    //     }
    //     printf("\n");
    // }
    // // end test record_preferences()

    // // test add_pairs()
    // printf("\npair_count: %i\n", pair_count);
    // printf("\nunsorted pairs: (winner, loser)\n");
    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf("%i, %i\n", pairs[i].winner, pairs[i].loser);
    // }
    // printf("\n");
    // // end test add_pairs()

    // // test sort_pairs()
    // printf("sorted pairs: (winner, loser)\n");
    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf("%i, %i\n", pairs[i].winner, pairs[i].loser);
    // }
    // printf("\n");
    // // end test sort_pairs()

    // // test lock_pairs()
    // printf("locked pairs matrix\n");
    // for (int i = 0; i < candidate_count; i++)
    // {
    //     for (int j = 0; j < candidate_count; j++)
    //     {
    //         if (locked[i][j])
    //         {
    //             printf("[%i][%i]: TRUE\t", i, j);
    //         }
    //         else if (!locked[i][j])
    //         {
    //             printf("[%i][%i]: \t", i, j);
    //         }
    //         else
    //         {
    //             printf("[%i][%i]: ???\t", i, j);
    //         }
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    // // end test lock_pairs()

    return 0;
} // end main


// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // ranks[i] represents voter's ith preference
    int false_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences array given one voter's ranks
// preferences[i][j] is number of voters who prefer i over j
// ranks[i] represents voter's ith preference
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // whenever i is less than j, add one to the preferences array
            // using the corresponding ranks at i and j
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]] ++;
            }
        }
    }
    return;
}

// Record pairs (update pairs array and pair_count) of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count ++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
// strength of victory is defined to be the number of voters
// who prefer the preferred candidate
void sort_pairs(void)
{
    // use bubble sort
    int n = pair_count;
    for (int i = 0; i < n - 1; i++)
    {
        // for j from 0 to n - 2
        for (int j = 0; j <= i - 1; j++)
        {
            // if values are out of order (sorting descending)
            // preferences[i][j] = number of voters that prefer i over j
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                // swap numbers
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
// update 'locked' array.
// locked[i][j] means candidate i is locked in over candidate j
// bool locked[MAX][MAX]; has been initialized with all values = false
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int winner_count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (!locked[j][i])
            {
                winner_count ++;
            }
        }

        if (winner_count == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}