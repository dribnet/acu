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
void acxFrameRateDelay(int targetFPS);


void acxNumberedFilename(char *dest, char *tmpl, int *num);

void acxReadToEOL(FILE *fp);
void acxReadSpace(FILE *fp);
void acxReadWord(FILE *fp, char *word);
float acxReadFloat(FILE *fp);

int acxLoadFontOrDie(char *filename);


extern float acxLeftRightAngle, acxUpDownAngle, acxFwdBackTrans;
extern float acxLastMouseX, acxLastMouseY;

void acxTrackballMouseDown(float x, float y);
void acxTrackballMouseDrag(float x, float y);
void acxTrackballTransform();
void acxZoomMouseDown(float x, float y);
void acxZoomMouseDrag(float x, float y);
void acxZoomTransform();


void acxSphericalToCartesian(float x, float y, float z,
			     float *cx, float *cy, float *cz);
void acxCartesianToSpherical(float cx, float cy, float cz, 
			     float *x, float *y, float *z);

#endif
