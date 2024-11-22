// Input is a list of words
// It has less than 1000 words
// each word can not be longer than 100 characters

// Method 1
// So I will create a void function that will reverse the string by taking in a string and then reversing the characters in the string
// Then I will create a main function that will take in the input string and then split the string by commas

// Test_cases

// Input1 = "Hello,World,CS240"
// Output1 = "olleH,dlroW,042SC"
// Input2 = "Hello,World"
// Output2 = "olleH,dlroW"
// Input3 = "a,b,c,d"
// Output3 = "d,c,b,a"

#include <stdio.h>
#include <string.h>

void reverseString(char *str) // This function reverses a string
{
    int len = strlen(str);            // You take in the length of the string
    for (int i = 0; i < len / 2; i++) // This will loop through half of the string
    {
        char temp = str[i];        // Now it will swap the characters
        str[i] = str[len - 1 - i]; // Now this will swap the first and last characters of the string
        str[len - 1 - i] = temp;
    }
}

int main()
{
    char input[10000]; // Allocate enough space for input

    // Read input using scanf, allowing multiple words until newline
    scanf("%[^\n]", input); // Read everything until a newline character

    char *words[1000]; // Array to store pointers to words
    int wordCount = 0;

    char *substring = strtok(input, ","); // This will split the input string by commas
    while (substring != NULL)
    {
        words[wordCount++] = substring;
        substring = strtok(NULL, ",");
    }

    // This for loop prints the words in reverse order
    for (int i = wordCount - 1; i >= 0; i--)
    {
        reverseString(words[i]); // Reverse the word before printing
        printf("%s", words[i]);  // Then print the word
        if (i > 0)
        {
            printf(","); // This will print out the comma after each word except the last one
        }
    }

    printf("\n"); // Print newline at the end as well
    return 0;
}
