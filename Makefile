#!gmake
#include $(ROOT)/usr/include/make/commondefs

MYINC_DIR = /u/$(USER)/include
ACINC_DIR = /acg/include

MYLIB_DIR = /u/$(USER)/lib
ACLIB_DIR = /acg/lib

default: lib

extralibs = -lsocket -lpthread

CC=CC
OPTIONS=-g -DACU_IRIX -DAC_GLWRAP  -LANG:ansi-for-init-scope=ON

.c.o:
	$(CC) $(OPTIONS) $(extralibs) -c $<

%.o : %.cpp
	$(CC) $(OPTIONS) $(extralibs)  -c $<

OBJS=\
	acApp.o acVec3f.o acVec4f.o acMatrix4f.o ai.o acx.o \
	geometry.o jpeg.o main.o misc.o text.o video.o \
	acBitmapFont.o acVectorFont.o acSocketIO.o \
	acGLWrapper.o acGLUnwrapper.o # acFreeTypeFont.o 

lib:	$(OBJS)
	rm -f libacu.a libacu.so
	/usr/bin/ar ru libacu.a $?
	/usr/bin/ld -n32 -shared $(OBJS) -o libacu.so
	chmod 555 libacu.a libacu.so

clean:
	rm -f *.o libacu.a libacu.so *~

install: lib
	rm -f $(ACLIB_DIR)/libacu.a $(ACLIB_DIR)/libacu.so
	cp libacu.a libacu.so $(ACLIB_DIR)/.
	chmod 555 $(ACLIB_DIR)/libacu.a $(ACLIB_DIR)/libacu.so
	cp *.h $(ACINC_DIR)/.

mine: lib
	rm -f $(MYLIB_DIR)/libacu.a $(MYLIB_DIR)/libacu.so
	cp libacu.a libacu.so $(MYLIB_DIR)/.
	chmod 555 $(MYLIB_DIR)/libacu.a $(MYLIB_DIR)/libacu.so
	cp *.h $(MYINC_DIR)/.

again: clean lib

