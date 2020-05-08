#include <stdio.h>
#include <string.h>

int cmmdc(int x, int y)
{
    if (!y) return x;
    return cmmdc(y, x % y);
}

int prime(int x)
{
    if (x < 2 || (x > 2 && x % 2 == 0))
        return 0;
    for (int d = 3; d * d <= x; d += 2)
        if (x % d == 0)
            return 0;
    return 1;
}

void compute_subsequence(int a[],int n, int *start,int *stop)
{
    int j = 0, maxi=0;
    for (int i = 0; i < n - 1; i++)
        if (prime(abs(a[i] - a[i + 1])))
            j++;
        else
        {
            j++;
            if (j > maxi)
            {
                maxi = j;
                *start = i - j + 1;
                *stop = i;
            }
            j = 0;
        }
    j++;
    if (j > maxi)
    {
        maxi = j;
        *start = n - j;
        *stop = n-1;
    }
}

void printSubsequence(int a[], int st, int end)
{
    for (int i = st; i <= end; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main()
{
    while (1)
    {
        printf("Press\n1 to compute subsequence\n2 to determine relative prime no. to n\n");
        int option = 0;
        scanf_s("%d", &option);
        if (option == 1)
        {
            int a[100], j = 0, start, stop;
            char x[100];
            scanf_s("%s", &x, 99);
            while (strcmp(x, "exit"))
            {
                a[j++] = atoi(x);
                scanf_s("%s", &x, 99);
            }
            compute_subsequence(a, j, &start, &stop);
            printSubsequence(a, start, stop);
        }
        else if (option == 2)
        {
            int n, x = 1;
            printf("Insert n: ");
            scanf_s("%d", &n);
            while (x < n)
            {
                if (cmmdc(x, n) == 1)
                    printf("%d ", x);
                x++;
            }
            printf("\n");
        }
        else if (option == 3)
            break;
    }
    return 0;
}