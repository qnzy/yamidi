CC ?= gcc
CFLAGS += -Wall -Wextra -Wpedantic # -Werror
TESTEXE = test

test: test.c yamidi.h
	$(CC) $(CFLAGS) test.c -o $(TESTEXE)

clean:
	rm -rf *.o $(TESTEXE)
