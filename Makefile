#!gmake

default: lib

CC=gcc
OPTIONS=-g -DACU_IRIX

.c.o:
	$(CC) $(OPTIONS) -c $<

%.o : %.cpp
	$(CC) $(OPTIONS) -c $<

OBJS=\
	acApp.o \
	acFont.o \
	acVec3f.o \
	geometry.o \
	jpeg.o \
	main.o \
	misc.o \
	text.o \
	video.o 


lib:	$(OBJS)
	/usr/bin/ar ruv libacu.a $?

clean:
	rm -f *.o libacu.a *~

install: $(lib)
	rm -f /acg/lib/libacu.a
	cp libacu.a /acg/lib/.
	chmod 555 /acg/lib/libacu.a
	cp *.h /acg/include/.

again: clean lib

