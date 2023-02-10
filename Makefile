.PHONY: all lib src

all: lib src

lib:
	$(MAKE) -C ./lib

src:
	$(MAKE) -C ./src

clean:
	$(MAKE) -C ./lib clean
	$(MAKE) -C ./src clean