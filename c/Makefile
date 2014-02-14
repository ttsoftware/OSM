SOURCES  := dlisttest.c

LIBS	 := dlist.c

OBJECTS  := $(patsubst %.c, %.o, $(SOURCES))
TARGETS  := $(patsubst %.o, %, $(OBJECTS))

CC      := gcc -Werror

all: $(TARGETS)

$(TARGETS): %:
	$(CC) -o $@ $(LIBS) $(SOURCES)

clean:
	rm -f $(OBJECTS) *.o $(TARGETS) *~

.PHONY: clean
