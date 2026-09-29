#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char id;
    int deadline;
    int profit;
} job;

/* Compare jobs according to profit in descending order */
int compare(const void *a, const void *b)
{
    job *jobA;
    job *jobB;

    jobA = (job *)a;
    jobB = (job *)b;

    return jobB->profit - jobA->profit;
}

/* Find maximum deadline */
int findMaxDeadline(job jobs[], int n)
{
    int max;
    int i;

    max = jobs[0].deadline;

    for (i = 1; i < n; i++)
    {
        if (jobs[i].deadline > max)
        {
            max = jobs[i].deadline;
        }
    }

    return max;
}

/* Job Sequencing Function */
void jobSequencing(job jobs[], int n)
{
    int maxDeadline;
    int *slot;
    int totalProfit;
    int i;
    int j;

    /* Sort jobs according to profit */
    qsort(jobs, n, sizeof(job), compare);

    /* Find maximum deadline */
    maxDeadline = findMaxDeadline(jobs, n);

    /* Allocate memory for slots */
    slot = (int *)malloc((maxDeadline + 1) * sizeof(int));

    if (slot == NULL)
    {
        printf("Memory allocation failed!");
        return;
    }

    /* Initialize all slots to -1 */
    for (i = 0; i <= maxDeadline; i++)
    {
        slot[i] = -1;
    }

    totalProfit = 0;

    /* Schedule each job */
    for (i = 0; i < n; i++)
    {
        /* Find free slot from deadline towards 1 */
        for (j = jobs[i].deadline; j > 0; j--)
        {
            if (slot[j] == -1)
            {
                slot[j] = i;
                totalProfit = totalProfit + jobs[i].profit;
                break;
            }
        }
    }

    /* Display scheduled jobs */
    printf("\nScheduled Jobs: ");

    for (i = 1; i <= maxDeadline; i++)
    {
        if (slot[i] != -1)
        {
            printf("%c ", jobs[slot[i]].id);
        }
    }

    /* Display total profit */
    printf("\nTotal Profit: %d\n", totalProfit);

    /* Free allocated memory */
    free(slot);
}

/* Main Function */
int main()
{
    int n;
    int i;
    job *jobs;

    printf("Enter number of jobs: ");
    scanf("%d", &n);

    /* Allocate memory for jobs */
    jobs = (job *)malloc(n * sizeof(job));

    if (jobs == NULL)
    {
        printf("Memory allocation failed!");
        return 1;
    }

    /* Input job details */
    for (i = 0; i < n; i++)
    {
        printf("\nEnter job %d details:\n", i + 1);

        printf("Job ID (single character): ");
        scanf(" %c", &jobs[i].id);

        printf("Deadline: ");
        scanf("%d", &jobs[i].deadline);

        printf("Profit: ");
        scanf("%d", &jobs[i].profit);
    }

    /* Call job sequencing */
    jobSequencing(jobs, n);

    /* Free memory */
    free(jobs);

    return 0;
}
