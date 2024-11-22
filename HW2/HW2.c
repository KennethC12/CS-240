#include <stdio.h>
#include <stdlib.h>

// Function to calculate GCD using Euclidean algorithm
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Comparator function for qsort
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    char input[100000]; // Input string
    int arr[10000];     // Array to store the integers
    int n = 0;          // Counter for the number of integers

    // Read input as a string
    scanf("%s", input);

    // Parse the input into integers
    int num = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == ',')
        {
            arr[n++] = num;
            num = 0;
        }
        else
        {
            num = num * 10 + (input[i] - '0');
        }
    }
    arr[n++] = num; // Add the last number

    // Sort the array
    qsort(arr, n, sizeof(int), compare);

    // Find the GCD of the smallest and largest number
    int result_gcd = gcd(arr[0], arr[n - 1]);

    // Output the GCD
    printf("%d\n", result_gcd);

    // Output the sorted array
    for (int i = 0; i < n; i++)
    {
        if (i > 0)
            printf(",");
        printf("%d", arr[i]);
    }
    printf("\n");

    return 0;
}
