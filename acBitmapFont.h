#ifndef _AC_BITMAP_FONT_H_
#define _AC_BITMAP_FONT_H_

#include "acu.h"
#include "acFont.h"


class acBitmapFont : public acFont {
public:
  acBitmapFont() { }  // for subclasses.. grr.
  acBitmapFont(const char *filename);

  float getDescent();
  float getHeight();
  float charWidth(unsigned char c);
  float charHeight(unsigned char c);
  boolean charExists(unsigned char c);
  void drawChar(unsigned char c, float x, float y);
  int getFormat();
  unsigned char* getCharData(unsigned char c, float *x, float *y, 
			     float *w, float *h);
  //protected:
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

  float charBitmapWidth(unsigned char c);
  float charBitmapHeight(unsigned char c);
  float charTop(unsigned char c);
  float charTopExtent(unsigned char c);
  float charLeftExtent(unsigned char c);
};

#endif

