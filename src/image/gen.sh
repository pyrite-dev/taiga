#!/bin/sh
if [ -d src ]; then
	cd src
fi
if [ -d image ]; then
	cd image
fi
for i in *.gif *.png; do
	NAME="`echo "$i" | rev | cut -d/ -f1 | rev | cut -d. -f1`"
	NAME2="`echo "$NAME" | sed 's/-/_/g'`"
	xxd -i -n image_$NAME2 $i > $NAME.c
	echo "extern unsigned char image_$NAME2[];" > $NAME.h
	echo "extern unsigned int image_${NAME2}_len;" >> $NAME.h
done
