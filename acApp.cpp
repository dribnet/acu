#include "acApp.h"

acApp *acApp::theApp = NULL;
int grabCount;
boolean validWindowSize;

/* for mouseCallback Y switcheroo and reshaping */
extern GLint acuWindowHeight;
extern GLint acuWindowWidth;

acApp::acApp()
{
  grabCount = -1;
  validWindowSize = FALSE;
  X = Y = 0;
  W = H = 100;
}

void acApp::selfStart()
{
  int screenSize[2];
  
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

void acApp::resize( float posX, float posY, float width, float height) {
  X = posX;
  Y = posY;
  W = width;
  H = height;
}

bool acApp::pointInside( float x, float y ) {
  return (x >= 0 && y >= 0 && x < W && y < H);
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

void acApp::mouseDown(float x, float y, int button) { }
void acApp::mouseUp(float x, float y, int button) { }
void acApp::mouseMove(float x, float y) { }
void acApp::mouseDrag(float x, float y) { }

void acApp::keyDown( char c ) { 
  // Default behavior, close program on escape
  if (c == 27) // escape
    acuClose();
}
void acApp::specialKeyDown( int key) { }
 
void acApp::draw() { }
void acApp::idle() { }

void display_cb(void)
{
  if (!validWindowSize)
    validWindowSize = (acuGetInteger(ACU_WINDOW_WIDTH) != 0);
  if (validWindowSize) {
    /* BENJAMIN FRY -- FIX ME!!! */
    acuOpenMazoFrame();
    acApp::theApp->draw();
    acuCloseMazoFrame();
  }
}

void mouse_cb(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN) {
    acApp::theApp->mouseDown(x, ((acuWindowHeight-1)-y), button);
  } else if (state == GLUT_UP) {
    acApp::theApp->mouseUp(x, ((acuWindowHeight-1)-y), button);
  }
}

void motion_cb(int x, int y)
{
  acApp::theApp->mouseDrag(x, ((acuWindowHeight-1)-y));
}

void passive_motion_cb(int x, int y)
{
  acApp::theApp->mouseMove(x, ((acuWindowHeight-1)-y));
}

void idle_cb(void)
{
  acApp::theApp->idle();
  glutPostRedisplay();
}

void keyboard_cb(unsigned char key, int x, int y)
{
  acApp::theApp->keyDown(key);
}

void special_key_cb(int key, int x, int y)
{
  acApp::theApp->specialKeyDown(key);
}

void reshape_cb(int width, int height) {
  acuWindowWidth = width;
  acuWindowHeight = height;
  acApp::theApp->resize(0, 0, width, height);
}

