#include "lexer/lexer.h"
#include "lexer/token.h"
#include <string.h> // For string comparison

struct lexer *new_lexer(char *input)
{
    struct lexer *l = malloc(sizeof(struct lexer));

    l->input = input;
    l->position = 0;
    l->current = input[0];

    return l;
}

bool step_lexer(struct lexer *l)
{
    if (l->current == '\0')
    {
        return false;
    }

    l->position++;
    l->current = l->input[l->position];

    return true;
}

void eatwhitespace(struct lexer *l)
{
    while (l->current == ' ' || l->current == '\t' || l->current == '\n' || l->current == '\r')
    {
        step_lexer(l);
    }
}

bool eatString(struct lexer *l, struct token **t)
{
    if (l->current != '"')
    {
        return false;
    }

    step_lexer(l);
    int start = l->position;

    while (l->current != '"' && l->current != '\0')
    {
        step_lexer(l);
    }

    int end = l->position;

    step_lexer(l);

    enum TokenType type = TOKEN_STRING;

    if (l->current == ':')
    {
        step_lexer(l);
        type = TOKEN_KEY;
    }

    char *literal = malloc(sizeof(char) * (end - start + 1));

    for (int i = start; i < end; i++)
    {
        literal[i - start] = l->input[i];
    }

    literal[end - start] = '\0';
    *t = new_token(type, literal);

    return true;
}

bool eatKeyword(struct lexer *l, struct token **t)
{
    char *keyword;
    enum TokenType type;

    if (l->current == 't')
    {
        keyword = "true";
        type = TOKEN_TRUE;
    }
    else if (l->current == 'f')
    {
        keyword = "false";
        type = TOKEN_FALSE;
    }
    else if (l->current == 'n')
    {
        keyword = "null";
        type = TOKEN_NULL;
    }
    else
    {
        return false;
    }

    for (int i = 0; keyword[i] != '\0'; i++)
    {
        if (l->current != keyword[i])
        {
            return false;
        }
        step_lexer(l);
    }

    *t = new_token(type, keyword);
    return true;
}

bool eatNumber(struct lexer *l, struct token **t)
{
    if (l->current != '-' && (l->current < '0' || l->current > '9'))
    {
        return false;
    }

    int start = l->position;

    if (l->current == '-')
    {
        step_lexer(l);
    }

    while (l->current >= '0' && l->current <= '9')
    {
        step_lexer(l);
    }

    if (l->current == '.')
    {
        step_lexer(l);

        while (l->current >= '0' && l->current <= '9')
        {
            step_lexer(l);
        }
    }

    if (l->current == 'e' || l->current == 'E')
    {
        step_lexer(l);

        if (l->current == '+' || l->current == '-')
        {
            step_lexer(l);
        }

        while (l->current >= '0' && l->current <= '9')
        {
            step_lexer(l);
        }
    }

    int end = l->position;

    char *literal = malloc(sizeof(char) * (end - start + 1));

    for (int i = start; i < end; i++)
    {
        literal[i - start] = l->input[i];
    }

    literal[end - start] = '\0';

    *t = new_token(TOKEN_NUMBER, literal);

    return true;
}

bool eatSymbol(struct lexer *l, struct token **t)
{
    char c = l->current;
    step_lexer(l);

    if (c == '[')
    {
        *t = new_token(TOKEN_ARRAY_OPEN, "[");
        return true;
    }
    if (c == ']')
    {
        *t = new_token(TOKEN_ARRAY_CLOSE, "]");
        return true;
    }
    if (c == '{')
    {
        *t = new_token(TOKEN_OBJECT_OPEN, "{");
        return true;
    }
    if (c == '}')
    {
        *t = new_token(TOKEN_OBJECT_CLOSE, "}");
        return true;
    }
    if (c == ',')
    {
        *t = new_token(TOKEN_COMMA, ",");
        return true;
    }

    return false;
}

bool nextToken(struct lexer *l, struct token **t)
{
    eatwhitespace(l);

    if (l->current == '\"')
    {
        eatString(l, t);
        return true;
    }
    if (l->current == 't' || l->current == 'f' || l->current == 'n')
    {
        eatKeyword(l, t);
        return true;
    }
    if (l->current == '-' || (l->current >= '0' && l->current <= '9'))
    {
        eatNumber(l, t);
        return true;
    }
    if (l->current == '[' || l->current == ']' || l->current == '{' || l->current == '}' || l->current == ',')
    {
        eatSymbol(l, t);
        return true;
    }

    *t = new_token(TOKEN_END, "");

    return false;
}