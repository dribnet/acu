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
  virtual float charWidth(unsigned char c) { return 0; }
  virtual float charHeight(unsigned char c) { return 0; }
  virtual boolean charExists(unsigned char c) { return FALSE; }
  virtual void drawChar(unsigned char c, float x, float y) { }
  virtual float kernWidth(unsigned char a, unsigned char b) { return 0; }
  virtual int getFormat() { return ACU_ERROR; }
  virtual boolean isValid() { return valid; }

  virtual float stringWidth(unsigned char *s) {
    float wide = 0;
    float pwide = 0;
    unsigned char previous = 0;
    while (*s != 0) {
      if (*s == '\n') {
	if (wide > pwide) pwide = wide;
	wide = 0;
	previous = 0;
      } else {
	wide += charWidth(*s);
	if (previous != 0) 
	  wide += kernWidth(previous, *s);
	previous = *s;
      }
      s++;
    }
    return (pwide > wide) ? pwide : wide;
  }

  virtual void drawString(unsigned char *c, float x, float y) {
    glPushMatrix();
    float startX = x;
    int index = 0;
    unsigned char previous = 0;
    while (c[index] != 0) {
      if (c[index] == '\n') {
	x = startX;
	y -= getDefaultLeading();
	//printf("adding leading\n");
	previous = 0;
      } else {
	drawChar(c[index], x, y);
	x += charWidth(c[index]);
	if (previous != 0)
	  x += kernWidth(previous, c[index]);
	previous = c[index];
      }
      index++;
    }
    glPopMatrix();
  }


protected:
  boolean valid;
};


#endif
