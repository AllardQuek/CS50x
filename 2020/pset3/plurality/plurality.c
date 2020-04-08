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
    candidate_count = argc - 1;     // Do not include first argument which runs the script
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // For each candidate, initalise their name and votes values
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];   // Start from 2nd arg onwards
        candidates[i].votes = 0;            // Initially no votes yet
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
    // TODO: Assume no 2 candidates have same name
    // If name matches any candidate, update candidate's vote total; return True if successful
    for (int i = 0; i < candidate_count; i++)
    {
        // printf("NAME: %s\n", candidates[i].name);
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            // printf("%i\n", candidates[i].votes);
            return true;
        }
    }

    return false;

}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    // Print NAME of candidate with most votes then print NEWLINE
    // If tie, output NAMES of winners, each on a SEPARATE LINE
    int max_idxs[9];    // At most a tie between all 9 candidates
    int counter = 0;
    int max = -1;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max)
        {
            max = candidates[i].votes;
            max_idxs[counter] = i;
            counter ++;
        }
        else if (candidates[i].votes == max)
        {
            max_idxs[counter] = i;
            counter++;
        }
    }

    for (int j = 0; j < counter; j++)
    {
        int ind = max_idxs[j];
        printf("%s\n", candidates[ind].name);
    }

    return;
}

