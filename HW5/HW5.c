#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct // Node structure
{
    int id;
    char *name;
    int parent;
    int *children;
    int child_count;
    int child_capacity;
} Node;

static Node *nodes = NULL; // Array of nodes
static int N;

static void addChild(int parent, int child) // Add child to parent
{
    if (nodes[parent].child_count == nodes[parent].child_capacity) // If child count is equal to child capacity
    {
        int new_cap = (nodes[parent].child_capacity == 0) ? 4 : nodes[parent].child_capacity * 2; // If child capacity is 0, new capacity is 4, else new capacity is double of child capacity
        nodes[parent].children = realloc(nodes[parent].children, new_cap * sizeof(int));          // Reallocate memory for children
        if (!nodes[parent].children)                                                              // If children is NULL
        {
            fprintf(stderr, "Memory allocation error\n");
            exit(1);
        }
        nodes[parent].child_capacity = new_cap; // Set new capacity
    }
    nodes[parent].children[nodes[parent].child_count++] = child; // Add child to parent's children array
    nodes[child].parent = parent;                                // Set child's parent
}

static void removeChild(int parent, int child) // Remove child from parent
{
    // Remove child from parent's children array
    int i;
    for (i = 0; i < nodes[parent].child_count; i++)
    {
        if (nodes[parent].children[i] == child) // If child is found
        {
            // Shift elements
            nodes[parent].children[i] = nodes[parent].children[nodes[parent].child_count - 1];
            nodes[parent].child_count--;
            return;
        }
    }
}

static int compareByID(const void *a, const void *b) // Compare by ID
{
    int A = *(int *)a;
    int B = *(int *)b;
    return (nodes[A].id - nodes[B].id); // Return difference of IDs
}

static int compareByName(const void *a, const void *b) // Compare by name
{
    int A = *(int *)a;
    int B = *(int *)b;
    return strcmp(nodes[A].name, nodes[B].name); // Return difference of names
}

static void sortChildrenByID(int X) // Sort children by ID
{
    if (nodes[X].child_count > 1) // If child count is greater than 1
    {
        qsort(nodes[X].children, nodes[X].child_count, sizeof(int), compareByID);
    }
}

static void sortChildrenByName(int X) // Sort children by name
{
    if (nodes[X].child_count > 1)
    {
        qsort(nodes[X].children, nodes[X].child_count, sizeof(int), compareByName);
    }
}

static void printChildren(int X) // Print children
{
    for (int i = 0; i < nodes[X].child_count; i++)
    {
        if (i > 0) // If i is greater than 0
            printf(",");
        printf("%s", nodes[nodes[X].children[i]].name);
    }
    if (nodes[X].child_count > 0)
        printf("\n");
}

static void removeNode(int X) // Remove node
{
    if (X == 0)
    {
        // Can't remove root
        return;
    }
    int p = nodes[X].parent;
    if (p == -1)
    {
        // X is root? not possible since X !=0
        return;
    }

    // If X has no children, just remove X
    if (nodes[X].child_count == 0)
    {
        removeChild(p, X);
        // X is no longer in the tree, but we do not free memory of arrays
        // to keep it consistent. It's effectively removed.
        nodes[X].parent = -1;
        return;
    }

    // X has children, find child with smallest ID
    int min_id_child = nodes[X].children[0];
    for (int i = 1; i < nodes[X].child_count; i++)
    {
        int c = nodes[X].children[i];
        if (nodes[c].id < nodes[min_id_child].id)
        {
            min_id_child = c;
        }
    }

    // Remove X from parent's children
    removeChild(p, X);

    // min_id_child takes X's place: add min_id_child to p's children
    addChild(p, min_id_child);

    // Now, all other children of X (except min_id_child) should be moved under min_id_child
    // First, gather all other children
    int i;
    for (i = 0; i < nodes[X].child_count; i++)
    {
        int c = nodes[X].children[i];
        if (c != min_id_child)
        {
            // Move c under min_id_child
            nodes[c].parent = min_id_child;
            addChild(min_id_child, c);
        }
    }

    // Clear X's children since we moved them
    free(nodes[X].children);
    nodes[X].children = NULL;
    nodes[X].child_count = 0;
    nodes[X].child_capacity = 0;
    nodes[X].parent = -1;
}

