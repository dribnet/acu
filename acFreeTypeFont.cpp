#include "acFreeTypeFont.h"


acFreeTypeFont::acFreeTypeFont(const char *name) {
  valid = FALSE;

  char filename[256];
  strcpy(filename, name);
  char *p = strchr(filename, ' ');
  *p++ = 0;
  fontSize = atoi(p);
  
  face = new FTFace();
  if (!face->open(filename)) {
    sprintf(acuDebugStr, "unable to open font %s", filename);
    acuDebugString(ACU_DEBUG_PROBLEM);
    return;
  }

  font = new GLTTPixmapFont(face);
  if (!font->create(fontSize)) {
    sprintf(acuDebugStr, "could not set up %s in size %d", font, fontSize);
    acuDebugString(ACU_DEBUG_PROBLEM);
    return;
  }
  valid = TRUE;
  //printf("initialized font\n");
}

acFreeTypeFont::acFreeTypeFont(const char *filename) {
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

  // read in the FreeType data
  //images = new unsigned char[numChars][64*64*4];
  images = new unsigned char*[numChars];
  for (i = 0; i < numChars; i++) {
    images[i] = new unsigned char[64*64*4];
    int FreeTypeSize = height[i] * width[i];
    //printf("FreeType size is %d\n", FreeTypeSize);
    unsigned char *temp = new unsigned char[FreeTypeSize];
    fread(temp, FreeTypeSize, 1, fp);

    // convert the FreeType to an alpha channel
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

float acFreeTypeFont::getDescent() {
  return (float)(height['p'-33] - topExtent['p'-33]) / 64.0f;
}

float acFreeTypeFont::getHeight() {
  return (float)mboxY / 64.0f;
}

float acFreeTypeFont::charWidth(char c) {
  // width of the horizontal space char takes up
  if (c != ' ') {
    return (float)setWidth[c-33] / 64.0f;
  } else {
    //return charWidth('i')*1.2f;
    return charWidth('n'); // support monospace better
  }
}

float acFreeTypeFont::charHeight(char c) {
  return (float)height[c-33] / 64.0f;
}

float acFreeTypeFont::charFreeTypeWidth(char c) {
  // width of the FreeType itself
  return (float)width[c-33] / 64.0f;
}

float acFreeTypeFont::charFreeTypeHeight(char c) {
  // same as charHeight
  return (float)height[c-33] / 64.0f;
}

float acFreeTypeFont::charTop(char c) {
  return -charHeight(c) + (float)(topExtent[c-33]) / 64.0f;
}

float acFreeTypeFont::charTopExtent(char c) {
  return (float)topExtent[c-33] / 64.0f;
}

float acFreeTypeFont::charLeftExtent(char c) {
  return (float)leftExtent[c-33] / 64.0f;
}

boolean acFreeTypeFont::charExists(char c) {
  //return (c-33 < numChars);
  return ((c > 32) && (c-33 < numChars));

}

unsigned char* acFreeTypeFont::getCharData(char c, float *x, float *y, float *w, float *h) {
  if (!charExists(c)) return NULL;
  *x = charLeftExtent(c);
  *y = charTop(c);
  *w = charFreeTypeWidth(c);
  *h = charHeight(c);
  /*
  params[0] = charLeftExtent(c); // x
  params[1] = charTop(c); // y
  params[2] = charFreeTypeWidth(c); // width
  params[3] = charHeight(c); // height
  //params[4] = bwidth; // maxu
  //params[5] = height; // maxv
  */
  return images[c-33];
}

void acFreeTypeFont::drawChar(char c, float x, float y) {
  // x,y is insertion point, lower-left, on baseline
  //if (c < 33) return;
  //if (c > numChars + 32) return;
  if (!charExists(c)) return;

  //glEnable(GL_TEXTURE_2D);

  float height = charHeight(c);
  //float width = charWidth(c);
  float bwidth = charFreeTypeWidth(c);
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


