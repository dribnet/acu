#ifndef _AC_FONT_H_
#define _AC_FONT_H_

#include "acu.h"


class acFont {
public:
  virtual float getAscent() { return charHeight('H'); }
  virtual float getDescent() { return 0; }
  virtual float getXHeight() { return charHeight('x'); }
  virtual float getHeight() { return 0; }
  virtual float getEmWidth() { return charWidth('M'); }
  virtual float getDefaultLeading() { return getHeight() * 1.2; }
  virtual float charWidth(char c) { return 0; }
  virtual float charHeight(char c) { return 0; }
  virtual boolean charExists(char c) { return FALSE; }
  virtual void drawChar(char c, float x, float y) { }
  virtual float kernWidth(char a, char b) { return 0; }
  virtual boolean isValid() { return valid; }

  virtual float stringWidth(char *s) {
    float wide = 0.0;
    char previous = 0;
    while (*s != 0) {
      wide += charWidth(*s);
      if (previous != 0) 
	wide += kernWidth(previous, *s);
      previous = *s++;
    }
    return wide;
  }

  virtual void drawString(char *c, float x, float y) {
    glPushMatrix();
    int index = 0;
    char previous = 0;
    while (c[index] != 0) {
      drawChar(c[index], x, y);
      x += charWidth(c[index]);
      if (previous != 0)
	x += kernWidth(previous, c[index]);
      previous = c[index];
      index++;
    }
    glPopMatrix();
  }
  
  
protected:
  boolean valid;
};


#endif
