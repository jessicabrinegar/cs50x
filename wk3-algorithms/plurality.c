#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Implement a program that runs a plurality election
// In plurality vote, every voter gets to vote for one candidate.
// At the end of the election, whichever candidate has the greatest number of votes is declared the winner of the election
// Example:
/*
$ ./plurality Alice Bob Charlie
Number of voters: 4
Vote: Alice
Vote: Bob
Vote: Charlie
Vote: Alice
Alice
*/

// Max number of candidates
// This is a constant variable that can be used throughout the program
#define MAX 9

// A struct groups related variables. Unlike an array, it can have various data types.
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
    // Candidate count found by getting number of arguments given (minus 1 because one argument is ./plurality (to run the program))
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
        printf("%s\n", candidates[i].name);
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
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > count)
        {
            count = candidates[i].votes;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == count)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}