#include "acBitmapFont.h"


acBitmapFont::acBitmapFont(const char *filename) {
  int i;
  valid = FALSE;
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL) {
    sprintf(acuDebugStr, "Could not open font file %s", filename);
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
  for (i = 0; i < numChars; i++) {
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

float acBitmapFont::getDescent() {
  return (float)(height['p'-33] - topExtent['p'-33]) / 64.0f;
}

float acBitmapFont::getHeight() {
  return (float)mboxY / 64.0f;
}

float acBitmapFont::charWidth(char c) {
  // width of the horizontal space char takes up
  if (c != ' ') {
    return (float)setWidth[c-33] / 64.0f;
  } else {
    //return charWidth('i')*1.2f;
    return charWidth('n'); // support monospace better
  }
}

float acBitmapFont::charHeight(char c) {
  return (float)height[c-33] / 64.0f;
}

float acBitmapFont::charBitmapWidth(char c) {
  // width of the bitmap itself
  return (float)width[c-33] / 64.0f;
}

float acBitmapFont::charBitmapHeight(char c) {
  // same as charHeight
  return (float)height[c-33] / 64.0f;
}

float acBitmapFont::charTop(char c) {
  return -charHeight(c) + (float)(topExtent[c-33]) / 64.0f;
}

float acBitmapFont::charTopExtent(char c) {
  return (float)topExtent[c-33] / 64.0f;
}

float acBitmapFont::charLeftExtent(char c) {
  return (float)leftExtent[c-33] / 64.0f;
}

boolean acBitmapFont::charExists(char c) {
  //return (c-33 < numChars);
  return ((c > 32) && (c-33 < numChars));

}

unsigned char* acBitmapFont::getCharData(char c, float *x, float *y, float *w, float *h) {
  if (!charExists(c)) return NULL;
  *x = charLeftExtent(c);
  *y = charTop(c);
  *w = charBitmapWidth(c);
  *h = charHeight(c);
  /*
  params[0] = charLeftExtent(c); // x
  params[1] = charTop(c); // y
  params[2] = charBitmapWidth(c); // width
  params[3] = charHeight(c); // height
  //params[4] = bwidth; // maxu
  //params[5] = height; // maxv
  */
  return images[c-33];
}

void acBitmapFont::drawChar(char c, float x, float y) {
  // x,y is insertion point, lower-left, on baseline
  //if (c < 33) return;
  //if (c > numChars + 32) return;
  if (!charExists(c)) return;

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


