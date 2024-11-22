#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT 10000   // Maximum input size
#define MAX_WORD_LEN 1000 // Maximum length of a word
#define MAX_WORDS 1000    // Maximum number of words

// Struct to store word and its original index
typedef struct
{
    char *word;
    int index;
} WordEntry;

// Custom strcmp() to compare two strings in ascending order
int my_strcmp(const char *a, const char *b)
{
    while (*a && (*a == *b))
    {
        a++;
        b++;
    }
    return *(unsigned char *)a - *(unsigned char *)b;
}

// Function prototype for custom strstr()
const char *my_strstr(const char *haystack, const char *needle);

// Comparison function for qsort() to sort WordEntry structs by word
int compare(const void *a, const void *b)
{
    WordEntry *entryA = (WordEntry *)a;
    WordEntry *entryB = (WordEntry *)b;
    return my_strcmp(entryA->word, entryB->word);
}

// Function to duplicate a string (manual implementation of strdup)
char *my_strdup(const char *src)
{
    int len = 0;
    while (src[len] != '\0')
    {
        len++;
    }
    char *dst = (char *)malloc((len + 1) * sizeof(char));
    if (!dst)
    {
        fprintf(stderr, "Memory allocation failed in my_strdup\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= len; i++)
    {
        dst[i] = src[i];
    }
    return dst;
}

// Custom strstr() to search for a substring within a string
const char *my_strstr(const char *haystack, const char *needle)
{
    if (!*needle)
        return haystack; // Empty needle matches the whole string

    const char *h, *n;
    for (; *haystack; haystack++)
    {
        h = haystack;
        n = needle;
        while (*h && *n && *h == *n)
        {
            h++;
            n++;
        }
        if (!*n)
            return haystack; // Found needle
    }
    return NULL; // Needle not found
}

int main()
{
    char input[MAX_INPUT];      // Buffer for input
    WordEntry words[MAX_WORDS]; // Array to store all words
    int word_count = 0;         // Counter for total words
    int cs240_count = 0;        // Counter for "CS240" words
    int current_word_index = 0; // Tracks the index of each word in the original input

    // Initialize the input buffer
    for (int i = 0; i < MAX_INPUT; i++)
    {
        input[i] = '\0';
    }

    // Read input using getchar() until the first newline
    int ch, pos = 0;
    while ((ch = getchar()) != EOF && ch != '\n' && pos < MAX_INPUT - 1)
    {
        input[pos++] = (char)ch;
    }
    input[pos] = '\0'; // Null-terminate the input

    // Tokenization and filtering
    char *start = input;

    for (int i = 0; i <= pos; i++)
    {
        char c = input[i];

        // Word delimiters: space, tab, newline, comma, or end of string
        if (c == ' ' || c == '\t' || c == '\n' || c == ',' || c == '\0')
        {
            if (start < &input[i])
            {                    // Valid word found
                input[i] = '\0'; // Null-terminate the word

                // Duplicate the word
                if (word_count >= MAX_WORDS)
                {
                    fprintf(stderr, "Exceeded maximum number of words (%d)\n", MAX_WORDS);
                    exit(EXIT_FAILURE);
                }
                words[word_count].word = my_strdup(start);
                words[word_count].index = current_word_index;
                word_count++;

                // Check if the word contains "CS240"
                if (my_strstr(start, "CS240"))
                {
                    cs240_count++;
                }

                current_word_index++; // Increment the word index
            }
            else if (c == ',')
            { // Empty word detected
                // Represent empty word as empty string
                if (word_count >= MAX_WORDS)
                {
                    fprintf(stderr, "Exceeded maximum number of words (%d)\n", MAX_WORDS);
                    exit(EXIT_FAILURE);
                }
                words[word_count].word = my_strdup("");
                words[word_count].index = current_word_index;
                word_count++;

                // Empty words do not contain "CS240", so no increment to cs240_count
                current_word_index++; // Increment word index for empty word
            }
            start = &input[i + 1]; // Move to the start of the next word
        }
        // Continue accumulating characters into the current word
    }

    // If no words contain "CS240", exit without printing
    if (cs240_count == 0)
        return 0;

    // Create an array to store "CS240" words and their original indices
    WordEntry *cs240_words = (WordEntry *)malloc(cs240_count * sizeof(WordEntry));
    if (!cs240_words)
    {
        fprintf(stderr, "Memory allocation failed for cs240_words\n");
        exit(EXIT_FAILURE);
    }

    int idx = 0;
    for (int i = 0; i < word_count; i++)
    {
        if (my_strstr(words[i].word, "CS240"))
        {
            cs240_words[idx].word = words[i].word;
            cs240_words[idx].index = words[i].index;
            idx++;
        }
    }

    // Sort the "CS240" words lexicographically in ascending order using qsort()
    qsort(cs240_words, cs240_count, sizeof(WordEntry), compare);

    // Replace the sorted "CS240" words back into the words array
    idx = 0;
    for (int i = 0; i < word_count; i++)
    {
        if (my_strstr(words[i].word, "CS240"))
        {
            free(words[i].word);                     // Free the original word
            words[i].word = cs240_words[idx].word;   // Replace with sorted word
            words[i].index = cs240_words[idx].index; // Update the index
            idx++;
        }
    }

    // Free the cs240_words array as its contents have been moved back to words
    free(cs240_words);

    // Print sorted words, including empty entries
    for (int i = 0; i < word_count; i++)
    {
        printf("%s", words[i].word);
        if (i < word_count - 1)
            printf(",");
    }
    printf("\n");

    // Print the original word indices of sorted "CS240" words
    // Modified loop to match the desired format
    for (int i = 0; i < word_count; i++)
    {
        if (my_strstr(words[i].word, "CS240"))
        {
            if (i > 0)
                printf(",");              // Print comma before the index starting from the second valid index
            printf("%d", words[i].index); // Print the original index
        }
    }
    printf("\n");

    // Free dynamically allocated memory for all words
    for (int i = 0; i < word_count; i++)
    {
        free(words[i].word);
    }

    return 0;
}
