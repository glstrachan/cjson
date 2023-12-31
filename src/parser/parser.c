#include "parser/parser.h"

struct parser *new_parser(struct token *tokens)
{
    struct parser *parser = malloc(sizeof(struct parser));

    parser->tokens = tokens;
    parser->position = 0;
    parser->current = tokens[0];

    return parser;
}

void free_parser(struct parser *parser)
{
    free_node(parser->head);
    free(parser);
}

bool step(struct parser *parser)
{
    if (parser->current.type == TOKEN_END)
    {
        return false;
    }

    parser->position++;
    parser->current = parser->tokens[parser->position];

    return true;
}

void parse(struct parser *parser)
{
    parse_object(parser, &parser->head);
}

bool parse_value(struct parser *parser, struct node **node)
{
    switch (parser->current.type)
    {
    case TOKEN_OBJECT_OPEN:
        return parse_object(parser, node);
    case TOKEN_ARRAY_OPEN:
        return parse_array(parser, node);
    case TOKEN_TRUE:
    case TOKEN_FALSE:
        return parse_boolean(parser, node);
    case TOKEN_NULL:
        return parse_null(parser, node);
    case TOKEN_STRING:
        return parse_string(parser, node);
    case TOKEN_NUMBER:
        return parse_number(parser, node);
    default:
        return false;
    }
}

bool parse_object(struct parser *parser, struct node **n)
{
    if (parser->current.type != TOKEN_OBJECT_OPEN)
    {
        return false;
    }

    if (!step(parser))
    {
        return false;
    }

    int size = 0;
    struct key_value_node *nodes = malloc(sizeof(struct key_value_node));

    while (parser->current.type != TOKEN_OBJECT_CLOSE)
    {
        if (parser->current.type != TOKEN_KEY)
        {
            return false;
        }

        // Make a new keyvalue pair node

        char *key = parser->current.literal;

        if (!step(parser))
        {
            return false;
        }

        struct node *value;

        if (!parse_value(parser, &value))
        {
            return false;
        }

        // Add the node to the object node
        nodes = realloc(nodes, sizeof(struct key_value_node) * (size + 1));
        nodes[size] = *new_key_value_node(key, value);
        size++;
    }

    *n = new_node(NODE_OBJECT, new_object_node(nodes, size));

    if (!step(parser))
    {
        return false;
    }

    return true;
}

bool parse_array(struct parser *parser, struct node **n)
{
    if (parser->current.type != TOKEN_ARRAY_OPEN)
    {
        return false;
    }

    if (!step(parser))
    {
        return false;
    }

    int size = 0;
    struct node *nodes = malloc(sizeof(struct node));

    while (parser->current.type != TOKEN_ARRAY_CLOSE)
    {
        // Make a new value node
        struct node *value;
        parse_value(parser, &value);

        // Add the node to the array node
        nodes = realloc(nodes, sizeof(struct node) * (size + 1));
        nodes[size] = *value;
        size++;
    }

    *n = new_node(NODE_ARRAY, new_array_node(nodes, size));

    if (!step(parser))
    {
        return false;
    }

    return true;
}

bool parse_boolean(struct parser *parser, struct node **n)
{
    if (parser->current.type != TOKEN_TRUE && parser->current.type != TOKEN_FALSE)
    {
        return false;
    }

    struct boolean_node *node = new_boolean_node(parser->current.type == TOKEN_TRUE);
    *n = new_node(NODE_BOOLEAN, node);

    if (!step(parser))
    {
        return false;
    }

    return true;
}

bool parse_null(struct parser *parser, struct node **n)
{
    if (parser->current.type != TOKEN_NULL)
    {
        return false;
    }

    struct null_node *node = new_null_node();
    *n = new_node(NODE_NULL, node);

    if (!step(parser))
    {
        return false;
    }

    return true;
}

bool parse_string(struct parser *parser, struct node **n)
{
    if (parser->current.type != TOKEN_STRING)
    {
        return false;
    }

    struct string_node *node = new_string_node(parser->current.literal);
    *n = new_node(NODE_STRING, node);

    if (!step(parser))
    {
        return false;
    }

    return true;
}

bool parse_number(struct parser *parser, struct node **n)
{
    if (parser->current.type != TOKEN_NUMBER)
    {
        return false;
    }

    char *s = parser->current.literal;

    double base = strtod(s, NULL);
    double exponent = 1;

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == 'e' ||s[i] ==  'E')
        {
            exponent = strtod(&s[i + 1], NULL);
        }
    }

    double d = base * pow(10, exponent);

    struct number_node *node = new_number_node(d);
    *n = new_node(NODE_NUMBER, node);

    if (!step(parser))
    {
        return false;
    }

    return true;
}
