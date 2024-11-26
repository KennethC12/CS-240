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

// Function to insert a node at the beginning
void insertAtBeginning(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head != NULL)
    {
        newNode->next = *head;
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Function to insert a node at the end
void insertAtEnd(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    struct Node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to delete a node with a given key
void deleteNode(struct Node **head, int key)
{
    struct Node *temp = *head;
    while (temp != NULL && temp->data != key)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Node with data %d not found.\n", key);
        return;
    }
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

// Main function to test the doubly linked list
int main()
{
    struct Node *head = NULL;

    // Insert elements
    insertAtBeginning(&head, 10);
    insertAtBeginning(&head, 20);
    insertAtEnd(&head, 5);
    insertAtEnd(&head, 1);

    // Display the list
    displayForward(head);
    displayBackward(head);

    // Delete a node
    deleteNode(&head, 20);
    displayForward(head);
    displayBackward(head);

    return 0;
}
