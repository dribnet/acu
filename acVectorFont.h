#ifndef _AC_VECTOR_FONT_H_
#define _AC_VECTOR_FONT_H_

#include "acu.h"
#include "acFont.h"


// this may cause name conflicts down the road
#define MOVETO 1
#define LINETO 2


class acVectorFont : public acFont {
public:
  acVectorFont(const char* filename);

  float getDescent();
  float getHeight();
  float charWidth(char c);
  float charHeight(char c);
  boolean charExists(char c);
  //float kernWidth(char a, char b);
  void drawChar(char c, float x, float y);
   
protected:
  float x[256][50];
  float y[256][50];
  int kind[256][50];
  int numPoints[256];
  float width[256];
  float height[256];
  
  float descent;
  float maxHeight;
};

#endif





