#include "acu.h"

#if defined(ACU_LINUX)
#include <limits.h>
#endif

/* These functions exist either as convenience (lerp)
 * or because they are system-dependent (random, time).
 * In the latter case, #defines will be used when porting
 * acu to other platforms. 
 */

GLint acuTimeStep = 1;

int acuCurrentTimeMillis() {
  /* exactly what you need, when you need it */
  return glutGet((GLenum) GLUT_ELAPSED_TIME) / acuTimeStep;
}


// hsb/rgb functions stolen from java awt
// and modified to use all floats, from 0..1

void acuColorHsb(float h, float s, float b, float a) { 
  float which, f, p, q, t;

  if (s == 0) {
    glColor4f(b, b, b, a);
    return;
  }
  which = (h - floor(h)) * 6.0;
  f = which - floor(which);
  p = b * (1.0 - s);
  q = b * (1.0 - s * f);
  t = b * (1.0 - (s * (1.0 - f)));
  
  switch ((int)which) {
  case 0: glColor4f(b, t, p, a); break;
  case 1: glColor4f(q, b, p, a); break;
  case 2: glColor4f(p, b, t, a); break;
  case 3: glColor4f(p, q, b, a); break;
  case 4: glColor4f(t, p, b, a); break;
  case 5: glColor4f(b, p, q, a); break;
  }
}


void acuHsbToRgb(GLfloat *hsb, GLfloat *rgb) {
  if (hsb[1] == 0) {
    rgb[0] = rgb[1] = rgb[2] = hsb[2];
  } else {
    GLfloat h = (hsb[0] - floor(hsb[0])) * 6.0;
    GLfloat f = h - floor(h);
    GLfloat p = hsb[2] * (1.0 - hsb[1]);
    GLfloat q = hsb[2] * (1.0 - hsb[1] * f);
    GLfloat t = hsb[2] * (1.0 - (hsb[1] * (1.0 - f)));
    switch ((int) h) {
    case 0:
      rgb[0] = hsb[2];
      rgb[1] = t;
      rgb[2] = p;
      break;
    case 1:
      rgb[0] = q;
      rgb[1] = hsb[2];
      rgb[2] = p;
      break;
    case 2:
      rgb[0] = p;
      rgb[1] = hsb[2];
      rgb[2] = t;
      break;
    case 3:
      rgb[0] = p;
      rgb[1] = q;
      rgb[2] = hsb[2];
      break;
    case 4:
      rgb[0] = t;
      rgb[1] = p;
      rgb[2] = hsb[2];
      break;
    case 5:
      rgb[0] = hsb[2];
      rgb[1] = p;
      rgb[2] = q;
      break;
    }
  }
}


void acuRgbToHsb(GLfloat *rgb, GLfloat *hsb) {
  GLfloat cmax = (rgb[0] > rgb[1]) ? rgb[0] : rgb[1];
  GLfloat cmin = (rgb[0] < rgb[1]) ? rgb[0] : rgb[1];

  if (rgb[2] > cmax) cmax = rgb[2];
  if (rgb[2] < cmin) cmin = rgb[2];
  
  // brightness is the max of r, g, b
  hsb[2] = cmax;

  // saturation is the min divided by the max
  if (cmax != 0)
    hsb[1] = (cmax - cmin) / cmax;
  else
    hsb[1] = 0;

  // hue is a little more difficult
  if (hsb[1] == 0)
    hsb[0] = 0;
  else {
    GLfloat redc = (cmax - rgb[0]) / (cmax - cmin);
    GLfloat greenc = (cmax - rgb[1]) / (cmax - cmin);
    GLfloat bluec = (cmax - rgb[2]) / (cmax - cmin);
    if (rgb[0] == cmax)
      hsb[0] = bluec - greenc;
    else if (rgb[1] == cmax)
      hsb[0] = 2.0 + redc - bluec;
    else
      hsb[0] = 4.0 + greenc - redc;
    hsb[0] = hsb[0] / 6.0;
    if (hsb[0] < 0)
      hsb[0] = hsb[0] + 1.0;
  }
}

GLfloat acuRandomf() {
#if defined(ACU_IRIX)
  return (GLfloat)random()*2.0 / (LONG_MAX+1.0) - 1.0;
#elif defined(ACU_LINUX)
  return (GLfloat)random()*2.0 / (LONG_MAX+1.0) - 1.0;
#elif defined(ACU_WIN32)
  return (GLfloat) ((float)(rand() >> 0) / 16384.0) - 1.0;
#else
  acuDebug(ACU_DEBUG_EMERGENCY, "Please implement acuRandom on your platform");
#endif
}


