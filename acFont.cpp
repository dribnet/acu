#include "acFont.h"

acFont::acFont(const char *filename) {
  int i;

  valid = FALSE;
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL) {
    sprintf(acuDebugStr, "Could not open file %s", filename);
    acuDebugString(ACU_DEBUG_PROBLEM);
    return;
  }

  // read the base font information
  numChars = acuReadInt(fp);
  numBits = acuReadInt(fp);
  mboxX = acuReadInt(fp);
  mboxY = acuReadInt(fp);
  baseHt = acuReadInt(fp);
  acuReadInt(fp);  // ignore 4 for struct;

  // allocate enough space for the character info
  value = new int[numChars];
  height = new int[numChars];
  width = new int[numChars];
  setWidth = new int[numChars];
  topExtent = new int[numChars];
  leftExtent = new int[numChars];

  // read the information about the individual characters
  for (i = 0; i < numChars; i++) {
    value[i] = acuReadInt(fp);
    height[i] = acuReadInt(fp);
    width[i] = acuReadInt(fp);
    setWidth[i] = acuReadInt(fp);
    topExtent[i] = acuReadInt(fp);
    leftExtent[i] = acuReadInt(fp);
    acuReadInt(fp); // pointer, ignored
  }

  // read in the bitmap data
  //images = new unsigned char[numChars][64*64*4];
  images = new unsigned char*[numChars];
  for (i = 0 ; i < numChars; i++) {
    images[i] = new unsigned char[64*64*4];
    int bitmapSize = height[i] * width[i];
    //printf("bitmap size is %d\n", bitmapSize);
    unsigned char *temp = new unsigned char[bitmapSize];
    fread(temp, bitmapSize, 1, fp);

    // convert the bitmap to an alpha channel
    int w = width[i];
    int h = height[i];
    for (int x = 0; x < w; x++) {
      for (int y = 0; y < h; y++) {
	int offset = (y*64 + x) * 4;
	images[i][offset + 0] = 255;
	images[i][offset + 1] = 255;
	images[i][offset + 2] = 255;
	images[i][offset + 3] = temp[(h-y-1)*w + x];
	//printf((images[i][offset+3] > 128) ? "*" : ".");
      }
      //printf("\n");
    }
  }

  // build textures for each of the characters
  texNames = new GLuint[numChars];
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  //printf("numChars is %d\n", numChars);
  glGenTextures(numChars, texNames);
  //for (int m = 0; m < numChars; m++) {
  //printf("%d ", texNames[m]);
  //}
    
  for (i = 0; i < numChars; i++) {
    glBindTexture(GL_TEXTURE_2D, texNames[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0,
		 GL_RGBA, GL_UNSIGNED_BYTE, images[i]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  }
  valid = TRUE;
}


float acFont::getAscent() {
  return (float)height['H'-33] / 64.0f;
}

float acFont::getDescent() {
  return (float)(height['p'-33] - topExtent['p'-33]) / 64.0f;
}

float acFont::getXHeight() {
  return (float)height['x'-33] / 64.0f;
}

float acFont::getHeight() {
  return (float)mboxY / 64.0f;
}

float acFont::getEmWidth() {
  return (float)width['M'-33] / 64.0f;
}

float acFont::getDefaultLeading() {
  return getHeight() * 1.1f; // + or * some value??;
}

float acFont::stringWidth(char *s) {
  float wide = 0.0;
  while (*s != 0) {
    wide += charWidth(*s++);
  }
  return wide;
}

float acFont::charWidth(char c) {
  // width of the horizontal space char takes up
  if (c != ' ') {
    return (float)setWidth[c-33] / 64.0f;
  } else {
    return charWidth('i')*1.2f;
  }
}

float acFont::charHeight(char c) {
  return (float)height[c-33] / 64.0f;
}

float acFont::charBitmapWidth(char c) {
  // width of the bitmap itself
  return (float)width[c-33] / 64.0f;
}

float acFont::charBitmapHeight(char c) {
  // same as charHeight
  return (float)height[c-33] / 64.0f;
}

float acFont::charTop(char c) {
  return -charHeight(c) + (float)(topExtent[c-33]) / 64.0f;
}

float acFont::charTopExtent(char c) {
  return (float)topExtent[c-33] / 64.0f;
}

float acFont::charLeftExtent(char c) {
  return (float)leftExtent[c-33] / 64.0f;
}

boolean acFont::charExists(char c) {
  return (c-33 < numChars);
}

// these old school bitmaps have no 
// kerning info, so this returns 0
float acFont::kernWidth(char a, char b) {
  return 0.0f;
}


void acFont::drawChar(char c, float x, float y) {
  // x,y is insertion point, lower-left, on baseline
  if (c < 33) return;
  if (c > numChars + 32) return;

  //glEnable(GL_TEXTURE_2D);

  float height = charHeight(c);
  //float width = charWidth(c);
  float bwidth = charBitmapWidth(c);
  float top = charTop(c);
  float lextent = charLeftExtent(c);

#ifndef CANNOT_BIND_TEXTURES

  if (glIsTexture(texNames[c-33])) {
    acuNamedTexRectf(x+lextent, y+top, 
		     x+lextent+bwidth, y+height+top, 
		     texNames[c-33], bwidth, height);
  } else {
    sprintf(acuDebugStr, "Could not bind: %c %d\n", c, c);
    acuDebugString(ACU_DEBUG_MUMBLE);
    acuTexRectf(x+lextent, y+top, x+lextent+bwidth, y+height+top, 
		images[c-33], GL_RGBA, 4, 64, 64, bwidth, height);
  }

#else  

  acuTexRectf(x+lextent, y+top, x+lextent+bwidth, y+height+top, 
	      images[c-33], GL_RGBA, 4, 64, 64, bwidth, height);
#endif

#if 0
  // to draw the baseline
  glBegin(GL_LINES);
  glVertex3f(x, y, 0);
  glVertex3f(x+width*0.95f, y, 0);
  glEnd();
#endif
}


boolean acFont::isValid() {
  return valid;
}
