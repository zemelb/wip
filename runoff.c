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
    // TODO

    //look for candidate called name
    //if found, update preferences so that they are the (voter)'s (rank) preference and return true
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)      //if match for name found
        {
            preferences[voter][rank] = i;
            return true;
        }
    }

    //if not found, return false
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO

    //update vote counts for all non-eliminated candidates

    for (int j = 0; j < 1; j++)
    {
        //incrementing through total number of voters
        for (int i = 0; i < voter_count; i++)
        {
            int n = preferences[i][j];

            if (candidates[n].eliminated == false)
            {
                candidates[n].votes++;
                j=0;
            }
            else
            //if candidate is eliminated, go to voter's nextp preference
            {
                i--;
                j++;
            }
        }
    }

    //remember each voter votes for their highest preference candidate who has not yet been eliminated

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO

    //if any candidate has more than half the vote, print their name and return true

    int votesneeded = voter_count / 2 + 0.5;
    bool winner;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > votesneeded)
        {
            winner = true;
            printf("%s\n", candidates[i].name);
            return winner;
        }
    }
    //if no one has won, print nothing and return false
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    //initialize a, will use this as the min vote count. start it as the total number of voters
    int a = voter_count;

    //return minimum number of votes of anyone still in the election (eliminated = false)

    //iterate through each candidate
    for (int i = 0; i < candidate_count; i++)
    {

    //if eliminated = false,
        if (candidates[i].eliminated == false && a > candidates[i].votes)
            a = candidates[i].votes;
    }
    return a;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO

    //input is minimum number of votes, int min

    for (int i = 0; i < candidate_count; i++)
    {
    //returns true if the election is tied between all remaining candidates
        if (candidates[i].eliminated == false && candidates[i].votes == min)
            return true;
    }
    //otherwise return false
    return false;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // TODO

    //eliminate anyone still in the race who has the min number of votes, which is what we calculated in find_min

    for (int i = 0; i < candidate_count; i++)
        // if candidate's votes are equal to or less than minimum votes, change .eliminated to true
        
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes == min)
            {
                candidates[i].eliminated = true;   
            }
        }
    return;
}
