#ifndef _AC_BITMAP_FONT_H_
#define _AC_BITMAP_FONT_H_

#include "acu.h"
#include "acFont.h"


class acBitmapFont : public acFont {
public:
  acBitmapFont(const char *filename);

  float getDescent();
  float getHeight();
  float charWidth(char c);
  float charHeight(char c);
  boolean charExists(char c);
  void drawChar(char c, float x, float y);

protected:
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

  float charBitmapWidth(char c);
  float charBitmapHeight(char c);
  float charTop(char c);
  float charTopExtent(char c);
  float charLeftExtent(char c);
};

#endif

