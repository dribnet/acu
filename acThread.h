#ifndef AC_THREAD_H
#define AC_THREAD_H

// this includes acu constants
//#include "acApp.h"

#include <stdio.h>
//#ifdef ACU_WIN32
// this includes HANDLE, etc. for windows
#include <wtypes.h>
//#endif


/*
  notes about using acThread:

  you cannot start a thread until idle(), 
    it cannot be started inside your acApp's class constructor
    do something like this:
    void idle() {
      if (!started) {
        myThread->start();
	started = TRUE;
      }
    }

  stop() currently does nothing
  the destructor ~acThread() just calls stop (which does nothing)
 */

class acThread {
public:
  acThread();
  ~acThread();

  void start();
  void stop();

  virtual void run();

  static void sleep(int millis);  // hot mama java style

private:
  unsigned long threadID;
  HANDLE threadHandle;
};


#endif
