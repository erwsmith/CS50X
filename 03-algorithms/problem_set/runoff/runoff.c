// Perform runoff voting given command line entries
// Usage: ./runoff [candidate_1 candidate_2 ... candidate_n]
// main loop and function prototypes provided by CS50X, functions written by Eric 14 April 2022

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

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

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

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

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // test tabulate
        // for (int i = 0; i < candidate_count; i++)
        // {
        //     printf("%s %i\n", candidates[i].name, candidates[i].votes);
        // }
        
        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;

    // FUNCTION TESTING

    // vote function (called above)
    // preferences[i][j] stores the index of the candidate who is the jth ranked preference for the ith voter.
    // for (int voter = 0; voter < voter_count; voter++)
    // {
    //     printf("Voter %i: ", voter);
    //     for (int rank = 0; rank < candidate_count; rank++)
    //     {
    //         printf("%s ", candidates[preferences[voter][rank]].name);
    //         printf("%i ", rank);
    //     }
    //     printf("\n");
    // }

    // // tabulate must be called for print_winner to work
    // print_winner();
    // printf("%s\n", is_tie(find_min()) ? "true" : "false");
    // tabulate();
    // is_tie(find_min());

    // bool won = print_winner();
    // if (won)
    // {
    //     printf("end\n\n");
    // }

    // end of function testing

} // end of main()

// Record voter's preference for the given candidate if vote is valid
bool vote(int voter, int rank, string name)
{
    // validate vote, if valid, update preferences array to
    // indicate that the 'voter' has that 'candidate' as their 'rank' preference
    int false_count = 0;
    for (int c = 0; c < candidate_count; c++)
    {
        if (strcmp(name, candidates[c].name) == 0)
        {
            preferences[voter][rank] = c;
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
    for (int voter = 0; voter < voter_count; voter++)
    {
        for (int rank = 0; rank < candidate_count; rank++)
        {
            // printf("voter %i, rank %i, %s, (candidate index = %i)\n", voter, rank, candidates[preferences[voter][rank]].name, preferences[voter][rank]);
            if (!candidates[preferences[voter][rank]].eliminated)
            {
                candidates[preferences[voter][rank]].votes ++;
                break;
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > ((float) voter_count / 2))
        {
            printf("%s\n", candidates[i].name);
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
            if (!candidates[j].eliminated && !candidates[j + 1].eliminated && candidates[j].votes > candidates[j + 1].votes)
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

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int n = candidate_count;
    int remaining_candidates = 0;
    for (int i = 0; i < n; i++)
    {
        // if candidates haven't been eliminated and candidate votes are equal, add to tie count
        if (!candidates[i].eliminated)
        {
            remaining_candidates ++;
        }
    }
    // printf("Candidates remaining: %i\n", remaining_candidates);

    int tie_count = 0;
    for (int i = 0; i < remaining_candidates; i++)
    {
        if (candidates[i].votes == min)
        {
            tie_count ++;
        }
    }

    if (tie_count == remaining_candidates)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}