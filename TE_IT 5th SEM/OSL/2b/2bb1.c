#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>

void bubblesort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main()
{
    char *arg[20], str[20];
    int arr[100];
    int n;

    printf("\nEnter the number of elements to be entered in the array: ");
    scanf("%d", &n);

    printf("\nEnter the array numbers: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("\nProcess is with parent having id: %d", getpid());

    printf("\nArray before sorting is as follows: ");
    for (int i = 0; i < n; i++)
    {
        printf(" %d", arr[i]);
    }

    printf("\nCalling bubble sort function in parent");
    bubblesort(arr, n);

    printf("\nArray after sorting is as follows: ");
    for (int i = 0; i < n; i++)
    {
        printf(" %d", arr[i]);
    }

    printf("\nForking the process now");

    pid_t child = fork();

    if (child < 0)
    {
        printf("\nError while creating the child process");
    }
    else if (child == 0)
    {
        int i = 0;

        printf("\nProcess control is with the child process");
        printf("\nChild process id: %d", getpid());
        printf("\nChild parent process id: %d", getppid());

        for (i = 0; i < n; i++)
        {
            sprintf(str, "%d", arr[i]);
            arg[i] = malloc(sizeof(str));
            strcpy(arg[i], str);
        }
        arg[i] = '\0';

        printf("\nExecuting execve command now in child");
        execve("./2bb2", arg, NULL);
        printf("\nExecve is successfully executed now");
        printf("\nChild completely executed");
    }
    else
    {
        printf("\nProcess control is with the parent process having id: %d", getpid());
        printf("\nWaiting for the child to complete");
        wait(NULL);
        printf("\nParent is back again");
        printf("\nParent successfully executed");
    }
}

