#include <stdio.h>

int main()
{
    int letterCount[26] = {0}; // Array that holds char a->z
    int currentC;              // Flag to store the current char
    int maxChars = 1000;       // Maximum numbers allowed - Corner case
    int charsRead = 0;         // Counter of char read

    // Read char until EOF or maxChars is reached
    while ((currentC = getchar()) != EOF && charsRead < maxChars)
    {
        charsRead++; // Increment char read

        // If the current char is lowercase
        if (currentC >= 'a' && currentC <= 'z')
        {
            letterCount[currentC - 'a'] = 1; // Letter has to be marked 1 = true, 0 = false.
        }
    }

    // There has to be a counter
    int Ccount = 0;
    // For every letter in the alphabet
    for (int i = 0; i < 26; i++)
    {
        // If such one exists within the input
        if (letterCount[i])
        {
            // Increment that char count
            Ccount++;
        }
    }

    // Print specific letters count
    printf("%d\n", Ccount);

    return 0;
}