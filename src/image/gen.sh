#!/bin/sh
if [ -d src ]; then
	cd src
fi
if [ -d image ]; then
	cd image
fi
for i in *.gif *.png; do
	NAME="`echo "$i" | rev | cut -d/ -f1 | rev | cut -d. -f1`"
	xxd -i -n image_$NAME $i > $NAME.c
	echo "extern unsigned char image_$NAME[];" > $NAME.h
	echo "extern unsigned int image_${NAME}_len;" >> $NAME.h
done
