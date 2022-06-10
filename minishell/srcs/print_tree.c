#include "minishell.h"

#define COUNT 10

//cat <in >out | ls <in2 >out2 | <<in3 >>out3 grep | <<in4 less >out4

static void print_node(t_node *node);
static void print2DUtil(t_node *root, int space);

/*
 Code based in https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
*/

void print2D(t_node *root)
{
   print2DUtil(root, 0);
}

// It does reverse inorder traversal
static void print2DUtil(t_node *root, int space)
{
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->rigth, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    //printf("%s\n", root->data);
    print_node(root);

    // Process left child
    print2DUtil(root->left, space);
}


void print_array_string(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        printf("%s ", str[i]);
        i++;
    }
    printf("\n");
}

static void print_node(t_node *node)
{
    if (node->id == ID_PIPE)
        printf("|\n");
    else 
    {
        if (node->id == ID_IN_REDIR)
           printf("< "); 
        else if (node->id == ID_OUT_REDIR)
           printf("> "); 
        else if (node->id == ID_OUT_HERDOC)
           printf(">> ");
        else if (node->id == ID_IN_HERDOC)
           printf("<< ");    
        print_array_string(node->data);
    }
}