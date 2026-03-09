#!/bin/sh
echo > objs.mk
ls src/*.c src/action/*.c src/image/*.c src/skin/*.c external/xemil/src/*.c external/md4c/src/md4c.c | while read a; do
	O="src/`echo "$a" | sed 's/.c$/.o/' | sed 's/\//_/g'`"
	echo "OBJS += $O" >> objs.mk
	echo "$O: $a" >> objs.mk
	echo "	\$(CC) \$(CFLAGS) -c -o \$@ $a" >> objs.mk
done
