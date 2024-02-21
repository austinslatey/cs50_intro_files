#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

bool creates_cycle(int winner, int loser);

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[], int voter_count);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

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

        record_preferences(ranks, voter_count);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // iterate over all the candidates to find given name
    for (int i = 0; i < candidate_count; i++)
    {
        // if name is match for name of valid candidate
        if (strcmp(name, candidates[i]) == 0)
        {
            // update rank array to indicate that the voter has the candidate as their rank preference
            // if rank is successfully recorded, the function should return true
            int candidate_index = i;
            int temp = ranks[rank];
            ranks[rank] = candidate_index;

            // iterate over remaining ranks to adjust based on new vote
            for (int j = rank + 1; j < MAX; j++)
            {
                // if the candidate is already ranked higher statisticly, move it down
                if (ranks[j] == candidate_index)
                {
                    ranks[j] = temp;
                    break;
                }

                // else, shift the remaining candidates down
                int next_temp = ranks[j];
                ranks[j] = temp;
                temp = next_temp;
            }
            return true;
        }
    }

    // if error in rank recording return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[], int voter_count)
{
    // iterate over all pairs of candidates (i, j) to calculate pairwise strengths
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // initialize strengths to zero
            int strength_i_j = 0;
            int strength_j_i = 0;

            if (i != j)
            {
                // iterate over all voters to calculate pairwise strengths
                for (int k = 0; k < voter_count; k++)
                {
                    int preferred_i = ranks[k];
                    int preferred_j = -1;

                    // find index of candidate preferred
                    for (int l = 0; l < candidate_count; l++)
                    {
                        if (ranks[l] == preferred_i)
                        {
                            preferred_j = l;
                            break;
                        }
                    }

                    // if candidate j is preferred
                    if (preferred_j == j)
                    {
                        strength_j_i++;
                    }

                    // if candidate i is preferred
                    else if (preferred_j == i)
                    {
                        strength_i_j++;
                    }

                    // if voter does not have preference, then no strength is added
                }

                // update preferences based on strengths
                if (strength_i_j > strength_j_i)
                {
                    preferences[i][j]++;
                }
                else if (strength_j_i > strength_i_j)
                {
                    preferences[j][i]++;
                }
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // add all pairs of candidates where one candidate is preferred to the pairs array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // if candidate i is preferred over j, skip the pair
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }

    // update global variable ` pair_count ` to the number of candidate pairs
    // store between pairs[0] && pairs[pair_count - 1]
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // sort pairs in decreasing order of strength
    for (int i = 0; i < pair_count - 1; i++)
    {
        int max_strength = preferences[pairs[i].winner][pairs[i].loser];
        int max_strength_index = i;

        for (int j = i + 1; j < pair_count; j++)
        {
            int strength = preferences[pairs[j].winner][pairs[j].loser];
            if (strength > max_strength)
            {
                max_strength = strength;
                max_strength_index = j;
            }
        }

        pair temp_pair = pairs[i];
        pairs[i] = pairs[max_strength_index];
        pairs[max_strength_index] = temp_pair;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // create ` locked ` graph
    for (int i = 0; i < pair_count; i++)
    {
        // if cycle is created, remove pair[i] from locked graph
        locked[pairs[i].winner][pairs[i].loser] = true;

    }
    return;
}


// Print the winner of the election
void print_winner(void)
{
    // create array to track incoming edges for each candidate
    bool incoming[candidate_count];

    // initalize incoming edges to false every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        incoming[i] = false;
    }

    // mark the incoming edges as true for each candidate in locked graph
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                incoming[i] = true;
            }
        }
    }

    // find candidate with no incoming edges
    for (int i = 0; i < candidate_count; i++)
    {
        if (!incoming[i])
        {
            // print name of winning candidate
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}
