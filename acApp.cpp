#include "acApp.h"

acApp *acApp::theApp = NULL;
int aaGrabCount;
int aaLastMouseButton;
boolean aaValidWindowSize;

/* for mouseCallback Y switcheroo and reshaping */
extern "C" GLint acuWindowHeight;
extern "C" GLint acuWindowWidth;


/* This is some glue that connects the app to the window system */

/*
#ifdef ACU_WIN32
#include "ansi_prefix.win32.h"
#include <windows.h>
#include <stdio.h>
#define ExternalApp extern "C" __declspec(dllexport) acApp
#define ExternalType extern "C" __declspec(dllexport) char
#else
#define ExternalApp extern "C" acApp
#define ExternalType extern "C" char
#endif
*/

acApp::acApp()
{
  aaGrabCount = -1;
  aaValidWindowSize = FALSE;
  X = Y = 0;
  W = H = 100;
}

void acApp::selfStart()
{
  GLint screenSize[2];
  theApp = this;

  glutDisplayFunc(display_cb); 
  glutMouseFunc(mouse_cb);
  glutMotionFunc(motion_cb);
  glutPassiveMotionFunc(passive_motion_cb);
  glutIdleFunc(idle_cb);
  glutKeyboardFunc(keyboard_cb);
  glutSpecialFunc(special_key_cb);
  glutReshapeFunc(NULL);
  glutReshapeFunc(reshape_cb);

  acuGetIntegerv(ACU_WINDOW_SIZE, screenSize);
  resize(0, 0, screenSize[0], screenSize[1]);
  setFocus(true);
  glutMainLoop();
}

void acApp::setFocus(bool state) { }

void acApp::setParent(void *parent) { }

void acApp::resize(float posX, float posY, float width, float height) {
  X = posX;
  Y = posY;
  W = width;
  H = height;
}

bool acApp::pointInside(float x, float y) {
  return (x >= 0 && y >= 0 && x < W && y < H);
}

void acApp::screenGrab() {
  char ext[6];
  switch (acuGetInteger(ACU_SCREEN_GRAB_FORMAT)) {
    case ACU_FILE_FORMAT_JPEG: sprintf(ext, "jpg"); break;
    case ACU_FILE_FORMAT_RAW: sprintf(ext, "raw"); break;
    case ACU_FILE_FORMAT_PPM: sprintf(ext, "ppm"); break;
    case ACU_FILE_FORMAT_TIFF: sprintf(ext, "tif"); break;
  }

  char grabTemp[24];
  if (aaGrabCount == -1) {
    // set aaGrabCount by checking to see how many files exist
    aaGrabCount = 0;
    int fd = -1;
    do {
      if (fd != -1) { 
	close(fd);
	aaGrabCount++;
      }
      sprintf(grabTemp, "screen-%04d.%s", aaGrabCount, ext);
    } while ((fd = open(grabTemp, O_RDONLY)) != -1);
  }
  sprintf(grabTemp, "screen-%04d.%s", aaGrabCount, ext);
  acuScreenGrab(grabTemp);
  aaGrabCount++;
}

//int acApp::getModifiers() { return lastModifiers; }
void acApp::mouseMove(float x, float y) { }
void acApp::mouseDown(float x, float y, int button) { }

void acApp::mouseDrag(float x, float y) { 
  mouseDrag(x, y, aaLastMouseButton);
}

void acApp::mouseDrag(float x, float y, int button) { }
void acApp::mouseUp(float x, float y, int button) { }

void acApp::keyDown(char c) { 
  // Default behavior, close program on escape
  if (c == 27) // escape
    acuClose();
}
void acApp::specialKeyDown( int key) { }
 
void acApp::draw() { }
void acApp::idle() { }

void display_cb(void) {
  if (!aaValidWindowSize)
    aaValidWindowSize = (acuGetInteger(ACU_WINDOW_WIDTH) != 0);
  if (aaValidWindowSize) {
    /* BENJAMIN FRY -- FIX ME!!! */
    acuOpenMazoFrame();
    acApp::theApp->draw();
    acuCloseMazoFrame();
  }
}

