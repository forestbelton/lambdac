#include <stdlib.h>
#include "lambda.h"

int callInput(Input input) {
    return input->next(input->data);
}

typedef struct {
    char *str;
} StringInput_data;

int StringInput_next(void *vstr) {
    StringInput_data *data = vstr;
    int c = *data->str;

    if (c == 0) {
        return -1;
    } else {
        data->str++;
        return c;
    }
}

Input StringInput(char *str) {
    StringInput_data *data = malloc(sizeof *data);
    data->str = str;

    Input input = malloc(sizeof *input);
    input->data = data;
    input->next = &StringInput_next;

    return input;
}

int FileInput_next(void *vfp) {
    FILE *fp = vfp;

    return fgetc(fp);
}

Input FileInput(FILE *fp) {
    Input input = malloc(sizeof *input);
    input->data = fp;
    input->next = &FileInput_next;

    return input;
}
