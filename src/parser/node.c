#include "parser/node.h"

struct node *new_node(enum NodeType type, void *value)
{
    struct node *node = malloc(sizeof(struct node));

    node->type = type;
    node->value = value;

    return node;
}

void free_node(struct node *node)
{
    switch (node->type)
    {
    case NODE_KEYVALUE:
        free_key_value_node(node->value);
        break;
    case NODE_OBJECT:
        free_object_node(node->value);
        break;
    case NODE_ARRAY:
        free_array_node(node->value);
        break;
    case NODE_BOOLEAN:
        free_boolean_node(node->value);
        break;
    case NODE_NULL:
        free_null_node(node->value);
        break;
    case NODE_STRING:
        free_string_node(node->value);
        break;
    case NODE_NUMBER:
        free_number_node(node->value);
        break;
    }

    free(node);
}

struct key_value_node *new_key_value_node(char *key, struct node *value)
{
    struct key_value_node *node = malloc(sizeof(struct key_value_node));

    node->key = key;
    node->value = value;

    return node;
}

void free_key_value_node(struct key_value_node *node)
{
    free(node->key);
    free_node(node->value);
    free(node);
}

struct object_node *new_object_node(struct key_value_node *nodes, int size)
{
    struct object_node *node = malloc(sizeof(struct object_node));

    node->nodes = nodes;
    node->size = size;

    return node;
}

void free_object_node(struct object_node *node)
{
    for (int i = 0; i < node->size; i++)
    {
        free_key_value_node(&node->nodes[i]);
    }

    free(node);
}

struct array_node *new_array_node(struct node *nodes, int size)
{
    struct array_node *node = malloc(sizeof(struct array_node));

    node->nodes = nodes;
    node->size = size;

    return node;
}

void free_array_node(struct array_node *node)
{
    for (int i = 0; i < node->size; i++)
    {
        free_node(&node->nodes[i]);
    }

    free(node);
}

struct boolean_node *new_boolean_node(bool value)
{
    struct boolean_node *node = malloc(sizeof(struct boolean_node));

    node->value = value;

    return node;
}

void free_boolean_node(struct boolean_node *node)
{
    free(node);
}

struct null_node *new_null_node()
{
    struct null_node *node = malloc(sizeof(struct null_node));

    return node;
}

void free_null_node(struct null_node *node)
{
    free(node);
}

struct string_node *new_string_node(char *value)
{
    struct string_node *node = malloc(sizeof(struct string_node));

    node->value = value;

    return node;
}

void free_string_node(struct string_node *node)
{
    free(node->value);
    free(node);
}

struct number_node *new_number_node(double value)
{
    struct number_node *node = malloc(sizeof(struct number_node));

    node->value = value;

    return node;
}

void free_number_node(struct number_node *node)
{
    free(node);
}