
OBJS += external_xemil_src_array.o
external_xemil_src_array.o: external/xemil/src/array.c
	$(CC) $(CFLAGS) -c -o $@ external/xemil/src/array.c
OBJS += external_xemil_src_core.o
external_xemil_src_core.o: external/xemil/src/core.c
	$(CC) $(CFLAGS) -c -o $@ external/xemil/src/core.c
OBJS += external_xemil_src_file.o
external_xemil_src_file.o: external/xemil/src/file.c
	$(CC) $(CFLAGS) -c -o $@ external/xemil/src/file.c
OBJS += external_xemil_src_unicode.o
external_xemil_src_unicode.o: external/xemil/src/unicode.c
	$(CC) $(CFLAGS) -c -o $@ external/xemil/src/unicode.c
OBJS += external_xemil_src_util.o
external_xemil_src_util.o: external/xemil/src/util.c
	$(CC) $(CFLAGS) -c -o $@ external/xemil/src/util.c
OBJS += src_main.o
src_main.o: src/main.c
	$(CC) $(CFLAGS) -c -o $@ src/main.c
