#ifndef _AC_APP_H_
#define _AC_APP_H_

/*
#include <GL/glut.h>
#include <GL/glu.h>
*/
// TOM (some kinda ERROR directive went off) #include <sys/types.h>
// TOM (NOT GOOD IN WINDOWS) #include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "acu.h"


class acApp
{
public:

  /* Your application should just have a simple 'main' 
   * that looks something like this:
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

  /* Called once at the beginning of your application.
   * Do all acu-oriented initialization here, because
   * acuOpen() will have already been called by selfStart().
   */
  virtual void prepare();

  /* When your acApp is made visible, start will be called */
  virtual void start();

  /* If your acApp is backgrounded, stop will be called */
  virtual void stop();

  /* Called once every frame, just before draw().
   * This is automatically called repeatedly as your
   * application 'idles'. 
   */
  virtual void idle();

  /* Override this to do your actual drawing to the screen */
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
   */
  virtual void mouseDown(int x, int y, int button);
  virtual void mouseUp(int x, int y, int button);
  virtual void mouseMove(int x, int y);
  virtual void mouseDrag(int x, int y);

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

#endif
