#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lambda.h"

int main(int argc, char *argv[]) {
    char buf[256];

    printf("> ");
    fflush(stdout);

    while (fgets(buf, sizeof buf - 1, stdin) != NULL) {
        *strchr(buf, '\n') = 0;

        AST parsed = parse(StringInput(buf));

        if (parsed == NULL) {
            printf("parse error\n> ");
            continue;
        }

        AST out = eval(parsed);

        printAST(out);

        printf("> ");
        fflush(stdout);
    }

    return 0;
}
