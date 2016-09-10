CFILES=src/ast.c src/lambda.c src/parse.c src/input.c src/eval.c
OFILES=$(subst .c,.o,$(CFILES))
CFLAGS=-Wall -Wextra -Werror -O2 -std=gnu11 -Wno-unused-parameter -Iinclude

.PHONY: clean

lambda: $(OFILES)
	gcc $(OFILES) $(CFLAGS) -o $@

%.o: %.c
	gcc -c $(CFLAGS) $< -o $@

clean:
	rm -rf lambda $(OFILES)
