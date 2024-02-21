#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// pair_strengths[i][j] is the num of voters who prefer i over j
int pair_strengths[MAX_CANDIDATES][MAX_CANDIDATES] = {0};

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
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // iterate over all the candidates to find given name
    for (int i = 0; i < candidate_count; i++)
    {
        // if name is match for name of valid candidate
        if (strcmp(name, candidates[i].name) == 0)
        {
            // update global prefrences array to indicate that the voter has their rank preference
            // if preference is successfully recorded, the function should return true
            preferences[voter][rank] = i;
            return true;
        }
    }

    // else return false, for instance ` name != candidateName `
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // iterate over all pairs of candidates (i, j) to calculate pairwise strengths
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // initialize strengths to zero
            int strength_i_j = 0;
            int strength_j_i = 0;

            if (i != j)
            {
                // iterate over all voters to calculate pairwise strengths
                for (int k = 0; k < voter_count; k++)
                {
                    int preferred_i = preferences[k][0];
                    int preferred_j = preferences[k][1];
                    // check if voter k prefers i over j
                    if (preferred_i == i && preferred_j == j)
                    {
                        strength_i_j++;
                    }
                    // check if voter k prefers candidate(j) or candidate(i)
                    if (preferred_i == j && preferred_j == i)
                    {
                        strength_j_i++;
                    }
                    // if voter does not have preference, then no strength is added
                }
                // store strengths in pair_strengths array
                pair_strengths[i][j] = strength_i_j;
                pair_strengths[j][i] = strength_j_i;
            }

        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // calculate total number of votes
    int total_votes = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        total_votes += candidates[i].votes;
    }

    // iterate over candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if any candidate > 50% of votes
        if (candidates[i].votes > total_votes / 2)
        {
            // print winner & return true
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    // return false if a candidate has yet to win
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // initalize maximum possible value
    int min_votes = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if(!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }
    }

    // return minimum vote total for candidate to win the election
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // iterate over candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            // if a tie does not exist return false
            return false;
        }
    }

    // if a tie exists return true
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // min = min number of votes anyone in the election currently has
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && !candidates[i].eliminated)
        {
            candidates[i].eliminated = true;
        }
    }
    // eliminate candidate who has min votes
    return;
}