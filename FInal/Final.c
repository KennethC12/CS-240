#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define TITLE_SIZE 100

struct RecordData // Record data structure
{
    int id;
    char title[TITLE_SIZE];
};

typedef struct Node // Node structure
{
    struct RecordData data;
    struct Node *next, *prev;
} Node;

static void exitError() // Exit with error
{
    _exit(1);
}

static void trimTrailingWhitespace(char *str) // Trim trailing whitespace
{
    int index = (int)strlen(str) - 1;
    while (index >= 0 && (str[index] == ' ' || str[index] == '\t' ||
                          str[index] == '\n' || str[index] == '\r'))
    {
        str[index] = '\0';
        index--;
    }
}

static Node *createNode(struct RecordData record) // Create a new node
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
        exitError();
    newNode->data = record;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

static void insertSorted(Node **head, struct RecordData record) // Insert a record in sorted order
{
    Node *newNode = createNode(record);

    if (*head == NULL) // Insert at the beginning
    {
        *head = newNode;
        return;
    }

    Node *current = *head; // Traverse the list
    while (current->next && current->data.id < record.id)
    {
        current = current->next;
    }

    if (current->data.id >= record.id) // Insert before current
    {
        // Insert before current
        newNode->next = current;
        newNode->prev = current->prev;
        if (current->prev)
            current->prev->next = newNode;
        current->prev = newNode;
        if (*head == current)
            *head = newNode;
    }
    else // Insert after current
    {
        // Insert at the end
        newNode->prev = current;
        current->next = newNode;
    }
}

static void removeTitle(Node **head, const char *S) // Remove a record with a specific title
{
    Node *current = *head;
    while (current)
    {
        Node *nextNode = current->next; // Store the next node
        if (strcmp(current->data.title, S) == 0)
        {
            if (current->prev)                       // Remove the current node
                current->prev->next = current->next; // Update the next pointer of the previous node
            if (current->next)                       // Update the previous pointer of the next node
                current->next->prev = current->prev;
            if (*head == current)
                *head = current->next; // Update the head if necessary
            free(current);
        }
        current = nextNode;
    }
}

static void writeOutput(Node *head) // Write the output to OUT.BIN
{
    int out_fd = open("OUT.BIN", O_WRONLY | O_CREAT | O_TRUNC, 0666); // Open the output file
    if (out_fd < 0)                                                   // Check for errors
        exitError();

    Node *current = head;
    while (current) // Write the records to the output file
    {
        int len = (int)strlen(current->data.title);         // Get the length of the title
        if (write(out_fd, current->data.title, len) != len) // Write the title
        {
            close(out_fd);
            exitError();
        }
        if (current->next)
        {
            if (write(out_fd, ",", 1) != 1) // Write a comma
            {
                close(out_fd);
                exitError();
            }
        }
        current = current->next;
    }

    close(out_fd);
}

// Main function
int main()
{
    // Open the input file "DATA.BIN" in read-only mode
    int in_fd = open("DATA.BIN", O_RDONLY);
    if (in_fd < 0)
    {
        // If the file cannot be opened, exit with an error
        exitError();
    }

    // Read the number of records from the file
    int n;
    if (read(in_fd, &n, sizeof(int)) != sizeof(int))
    {
        // If the read operation fails, close the file and exit with an error
        close(in_fd);
        exitError();
    }

    // Initialize the head pointer of the linked list
    Node *head = NULL;
    for (int i = 0; i < n; i++)
    {
        // Read a record from the file
        struct RecordData record;
        if (read(in_fd, &record.id, sizeof(int)) != sizeof(int))
        {
            // If the read operation fails, close the file and exit with an error
            close(in_fd);
            exitError();
        }
        if (read(in_fd, record.title, TITLE_SIZE) != TITLE_SIZE)
        {
            // If the read operation fails, close the file and exit with an error
            close(in_fd);
            exitError();
        }
        // Null-terminate the title string
        record.title[TITLE_SIZE - 1] = '\0';
        // Remove trailing whitespace from the title string
        trimTrailingWhitespace(record.title);
        // Insert the record into the linked list in sorted order
        insertSorted(&head, record);
    }

    // Read the title to remove from the file
    char S[TITLE_SIZE];
    if (read(in_fd, S, TITLE_SIZE) != TITLE_SIZE)
    {
        // If the read operation fails, close the file and exit with an error
        close(in_fd);
        exitError();
    }
    // Close the input file
    close(in_fd);
    // Null-terminate the title string
    S[TITLE_SIZE - 1] = '\0';
    // Remove trailing whitespace from the title string
    trimTrailingWhitespace(S);
    // Remove the record with the specified title from the linked list
    removeTitle(&head, S);
    // Write the modified linked list to the output file
    writeOutput(head);

    // Free the memory allocated for the linked list
    while (head)
    {
        // Store the current node in a temporary pointer
        Node *temp = head;
        // Move to the next node in the list
        head = head->next;
        // Free the memory allocated for the current node
        free(temp);
    }

    // Return 0 to indicate successful execution
    return 0;
}