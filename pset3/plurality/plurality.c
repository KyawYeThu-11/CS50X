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

//for tie_winners
typedef struct
{
    string name;
    int votes;
}
tieWinners;

tieWinners tie_winners[MAX];


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
    for (int i=0; i < candidate_count; i++)
    {
        if (strcmp(name,candidates[i].name)==0)
        {
            candidates[i].votes++;//using the concept of reference variable
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int counter=0;
    int index=0;

    //Putting the most voted person last
    for (int i=0; i< candidate_count - 1; i++)
    {
        if (candidates[i].votes>candidates[i + 1].votes)
        {
            candidates[i + 1].votes=candidates[i].votes;
            candidates[i + 1].name=candidates[i].name;
        }
        //collecting the first person of the tie_winner so far
        else if (candidates[i].votes==candidates[i + 1].votes)
        {
            tie_winners[index].name=candidates[i].name;
            tie_winners[index].votes=candidates[i].votes;
            index++;
        }
    }

    //if there is indeed tie winner
    if (index!=0)
    {
        //if there is tie winner who has the same vote as that of the last person
        if (tie_winners[index - 1].votes==candidates[candidate_count-1].votes)
        {
            //selecting only those who have the same vote as that of the last person
            for (int i=0; i<index; i++)
            {
                if(tie_winners[i].votes==tie_winners[index - 1].votes)
                {
                    printf("%s\n", tie_winners[i].name);
                }
            }
            printf("%s\n", candidates[candidate_count-1].name);
        }
        else if (tie_winners[index].votes < candidates[candidate_count-1].votes)
        {
            printf("%s\n", candidates[candidate_count-1].name);
        }
    }
    else
    {
        printf("%s\n", candidates[candidate_count-1].name);
    }
}

