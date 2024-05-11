#include <stdio.h>

struct process
{
    int max[10], allocate[10], need[10];
} p[10];

int n, m;

void input(int[]);
void display(struct process p[]);
int isSafeState(int[], int[], struct process p[]);
int safetyAlgorithm(int[], int[], struct process p[]);

int main()
{
    int i;
    printf("\nEnter No of processes: ");
    scanf("%d", &n);
    printf("Enter no of resources: ");
    scanf("%d", &m);

    int available[m];
    int safeSequence[n];

    printf("\n*****Enter details of process*****");
    input(available);
    display(p);
    printf("\n\n");

    int flag = 1;
    while (flag)
    {
        printf("Menu :: 1) Find System Safety\t2) Get Safe Sequence\t3) Resource Request\t4) Exit\n");
        printf("Choice :: ");
        int ch;
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            if (isSafeState(available, safeSequence, p))
            {
                printf("\n\tSYSTEM IS IN SAFE STATE...\n\n");
            }
            else
                printf("\nSYSTEM IS IN UNSAFE STATE!!!\n\n");
            break;
        case 2:
            printf("\n");
            if (isSafeState(available, safeSequence, p))
            {
                printf("Safe Sequence is :: \t");
                for (i = 0; i < n; i++)
                    printf("P%d -> ", safeSequence[i]);
            }
            printf("\n\n");
            break;
        case 3:
            printf("Enter the Process no. for request :: ");
            int proc;
            scanf("%d", &proc);

            // Copying the processes
            struct process pc[10];

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    pc[i].max[j] = p[i].max[j];
                    pc[i].allocate[j] = p[i].allocate[j];
                    pc[i].need[j] = p[i].need[j];
                }
            }

            printf("Enter the resource requests :: \n");

            for (int i = 0; i < m; i++)
            {
                int tp;
                scanf("%d", &tp);
                pc[proc].allocate[i] += tp;
                pc[proc].need[i] = pc[proc].max[i] - pc[proc].allocate[i];
            }

            if (isSafeState(available, safeSequence, pc))
            {
                printf("\tSystem is Safe with the given Resource Request !!!");
                printf("\n");
                if (isSafeState(available, safeSequence, p))
                {
                    printf("Safe Sequence is :: \t");
                    for (i = 0; i < n; i++)
                        printf("P%d -> ", safeSequence[i]);
                }
                printf("\n\n");
            }
            else
                printf("\tSystem is Not Safe with the given Resource Request !!!");

            printf("\n\n");
            break;
        case 4:
            printf("Exiting ...\n\n");
            flag = 0;
            break;
        default:
            printf("Invalid Input !!!\n\n");
            break;
        }
    }

    return 0;
}

void input(int available[m])
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        printf("\nEnter the details of process P%d: ", i);
        printf("\n\tEnter the allocated resources: ");
        for (j = 0; j < m; j++)
        {
            scanf("%d", &p[i].allocate[j]);
        }
        printf("\tEnter the max resources: ");
        for (j = 0; j < m; j++)
        {
            scanf("%d", &p[i].max[j]);
            p[i].need[j] = p[i].max[j] - p[i].allocate[j];
        }
    }
    printf("\nEnter the available resources: ");
    for (j = 0; j < m; j++)
    {
        scanf("%d", &available[j]);
    }
}

void display(struct process p[])
{
    int i, j;
    printf("\n\tPID\tALLOCATE\tMAX\t\tNEED\n");
    for (i = 0; i < n; i++)
    {
        printf("\tP%d\t", i);
        for (j = 0; j < m; j++)
            printf("%d ", p[i].allocate[j]);
        printf("\t\t");
        for (j = 0; j < m; j++)
            printf("%d ", p[i].max[j]);
        printf("\t\t");
        for (j = 0; j < m; j++)
            printf("%d ", p[i].need[j]);
        printf("\n");
    }
}

int isSafeState(int available[m], int safeSequence[n], struct process p[])
{
    if (safetyAlgorithm(available, safeSequence, p) == 1)
        return 1;
    return 0;
}

int safetyAlgorithm(int available[m], int safeSequence[n], struct process p[])
{
    int i, j;

    int work[m], finish[n];
    for (j = 0; j < m; j++)
        work[j] = available[j];

    for (i = 0; i < n; i++)
        finish[i] = 0;

    int proceed = 1, k = 0;
    while (proceed)
    {
        proceed = 0;
        for (i = 0; i < n; i++)
        {
            int flag = 1;
            if (finish[i] == 0)
            {
                for (j = 0; j < m; j++)
                {
                    if (p[i].need[j] <= work[j])
                    {
                        continue;
                    }
                    else
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 0)
                    continue;

                for (j = 0; j < m; j++)
                {
                    work[j] += p[i].allocate[j];
                }
                finish[i] = 1;
                safeSequence[k++] = i;
                proceed = 1;
            }
        }
    }

    for (i = 0; i < n && finish[i] == 1; i++)
        continue;
    if (i == n)
        return 1;
    return 0;
}

// a=10 b=5 c=7

    //    PID     ALLOCATE        MAX             NEED
    //     P0      0 1 0           7 5 3           7 4 3
    //     P1      2 0 0           3 2 2           1 2 2
    //     P2      3 0 2           9 0 2           6 0 0
    //     P3      2 1 1           2 2 2           0 1 1
    //     P4      0 0 2           4 3 3           4 3 1 
    //3 3 2
    //process 2
    //0 1 0