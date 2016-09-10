#include <assert.h>
#include <string.h>

#include "lambda.h"

AST substitute(char *name, AST arg, AST body);

AST eval(AST ast) {
    if (ast->type == TY_APPLY) {
        AST fn  = eval(ast->apply.left);
        AST arg = eval(ast->apply.right);

        assert(fn->type == TY_ABSTRACT);
        return substitute(fn->abstract.name, arg, fn->abstract.body);
    }

    return ast;
}

AST substitute(char *name, AST arg, AST body) {
    switch (body->type) {
        case TY_VAR:
            return strcmp(body->var.name, name) == 0
                ? arg
                : body;

        case TY_APPLY:
            return App(
                substitute(name, arg, body->apply.left),
                substitute(name, arg, body->apply.right)
            );

        case TY_ABSTRACT:
            return Abs(
                body->abstract.name,
                substitute(name, arg, body->abstract.body)
            );
    }
}
