#pragma once
#include <stdlib.h>

enum TokenType
{
    TOKEN_STRING,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NULL,
    TOKEN_KEY,
    TOKEN_NUMBER,
    TOKEN_ARRAY_OPEN,
    TOKEN_ARRAY_CLOSE,
    TOKEN_OBJECT_OPEN,
    TOKEN_OBJECT_CLOSE,
    TOKEN_COMMA,
};

struct token
{
    enum TokenType type;
    char *literal;
};

struct token *new_token(enum TokenType type, char *literal);
void free_token(struct token *t);