#include "acThread.h"


long WINAPI acThreadProcess(long parameter);
long WINAPI acThreadProcess(long parameter) {
  //printf("attempting to start %x\n", parameter);
  acThread *theThread = (acThread*)parameter;
  theThread->run();
  return 1L;
}


acThread::acThread() {
}


acThread::~acThread() {
  stop();
}


void acThread::start() {
  threadID = 0;
  threadHandle = CreateThread(NULL,   // no specific security settings
			      0,      // use a regular stack size
			      (LPTHREAD_START_ROUTINE) acThreadProcess,
			      this,   // pass self as arg to thread function
			      //NULL,   // null arg to thread function
			      (unsigned long) 0, // CREATE_SUSPENDED is false
			      &threadID);  // unique integer ID for thread
  if (!threadHandle) {
    //acuDebug(ACU_DEBUG_EMERGENCY, "could not create thread");
    fprintf(stderr, "could not create thread\n");
    // this will terminate the application
  } 
  SetThreadPriority(threadHandle, THREAD_PRIORITY_NORMAL);
}


void acThread::run() { }


void acThread::stop() { }


void acThread::sleep(int millis) {
  Sleep(millis);
}
