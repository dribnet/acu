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
  char currentLetter = 0;
  int currentPoint = 0;
  while (fgets(str, 64, fp)) {
    switch (str[0]) {
    case 'C':
      if (currentLetter != 0) {
	numPoints[currentLetter] = currentPoint;
	currentPoint = 0;
      }
      currentLetter = str[2];
      width[currentLetter] = 0;
      height[currentLetter] = 0;
      currentPoint = 0;
      break;

    case 'L':
      sscanf(str, "L %f %f\n", &nX, &nY);
      kind[currentLetter][currentPoint] = LINETO;
      x[currentLetter][currentPoint] = nX;
      y[currentLetter][currentPoint] = nY;
      if (nX > width[currentLetter])
	width[currentLetter] = nX;
      if (nY > height[currentLetter])
	height[currentLetter] = nY;
      currentPoint++;
      break;

    case 'M':
      sscanf(str, "M %f %f\n", &nX, &nY);
      kind[currentLetter][currentPoint] = MOVETO;
      x[currentLetter][currentPoint] = nX;
      y[currentLetter][currentPoint] = nY;
      if (nX > width[currentLetter])
	width[currentLetter] = nX;
      if (nY > height[currentLetter])
	height[currentLetter] = nY;
      currentPoint++;
    }
  }
  fclose(fp);

  for (int c = 0; c < 256; c++) {
    // design flaw in these vector fonts
    width[c] *= 1.5;
  }

  descent = 0;
  maxHeight = 0;
  for (i = 0; i < 256; i++) {
    for (int p = 0; p < numPoints[i]; p++) {
      if (y[i][p] < descent) descent = y[i][p];
      if (y[i][p] > maxHeight) maxHeight = y[i][p];
    }
  }
  valid = TRUE;
}


void acVectorFont::drawChar(char c, float tx, float ty) {
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

float acVectorFont::charWidth(char c) {
  if (c != ' ') {
    return width[c];
  } else { 
    return charWidth('n');
  }
}

float acVectorFont::charHeight(char c) {
  return height[c];
}

boolean acVectorFont::charExists(char c) {
  return (numPoints[c] != 0);
}
