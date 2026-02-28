CC = cc
CFLAGS = -I external/xemil/include
LDFLAGS =
LIBS =

.PHONY: all clean

all: taiga

include objs.mk

taiga$(E): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f *.o taiga taiga.exe
