#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

//My variables
int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool isLoop(int pairWinner, int lastLoser);

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
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++)
    {
        if (strcmp(name, candidates[candidateIndex]) == 0)
        {
            ranks[rank] = candidateIndex;
            return true;                    //We shall assume no duplicate names
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = 1; j < candidate_count - i; j++)
        {
            preferences[ranks[i]][ranks[i+j]]++; //step through recording who preferred who to whom
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            //Assigning pairs where it isn't a draw to a new array called "pairs"
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int swaps = -1;
    pair swapper;
    swapper.winner = 0;
    swapper.loser = 0;

    do
    {
        swaps = 0;
        for (int i = pair_count - 1; i > 0; i--)
        {
            //Bubble sort but in descending order
            if (preferences[pairs[i].winner][pairs[i].loser] > preferences[pairs[i - 1].winner][pairs[i - 1].loser])
            {
                swaps++;
                swapper = pairs[i - 1];
                pairs[i - 1] = pairs[i];
                pairs[i] = swapper;
            }
        }
    }
    while (swaps !=0);

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int x = 0; x < pair_count; x++) //Step through pairs, locking each one if it doesn't make a loop
    {
        locked[pairs[x].winner][pairs[x].loser] = true;
        if (isLoop(pairs[x].winner, pairs[x].loser) == true)
        {                                                  
            locked[pairs[x].winner][pairs[x].loser] = false; //Clunky perhaps but needed to be able to recursively iterate over the graph
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    int numFalse = 0;

    for (int a = 0; a < candidate_count; a++)
    {
        numFalse = 0;

        for (int b = 0; b < candidate_count; b++)
        {
            if (locked[b][a] == false)
            {
                numFalse++;
            }
        }

        if (numFalse == candidate_count)
        {
            printf("%s\n", candidates[a]);
        }
    }
    return;
}

bool isLoop(int pairWinner, int lastLoser)
{
    bool wasThisALoop = false;
    int loser = 0;

    while (wasThisALoop == false && loser < candidate_count) //We only need one instance of true to get out of this quagmire
    {
        if (locked[lastLoser][loser] == true) //Checks through all of the candidates lastLoser points to in the graph so far
        {
            if (loser == pairWinner) //If the pointee is the winner of the pair that was passed to the first instance of isLoop then it's a loop
            {
                wasThisALoop = true;
            }
            else
            {
                wasThisALoop = isLoop(pairWinner, loser); //Else go one level deeper and iterate over all the candidates the pointee points to
            }
        }

        loser++;
    }
    return wasThisALoop;
}