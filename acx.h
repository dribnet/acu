#ifndef ACX_H
#define ACX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "acu.h"
#include "acVec3f.h"
#include "acMatrix4f.h"

/* for file stuff */
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

/* some functions check aiCapture */
#include "ai.h"


#define acxNextPowerOf2(x) ((int) pow(2, ceil(log(x) / log(2))))


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

  /*
void acxSphericalToCartesian3(float *s, float *c);
void acxSphericalToCartesian2(float *x, float *y, float *z,
			     float *cx, float *cy, float *cz);
void acxSphericalToCartesian(float x, float y, float z,
			     float *cx, float *cy, float *cz);
void acxCartesianToSpherical(float cx, float cy, float cz, 
			     float *x, float *y, float *z);
#define acxSphericalToCartesian4(s, c) { \
  register float x0 = s[0] * TWO_PI; \
  register float y0 = s[1] * PI; \
  register float z0 = s[2] * TWO_PI; \
  c[0] = z0 * cos(x0) * sin(y0); \
  c[1] = z0 * sin(x0) * sin(y0); \
  c[2] = z0 * cos(y0); }
  */

#define acxSphericalToCartesian(sx, sy, sz, cx, cy, cz) { \
  float _x0 = sx * TWO_PI; \
  float _y0 = sy * PI; \
  float _z0 = sz * TWO_PI; \
  cx = _z0 * cos(_x0) * sin(_y0); \
  cy = _z0 * sin(_x0) * sin(_y0); \
  cz = _z0 * cos(_y0); }

#define acxCartesianToSpherical(cx, cy, cz, sx, sy, sz) { \
  sz = sqrt(cx*cx + cy*cy + cz*cz) / TWO_PI; \
  sx = (cx == 0) ? 0 : atan(cy/cx) / TWO_PI; \
  sy = (cz == 0) ? 0 : atan(sqrt(cx*cx + cy*cy) / cz) / PI; }

#ifdef __cplusplus
}
#endif
#endif /* ACX_H */
