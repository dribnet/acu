#include "acApp.h"

//acApp *acApp::theApp = NULL;
int aaGrabCount;
int aaLastMouseButton;
boolean aaValidWindowSize;
acApp* apps[10];

/* for mouseCallback Y switcheroo and reshaping */
extern "C" GLint acuWindowHeight;
extern "C" GLint acuWindowWidth;

// keep these here, otherwise will cause conflicts! (don't put in .h)
#include <fcntl.h>
#include <unistd.h>


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
  //theApp = this;
  apps[glutGetWindow()] = this;

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

void acApp::subStart() {
  //theApp = this;
  apps[glutGetWindow()] = this;

  glutDisplayFunc(display_cb); 
  glutMouseFunc(mouse_cb);
  glutMotionFunc(motion_cb);
  glutPassiveMotionFunc(passive_motion_cb);
  glutIdleFunc(idle_cb);
  glutKeyboardFunc(keyboard_cb);
  glutSpecialFunc(special_key_cb);
  glutReshapeFunc(NULL); // why first set to null?
  glutReshapeFunc(reshape_cb);
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
    case ACU_FILE_FORMAT_SCRSAVE: sprintf(ext, "rgb"); break;
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

void acApp::mouseDrag(float x, float y) { }
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
    //acApp::theApp->draw();
    apps[glutGetWindow()]->draw();
    acuCloseMazoFrame();
  }
}

void mouse_cb(int button, int state, int x, int y) {
  //lastModifiers = glutGetModifiers();
  if (state == GLUT_DOWN) {
    apps[glutGetWindow()]->mouseDown(x, ((acuWindowHeight-1)-y), button);
  } else if (state == GLUT_UP) {
    apps[glutGetWindow()]->mouseUp(x, ((acuWindowHeight-1)-y), button);
  }
  aaLastMouseButton = button;
}

void motion_cb(int x, int y) {
  //lastModifiers = glutGetModifiers();
  apps[glutGetWindow()]->mouseDrag(x, ((acuWindowHeight-1)-y));
  apps[glutGetWindow()]->mouseDrag(x, ((acuWindowHeight-1)-y), aaLastMouseButton);
}

void passive_motion_cb(int x, int y) {
  //lastModifiers = glutGetModifiers();
  apps[glutGetWindow()]->mouseMove(x, ((acuWindowHeight-1)-y));
}

void idle_cb(void) {
  apps[glutGetWindow()]->idle();
  glutPostRedisplay();
}

void keyboard_cb(unsigned char key, int x, int y) {
  //lastModifiers = glutGetModifiers();
  apps[glutGetWindow()]->keyDown(key);
}

void special_key_cb(int key, int x, int y) {
  //lastModifiers = glutGetModifiers();
  apps[glutGetWindow()]->specialKeyDown(key);
}

void reshape_cb(int width, int height) {
  acuWindowWidth = width;
  acuWindowHeight = height;
  apps[glutGetWindow()]->resize(0, 0, width, height);
}


