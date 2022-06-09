#include "minishell.h"

static void printtree(t_node *root, int level);
static void print_tabs(int numtabs);
static void print_node(t_node *node);


void print_tree(t_node *root)
{
    printtree(root, 0);
}

static void printtree(t_node *root, int level)
{
    if (root == NULL)
    {
        print_tabs(level);
        return ;
    }
    print_tabs(level);
    print_node(root);

    print_tabs(level);
    printtree(root->left, level+1);

    print_tabs(level);
    printtree(root->rigth, level+1);

    printf("\n");
}

static void print_tabs(int numtabs)
{
    int i;

    i = 0;
    while (i < numtabs)
    {
        printf("    ");
        i++;
    }
}

static void print_node(t_node *node)
{
    if (node->id == ID_PIPE)
        printf("|\n");
    else if (node->id == ID_CMD)
        printf("%s\n", node->data);
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
        printf("%s\n", node->data);
    }
}





