// This LinkedList is like a Queue, where we can add elements to the front of the list
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

int main(int argc, char *argv[])
{
    node *list = NULL;
    for (int i = 1; i < argc; i++)
    {
        int number = atoi(argv[i]);

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // Free the memory
            return 1;
        }

        n->number = number; // n->number means to go to that struct and access the number field
        n->next = list;
        list = n;
    }

    // Now we print whole list
    node *ptr = list;
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number); // Print the number in the list
        ptr = ptr->next;             // Then move to the next node
    }
}
