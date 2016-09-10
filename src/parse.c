#include <stdio.h>
#include <stdlib.h>

#include "lambda.h"

/* grammar
 *
 * ast := name
 *      | abs
 *      | app
 *
 * name := letter
 * abs := "\" letter "." ast
 * app := "(" ast " " ast ")"
 */

/*
 * '\' -> 92 BACKSLASH
 * '.' -> 46 PERIOD
 * '(' -> 40 LPAREN
 * ')' -> 41 RPAREN
 * ' ' -> 32 SPACE
 * c   -> __ LETTER
 *
 */

#define LEN(xs) (sizeof (xs) / sizeof ((xs)[0]))

#define NEXT(c) do {           \
    int ch = callInput(input); \
                               \
    if (tokens[ch] != c) {     \
        return NULL;           \
    }                          \
} while(0)

#define CHECK(nt) do {  \
    if ((nt) == NULL) { \
        return NULL;    \
    }                   \
} while(0)

typedef enum {
    UNKNOWN,
    BACKSLASH,
    PERIOD,
    LPAREN,
    RPAREN,
    SPACE,
    LETTER
} Token;

static Token tokens[256] = {
    ['\\'] = BACKSLASH,
    ['.']  = PERIOD,
    ['(']  = LPAREN,
    [')']  = RPAREN,
    [' ']  = SPACE,
    ['a' ... 'z'] = LETTER
};

char *c2s(int ch) {
    char *s = malloc(2);

    s[0] = ch;
    s[1] = 0;

    return s;
}

AST parseVar(int ch) {
    char *name = c2s(ch);
    return Var(name);
}

AST parseAbs(Input input) {
    int ch = callInput(input);
    if (ch == EOF) {
        return NULL;
    }

    char *name = c2s(ch);

    NEXT(PERIOD);

    AST body = parse(input);
    CHECK(body);

    return Abs(name, body);
}

AST parseApp(Input input) {
    AST left = parse(input);
    CHECK(left);

    NEXT(SPACE);

    AST right = parse(input);
    CHECK(right);

    NEXT(RPAREN);

    return App(left, right);
}

AST parse(Input input) {
    int ch = callInput(input);

    if (ch == EOF) {
        return NULL;
    }

    switch (tokens[ch]) {
        case LETTER:    return parseVar(ch);
        case BACKSLASH: return parseAbs(input);
        case LPAREN:    return parseApp(input);
        default:        return NULL;
    }
}
