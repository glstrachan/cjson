#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include "token.h"

struct lexer
{
    char *input;
    int position;
    char current;
};

struct lexer* new_lexer(char *input);
void free_lexer(struct lexer *l);

bool step_lexer(struct lexer *l);

void eatwhitespace(struct lexer *l);
bool eatString(struct lexer *l, struct token **t);
bool eatKeyword(struct lexer *l, struct token **t);
bool eatNumber(struct lexer *l, struct token **t);
bool eatSymbol(struct lexer *l, struct token **t);
bool nextToken(struct lexer *l, struct token **t);