#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];
int new_prefer[MAX][MAX];
int newnew_prefer[MAX][MAX];
int prefer[MAX][MAX];


// Each pair has a winner, loser, each of which represent the candidate's index in the candidate array
//Array of all pairs where one candidate is preferred above another
//If there is a pair where two candidates tie, we will not add that pair in that array.
typedef struct
{
    int winner;
    int loser;
    int diff;
}
pair;

typedef struct
{
    int winner;
    int loser;
    int diff;
}
memory;
memory memories[1];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];



// Array of candidates
string candidates[MAX];
//Array of pairs
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
    for(int i=0; i<candidate_count; i++)
    {
        if(strcmp(name, candidates[i])==0)
        {
            ranks[rank]= i;
            return true;
        }
    }
    return false;
}

bool lookup (int k, int length, int finished_candidate[]);
// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int finished_candidate[MAX]={};
    int number_finished=0;

    printf("first array!\n");
    for (int a=0; a< candidate_count; a++)
    {
        for(int b=0; b<candidate_count; b++)
        {
            printf("%i",preferences[a][b]);
        }
        printf("\n");
    }
    printf("\n");
    
    for (int i=0; i< candidate_count; i++)
    {
        for (int j=0; j < candidate_count; j++)
        {
            for (int k=0; k < candidate_count; k++)
            {
                if (j!=ranks[i])
                {
                    printf("%i", prefer[ranks[j]][ranks[k]]);
                    continue;
                }
                else if (j==ranks[i] && k==ranks[i])
                {
                    printf("%i", prefer[ranks[j]][ranks[k]]);
                    continue;
                }
                else if (j==ranks[i] && lookup(k, number_finished, finished_candidate)==true)
                {
                    printf("%i", prefer[ranks[j]][ranks[k]]);
                    continue;
                }
                else
                {
                     printf("%i", prefer[ranks[j]][ranks[k]]);
                     prefer[ranks[j]][ranks[k]]++;
                }

            }

        printf("\n");
        }
        printf("\n");
        finished_candidate[i]=ranks[i];
        number_finished++;
    }

    for (int a=0; a< candidate_count; a++)
    {
        for(int b=0; b<candidate_count; b++)
        {
            new_prefer[a][b]=prefer[ranks[a]][ranks[b]];
            newnew_prefer[a][b]=prefer[ranks[a]][ranks[b]];
            preferences[a][b]=prefer[ranks[a]][ranks[b]];
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int pointer=0;
    pair_count=pointer;
    for(int i=0; i< candidate_count; i++)
    {
        for(int j=0; j< candidate_count; j++)
        {
            if(new_prefer[i][j]==0)
            {
                continue;
            }
            else if (new_prefer[i][j]>new_prefer[j][i])
            {
                pairs[pointer].winner=i;
                pairs[pointer].loser=j;
                pointer++;
                new_prefer[j][i]=0;
            }
            else if (new_prefer[i][j]<new_prefer[j][i])
            {
                pairs[pointer].winner=j;
                pairs[pointer].loser=i;
                pointer++;
                new_prefer[j][i]=0;
            }
            else if (new_prefer[i][j]==new_prefer[j][i])
            {
                preferences[j][i]=0;
                continue;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //be aware if you have to initially set diff to zero
    for (int i=0; i<pair_count; i++)
    {
        pairs[i].diff=pairs[i].winner-pairs[i].loser;
    }

    //sorting from strongest to weakest
    while(true)
    {
        int indicator=0;
        for (int i=0; i< pair_count-1; i++)
        {
            if (pairs[i].diff<pairs[i+ 1].diff)
            {
                memories[0].winner=pairs[i+ 1].winner;
                memories[0].loser=pairs[i+ 1].loser;
                memories[0].diff=pairs[i+ 1].diff;

                pairs[i+ 1].winner=pairs[i].winner;
                pairs[i+ 1].loser=pairs[i].loser;
                pairs[i+ 1].diff=pairs[i].diff;

                pairs[i].winner=memories[0].winner;
                pairs[i].loser=memories[0].loser;
                pairs[i].diff=memories[0].diff;
            }
        }

        for (int i=0; i< pair_count-1; i++)
        {
            if (pairs[i].diff>pairs[i+ 1].diff)
            {
                indicator++;
                continue;
            }
        }

        if(indicator==pair_count- 1)
        {
            break;
        }
    }
    return;
}

void graphing_locked(void);
bool find_circle(void);
void break_circle(void);
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    while(true)
    {
        graphing_locked();

        if(find_circle()==false)
        {
            break;
        }

        break_circle();
    }


    return;
}

// Print the winner of the election
void print_winner(void)
{
    for(int i=0; i< candidate_count; i++)
    {
        int true_count=0;
        for(int j=0; j< candidate_count; j++)
        {
            if(newnew_prefer[i][j]==0)
            {
                continue;
            }
            else if (locked[i][j]==true)
            {
                true_count++;
            }
        }
        if(true_count==candidate_count- 1)
        {
            printf("%s\n", candidates[i]);
        }

    }
    return;
}

bool lookup (int k, int length, int finished_candidate[])
{
    for (int i=0; i< length; i++)
    {
        if(k==finished_candidate[i])
        {
            return true;
        }

    }
    return false;
}

void graphing_locked(void)
{
     for (int pointer=0; pointer< pair_count; pair_count++)
     {
         for(int i=0; i< candidate_count; i++)
         {
            for(int j=0; j< candidate_count; j++)
            {
                if(newnew_prefer[i][j]==0)
                {
                    continue;
                }
                else if (newnew_prefer[i][j]-newnew_prefer[j][i]==pairs[pointer].diff)
                {
                    locked[i][j]=true;
                    newnew_prefer[j][i]=0;
                }
                else if (newnew_prefer[j][i]-newnew_prefer[i][j]==pairs[pointer].diff)
                {
                    locked[j][i]=true;
                    newnew_prefer[i][j]=0;
                }
            }
         }
     }
}

bool find_circle (void)
{
     int array[MAX]={};
     for(int i=0; i< candidate_count; i++)
     {
        int true_count=0;
        for(int j=0; j< candidate_count; j++)
        {
            if(locked[i][j]==true)
            {
                true_count++;
            }
        }
        array[i]=true_count;
     }

     //Finding if there are two rows in which true counts are the same. (if there is a circle)
     int counter=0;
     for (int i=0; i<candidate_count; i++)
     {
         for (int j=0; j< candidate_count; j++)
         {
             if (array[i]==array[j])
             {
                 counter++;
             }
         }
     }

     if(counter>candidate_count)
     {
        return true;
     }
     else
     {
         return false;
     }

}

void break_circle(void)
{
    for(int i=0; i< pair_count; i++)
    {
        if (i==pair_count- 1)
        {
            pair_count--;
        }
    }
}