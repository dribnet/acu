#include "acu.h"
#include "acFont.h"
#include "acBitmapFont.h"
//#include "acFreeTypeFont.h"
#include "acVectorFont.h"

#define ACU_FONT_LIST_MAX 50

boolean acuTextInited = FALSE;
boolean acuFontNormalize = TRUE;

acFont* acutFontList[ACU_FONT_LIST_MAX];
char acutFontNames[ACU_FONT_LIST_MAX][128];
int acutCurrentFont;


void acuTextInit() {
  //printf("text init called\n");
  //acutFontList = new acFont*[ACU_FONT_LIST_MAX];
  for (int i = 0; i < ACU_FONT_LIST_MAX; i++) {
    acutFontList[i] = NULL;
    acutFontNames[i][0] = 0; // empty string
  }
  acutCurrentFont = ACU_ERROR;
  acuTextInited = TRUE;
}


void acuUnloadFont(int which) {
  if (acutCurrentFont == which) {
    acuDebug(ACU_DEBUG_PROBLEM, "you cannot unload the current font");
    return;
  }
  acutFontList[which] = NULL;
  acutFontNames[which][0] = 0;
}


int acuFindFont(char *filename) {
  for (int i = 0; i < ACU_FONT_LIST_MAX; i++) {
    if (strcmp(acutFontNames[i], filename) == 0)
      return i;
  }
  return ACU_ERROR;
}


// returns ACU_ERROR, -1 if problems
int acuLoadFont(char *filename) {
  if (!acuTextInited) acuTextInit();

  int which = acuFindFont(filename);
  if (which != ACU_ERROR) return which;

  // construct it depending on what type of font it is
  acFont *newbie = NULL;
  if (strstr(filename, ".jvf") || strstr(filename, ".JVF")) {
    newbie = new acVectorFont(filename);
  } else if (strstr(filename, ".ttf") || strstr(filename, ".TTF")) {
    //newbie = new acFreeTypeFont(filename);
  } else {
    newbie = new acBitmapFont(filename);
  }

  if ((newbie == NULL) || (!newbie->isValid())) {
    return ACU_ERROR;
  }

  for (int i = 0; i < ACU_FONT_LIST_MAX; i++) {
    if (acutFontList[i] == NULL) {
      acutFontList[i] = newbie;
      //printf("setting font %d, %d to %s\n", newbie, i, filename);
      strcpy(acutFontNames[i], filename);
      return i;
    }
  }
  delete newbie;
  sprintf(acuDebugStr, "Too many fonts, cannot open %s", filename);
  acuDebugString(ACU_DEBUG_PROBLEM);
  return ACU_ERROR;
}


void acuSetFont(int index) {
  if (acutFontList[index] != NULL) {
    acutCurrentFont = index;
  } else {
    sprintf(acuDebugStr, "Index %d is not a valid font.", index);
    acuDebugString(ACU_DEBUG_PROBLEM);
  }
}


void* acuGetFont(int index) {
  return acutFontList[index];
}


void acuDrawChar(char c, GLfloat x, GLfloat y) {
  if (acutCurrentFont == ACU_ERROR) return;
  acutFontList[acutCurrentFont]->drawChar(c, x, y);
}


void acuDrawString(char *c, GLfloat x, GLfloat y) {
  if (acutCurrentFont == ACU_ERROR) return;
  acutFontList[acutCurrentFont]->drawString(c, x, y);
}


float acuGetCharMetric(acuEnum pname, char c) {
  if (acutCurrentFont == ACU_ERROR) {
    acuDebug(ACU_DEBUG_PROBLEM,
	     "Can't get char metrics when no font is set");
    return 0;
  }
  switch (pname) {
  case ACU_CHAR_WIDTH:
    return acutFontList[acutCurrentFont]->charWidth(c);
  default:
    break;
  }
  return 0;
}


void acuGetCharMetrics(acuEnum pname, char *c, GLfloat *metrics) {
  if (acutCurrentFont == ACU_ERROR) return;

  switch (pname) {
  case ACU_STRING_WIDTH:
    metrics[0] = acutFontList[acutCurrentFont]->stringWidth(c);
    break;

  default:
    sprintf(acuDebugStr, 
	    "acuGetCharMetrics: %d is not a valid param.", pname);
    acuDebugString(ACU_DEBUG_PROBLEM);
    break;
  }
}
