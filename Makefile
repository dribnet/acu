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

again: clean lib

