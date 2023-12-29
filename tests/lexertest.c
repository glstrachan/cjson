#include <stdio.h>
#include "lexer/lexer.h"
#include "lexer/token.h"

int main() {
    char *input = "{\"string\": \"value\", \"number\": -2.3e+4, \"array\": [1.2, 0.0, -2.2], \"keyTrue\": true}";

    struct lexer *l = new_lexer(input);
    struct token *t;

    while (nextToken(l, &t)) {
        printf("type: %3d, literal: %s\n", t->type, t->literal);
    }

    return 0;
}