#pragma once
#include "parser/node.h"
#include "lexer/token.h"
#include <stdbool.h>

struct parser
{
    struct node* head;
    struct token* tokens;
    int size;
};

struct parser* new_parser(struct token* tokens, int size);
void free_parser(struct parser* parser);

bool peek(struct parser* parser, int loc, struct token** t);

void parse(struct parser* parser);

bool parse_value(struct parser* parser, int loc, struct node** n);
bool parse_object(struct parser* parser, int loc, struct node** n);
bool parse_array(struct parser* parser, int loc, struct node** n);
bool parse_boolean(struct parser* parser, int loc, struct node** n);
bool parse_null(struct parser* parser, int loc, struct node** n);
bool parse_string(struct parser* parser, int loc, struct node** n);
bool parse_number(struct parser* parser, int loc, struct node** n);