void mouse_cb(int button, int state, int x, int y) {
  //lastModifiers = glutGetModifiers();
  if (state == GLUT_DOWN) {
    acApp::theApp->mouseDown(x, ((acuWindowHeight-1)-y), button);
  } else if (state == GLUT_UP) {
    acApp::theApp->mouseUp(x, ((acuWindowHeight-1)-y), button);
  }
  aaLastMouseButton = button;
}

void motion_cb(int x, int y) {
  //lastModifiers = glutGetModifiers();
  acApp::theApp->mouseDrag(x, ((acuWindowHeight-1)-y));
}

void passive_motion_cb(int x, int y) {
  //lastModifiers = glutGetModifiers();
  acApp::theApp->mouseMove(x, ((acuWindowHeight-1)-y));
}

void idle_cb(void) {
  acApp::theApp->idle();
  glutPostRedisplay();
}

void keyboard_cb(unsigned char key, int x, int y) {
  //lastModifiers = glutGetModifiers();
  acApp::theApp->keyDown(key);
}

void special_key_cb(int key, int x, int y) {
  //lastModifiers = glutGetModifiers();
  acApp::theApp->specialKeyDown(key);
}

void reshape_cb(int width, int height) {
  acuWindowWidth = width;
  acuWindowHeight = height;
  acApp::theApp->resize(0, 0, width, height);
}

/*----------------- gl wrapper code -----------------*/

#ifdef AC_GLWRAP

#define getTime() ((float)clock())
#define TIME_CONVERT 1000000.0

#define	LISTENQ		1024
#define bzero(ptr,n)    memset(ptr, 0, n)
#define	SA	        struct sockaddr
#define	MAXLINE		4096	

void* eventcaller( void* arg );
void* waitforquit( void* arg );

struct threadStruct
{
  char* hostname;
  acApp* App;
};

static bool QUIT_NOW = false;

void acApp::wrapStart()
{
  theApp = this;
  resize(0, 0, 1024,768 );

  // -------------- get hostname from user ------
  printf("enter hostname: ");
  char hostname[256];
  gets(hostname);
  if ( strlen(hostname) < 2 )
    strcpy( hostname, "localhost" );

  // ---------------- prelaunch ------------------
  int sockfd;
  long wrapFrameCount = 0;
  
  struct sockaddr_in servaddr;
  struct in_addr **pptr;
  
  struct hostent *hp;
  if ( (hp = gethostbyname(hostname)) == NULL )
    {
      printf("host name error\n");
      exit(0);
    }
  pptr = (struct in_addr**) hp->h_addr_list;
  
  if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    {
      printf("socket error");
      exit(0);
    }

  bzero( &servaddr, sizeof(servaddr) );
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(9999);
  memcpy( &servaddr.sin_addr, *pptr, sizeof(struct in_addr) );
  printf( "trying %s\n", Sock_ntop( (SA*)&servaddr,
				    sizeof(servaddr)) );
  
  // put exit(0) back in 
  if ( connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) < 0 )
    {
      printf("connect error\n");
      exit(0);
    }
  printf("connected to draw server\n");
  
  // launch event thread
  threadStruct* pass = new threadStruct;
  pass->hostname = hostname;
  pass->App = this;

  int status;
  pthread_t thread;
  status = pthread_create( &thread, NULL, eventcaller, (void*)pass );
  if ( status != 0 )
    {
      printf("error creating thread\n");
      exit(0);
    }
  printf("successful thread creation\n");

  pthread_create( &thread, NULL, waitforquit, (void*)NULL );

  // ---------------- postlaunch ------------------

  float lastTime = getTime();
  long timeStart = getTime();
  long frameNum = 0;
  
  while( true )
    {
      // printf("test3\n");
      if ( getTime() - lastTime > TIME_CONVERT*0.005 )
	{
	  idle();
	  acGLWrapStart();
	  draw();
	  acGLWrapFinish();
	  int bufferSize = acGLWrapGetBufferSize();
	  int curTime = time(0);
	
	  if ( Writen( sockfd, &bufferSize, sizeof(int) )==0 )
	    goto closelabel;
	  if ( Writen( sockfd, &curTime, sizeof(int) )==0 )
	    goto closelabel;
	  if ( Writen( sockfd, acGLWrapGetBuffer(), bufferSize )==0 )
	    goto closelabel;
	  frameNum++;
	  if ( frameNum%100==50 )
	   {
	      long nowTime = ((float)getTime());
	      float rate = (float) frameNum * TIME_CONVERT;
	      rate /= (float)(nowTime-timeStart);
	      printf("client frame rate: %f\n", rate );
	      printf("client bytes/frame: %d\n", bufferSize );
	      //  printf("event: %d\n", eventInt );
	    }
	  lastTime = getTime();
	  wrapFrameCount++;
	}
      if ( QUIT_NOW )
	goto closelabel;
      sleep(0);
    }
