
OBJS += src/external_xemil_src_array.o
src/external_xemil_src_array.o: external/xemil/src/array.c
	$(CC) $(CFLAGS) -c -o $@ external/xemil/src/array.c
OBJS += src/external_xemil_src_core.o
src/external_xemil_src_core.o: external/xemil/src/core.c
	$(CC) $(CFLAGS) -c -o $@ external/xemil/src/core.c
OBJS += src/external_xemil_src_file.o
src/external_xemil_src_file.o: external/xemil/src/file.c
	$(CC) $(CFLAGS) -c -o $@ external/xemil/src/file.c
OBJS += src/external_xemil_src_unicode.o
src/external_xemil_src_unicode.o: external/xemil/src/unicode.c
	$(CC) $(CFLAGS) -c -o $@ external/xemil/src/unicode.c
OBJS += src/external_xemil_src_util.o
src/external_xemil_src_util.o: external/xemil/src/util.c
	$(CC) $(CFLAGS) -c -o $@ external/xemil/src/util.c
OBJS += src/src_main.o
src/src_main.o: src/main.c
	$(CC) $(CFLAGS) -c -o $@ src/main.c
