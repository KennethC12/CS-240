#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
} node;

// Function prototypes
node *insert(node *root, int number);
node *delete(node *root, int number);
node *find_min(node *root);
void print_in_order(node *root);
int search(node *root, int number);
void free_tree(node *root);

int main(void)
{
    node *root = NULL;
    int choice, value;

    while (1)
    {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Print In-Order\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            root = insert(root, value);
            break;
        case 2:
            printf("Enter value to search: ");
            scanf("%d", &value);
            if (search(root, value))
                printf("Value %d found in the tree.\n", value);
            else
                printf("Value %d not found in the tree.\n", value);
            break;
        case 3:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            root = delete (root, value);
            break;
        case 4:
            printf("In-order Traversal:\n");
            print_in_order(root);
            printf("\n");
            break;
        case 5:
            free_tree(root);
            printf("Exiting program.\n");
            return 0;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
}

// Function to insert a value into the BST
node *insert(node *root, int number)
{
    if (root == NULL)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Memory allocation failed\n");
            return NULL;
        }
        new_node->number = number;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    if (number < root->number)
    {
        root->left = insert(root->left, number);
    }
    else if (number > root->number)
    {
        root->right = insert(root->right, number);
    }
    return root;
}

// Function to search for a value in the BST
int search(node *root, int number)
{
    if (root == NULL)
    {
        return 0; // Not found
    }
    if (number == root->number)
    {
        return 1; // Found
    }
    else if (number < root->number)
    {
        return search(root->left, number);
    }
    else
    {
        return search(root->right, number);
    }
}

// Function to delete a value from the BST
node *delete(node *root, int number)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (number < root->number)
    {
        root->left = delete (root->left, number);
    }
    else if (number > root->number)
    {
        root->right = delete (root->right, number);
    }
    else
    {
        // Case 1: No child
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        // Case 2: One child
        else if (root->left == NULL)
        {
            node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            node *temp = root->left;
            free(root);
            return temp;
        }
        // Case 3: Two children
        else
        {
            node *temp = find_min(root->right);
            root->number = temp->number;
            root->right = delete (root->right, temp->number);
        }
    }
    return root;
}

// Function to find the node with the smallest value in a subtree
node *find_min(node *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

// Function to print the BST in in-order traversal
void print_in_order(node *root)
{
    if (root == NULL)
    {
        return;
    }
    print_in_order(root->left);
    printf("%d ", root->number);
    print_in_order(root->right);
}

// Function to free the memory allocated for the BST
void free_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
