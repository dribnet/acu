#include <stdio.h>  
#include <windows.h>  


// added by fry, 26 september 2001

// this is a simplified version of the code max wrote for
// the moma project, with api fixed to look something like 
// a regular streams-type object. 
// example code at the end of this document.


class acSerial {
public:
  HANDLE comm;

  acSerial(char *portname, int rate);
  ~acSerial();

  int read(unsigned char *buffer, int count);
  int write(unsigned char *buffer, int count);
};


/*
// sample implementation example
// not guaranteed to work, but there haven't been any 
// confirmed bugs found here yet. just bitchin and moanin.

class HappySerial : public acThread {
public:
  unsigned char buffer[128];
  acSerial *happy;
  boolean ready;

  HappySerial() {
    ready = false;
    happy = new acSerial("COM2", 9600);
  }

  ~HappySerial() {
    delete happy;
  }

  void run() {
    while (true) {
      while (ready) { }  // wait until the app reads
      //printf("reading...\n");
      int count = happy->read(buffer, 4);
      //printf("got data..\n");
      ready = true;
      acThread::sleep(50);
    }
  }
};



inside draw() ...

    if (happy.ready) {
      tilt +=
        ((TWO_PI * ((float)happy.buffer[0] / 255.0)) - tilt) / 20.0;

      rotationSpeed +=
        ((4.0 * ((float)happy.buffer[1] / 255.0)) - rotationSpeed) / 10.0;

      thickSteps = (STEPS * happy.buffer[2]) / 255;

      //printf("got new data %d %d %d %d\n",
      //     happy.buffer[0], happy.buffer[1],
      //     happy.buffer[2], happy.buffer[3]);
      happy.ready = false;
    } else {
      //printf("no new data\n");
    }

*/
