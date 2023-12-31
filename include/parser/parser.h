#pragma once
#include "parser/node.h"
#include "lexer/token.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

struct parser
{
    struct node *head;
    struct token *tokens;
    int position;
    struct token current;
};

struct parser *new_parser(struct token *tokens);
void free_parser(struct parser *parser);

bool step(struct parser *parser);

void parse(struct parser *parser);

bool parse_value(struct parser *parser, struct node **n);
bool parse_object(struct parser *parser, struct node **n);
bool parse_array(struct parser *parser, struct node **n);
bool parse_boolean(struct parser *parser, struct node **n);
bool parse_null(struct parser *parser, struct node **n);
bool parse_string(struct parser *parser, struct node **n);
bool parse_number(struct parser *parser, struct node **n);