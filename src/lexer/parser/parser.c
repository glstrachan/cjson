#include "parser/parser.h"

struct parser *new_parser(struct token *tokens, int size)
{
    struct parser *parser = malloc(sizeof(struct parser));

    parser->tokens = tokens;
    parser->size = size;

    return parser;
}

void free_parser(struct parser *parser)
{
    free_node(parser->head);
    free(parser);
}

bool peek(struct parser *parser, int loc, struct token **t)
{
    if (loc >= parser->size)
    {
        return false;
    }

    *t = &parser->tokens[loc];

    return true;
}

void parse(struct parser *parser)
{
    parse_object(parser, 0, &parser->head);
}

bool parse_value(struct parser* parser, int loc, struct node** n) {
    switch(parser->tokens[loc].type) {
        case TOKEN_OBJECT_OPEN:
            return parse_object(parser, loc, n);
        case TOKEN_ARRAY_OPEN:
            return parse_array(parser, loc, n);
        case TOKEN_TRUE:
        case TOKEN_FALSE:
            return parse_boolean(parser, loc, n);
        case TOKEN_NULL:
            return parse_null(parser, loc, n);
        case TOKEN_STRING:
            return parse_string(parser, loc, n);
        case TOKEN_NUMBER:
            return parse_number(parser, loc, n);
    }

    return false;
}

bool parse_object(struct parser *parser, int loc, struct node **n)
{
    if (parser->tokens[loc].type != TOKEN_OBJECT_OPEN)
    {
        return false;
    }

    loc++;

    while (parser->tokens[loc].type != TOKEN_OBJECT_CLOSE && loc < parser->size)
    {
        if (parser->tokens[loc].type != TOKEN_KEY)
        {
            return false;
        }

        // Make a new keyvalue pair node

        loc++;
    }

    return true;
}

bool parse_array(struct parser *parser, int loc, struct node **n)
{
}

bool parse_boolean(struct parser *parser, int loc, struct node **n)
{
}

bool parse_null(struct parser *parser, int loc, struct node **n)
{
}

bool parse_string(struct parser *parser, int loc, struct node **n)
{
}

bool parse_number(struct parser *parser, int loc, struct node **n)
{
}
