#ifndef _AC_CRAPP_H_
#define _AC_CRAPP_H_

#include <fcntl.h>
#include <unistd.h>

#include "acu.h"

class acApp {
public:
  /* Your application can just have a simple 'main' in
   * a separate main.cpp file that looks something like this:
   * void main() {
   *   MyAcApp *myApp = new MyAcApp();
   *   myApp->selfStart();
   * }
   * selfStart() is the 'bootstrap' function to get the
   * app up and running. Don't override it unless you know
   * what you're doing.
   */
  acApp();
  virtual void selfStart();

  /* Called to let you know your program is (or isn't) getting attention. */
  virtual void setFocus(bool state);

  virtual void setParent(void *parent);

  /* The X, Y, W, H variables are the position and size of the window */
  float X, Y, W, H;

  /* Called when you are resized.
     Default implementation is to update X, Y, W, H
     If you override resize(), call acApp::resize() or do 
     this yourself */
  virtual void resize( float posX, float posY, float width, float height);

  /* Someone is asking you if (x,y) is your responsibility */
  virtual bool pointInside( float x, float y );

  /* (Generally) called once every frame, just before draw().
   * This is automatically called repeatedly as your
   * application 'idles'. Move things around here.
   */
  virtual void idle();

  /* Override this to do your actual drawing to the screen */
  /* A good acApp should draw the same thing if draw is called */
  /* twice in succession since idle(), not draw(), changes the model */
  virtual void draw();

  /* Writes the current GL buffer (your application's window)
   * to a JPEG file called 'screen-XXXX.jpg' with XXX being
   * automatically numbered. In addition, it won't write over
   * existing screen-XXXX files, because it looks for the highest
   * numbered screen in the current directory. 
   *
   * See acu.h for more information about writing to 
   * different file formats.
   *
   * If you're the type of person who wants to make a movie
   * of your acu application, you could use the following code
   * to resize your window so that subsequent screen grabs
   * would be 640x480. Put this towards the end of your 
   * prepare() function. 
   *
   * int screenSize[2];
   * screenSize[0] = 640;
   * screenSize[1] = 480;
   * acuSetIntegerv(ACU_WINDOW_SIZE, screenSize);
   */
  void screenGrab();

  /* Override these functions to get mouse events.
   * for mouseDown and mouseUp, button is one of:
   * GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON
   * Modifiers are one of:
   * GLUT_ACTIVE_SHIFT, GLUT_ACTIVE_CTRL, GLUT_ACTIVE_ALT 
   */
  int getModifiers();
  virtual void mouseDown(float x, float y, int button);
  virtual void mouseUp(float x, float y, int button);
  virtual void mouseMove(float x, float y);
  virtual void mouseDrag(float x, float y);

  /* Override to get keys from the keyboard. */
  virtual void keyDown(char c);
  
  /* Any sort of non-standard key, possibilities are:
   * GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, 
   * GLUT_KEY_F5, GLUT_KEY_F6, GLUT_KEY_F7, GLUT_KEY_F8, 
   * GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
   * GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN 
   * GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN,
   * GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
   */
  virtual void specialKeyDown(int key); 

  static acApp *theApp;
};

void display_cb(void);
void mouse_cb(int button, int state, int x, int y);
void motion_cb(int x, int y);
void passive_motion_cb(int x, int y);
void idle_cb(void);
void keyboard_cb(unsigned char key, int x, int y);
void special_key_cb(int key, int x, int y);
void reshape_cb(int x, int y);

#endif
