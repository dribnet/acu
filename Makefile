#!gmake
include $(ROOT)/usr/include/make/commondefs

default: mine

CC=CC
OPTIONS=-g -DACU_IRIX

.c.o:
	$(CC) $(OPTIONS) -c $<

%.o : %.cpp
	$(CC) $(OPTIONS) -c $<

OBJS=\
	acApp.o acBitmapFont.o acVectorFont.o acVec3f.o \
	geometry.o jpeg.o main.o misc.o text.o video.o 

lib:	$(OBJS)
	/usr/bin/ar ruv libacu.a $?
	/usr/bin/ld -n32 -shared $(OBJS) -o libacu.so

clean:
	rm -f *.o libacu.a libacu.so *~

install: $(lib)
	rm -f /acg/lib/libacu.a /acg/lib/libacu.so
	cp libacu.a libacu.so /acg/lib/.
	chmod 555 /acg/lib/libacu.a /acg/lib/libacu.so
	cp *.h /acg/include/.

mine: lib
	cp libacu.* /mas/u/$(USER)/lib

again: clean lib







