#include "acVectorFont.h"


acVectorFont::acVectorFont(const char* filename) {
  valid = FALSE;
  int i;

  for (i = 0; i < 256; i++) {
    numPoints[i] = 0;
    width[i] = 0;
    height[i] = 0;
  }
  
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    sprintf(acuDebugStr, "Could not open font file %s", filename);
    acuDebugString(ACU_DEBUG_PROBLEM);
    return;
  }

  // read the font
  char str[64];
  float nX, nY;
  unsigned char currentLetter = 0;
  int currentPoint = 0;
  float bigWidth = 0;
  float bigHeight = 0;
  leading = 0;

  // fgets reads until newline or eof
  while (fgets(str, 64, fp)) {
    switch (str[0]) {
    case 'C':  // what character
      if (currentLetter != 0) {
	numPoints[currentLetter] = currentPoint;
	height[currentLetter] = bigHeight;
	if (width[currentLetter] == 0) {
	  // support the old-school format, not for long
	  width[currentLetter] = bigWidth * 1.5;
	}
	currentPoint = 0;
      }
      currentLetter = str[2];
      width[currentLetter] = 0;
      height[currentLetter] = 0;
      bigWidth = 0; 
      bigHeight = 0;
      currentPoint = 0;
      break;

    case 'L':  // lineto
      sscanf(str, "L %f %f\n", &nX, &nY);
      kind[currentLetter][currentPoint] = LINETO;
      x[currentLetter][currentPoint] = nX;
      y[currentLetter][currentPoint] = nY;
      if (nX > bigWidth) bigWidth = nX;
      if (nY > bigHeight) bigHeight = nY;
      currentPoint++;
      break;

    case 'M':  // moveto
      sscanf(str, "M %f %f\n", &nX, &nY);
      kind[currentLetter][currentPoint] = MOVETO;
      x[currentLetter][currentPoint] = nX;
      y[currentLetter][currentPoint] = nY;
      if (nX > bigWidth) bigWidth = nX;
      if (nY > bigHeight) bigHeight = nY;
      currentPoint++;
      break;

    case 'W':  // width
      sscanf(str, "W %f\n", &width[currentLetter]);
      break;

    case 'D':  // leading
      sscanf(str, "D %f\n", &leading);
      break;

    case 0:  // blank line
    case '#':  // comment
      break;

    default:
      // got something not understood
      sprintf(acuDebugStr, "strange line in %s: \"%s\"", filename, str);
      acuDebugString(ACU_DEBUG_PROBLEM);
      break;
    }
  }
  // cleanup for the last char read from the file
  if (currentLetter != 0) {
    numPoints[currentLetter] = currentPoint;
    height[currentLetter] = bigHeight;
    if (width[currentLetter] == 0) {
      // support the old-school format, not for long
      width[currentLetter] = bigWidth * 1.5;
    }
  }
  fclose(fp);

  descent = 0;
  maxHeight = 0;
  for (i = 0; i < 256; i++) {
    for (int p = 0; p < numPoints[i]; p++) {
      if (y[i][p] < descent) descent = y[i][p];
      if (y[i][p] > maxHeight) maxHeight = y[i][p];
    }
  }
  if (leading == 0) {
    // default leading, if not defined in font
    leading = getHeight() * 1.2;
  }
  valid = TRUE;
}

int acVectorFont::getFormat() {
  return ACU_VECTOR_FONT;
}

void acVectorFont::drawChar(unsigned char c, float tx, float ty) {
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < numPoints[c]; i++) {
    if (kind[c][i] == MOVETO) {
      glEnd();
      glBegin(GL_LINE_STRIP);
    }
    //acuDebug(ACU_DEBUG_PROBLEM, "vecfont not finished yet!\n");
    glVertex2f(tx + x[c][i], ty + y[c][i]);
  }
  glEnd();
}

float acVectorFont::getDescent() {
  return descent;
}

float acVectorFont::getHeight() {
  return maxHeight + descent;
}

float acVectorFont::charWidth(unsigned char c) {
  if (c != ' ') {
    return width[c];
  } else { 
    return charWidth('n');
  }
}

float acVectorFont::charHeight(unsigned char c) {
  return height[c];
}

boolean acVectorFont::charExists(unsigned char c) {
  return (numPoints[c] != 0);
}


float acVectorFont::getDefaultLeading() { 
  return leading;
}
