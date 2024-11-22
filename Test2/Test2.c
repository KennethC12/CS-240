/*

Input: A list of words: X1,X2,...,Xn (n < 1000) separated by a comma ','. Each word is not longer
than 100 characters.
Output: Print these words into stdout, separated by comma ‘,’ while each word is reversed
itself. If no words are provided, print nothing to the standard output.  */

// Input is a list of words
// It has less than 1000 words
// each word is not longer than 100 chars

// Output is a reverse words
// Case: If nothing chars
// return nothing

#include <stdio.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

// Function to reverse
void reverse(char *str)
{
    int len = strlen(str);
    int i;
    for (i = 0; i < len / 2; i++)
    {
        // SWAP
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int main(int argc, char *argv[])
{
    char words[MAX_WORDS][MAX_WORD_LENGTH]; // Store words
    int count = 0;                          // Count for each char
    int index = 0;                          // Index for each char

    // Get the input string from the first command-line argument
    // Pointer points -> [0][1][3][4]
    char *input = argv[1];

    // Go through the list until the end
    // We can either do this with the NULL at the end of a "list"
    // If we encounter a , -> we should know it's the end of a word or "string"
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == ',')
        {
            // So when we do, we need to stop, reverse, and reset for the next one
            // Stop
            words[count][index] = '\0';
            // Reverse
            reverse(words[count]);
            // Next word
            count++;
            // I need to iterate through the next word
            index = 0;
        }
        else
        {
            // Add char to the current word
            if (index < MAX_WORD_LENGTH - 1)
            {
                words[count][index] = input[i];
                index++;
            }
            else
            {
                // Corner case met
            }
        }
    }

    if (index > 0)
    {
        // This is for the last word
        words[count][index] = '\0';
        reverse(words[count]);
        count++;
    }

    // Print the reversed words separated by commas
    for (int i = 0; i < count; i++)
    {
        printf("%s", words[i]);
        if (i != count - 1)
        {
            printf(",");
        }
    }

    return 0;
}
