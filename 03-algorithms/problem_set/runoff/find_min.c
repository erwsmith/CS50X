#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                // this line was in the original, it exits the program without printing 'invalid vote'
                return 4;
            }
        }
        printf("\n");
    }
    // find_min();
    printf("min: %i\n", find_min());
}

bool vote(int voter, int rank, string name)
{
    // validate vote, if valid, update preferences array to
    // indicate that the 'voter' has that 'candidate' as their 'rank' preference
    // using index j to refer to the candidate and i to refer to the voter
    // even though it breaks the convention of i outer loop, j inner loop.
    int false_count = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(name, candidates[j].name) == 0)
        {
            preferences[voter][j] = rank;
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

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // check if candidate has been eliminated
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            for (int j = 0; j < voter_count; j++)
            {
                // if candidate is a voter's top choice, add 1 to their vote count
                if (preferences[j][i] == 0)
                {
                    candidates[i].votes ++;
                }
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes > ((float) voter_count / 2))
        {
            printf("%s\n", candidates[j].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min;
    int n = candidate_count;
    for (int i = 0; i < n - 1; i++)
    {
        // for j from 0 to n - 2
        for (int j = 0; j <= n - 2; j++)
        {
            // set new min value
            if (candidates[j].eliminated == false && candidates[j].votes > candidates[j + 1].votes)
            {
                min = candidates[j + 1].votes;
            }
            else
            {
                min = candidates[j].votes;
            }
        }
    }
    return min;
}