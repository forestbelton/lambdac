#include <stdlib.h>

#include "lambda.h"

AST Var(char *name) {
    AST ast = malloc(sizeof *ast);

    ast->type = TY_VAR;
    ast->var.name = name;

    return ast;
}

AST App(AST left, AST right) {
    AST ast = malloc(sizeof *ast);

    ast->type = TY_APPLY;
    ast->apply.left = left;
    ast->apply.right = right;

    return ast;
}

AST Abs(char *name, AST body) {
    AST ast = malloc(sizeof *ast);

    ast->type = TY_ABSTRACT;
    ast->abstract.name = name;
    ast->abstract.body = body;

    return ast;
}

void printAST_rec(AST ast) {
    switch (ast->type) {
        case TY_VAR:
            printf("%s", ast->var.name);
            break;

        case TY_APPLY:
            putchar('(');
            printAST_rec(ast->apply.left);
            putchar(' ');
            printAST_rec(ast->apply.right);
            putchar(')');
            break;

        case TY_ABSTRACT:
            putchar('\\');
            printf("%s", ast->abstract.name);
            putchar('.');
            printAST_rec(ast->abstract.body);
            break;
    }
}

void printAST(AST ast) {
    printAST_rec(ast);
    putchar('\n');
}
