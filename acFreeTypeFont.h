#ifndef _AC_FREETYPE_FONT_H_
#define _AC_FREETYPE_FONT_H_

#include "acu.h"
#include "acFont.h"

// haven't sorted through which of these are needed
#include "FTEngine.h"
#include "FTFace.h"
#include "FTInstance.h"
#include "FTGlyph.h"
#include "FTGlyphBitmap.h"
#include "FTGlyphPixmap.h"
#include "FTBitmapFont.h"
#include "GLTTBitmapFont.h"
#include "GLTTPixmapFont.h"
#include "GLTTOutlineFont.h"
#include "GLTTFont.h"
#include "GLTTGlyphPolygonizer.h"
#include "GLTTGlyphTriangulator.h"


class acFreeTypeFont : public acFont {
public:
  acFreeTypeFont(const char* filename);

  float getDescent();
  float getHeight();
  float charWidth(char c);
  float charHeight(char c);
  boolean charExists(char c);
  float stringWidth(char *s);
  void drawChar(char c, float x, float y);
  void drawString(char *s, float x, float y);
  //float getDefaultLeading();

protected:
  FTFace *face;
  GLTTPixmapFont *font;
  int fontSize;
};

#endif





