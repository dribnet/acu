#include "acu.h"
#include "acx.h"


/*
  THIS IS HIGHLY UNSUPPORTED CODE THAT CHANGES ALL THE TIME
  ben fry 99.12.19
*/

#ifndef AI_H
#define AI_H


extern boolean aiCapture;
extern FILE *aifp;

void aiBegin(char *filename);
void aiEnd();
void aiScreenShapeMacro();

void aiFillColorRGB(float r, float g, float b);
void aiStrokeColorRGB(float r, float g, float b);
void aiStrokeColorHSB(float h, float s, float b);
void aiStrokeColorHSBA(float h, float s, float b, float a);
void aiStrokeColorGet();

void aiBeginGroup();
void aiEndGroup();

void aiBeginLock();
void aiEndLock();

void aiStrokeWidth(float width);
void aiStrokeWidthGet();

void aiBeginPath();
void aiMoveTo(float x, float y);
void aiLineTo(float x, float y);
void aiCurveTo(float x1, float y1, float x2, float y2, float x3, float y3);
void aiEndPath();

void aiLineMacro(float x1, float y1, float x2, float y2);
void aiFilledRectangleMacro(float x1, float y1, float x2, float y2);

void aiSetMatrix(float *matrix);
void aiSetMatrixGet();
void aiMoveTo3f(float x, float y, float z);
void aiLineTo3f(float x, float y, float z);

void aiSetFont(char *fontFace, int fontSize);
void aiDrawString(char *what, float x, float y);
void aiDrawString3f(char *what, float x, float y, float z);

void aigSetFont(char *filename);
float aigStringWidth(char *s);
void aigDrawChar(char c, float x, float y);
void aigDrawString(char *s, float x, float y);

#define AIG_OPCODE_MAX 100
#define AIG_SCALE 125
class aiGlyph {
  public:
  int count;
  char opcode[AIG_OPCODE_MAX];
  float value[AIG_OPCODE_MAX][6];  
  float left; 
  float extent;

  aiGlyph() { 
    count = 0;
  }

  void draw(FILE *fp, float x, float y);
};


#endif
