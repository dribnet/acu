#ifndef _ACUX_
#define _ACUX_

#include "acu.h"
#include "acVec3f.h"
#include "acMatrix4f.h"

/* for file stuff */
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

/* some functions check aiCapture */
#include "ai.h"


void drawCatmullRom(int pointCount, float *xpoints, float *ypoints);
void drawCatmullRomBezier(int pointCount, float *xpoints, float *ypoints);
void drawBezier(int pointCount, float *xpoints, float *ypoints);

float acuxFrameRate();

void acuxNumberedFilename(char *dest, char *tmpl, int *num);

void acuxReadToEOL(FILE *fp);
void acuxReadSpace(FILE *fp);
void acuxReadWord(FILE *fp, char *word);
float acuxReadFloat(FILE *fp);

#endif
