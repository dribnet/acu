#include "acFreeTypeFont.h"


acFreeTypeFont::acFreeTypeFont(const char *name) {
  valid = FALSE;

  char filename[256];
  strcpy(filename, name);
  char *p = strchr(name, ' ');
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
  printf("initialized font\n");
}


float acFreeTypeFont::getDescent() {
  if (acuFontNormalize)
    return (float)font->getDescender() / (float)fontSize;

  return font->getDescender();
}


float acFreeTypeFont::getHeight() {
  if (acuFontNormalize)
    return (float)font->getHeight() / (float)fontSize;

  return font->getHeight();
}


float acFreeTypeFont::charWidth(char c) {
  char temp[2];
  temp[0] = c;
  temp[1] = 0;
  
  return stringWidth(temp);
}


float acFreeTypeFont::stringWidth(char *s) {
  if (acuFontNormalize)
    return font->getWidth(s) / (float)fontSize;

  return font->getWidth(s);
}


float acFreeTypeFont::charHeight(char c) {
  return getHeight();
}


boolean acFreeTypeFont::charExists(char c) {
  return TRUE;
  //return ((c > 32) && (c-33 < numChars));
}


void acFreeTypeFont::drawChar(char c, float x, float y) {
  char temp[2];
  temp[0] = c;
  temp[1] = 0;
  drawString(temp, x, y);
}


void acFreeTypeFont::drawString(char *s, float x, float y) {
  if (acuFontNormalize) {
    // for compatability with sizes from other fonts
    glPushMatrix();
    float normalized = 1.0f / (float)fontSize;
    glScalef(normalized, normalized, normalized);
    font->output(x, y, s);
    glPopMatrix();
  } else {
    font->output(x, y, s);
  }
}

