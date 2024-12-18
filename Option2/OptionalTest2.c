#include <stdio.h>
#include <string.h>

int isPalindrome(const char *str)
{
    int len = (int)strlen(str); // Length of the string
    int left = 0;               // Leftmost index
    int right = len - 1;        // Rightmost index

    while (left < right) // Compare characters from both ends
    {
        char char1 = str[left];  // Left character
        char char2 = str[right]; // Right character

        // Convert uppercase letters to lowercase by ASCII code
        if (char1 >= 'A' && char1 <= 'Z')
            char1 = char1 + 32;
        if (char2 >= 'A' && char2 <= 'Z')
            char2 = char2 + 32;

        if (char1 != char2) // If characters dont match
        {
            return 0; // Not a palindrome
        }
        left++;  // Move to the next characters
        right--; // Move to the next characters
    }
    return 1; // Is a palindrome
}

int main() // Main function
{
    char word[101];           // Word buffer
    char lastPalindrome[101]; // Last palindrome found
    int found = 0;

    // Read words until EOF
    while (scanf("%100s", word) == 1)
    {
        if (isPalindrome(word))
        {
            strcpy(lastPalindrome, word); // Copy the last palindrome
            found = 1;
        }
    }

    // Print the last palindrome if any
    if (found)
    {
        printf("%s\n", lastPalindrome);
    }

    return 0;
}