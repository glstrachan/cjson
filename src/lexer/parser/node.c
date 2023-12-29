#include "parser/node.h"

struct node *new_node(enum NodeType type, void *value)
{
    struct node *n = malloc(sizeof(struct node));

    n->type = type;
    n->value = value;

    return n;
}

void free_node(struct node *node)
{
    
}