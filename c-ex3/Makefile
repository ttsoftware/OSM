SOURCES := PThread_matmult.c

LIBS	:= stack.c dlist.c

OBJECTS := $(patsubst %.c, %.o, $(SOURCES))
TARGETS := $(patsubst %.o, %, $(OBJECTS))

CC := gcc -Werror -Wall -pedantic -std=c99 -ggdb -lpthread

all: $(TARGETS)

$(TARGETS): %:
	$(CC) -o $@ $(LIBS) $(SOURCES)

clean:
	rm -f $(OBJECTS) *.o $(TARGETS) *~

.PHONY: clean