GLfloat acuRandomuf() {
#if defined(ACU_IRIX)
  return (GLfloat)random() / (LONG_MAX+1.0);
#elif defined(ACU_LINUX)
  return (GLfloat)random() / (LONG_MAX+1.0);
#elif defined(ACU_WIN32)
  return (GLfloat) ((float)(rand() >> 0) / 32768.0);
#else
  acuDebug(ACU_DEBUG_EMERGENCY, "Please implement acuRandom on your platform");
#endif
}


GLint acuRandomui() {
#if defined(ACU_IRIX)
  return random();
#elif defined(ACU_LINUX)
  return random();
#elif defined(ACU_WIN32)
  return rand();
#else
  acuDebug(ACU_DEBUG_EMERGENCY, "Please implement acuRandom on your platform");
#endif
}

GLfloat acuLerpf(GLfloat t, GLfloat a, GLfloat b) {
  return (a + t * (b - a));
}

GLfloat acuSerpf(GLfloat t, GLfloat a, GLfloat b) {
	float factor;
	
	if(t<0.5) factor = 2.0 * t * t;
	else factor = 1 - 2.0 * (1.0 - t) * (1.0 - t);
	return (a + factor * (b - a));
}


int acuReadInt(FILE *fp) {
  int c1 = fgetc(fp);
  int c2 = fgetc(fp);
  int c3 = fgetc(fp);
  int c4 = fgetc(fp);
#ifndef GRABASS_ENDIAN_SWAP
  return (c1 << 24) | (c2 << 16) | (c3 << 8) | (c4);
#else
  return (c4 << 24) | (c3 << 16) | (c2 << 8) | (c1);
#endif
}


unsigned char* acuRecomponentArray2D(unsigned char *data, 
				     int width, int height,
				     int inComponents, int outComponents,
				     unsigned char background) {
  int i, j;
  unsigned char *out;
  int count = width * height;

  out = (unsigned char*) malloc(count * outComponents);
  for (i = 0; i < count; i++) {
    for (j = 0; j < outComponents; j++) {
      out[i*outComponents+j] = data[i*inComponents+j];
    }
    for (j = inComponents; j < outComponents; j++) {
      out[i*outComponents+j] = background;
    }
  }
  return out;
}


unsigned char* acuResizeArray2D(unsigned char *data, 
				int inWidth, int inHeight,
				int outWidth, int outHeight,
				int components,
				unsigned char background) {
  int i, x, y;
  int src, dest;
  unsigned char *out;
    
  out = (unsigned char*) malloc(outWidth*outHeight * components);
  for (i = 0; i < outWidth*outHeight*components; i++) {
    out[i] = background;
  }

  //printf("in, out = %d %d, %d %d\n", inWidth, inHeight, outWidth, outHeight);
  for (y = 0; y < outHeight; y++) {
    src = y * inWidth * components;
    dest = y * outWidth * components;
    for (x = 0; x < outWidth*components; x++) {
      out[dest++] = data[src++];
    }
  }    
  return out;
}


void* acuReadRawFile(char *filename, int *length) {
  FILE *tp = fopen(filename, "r");
  if (tp == NULL) {
    sprintf(acuDebugStr, "could not find %s\n", filename);
    acuDebugString(ACU_DEBUG_PROBLEM);
    return NULL;
  }
  fseek(tp, 0, SEEK_END);
  int fileLength = (int) ftell(tp);
  rewind(tp);

  // it looks like NTFS files aren't the size
  // that ftell would lead us to believe
  char *fileData = new char[fileLength];
  int remaining = fileLength;
  int offset = 0;
  while (remaining) {
    int count = fread(&fileData[offset], 1, remaining, tp);
    if (feof(tp)) { 
      remaining = count;
      fileLength = offset + count;
    }
    offset += count;
    remaining -= count;
  }
  fclose(tp);
  *length = fileLength;
  return fileData;
}

/*
// aww, nobody liked this code anyway
unsigned char* acuReadRawFile(char *filename, int count) {
  unsigned char *buffer;
  FILE *fp;

  fp = fopen(filename, "rb");
  buffer = (unsigned char*) malloc(count);

  fread(buffer, 1, count, fp);
  fclose(fp);
  return buffer;
}
*/


void acuWriteRawFile(char *filename, void *data, int count) {
  FILE *fp = fopen(filename, "wb");
  fwrite(data, count, 1, fp);
  fclose(fp);
}

