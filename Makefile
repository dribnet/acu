#!gmake
#include $(ROOT)/usr/include/make/commondefs

#MYINC_DIR = /u/$(USER)/include
ACINC_DIR = /acg/include

#MYLIB_DIR = /u/$(USER)/lib
ACLIB_DIR = /acg/lib

default: lib

#jarold extralibs = -lsocket -lpthread
extralibs =

# these are the linux (?) options
#CC=CC
#OPTIONS=-g -DACU_LINUX -DAC_GLWRAP -LANG:ansi-for-init-scope=ON

# these are the options for cygwin make with gcc
CC=gcc
OPTIONS=-g -DNO_JPEG

#this is macosx
#CC=cc
#OPTIONS = -g -DACU_MAC -F/System/Library/Frameworks/GLUT

.c.o:
	$(CC) $(OPTIONS) $(extralibs) -c $<

%.o : %.cpp
	$(CC) $(OPTIONS) $(extralibs)  -c $<

OBJS=\
	acApp.o acGeo.o acVec3f.o acVec4f.o acMatrix4f.o \
	geometry.o main.o misc.o text.o video.o \
	acBitmapFont.o acVectorFont.o 
# NOT USED IN CYGWIN -- jpeg.o
# RETIRED -- acFreeTypeFont.o ai.o acx.o 

lib:	$(OBJS)
	rm -f libacu.a libacu.so
	/usr/bin/ar ru libacu.a $?
        # on mac you must run randlib, video.c un-inited constants mean -c
	#MAC: ranlib -c libacu.a

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

