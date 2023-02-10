CFLAGS = -Wall -Werror -fpic
LIB:= liblist.so
DEPS = $(wildcard *.h)
SOURCE = $(wildcard *.c)
OBJ = $(SOURCE:.c=.o)

.PHONY: all clean

all: $(LIB)

%.o: %.c $(DEPS)
	$(CC) -c $(CFLAGS) -o $@ $<

$(LIB): $(OBJ)
	$(CC) -shared -o $@ $^

clean:
	$(RM) $(OBJ) $(LIB)