#define NEW_SUBFILE_TYPE   254
#define IMAGE_WIDTH        256
#define IMAGE_LENGTH       257
#define BITS_PER_SAMPLE    258
#define PHOTO_INTERP       262
#define STRIP_OFFSETS      273
#define SAMPLES_PER_PIXEL  277
#define ROWS_PER_STRIP     278
#define STRIP_BYTE_COUNT   279

#define HDR_SIZE    8
#define MAP_SIZE    768
#define IMAGE_START 768

void writeTiffFileEntry(FILE *fp, int tag, int fieldType, 
			int count, int value) {
  fputc((tag >> 8) & 0xff, fp);
  fputc((tag >> 0) & 0xff, fp);

  fputc((fieldType >> 8) & 0xff, fp);
  fputc((fieldType >> 0) & 0xff, fp);

  fputc((count >> 24) & 0xff, fp);
  fputc((count >> 16) & 0xff, fp);
  fputc((count >> 8) & 0xff, fp);
  fputc((count >> 0) & 0xff, fp);

  if ((count == 1) && (fieldType == 3))
    value <<= 16;

  fputc((value >> 24) & 0xff, fp);
  fputc((value >> 16) & 0xff, fp);
  fputc((value >> 8) & 0xff, fp);
  fputc((value >> 0) & 0xff, fp);
}

void acuWriteTiffFile(char *filename, unsigned char *data, 
		      int width, int height) {
  //int bitsPerSample = 8;
  int imageSize = width * height;
  int nEntries = 9;

  int photoInterp = 2; 
  int samplesPerPixel = 3;

  int ifdSize = 2 + nEntries*12 + 4;
  //int stackSize = imageSize;

  int imageOffset = IMAGE_START;

  FILE *fp = fopen(filename, "wb");

  // write the header
  fputc(77, fp);  // "MM" (Motorola byte order)
  fputc(77, fp);
  fputc(0, fp);
  fputc(42, fp);  // 42 (magic number)
  fputc(0, fp);   // 8 (offset to first IFD)
  fputc(0, fp);
  fputc(0, fp);
  fputc(8, fp);

  // write IFD
  int bitsPerSampleOffset = HDR_SIZE + ifdSize;

  fputc((nEntries >> 8) & 0xff, fp);
  fputc((nEntries >> 0) & 0xff, fp);

  writeTiffFileEntry(fp, NEW_SUBFILE_TYPE,  4, 1, 0);
  writeTiffFileEntry(fp, IMAGE_WIDTH,       3, 1, width);
  writeTiffFileEntry(fp, IMAGE_LENGTH,      3, 1, height);
  writeTiffFileEntry(fp, BITS_PER_SAMPLE,   3, 3, bitsPerSampleOffset);
  writeTiffFileEntry(fp, PHOTO_INTERP,      3, 1, photoInterp);
  writeTiffFileEntry(fp, STRIP_OFFSETS,     4, 1, imageOffset);
  writeTiffFileEntry(fp, SAMPLES_PER_PIXEL, 3, 1, samplesPerPixel);
  writeTiffFileEntry(fp, ROWS_PER_STRIP,    3, 1, height);
  writeTiffFileEntry(fp, STRIP_BYTE_COUNT,  4, 1, imageSize*3);

  fputc(0, fp); // next IFD
  fputc(0, fp);
  fputc(0, fp);
  fputc(0, fp);

  // write bits per pixel and filler
  fputc(0, fp); 
  fputc(8, fp);
  fputc(0, fp); 
  fputc(8, fp);
  fputc(0, fp); 
  fputc(8, fp);
  int bpsSize = 6;

  int fillerCount = IMAGE_START - (HDR_SIZE+ifdSize+bpsSize);
  for (int i = 0; i < fillerCount; i++) fputc(0, fp);

  // write the image data
  fwrite(data, imageSize*3, 1, fp);

  fclose(fp);
}

/* video.c calls these functions, so they better be defined somewhere */
#ifdef NO_JPEG
unsigned char* acuReadJpegFile(char *filename,
                               int *width, int *height) 
{
  acuDebug(ACU_DEBUG_EMERGENCY, "This platform does not have acuReadJpegFile");
}

void acuWriteJpegFile(char *filename, unsigned char *data,
                      int width, int height, int quality)
{
  acuDebug(ACU_DEBUG_EMERGENCY, "This platform does not have acuWriteJpegFile");
}
#endif
