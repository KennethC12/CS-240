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

int main() // Main function
{
    int in_fd = open("DATA.BIN", O_RDONLY);
    if (in_fd < 0)
        exitError();

    int n;
    if (read(in_fd, &n, sizeof(int)) != sizeof(int))
    {
        close(in_fd);
        exitError();
    }

    Node *head = NULL; // Initialize the head pointer
    for (int i = 0; i < n; i++)
    {
        struct RecordData record; // Read the records
        if (read(in_fd, &record.id, sizeof(int)) != sizeof(int))
        {
            close(in_fd);
            exitError();
        }
        if (read(in_fd, record.title, TITLE_SIZE) != TITLE_SIZE)
        {
            close(in_fd);
            exitError();
        }
        record.title[TITLE_SIZE - 1] = '\0';
        trimTrailingWhitespace(record.title);
        insertSorted(&head, record);
    }

    char S[TITLE_SIZE]; // Read the title to remove
    if (read(in_fd, S, TITLE_SIZE) != TITLE_SIZE)
    {
        close(in_fd);
        exitError();
    }
    close(in_fd); // Close the input file
    S[TITLE_SIZE - 1] = '\0';
    trimTrailingWhitespace(S);

    removeTitle(&head, S); // Remove the record with the specified title
    writeOutput(head);

    // Free memory
    while (head)
    {
        Node *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}