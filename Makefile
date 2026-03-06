CC ?= cc
CFLAGS ?= -I external/xemil/include -I src
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
	-rm -f *.res

format:
	clang-format --verbose -i `find src -name "*.c" -or -name "*.h"`

clean:
	rm -f src/*.o taiga taiga.exe
