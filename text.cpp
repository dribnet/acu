#include "acu.h"
#include "acFont.h"

boolean acuTextInited;
acFont **fontList;
int fontListMax;
int currentFont;


void acuTextInit() {
  //printf("text init called\n");
  fontListMax = 50;
  fontList = new acFont*[fontListMax];
  for (int i = 0; i < fontListMax; i++) {
    fontList[i] = NULL;
  }
  currentFont = ACU_ERROR;
  acuTextInited = TRUE;
}


// returns ACU_ERROR, -1 if problems
int acuLoadFont(char *filename) {
  if (!acuTextInited) acuTextInit();

  acFont *newbie = new acFont(filename);
  if (!newbie->isValid()) {
    return ACU_ERROR;
  }

  for (int i = 0; i < fontListMax; i++) {
    if (fontList[i] == NULL) {
      fontList[i] = newbie;
      //printf("setting font %d, %d to %s\n", newbie, i, filename);
      return i;
    }
  }
  delete newbie;
  sprintf(acuDebugStr, "Too many fonts, cannot open %s", filename);
  acuDebugString(ACU_DEBUG_PROBLEM);
  return ACU_ERROR;
}


void acuSetFont(int index) {
  if (fontList[index] != NULL) {
    currentFont = index;
  } else {
    sprintf(acuDebugStr, "Index %d is not a valid font.", index);
    acuDebugString(ACU_DEBUG_PROBLEM);
  }
}


void acuDrawChar(char c, GLfloat x, GLfloat y) {
  if (currentFont == ACU_ERROR) return;
  fontList[currentFont]->drawChar(c, x, y);
}

void acuDrawString(char *c, GLfloat x, GLfloat y) {
  if (currentFont == ACU_ERROR) return;
  glPushMatrix();
  int index = 0;
  while (c[index] != 0) {
    fontList[currentFont]->drawChar(c[index], x, y);
    x += fontList[currentFont]->charWidth(c[index]);
    //glTranslatef(fontList[currentFont]->charWidth(c[index]), 0, 0);
    index++;
  }
  glPopMatrix();
}


float acuGetCharMetric(acuEnum pname, char c) {
  if (currentFont == ACU_ERROR) {
    acuDebug(ACU_DEBUG_PROBLEM,
	     "Can't get char metrics when no font is set");
    return 0;
  }
  switch (pname) {
  case ACU_CHAR_WIDTH:
    return fontList[currentFont]->charWidth(c);
  default:
    break;
  }
  return 0;
}


void acuGetCharMetrics(acuEnum pname, char *c, GLfloat *metrics) {
  if (currentFont == ACU_ERROR) return;

  switch (pname) {
  case ACU_STRING_WIDTH:
    metrics[0] = fontList[currentFont]->stringWidth(c);
    break;

  default:
    sprintf(acuDebugStr, 
	    "acuGetCharMetrics: %d is not a valid param.", pname);
    acuDebugString(ACU_DEBUG_PROBLEM);
  }
}

