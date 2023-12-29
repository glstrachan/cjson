#pragma once
#include <stdbool.h>

enum NodeType
{
    NODE_KEYVALUE,
    NODE_OBJECT,
    NODE_ARRAY,
    NODE_BOOLEAN,
    NODE_NULL,
    NODE_STRING,
    NODE_NUMBER
};

// High level node abstraction
struct node
{
   enum NodeType type;
   void* value;
};

struct node* new_node(enum NodeType type, void* value);
void free_node(struct node* node);

struct key_value_node
{
    char* key;
    struct node* value;
};

struct key_value_node* new_key_value_node(char* key, struct node* value);
void free_key_value_node(struct key_value_node* node);

struct object_node
{
    struct key_value_node* nodes;
    int size;
};

struct array_node* new_array_node(struct node* nodes, int size);
void free_array_node(struct array_node* node);

struct array_node
{
    struct node* nodes;
    int size;
};

struct object_node* new_object_node(struct key_value_node* nodes, int size);
void free_object_node(struct object_node* node);

struct boolean_node
{
    bool value;
};

struct boolean_node* new_boolean_node(bool value);
void free_boolean_node(struct boolean_node* node);

struct null_node
{
    bool value;
};

struct null_node* new_null_node();
void free_null_node(struct null_node* node);

struct string_node
{
    char* value;
};

struct string_node* new_string_node(char* value);
void free_string_node(struct string_node* node);

struct number_node
{
    double value;
};

struct number_node* new_number_node(double value);
void free_number_node(struct number_node* node);