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
  //printf("acThread::~acThread() called\n");
  stop();
}


void acThread::start() {
  //printf("start() %8x\n", this);
  threadID = 0;
  threadHandle = CreateThread(NULL,   // no specific security settings
			      0,      // use a regular stack size
			      (LPTHREAD_START_ROUTINE) acThreadProcess,
			      this,   // pass self as arg to thread function
			      //NULL,   // null arg to thread function
			      (unsigned long) 0, // CREATE_SUSPENDED is false
			      &threadID);  // unique integer ID for thread
  if (!threadHandle) {
    //printf("App: SoundOut thread creation failed.\n");
    acuDebug(ACU_DEBUG_EMERGENCY, "could not create thread");
    // this will terminate the application
  } 
  //printf("created %d\n", threadID);
  //else {
  //printf("App: SoundOut thread creation succeeded, ID %d.\n", id);
  SetThreadPriority(threadHandle, THREAD_PRIORITY_NORMAL);
  //}	
}


// don't forget to call Sleep() in subclass

void acThread::run() {
  //while (TRUE) {
  //printf("hello\n");
  //Sleep(0);
  //}
  // default method, overriden by subclasses
}


void acThread::stop() {
  //printf("acThread::stop() called\n");
  // duh.. what should i do here?
}
