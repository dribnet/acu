#include "acBitmapFont.h"


// this is for encoding from windows ansi to mac ordering for 
// the 8 bits chars outside ascii range (chars with values > 127)
int win2mac[256] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 
  19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 
  35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
  52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 
  69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 
  86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 
  102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 
  115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
  -1, -1, 226, 196, 227, 201, 160, 224, 246, 228, -1, 220, 206, -1, 
  -1, -1, -1, 212, 213, 210, 211, 165, 208, 209, 247, 170, -1, 221, 
  207, -1, -1, 217, -1, 193, 162, 163, 219, 180, -1, 164, 172, 169, 
  187, 199, 194, -1, 168, 248, 161, 177, -1, -1, 171, 181, 166, 225, 
  252, -1, 188, 200, -1, -1, -1, 192, 203, 231, 229, 204, 128, 129, 
  174, 130, 233, 131, 230, 232, 237, 234, 235, 236, -1, 132, 241, 
  238, 239, 205, 133, -1, 175, 244, 242, 243, 134, -1, -1, 167, 136, 
  135, 137, 139, 138, 140, 190, 141, 143, 142, 144, 145, 147, 146, 
  148, 149, -1, 150, 152, 151, 153, 155, 154, 214, 191, 157, 156, 158, 
  159, -1, -1
};


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
  //printf("num chars for font is %d\n", numChars);
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

int acBitmapFont::getFormat() {
  return ACU_BITMAP_FONT;
}

float acBitmapFont::getDescent() {
  return (float)(height['p'-33] - topExtent['p'-33]) / 64.0f;
}

float acBitmapFont::getHeight() {
  return (float)mboxY / 64.0f;
}

float acBitmapFont::charWidth(unsigned char c) {
  // width of the horizontal space char takes up
  //if (c != ' ') {
  if (charExists(c)) {
    return (float)setWidth[win2mac[c]-33] / 64.0f;

  } else {
    //return charWidth('i')*1.2f;
    return charWidth('n'); // support monospace better
  }
}

float acBitmapFont::charHeight(unsigned char c) {
  return charExists(c) ? (float)height[win2mac[c]-33]/64.0f : 0;
}

float acBitmapFont::charBitmapWidth(unsigned char c) {
  // width of the bitmap itself
  return charExists(c) ? (float)width[win2mac[c]-33] / 64.0f : 0;
}

float acBitmapFont::charBitmapHeight(unsigned char c) {
  // same as charHeight
  return charExists(c) ? (float)height[win2mac[c]-33] / 64.0f : 0;
}

float acBitmapFont::charTop(unsigned char c) {
  return charExists(c) ? 
    (-charHeight(c) + (float)(topExtent[win2mac[c]-33]) / 64.0f) : 0;
}

float acBitmapFont::charTopExtent(unsigned char c) {
  return charExists(c) ? 
    (float)topExtent[win2mac[c]-33] / 64.0f : 0;
}

float acBitmapFont::charLeftExtent(unsigned char c) {
  return charExists(c) ? 
    (float)leftExtent[win2mac[c]-33] / 64.0f : 0;
}

boolean acBitmapFont::charExists(unsigned char c) {
  //return (c-33 < numChars);
  if (win2mac[c] == -1) return false;  // out of encoding
  return ((c > 32) && (c-33 < numChars));
  //return ((c > 32) && (c < numChars));
}

unsigned char* acBitmapFont::getCharData(unsigned char c, float *x, float *y, float *w, float *h) {
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

void acBitmapFont::drawChar(unsigned char c, float x, float y) {
  // x,y is insertion point, lower-left, on baseline
  //if (c < 33) return;
  //if (c > numChars + 32) return;
  if (!charExists(c)) return;

  /*
  if (!charExists(c)) {
    int m = win2mac[c-128];
    if (m == -1) m = 'X';
    printf("%d does not exist %c '%c'\n", c, c, m);
    return;
  }

  //if (c+33 > 127) {
  if (c > 127) {
    //printf("got something outside: %d\n", c+33);
    c = win2mac[c];
    if (c == -1) return; // char not in encoding
    printf("found %c\n", (unsigned char)c);
  }
  //glEnable(GL_TEXTURE_2D);
  */

  float height = charHeight(c);
  //float width = charWidth(c);
  float bwidth = charBitmapWidth(c);
  float top = charTop(c);
  float lextent = charLeftExtent(c);

#ifndef CANNOT_BIND_TEXTURES

  if (glIsTexture(texNames[win2mac[c]-33])) {
    acuNamedTexRectf(x+lextent, y+top, 
		     x+lextent+bwidth, y+height+top, 
		     texNames[win2mac[c]-33], bwidth, height);
  } else {
    sprintf(acuDebugStr, "Could not bind: %c %d\n", c, c);
    acuDebugString(ACU_DEBUG_MUMBLE);
    acuTexRectf(x+lextent, y+top, x+lextent+bwidth, y+height+top, 
		images[c-33], GL_RGBA, 4, 64, 64, bwidth, height);
  }

#else  

  acuTexRectf(x+lextent, y+top, x+lextent+bwidth, y+height+top, 
	      images[win2mac[c]-33], GL_RGBA, 4, 64, 64, bwidth, height);
#endif

#if 0
  // to draw the baseline
  glBegin(GL_LINES);
  glVertex3f(x, y, 0);
  glVertex3f(x+width*0.95f, y, 0);
  glEnd();
#endif
}


