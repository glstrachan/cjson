#include <stdio.h>
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "parser/parser.h"
#include "parser/node.h"

void print_depth(int depth)
{
    for (int i = 0; i < depth; i++)
    {
        printf("\t");
    }
}

bool print_node(struct node *node, int depth)
{
    print_depth(depth);

    switch (node->type)
    {
    case NODE_KEYVALUE:
        printf("Key Value\n");
        print_depth(depth + 1);
        printf("Key: %s\n", ((struct key_value_node *)node->value)->key);
        print_depth(depth + 1);
        printf("Value:\n");
        print_node(((struct key_value_node *)node->value)->value, depth + 2);
        break;
    case NODE_OBJECT:
        printf("Object\n");

        for (int i = 0; i < ((struct object_node *)node->value)->size; i++)
        {
            print_node(new_node(NODE_KEYVALUE, &((struct object_node *)node->value)->nodes[i]), depth + 1);
        }

        break;
    case NODE_ARRAY:
        printf("Array\n");

        for (int i = 0; i < ((struct array_node *)node->value)->size; i++)
        {
            print_node(&((struct array_node *)node->value)->nodes[i], depth + 1);
        }

        break;
    case NODE_BOOLEAN:
        printf("Boolean\n");
        print_depth(depth + 1);
        printf("Value:\n");
        printf("%s\n", ((struct boolean_node *)node->value)->value ? "true" : "false");
        break;
    case NODE_NULL:
        printf("Null\n");
        break;
    case NODE_STRING:
        printf("String\n");
        print_depth(depth + 1);
        printf("Value:\n");
        printf("%s\n", ((struct string_node *)node->value)->value);
        break;
    case NODE_NUMBER:
        printf("Number\n");
        print_depth(depth + 1);
        printf("Value:\n");
        printf("%f\n", ((struct number_node *)node->value)->value);
        break;
    default:
        return false;
    }

    return true;
}

int main()
{
    char *input = "{\"string\": \"value\", \"number\": -2.3e+4, \"array\": [1.2, 0.0, -2.2], \"keyTrue\": true}";

    struct lexer *l = new_lexer(input);
    struct token *t;

    int size = 0;
    struct token *tokens = malloc(sizeof(struct token));

    printf("Lexer Tokens:\n");

    while (nextToken(l, &t))
    {
        // Print out the token
        printf("type: %3d, literal: %s\n", t->type, t->literal);

        // Add the token to the array
        tokens = realloc(tokens, sizeof(struct token) * (size + 1));
        tokens[size] = *t;
        size++;
    }

    // Create a new parser
    struct parser *p = new_parser(tokens);
    parse(p);

    printf("Parser AST:\n");

    struct node *node = p->head;

    print_node(node, 0);

    return 0;
}