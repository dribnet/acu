#include "acApp.h"

acApp *acApp::theApp = NULL;
int grabCount;
boolean validWindowSize;

acApp::acApp()
{
  grabCount = -1;
  validWindowSize = FALSE;
}

void acApp::selfStart()
{
  theApp = this;
  acuOpen();

  glutDisplayFunc(display_cb); 
  glutMouseFunc(mouse_cb);
  glutMotionFunc(motion_cb);
  glutPassiveMotionFunc(passive_motion_cb);
  glutIdleFunc(idle_cb);
  glutKeyboardFunc(keyboard_cb);
  glutSpecialFunc(special_key_cb);

  prepare();
  glutMainLoop();
}


void acApp::screenGrab()
{
  char ext[6];
  switch (acuGetInteger(ACU_SCREEN_GRAB_FORMAT)) {
  case ACU_FILE_FORMAT_JPEG: sprintf(ext, "jpg"); break;
  case ACU_FILE_FORMAT_RAW: sprintf(ext, "raw"); break;
  case ACU_FILE_FORMAT_PPM: sprintf(ext, "ppm"); break;
  case ACU_FILE_FORMAT_TIFF: sprintf(ext, "tif"); break;
  }

  char grabTemp[24];
  if (grabCount == -1) {
    // set grabCount by checking to see how many files exist
    grabCount = 0;
    int fd = -1;
    do {
      if (fd != -1) { 
	close(fd);
	grabCount++;
      }
      sprintf(grabTemp, "screen-%04d.%s", grabCount, ext);
    } while ((fd = open(grabTemp, O_RDONLY)) != -1);
  }
  sprintf(grabTemp, "screen-%04d.%s", grabCount, ext);
  acuScreenGrab(grabTemp);
  grabCount++;
}


void acApp::mouseDown(int x, int y, int button) { }
void acApp::mouseUp(int x, int y, int button) { }
void acApp::mouseMove(int x, int y) { }
void acApp::mouseDrag(int x, int y) { }

void acApp::keyDown( char c ) { 
  // Default behavior, close program on escape
  if (c == 27) // escape
    acuClose();
}
void acApp::specialKeyDown( int key) { }
 
void acApp::prepare() { }
void acApp::draw() { }
void acApp::idle() { }
void acApp::start() { }
void acApp::stop() { }

void display_cb(void)
{
  if (!validWindowSize)
    validWindowSize = (acuGetInteger(ACU_WINDOW_WIDTH) != 0);
  if (validWindowSize)
    acApp::theApp->draw();
}

void mouse_cb(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN) {
    acApp::theApp->mouseDown(x, y, button);
  } else if (state == GLUT_UP) {
    acApp::theApp->mouseUp(x, y, button);
  }
}

void motion_cb(int x, int y)
{
  acApp::theApp->mouseDrag(x, y);
}

void passive_motion_cb(int x, int y)
{
  acApp::theApp->mouseMove(x, y);
}

void idle_cb(void)
{
  acApp::theApp->idle();
  display_cb();
}

void keyboard_cb(unsigned char key, int x, int y)
{
  acApp::theApp->keyDown(key);
}

void special_key_cb(int key, int x, int y)
{
  acApp::theApp->specialKeyDown(key);
}

