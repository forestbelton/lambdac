#ifndef LAMBDA_H_
#define LAMBDA_H_

#include <stdio.h>

typedef enum {
    TY_VAR,
    TY_APPLY,
    TY_ABSTRACT
} ty;

typedef struct {
    char *name;
} ast_var;

typedef struct {
    struct ast *left;
    struct ast *right;
} ast_apply;

typedef struct {
    char *name;
    struct ast *body;
} ast_abstract;

typedef struct ast {
    ty type;
    union {
        ast_var var;
        ast_apply apply;
        ast_abstract abstract;
    };
} ast;

typedef ast *AST;

AST Var(char *name);
AST App(AST left, AST right);
AST Abs(char *name, AST body);

typedef struct {
    int (*next)(void *);
    void *data;
} input;

typedef input *Input;

Input StringInput(char *str);
Input FileInput(FILE *fp);
int callInput(Input input);

AST parse(Input input);
void printAST(AST ast);

AST eval(AST ast);

#endif
