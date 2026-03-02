
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
OBJS += src/src_classic.o
src/src_classic.o: src/classic.c
	$(CC) $(CFLAGS) -c -o $@ src/classic.c
OBJS += src/src_default.o
src/src_default.o: src/default.c
	$(CC) $(CFLAGS) -c -o $@ src/default.c
OBJS += src/src_dirent.o
src/src_dirent.o: src/dirent.c
	$(CC) $(CFLAGS) -c -o $@ src/dirent.c
OBJS += src/src_help.o
src/src_help.o: src/help.c
	$(CC) $(CFLAGS) -c -o $@ src/help.c
OBJS += src/src_image_fill.o
src/src_image_fill.o: src/image/fill.c
	$(CC) $(CFLAGS) -c -o $@ src/image/fill.c
OBJS += src/src_image_fixme.o
src/src_image_fixme.o: src/image/fixme.c
	$(CC) $(CFLAGS) -c -o $@ src/image/fixme.c
OBJS += src/src_image_logo1.o
src/src_image_logo1.o: src/image/logo1.c
	$(CC) $(CFLAGS) -c -o $@ src/image/logo1.c
OBJS += src/src_image_logo2.o
src/src_image_logo2.o: src/image/logo2.c
	$(CC) $(CFLAGS) -c -o $@ src/image/logo2.c
OBJS += src/src_image_note.o
src/src_image_note.o: src/image/note.c
	$(CC) $(CFLAGS) -c -o $@ src/image/note.c
OBJS += src/src_image_valid-css.o
src/src_image_valid-css.o: src/image/valid-css.c
	$(CC) $(CFLAGS) -c -o $@ src/image/valid-css.c
OBJS += src/src_image_valid-html401.o
src/src_image_valid-html401.o: src/image/valid-html401.c
	$(CC) $(CFLAGS) -c -o $@ src/image/valid-html401.c
OBJS += src/src_image_warning.o
src/src_image_warning.o: src/image/warning.c
	$(CC) $(CFLAGS) -c -o $@ src/image/warning.c
OBJS += src/src_main.o
src/src_main.o: src/main.c
	$(CC) $(CFLAGS) -c -o $@ src/main.c
OBJS += src/src_process.o
src/src_process.o: src/process.c
	$(CC) $(CFLAGS) -c -o $@ src/process.c
OBJS += src/src_seed.o
src/src_seed.o: src/seed.c
	$(CC) $(CFLAGS) -c -o $@ src/seed.c
OBJS += src/src_site.o
src/src_site.o: src/site.c
	$(CC) $(CFLAGS) -c -o $@ src/site.c
OBJS += src/src_util.o
src/src_util.o: src/util.c
	$(CC) $(CFLAGS) -c -o $@ src/util.c