closelabel:
  printf("closing draw connection: %d\n", sockfd );
  close(sockfd);
}

void* eventcaller( void* arg )
{
  int status = pthread_detach( pthread_self() );
  if ( status != 0 )
    {
      printf("bad detach\n");
      exit(0);
    }

  int esockfd;
  struct sockaddr_in eservaddr;
  struct in_addr **pptr;
  
  threadStruct* pass = (threadStruct*) arg;
  char* hostname = pass->hostname;

  struct hostent *hp;
  if ( (hp = gethostbyname(hostname)) == NULL )
    {
      printf("host name error\n");
      exit(0);
    }
  pptr = (struct in_addr**) hp->h_addr_list;

  if ( (esockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    {
      printf("socket error");
      exit(0);
    } 

  bzero( &eservaddr, sizeof(eservaddr) );
  eservaddr.sin_family = AF_INET;
  eservaddr.sin_port = htons(9876);
  memcpy( &eservaddr.sin_addr, *pptr, sizeof(struct in_addr) );
  printf( "trying %s\n", Sock_ntop( (SA*)&eservaddr,
				    sizeof(eservaddr)) );

  if ( connect(esockfd, (SA*)&eservaddr, sizeof(eservaddr)) < 0 )
    {
      printf("connect error\n");
      exit(0);
    } 

  printf("event connect success\n");

  // actual event communication
  EventStruct events;
  EventStruct lastEvents;
  long checkCount = 0;
  bool callMouseDown = false;
  bool callKeyDown = false;
  bool callMouseUp = false;

  long startTime = getTime();
  for( ; ; )
    {
      long nowTime = getTime();
      if ( checkCount%2000==1000 )
	printf("client EVENT rate: %.3f\n", 
	       (float)checkCount*TIME_CONVERT/(float)(nowTime-startTime) );
      
      if ( Readn( esockfd, &events, sizeof(events) )==0 )
	goto closelabel;
      
      if ( checkCount!=0 && !callMouseDown && 
	   events.mouseIsDown && !lastEvents.mouseIsDown )
	callMouseDown = true;

      if ( checkCount!=0 && !callMouseUp && 
	   !events.mouseIsDown && lastEvents.mouseIsDown )
	callMouseUp = true;

      if ( checkCount!=0 && ! callKeyDown && 
	   events.keyDown != lastEvents.keyDown )
	callKeyDown = true;
      
      lastEvents = events;
      // process events once per frame
      checkCount++;
      if ( callMouseDown )
	acApp::theApp->mouseDown( events.mouseX, events.mouseY, events.mouseButton );
      if ( callMouseUp )
	acApp::theApp->mouseUp( events.mouseX, events.mouseY, events.mouseButton );
      if ( events.mouseIsDown )
	acApp::theApp->mouseDrag( events.mouseX, events.mouseY );
      else
	acApp::theApp->mouseMove( events.mouseX, events.mouseY );
      if ( events.windowWidth != acApp::theApp->W || events.windowHeight != acApp::theApp->H )
	{
	  acApp::theApp->W = events.windowWidth;
	  acApp::theApp->H = events.windowHeight;
	  acApp::theApp->resize( 0, 0, events.windowWidth, events.windowHeight );
	}
      
      callMouseDown = callMouseUp = callKeyDown = false;
	  
      if ( QUIT_NOW )
	goto closelabel;
      sleep(0);
    }
  
closelabel:
  printf("closing event connection: %d\n", esockfd );
  close(esockfd);
  return NULL;
}


void* waitforquit( void* arg )
{
  int status = pthread_detach( pthread_self() );
  if ( status != 0 )
    {
      printf("bad detach\n");
      exit(0);
    }
  
  char str[256];
  printf("press 'q' to quit: ");
  gets( str );
  printf("done\n");
  QUIT_NOW = true;
  return NULL;
}

#endif
