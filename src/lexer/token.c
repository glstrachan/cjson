#include "lexer/token.h"

struct token *new_token(enum TokenType type, char *literal)
{
    struct token *t = malloc(sizeof(struct token));

    t->type = type;
    t->literal = literal;

    return t;
}