#ifndef _ACX_
#define _ACX_

#include "acu.h"
#include "acVec3f.h"
#include "acMatrix4f.h"

/* for file stuff */
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

/* some functions check aiCapture */
#include "ai.h"


void acxDrawCatmullRom(int pointCount, float *xpoints, float *ypoints);
void acxDrawCatmullRomBezier(int pointCount, float *xpoints, float *ypoints);
void acxDrawBezier(int pointCount, float *xpoints, float *ypoints);

float acxFrameRate();

void acxNumberedFilename(char *dest, char *tmpl, int *num);

void acxReadToEOL(FILE *fp);
void acxReadSpace(FILE *fp);
void acxReadWord(FILE *fp, char *word);
float acxReadFloat(FILE *fp);

void acxSphericalToCartesian(float x, float y, float z,
			      float *cx, float *cy, float *cz);
void acxCartesianToSpherical(float cx, float cy, float cz, 
			      float *x, float *y, float *z);

#endif
