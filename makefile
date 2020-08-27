CC ?= gcc
CFLAGS += -Wall -Wextra -Wpedantic -Werror -std=c99
TESTEXE = test

$(TESTEXE): test.c yamidi.h
	$(CC) $(CFLAGS) test.c -o $(TESTEXE)

clean:
	rm -rf *.o $(TESTEXE)
.PHONY: clean

lint:
	clang-tidy -checks="*,-llvm-header-guard" -header-filter=".*" test.c
	cppcheck --enable=all --inconclusive test.c
.PHONY: lint
