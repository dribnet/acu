#include "acu.h"
#include "acx.h"


/*
  THIS IS HIGHLY UNSUPPORTED CODE THAT CHANGES ALL THE TIME
  ben fry 99.12.19
*/


extern boolean aiCapture;

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
