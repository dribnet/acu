#ifndef _AC_FONT_H_
#define _AC_FONT_H_

#include "acu.h"

class acFont {
public:
  int numChars;
  int numBits;
  int mboxX;
  int mboxY;
  int baseHt;

  // per character
  int *value;
  int *height;
  int *width;
  int *setWidth;
  int *topExtent;
  int *leftExtent;

  unsigned char **images;
  GLuint *texNames;
  
  boolean valid;

  acFont(const char *filename);
  float getAscent();
  float getDescent();
  float getXHeight();
  float getHeight();
  float getEmWidth();
  float getDefaultLeading();
  float stringWidth(char *s);
  float charWidth(char c);
  float charHeight(char c);
  float charBitmapWidth(char c);
  float charBitmapHeight(char c);
  float charTop(char c);
  float charTopExtent(char c);
  float charLeftExtent(char c);
  boolean charExists(char c);
  float kernWidth(char a, char b);
  void drawChar(char c, float x, float y);
  boolean isValid();
};
#endif
