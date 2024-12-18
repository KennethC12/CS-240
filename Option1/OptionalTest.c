#include <stdio.h>

int main()
{
    int freq[10] = {0};
    int x;

    // Read until no more input
    while (scanf("%d", &x) == 1)
    {
        // Ensure that x is a digit 0-9
        if (x >= 0 && x <= 9)
        {
            freq[x]++; // Increment the frequency of the digit
        }
    }

    // Find the digit with the highest frequency
    // If there's a tie, choose the smallest digit
    int max_freq = -1;
    int result = 0; // Default to 0 if no input
    for (int i = 0; i < 10; i++)
    {
        if (freq[i] > max_freq)
        {
            max_freq = freq[i];
            result = i;
        }
    }

    printf("%d\n", result); // Output the result
    return 0;
}