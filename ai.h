#include "acu.h"
#include "acux.h"

extern boolean aiCapture;

void aiBegin(char *filename);
void aiEnd();

void aiFillColor(float r, float g, float b);
void aiStrokeColor(float r, float g, float b);

void aiBeginGroup();
void aiEndGroup();

void aiBeginLock();
void aiEndLock();

void aiBeginLine();
void aiMoveTo(float x, float y);
void aiLineTo(float x, float y);
void aiEndLine();

void aiLineMacro(float x1, float y1, float x2, float y2);
void aiFilledRectangleMacro(float x1, float y1, float x2, float y2);
