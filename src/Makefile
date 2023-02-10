CPPFLAGS = -I../lib
LDFLAGS:= -L../lib -llist
DEPS = $(wildcard *.h)
SOURCE = $(wildcard *.c)
OBJ = $(SOURCE:.c=.o)

BIN:= address_book

.PHONY: all clean

all: $(BIN)

%.o: %.c $(DEPS)
	$(CC) $(CPPFLAGS) -c -o $@ $^

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(BIN) $(OBJ)

