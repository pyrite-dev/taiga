CC = cc
CFLAGS = -I external/xemil/include -I src
LDFLAGS =
LIBS =

.PHONY: all clean

all: taiga

include objs.mk

taiga$(E): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f src/*.o taiga taiga.exe
