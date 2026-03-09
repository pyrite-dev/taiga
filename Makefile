CC ?= cc
CFLAGS ?= -I external/xemil/include -I external/md4c/src -I external/stb -I src $(DEFS)
LDFLAGS ?=
LIBS ?=
AFTER ?=

E ?=

.PHONY: all format clean

all: taiga$(E)

include objs.mk

taiga$(E): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)
	$(AFTER)

format:
	clang-format --verbose -i `find src -name "*.c" -or -name "*.h"`

clean:
	rm -f src/*.o src/*.res taiga taiga.exe
