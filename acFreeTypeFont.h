#ifndef _AC_FREETYPE_FONT_H_
#define _AC_FREETYPE_FONT_H_

#include "acu.h"
#include "acFont.h"


class acFreeTypeFont : public acFont {
public:
  acFreeTypeFont(const char *filename, int size);

  float getAscent();
  float getDescent();
  float getXHeight();
  float getHeight();
  float getEmWidth();
  float getDefaultLeading();
  float charWidth(char c);
  float charHeight(char c);
  boolean charExists(char c);
  void drawChar(char c, float x, float y);
  float kernWidth(char a, char b);

protected:
  int size; // useful?
  int tsize;

  int width[];
  int height[];
  int cols[];
  unsigned char **tdata;
  GLuint *tnames;

  int indices[256];

  //int advance; // 26.6
  //int delta_x, delta_y; // 26.6

  int ascent;
  int descent;
  
};

#endif
