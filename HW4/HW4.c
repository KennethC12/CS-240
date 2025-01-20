#include <stdio.h>
#include <stdlib.h>

// Define a structure for linked list nodes
typedef struct Node
{
    int value;          // Value of the node
    int original_index; // Original index of the node before sorting
    struct Node *next;  // Pointer to the next node
} Node;

// Function to create a new node
Node *create_node(int value, int original_index)
{
    Node *new_node = (Node *)malloc(sizeof(Node)); // Allocate memory for new node
    new_node->value = value;
    new_node->original_index = original_index;
    new_node->next = NULL;
    return new_node;
}

// Function to insert node at the end of the linked list
void append(Node **head, int value, int original_index)
{
    Node *new_node = create_node(value, original_index);
    if (*head == NULL)
    {
        *head = new_node; // If list is empty, set new node as head
    }
    else
    {
        Node *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next; // Traverse to the end of the list
        }
        temp->next = new_node; // Append new node at the end
    }
}

// Function to delete nodes with values less than X
void delete_nodes_less_than(Node **head, int X)
{
    Node *temp = *head;
    Node *prev = NULL;

    while (temp != NULL)
    {
        if (temp->value < X) // If node value is less than X
        {
            if (prev == NULL)
            { // Node to delete is the head
                *head = temp->next;
                free(temp);
                temp = *head;
            }
            else
            {
                prev->next = temp->next; // Remove node from list
                free(temp);
                temp = prev->next;
            }
        }
        else
        {
            prev = temp; // Move to next node
            temp = temp->next;
        }
    }
}

// Function to swap two nodes (used in sorting)
void swap(Node *a, Node *b)
{
    int temp_value = a->value;
    int temp_index = a->original_index;
    a->value = b->value;
    a->original_index = b->original_index;
    b->value = temp_value;
    b->original_index = temp_index;
}

// Bubble sort to sort the linked list in ascending order
void sort_list(Node *head)
{
    int swapped;
    Node *ptr1;
    Node *lptr = NULL;

    if (head == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->value > ptr1->next->value)
            {
                swap(ptr1, ptr1->next); // Swap adjacent nodes
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1; // Update last sorted position
    } while (swapped);
}

// Function to print the values and original indices of the linked list
void print_list(Node *head)
{
    Node *temp = head;
    int first = 1;
    while (temp != NULL)
    {
        if (!first)
            printf(",");
        printf("%d", temp->value); // Print sorted values
        first = 0;
        temp = temp->next;
    }
    printf("\n");

    temp = head;
    first = 1;
    while (temp != NULL)
    {
        if (!first)
            printf(",");
        printf("%d", temp->original_index); // Print original indices
        first = 0;
        temp = temp->next;
    }
    printf("\n");
}

// Free the linked list to avoid memory leaks
void free_list(Node *head)
{
    Node *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp); // Free allocated memory for each node
    }
}

int main()
{
    Node *head = NULL;
    int value, X;
    char comma;
    int index = 0;

    // Read the list of integers S
    while (scanf("%d%c", &value, &comma) == 2)
    {
        append(&head, value, index++); // Insert values into linked list
        if (comma != ',')
            break;
    }

    // Read the integer X
    scanf("%d", &X);

    // Delete nodes with values less than X
    delete_nodes_less_than(&head, X);

    // Sort the remaining list
    sort_list(head);

    // Print the sorted list and the original indices
    if (head != NULL)
    {
        print_list(head);
    }

    // Free the list
    free_list(head);

    return 0;
}
