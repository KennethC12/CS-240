#include <stdio.h>
#include <stdlib.h>

// Define the structure of a doubly linked list node
struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

// Function to create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a node in a sorted manner
void insertSorted(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);

    // If the list is empty or the new node should be the first node
    if (*head == NULL || (*head)->data >= data)
    {
        newNode->next = *head;
        if (*head != NULL)
        {
            (*head)->prev = newNode;
        }
        *head = newNode;
        return;
    }

    // Traverse the list to find the correct position for insertion
    struct Node *current = *head;
    while (current->next != NULL && current->next->data < data)
    {
        current = current->next;
    }

    // Insert the new node after 'current'
    newNode->next = current->next;
    if (current->next != NULL)
    {
        current->next->prev = newNode;
    }
    current->next = newNode;
    newNode->prev = current;
}

// Function to delete a node with a given key
void deleteNode(struct Node **head, int key)
{
    struct Node *temp = *head;

    // Traverse to find the node with the given key
    while (temp != NULL && temp->data != key)
    {
        temp = temp->next;
    }

    // If the node is not found
    if (temp == NULL)
    {
        printf("Node with data %d not found.\n", key);
        return;
    }

    // Adjust pointers and delete the node
    if (temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }
    else
    {
        *head = temp->next;
    }
    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }
    free(temp);
}

// Function to display the list forward
void displayForward(struct Node *head)
{
    struct Node *temp = head;
    printf("Forward: ");
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to display the list backward
void displayBackward(struct Node *head)
{
    struct Node *temp = head;
    if (temp == NULL)
    {
        printf("Backward: List is empty\n");
        return;
    }
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    printf("Backward: ");
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

// Main function to test the sorted doubly linked list
int main()
{
    struct Node *head = NULL;

    // Insert elements into the sorted list
    insertSorted(&head, 30);
    insertSorted(&head, 10);
    insertSorted(&head, 20);
    insertSorted(&head, 5);
    insertSorted(&head, 25);

    // Display the list
    displayForward(head);
    displayBackward(head);

    // Delete a node and display the list again
    deleteNode(&head, 10);
    displayForward(head);
    displayBackward(head);

    return 0;
}
