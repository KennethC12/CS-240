#include <stdio.h>

int main()
{
    int c; // c for getchar - ASCII code for integers
    int word_count = 0;
    int char_count[26] = {0}; //{0} this is going to make the alaphabet array to 0
    int in_word = 0;          // 0 means not in a word, 1 means in a word

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {                // this checks if the character is a space, new line, or tab, The '' is for a single character and "" is for a string
            in_word = 0; // if it is, then it is not in a word
        }
        else
        {
            if (!in_word)
            {                 // ! checks if the in_word is not true
                in_word = 1;  // This means that we are in the word
                word_count++; // This will increment the word count if we are in a word
            }
        }
        // Now we have to change the upper case to lower case because it simplifies to so we dont need to make 2 different arrays
        if ((c >= 'A') && (c <= 'Z'))
        {
            c = c + 32; // This will change the upper case to lower case, the 32 is basically the ASCII code for (a - A) == 32
        }

        // Now we have to check if the character is lowercase, if so then increment the array
        if ((c >= 'a') && (c <= 'z'))
        {
            char_count[c - 'a']++;
            // The array is basically doing the char - 'a' to get the index of the array and then it will increment the the char count
            // Example: if the char is 'b' then 'b' - 'a' = 1, so it will increment the array[b] by 1
        }
    }

    if (word_count == 0)
    { // This will print nothing if no character is entered
        return 0;
    }

    // Print the word count
    printf("%d\n", word_count); // %d is for integers

    for (int i = 0; i < 26; i++)
    {
        if (char_count[i] > 0)
        {
            // i + 'a' will convert the ASCII code to the character for example 0 + 'a' = 'a' and 1 + 'a' = 'b'
            putchar(i + 'a'); // This will print the character
            putchar(':');     // This will print the colon
            putchar(' ');     // This will print the space

            printf("%d\n", char_count[i]); // %d is for integers and char_count[i] is the count of the character
        }
    }
}