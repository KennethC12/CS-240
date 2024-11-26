#include <stdio.h>
#include <stdlib.h>

// Node representing a character
struct CharNode
{
    char c;
    struct CharNode *nextChar;
};

// Node representing a word (linked list of characters)
struct WordNode
{
    struct CharNode *word;
    struct WordNode *nextWord;
};

// Function to create a new character node
struct CharNode *createCharNode(char c) // Create a new character node
{
    struct CharNode *newCharNode = (struct CharNode *)malloc(sizeof(struct CharNode)); // Allocate memory for the new node
    if (!newCharNode)                                                                  // Check if memory allocation failed
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newCharNode->c = c;
    newCharNode->nextChar = NULL;
    return newCharNode;
}

// Function to create a new word node
struct WordNode *createWordNode(struct CharNode *word) // Create a new word node
{
    struct WordNode *newWordNode = (struct WordNode *)malloc(sizeof(struct WordNode)); // Allocate memory for the new node
    if (!newWordNode)                                                                  // Check if memory allocation failed
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newWordNode->word = word;
    newWordNode->nextWord = NULL;
    return newWordNode;
}

// Function to append a word to the list of words
void appendWord(struct WordNode **wordHead, struct CharNode *word) // Append a word to the list of words
{
    struct WordNode *newWordNode = createWordNode(word);
    if (*wordHead == NULL)
    {
        *wordHead = newWordNode;
    }
    else // Append the word to the end of the list
    {
        struct WordNode *currentWord = *wordHead; // Traverse the list to find the last word
        while (currentWord->nextWord != NULL)
        {
            currentWord = currentWord->nextWord;
        }
        currentWord->nextWord = newWordNode;
    }
}

// Function to get the last character of a word
char getLastChar(struct CharNode *word)
{
    char lastChar = '\0'; // Initialize to null character
    while (word != NULL)
    {
        lastChar = word->c; // Update the last character
        word = word->nextChar;
    }
    return lastChar;
}

// Function to filter words ending with a specific character
void filterWords(struct WordNode **wordHead, char filterChar)
{
    struct WordNode *currentWord = *wordHead; // Start from the head
    struct WordNode *previousWord = NULL;     // Keep track of the previous word

    while (currentWord != NULL)
    {
        char lastChar = getLastChar(currentWord->word);
        if (lastChar == filterChar) // Check if the word ends with the filter character
        {
            // Remove the word
            struct WordNode *tempWord = currentWord;
            if (previousWord == NULL)
            { // Removing the head word
                *wordHead = currentWord->nextWord;
            }
            else
            {
                previousWord->nextWord = currentWord->nextWord;
            }
            currentWord = currentWord->nextWord;

            // Free the character linked list
            struct CharNode *charNode = tempWord->word;
            while (charNode != NULL)
            {
                struct CharNode *tempChar = charNode;
                charNode = charNode->nextChar;
                free(tempChar); // Free the character node - VERY IMPORTANT
            }
            free(tempWord); // Free the word node - VERY IMPORTANT
        }
        else
        {
            previousWord = currentWord;
            currentWord = currentWord->nextWord;
        }
    }
}

// Function to reverse the linked list of words
struct WordNode *reverseWords(struct WordNode *wordHead)
{
    struct WordNode *previousWord = NULL;
    struct WordNode *currentWord = wordHead;
    struct WordNode *nextWord = NULL;

    while (currentWord != NULL)
    {
        nextWord = currentWord->nextWord;
        currentWord->nextWord = previousWord;
        previousWord = currentWord;
        currentWord = nextWord;
    }
    return previousWord;
}

// Function to print the words
void printWords(struct WordNode *wordHead)
{
    struct WordNode *currentWord = wordHead;
    while (currentWord != NULL)
    {
        struct CharNode *charNode = currentWord->word;
        while (charNode != NULL)
        {
            putchar(charNode->c);
            charNode = charNode->nextChar;
        }
        if (currentWord->nextWord != NULL)
        {
            putchar(' ');
        }
        currentWord = currentWord->nextWord;
    }
    putchar('\n');
}

// Function to free all words - VERY IMPORTANT
void freeWords(struct WordNode *wordHead)
{
    struct WordNode *tempWord;
    while (wordHead != NULL)
    {
        tempWord = wordHead;
        wordHead = wordHead->nextWord;

        // Free the character linked list
        struct CharNode *charNode = tempWord->word;
        while (charNode != NULL)
        {
            struct CharNode *tempChar = charNode;
            charNode = charNode->nextChar;
            free(tempChar);
        }
        free(tempWord);
    }
}

int main()
{
    struct WordNode *wordHead = NULL;
    struct CharNode *currentWordCharHead = NULL;
    struct CharNode *currentWordCharTail = NULL;
    char filterChar;
    int ch;

    // Read the first line of input character by character
    while ((ch = getchar()) != EOF)
    {
        if (ch == ' ' || ch == '\n')
        {
            if (currentWordCharHead != NULL)
            {
                // Append the word to the list of words
                appendWord(&wordHead, currentWordCharHead);

                // Reset for the next word
                currentWordCharHead = NULL;
                currentWordCharTail = NULL;
            }
            if (ch == '\n')
            {
                break;
            }
        }
        else
        {
            // Create a new character node
            struct CharNode *newCharNode = createCharNode(ch);
            if (currentWordCharHead == NULL)
            {
                currentWordCharHead = newCharNode;
                currentWordCharTail = newCharNode;
            }
            else
            {
                currentWordCharTail->nextChar = newCharNode;
                currentWordCharTail = newCharNode;
            }
        }
    }

    // If the last word doesn't end with a newline or space
    if (currentWordCharHead != NULL)
    {
        appendWord(&wordHead, currentWordCharHead);
    }

    // Read the second line (single character)
    filterChar = getchar();

    // Remove words ending with 'filterChar'
    filterWords(&wordHead, filterChar);

    // Reverse the linked list of words
    wordHead = reverseWords(wordHead);

    // Print the remaining words
    printWords(wordHead);

    // Free the linked list
    freeWords(wordHead);

    return 0;
}