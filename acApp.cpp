#include "acApp.h"

//acApp *acApp::theApp = NULL;
int aaGrabCount;
int aaLastMouseButton;
boolean aaValidWindowSize;
acApp* apps[10];

int aahaveShrunk=FALSE, aafullScreen=TRUE, aafullWidth, aafullHeight;
int aaWinH, aaWinW, aaWinX, aaWinY;

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

  // the following 3 lines were removed from acuOpen
  glutCreateWindow("acu");
  glutFullScreen();
  acuGlobalGLSettings();

  //theApp = this;
  apps[glutGetWindow()] = this;

  glutDisplayFunc(display_cb); 
  glutMouseFunc(mouse_cb);
  glutMotionFunc(motion_cb);
  glutPassiveMotionFunc(passive_motion_cb);
  glutIdleFunc(idle_cb);
  glutKeyboardFunc(keyboard_cb);
  glutSpecialFunc(special_key_cb);
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

/* this quitAtOne idle callback rewiring quit thing
 * is a workaround for bad driver/cards that don't like
 * to quit in fullscreen mode
 */
int quitAtOne = 0;

void winddown_cb(void) {
  if(quitAtOne <= 1) acuClose();
  else --quitAtOne;
}

void acApp::keyDown(char c) { 
  GLint small[] = {100, 100};
  // Default behavior, close program on escape
  if (c == 27) { // escape
    // it doesn't exit in fullscreen mode, but shrinks first
    acuSetIntegerv(ACU_WINDOW_SIZE, small);
    glutIdleFunc(winddown_cb);
    quitAtOne = 5;
  }
}

void acApp::specialKeyDown( int key) {
  /* default behavior of SKD: toggle between fullscreen on F1
   * if you override and want to keep, just call acApp::specialKeyDown(key) 
   * on F1 (or even acApp::specialKeyDown(GLUT_KEY_F1) on a different key)
   */
  GLint size[2];
  if(key == GLUT_KEY_F1) {
     if(aafullScreen) {
       if(aahaveShrunk == FALSE) {
         aahaveShrunk = TRUE;
         aafullWidth = acuWindowWidth;
         aafullHeight = acuWindowHeight;
         aaWinW = acuWindowWidth - 70;
         aaWinH = acuWindowHeight - 90;
         aaWinX = 35;
         aaWinY = 55;
       }
       aafullScreen = FALSE;
       aafullWidth = (int)W;
       aafullHeight = (int)H;
       size[0] = aaWinW; size[1] = aaWinH;
       acuSetIntegerv(ACU_WINDOW_SIZE, size);
       glutPositionWindow(aaWinX, aaWinY);
     }
     else {
       aafullScreen = TRUE;
       aaWinX = glutGet(GLUT_WINDOW_X);
       aaWinY = glutGet(GLUT_WINDOW_Y);
       aaWinW = (int)W;
       aaWinH = (int)H;
       glutFullScreen();
     }
  }
}
 
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