static void moveNode(int newParent, int Y)
{
    int oldParent = nodes[Y].parent;
    if (oldParent == -1)
    {
        // Y is root, can't move root
        return;
    }

    // Remove Y from old parent's children
    removeChild(oldParent, Y);
    // Add Y to new parent's children
    addChild(newParent, Y);
}

int main()
{
ios_base:; // no effect, just a label to keep code neat.
    if (scanf("%d", &N) != 1)
    {
        fprintf(stderr, "Failed to read N\n");
        return 1;
    }

    nodes = calloc(N, sizeof(Node));
    if (!nodes)
    {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    for (int i = 0; i < N; i++)
    {
        nodes[i].id = -1;
        nodes[i].parent = -1;
        nodes[i].children = NULL;
        nodes[i].child_count = 0;
        nodes[i].child_capacity = 0;
    }

    // Read employees
    for (int i = 0; i < N; i++)
    {
        int id;
        static char name[1001];
        if (scanf("%d", &id) != 1)
        {
            fprintf(stderr, "Failed to read ID\n");
            return 1;
        }
        if (scanf("%1000s", name) != 1)
        {
            fprintf(stderr, "Failed to read name\n");
            return 1;
        }
        nodes[id].id = id;
        nodes[id].name = strdup(name);
        if (!nodes[id].name)
        {
            fprintf(stderr, "Memory allocation error\n");
            return 1;
        }
    }

    // root is id=0, parent = -1 by default

    // Process commands until EOF
    char cmd[20];
    while (1) // Infinite loop
    {
        int r = scanf("%s", cmd); // Read command
        if (r == EOF || r == 0)
            break;

        if (strcmp(cmd, "ADD") == 0) // If command is ADD
        {
            int X, Y;
            if (scanf("%d %d", &X, &Y) != 2) // Read X and Y
            {
                fprintf(stderr, "Error reading ADD parameters\n");
                return 1;
            }
            // Add Y as child of X
            addChild(X, Y);
        }
        else if (strcmp(cmd, "REMOVE") == 0) // If command is REMOVE
        {
            int X;
            if (scanf("%d", &X) != 1)
            {
                fprintf(stderr, "Error reading REMOVE parameter\n");
                return 1;
            }
            removeNode(X);
        }
        else if (strcmp(cmd, "MOVE") == 0) // If command is MOVE
        {
            int X, Y;
            if (scanf("%d %d", &X, &Y) != 2)
            {
                fprintf(stderr, "Error reading MOVE parameters\n");
                return 1;
            }
            moveNode(X, Y);
        }
        else if (strcmp(cmd, "SORT_ID") == 0) // If command is SORT_ID
        {
            int X;
            if (scanf("%d", &X) != 1)
            {
                fprintf(stderr, "Error reading SORT_ID parameter\n");
                return 1;
            }
            sortChildrenByID(X);
        }
        else if (strcmp(cmd, "SORT_NAME") == 0) // If command is SORT_NAME
        {
            int X;
            if (scanf("%d", &X) != 1)
            {
                fprintf(stderr, "Error reading SORT_NAME parameter\n");
                return 1;
            }
            sortChildrenByName(X);
        }
        else if (strcmp(cmd, "PRINT") == 0) // If command is PRINT
        {
            int X;
            if (scanf("%d", &X) != 1)
            {
                fprintf(stderr, "Error reading PRINT parameter\n");
                return 1;
            }
            printChildren(X);
        }
        else
        {
            continue;
        }
    }

    // Free memory
    for (int i = 0; i < N; i++)
    {
        if (nodes[i].children)
            free(nodes[i].children);
        if (nodes[i].name)
            free(nodes[i].name);
    }
    free(nodes);
    return 0;
}