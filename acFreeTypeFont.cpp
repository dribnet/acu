#include "acFreeTypeFont.h"


TT_Engine *acFreeTypeFont::engine = NULL;

void acFreeTypeFont::initEngine() {
  //if (engine != NULL) return;
  engine = new TT_Engine;
  if (TT_Init_FreeType(engine)) {
    delete engine;
    engine = NULL;
    acuDebug(ACU_DEBUG_PROBLEM, "Could not initialize FreeType");
  }
}

TT_Face face;
TT_Instance instance;
TT_Glyph *glyphs;

acFreeTypeFont::acFreeTypeFont(const char *filename, int size) {
  valid = FALSE;

  if (engine == NULL) {
    initEngine();
    if (engine == NULL)
      return;
  }

  if (TT_Open_Face(engine, filename, &face))
    return;

  if (TT_New_Instance(face, &instance)) {
    (void) TT_Close_Face(face);
    return;
  }

  (void) TT_Set_Instance_Resolutions(instance, 96, 96);
  (void) TT_Set_Instance_PointSize(instance, size);
  (void) TT_Get_Instance_Metrics(instance, &imetrics); 
  (void) TT_Get_Face_Properties(instance, &properties);

  if (TT_New_Glyph(face, &glyph)) {
    (void) TT_Done_Instance(instance);
    (void) TT_Close_Face(face);
  }

  TT_CharMap charmap;
  boolean cmap = FALSE;
  int cmapCount = TT_Get_CharMap_Count(face);
  for (int i = 0; i < cmapCount; ++i) {
    short unsigned platform = 0;
    short unsigned encoding = 0;
    TT_Get_CharMap_ID(face, i, &platform, &encoding);
    if ((platform == 3 && encoding == 1) ||
        (platform == 0 && encoding == 0)) {
      TT_Get_CharMap(face, i, &charmap);
      break;
    }
  }
  
  if (i == cmapCount) {
    TT_Face_Properties properties;
    TT_Get_Face_Properties(face, &properties);
    int num_glyphs= properties.num_Glyphs;
    
    for (int ascii_code= 0; ascii_code < 256; ++ascii_code) {
      int glyph_index = TT_Char_Index(char_map, CP_Translate(ascii_code));
      if (glyph_index < 0 || glyph_index >= num_glyphs)
        glyph_index = 0;
      indices[ascii_code] = glyph_index;
    }
  } else {
    for (int ascii_code = 0; ascii_code < 256; ++ascii_code) {
      int glyph_index = TT_Char_Index(charmap, ascii_code);
      if (glyph_index < 0)
        glyph_index = 0;  // FIXME! default code
      indices[ascii_code] = glyph_index;
      cmap = TRUE;
    }
  }

  int glyphCount = 0;
  for (int i = 0; i < 0xffff; i++) {
    int index;
    if (cmap) {
      index = TT_Char_Index(cmap, i);
    } else {
      if (code >= properties.num_Glyphs)
	break;
      index = i;
    }
    if (index <= 0) continue;

    if (TT_Load_Glyph(instance, glyph, index, TTLOAD_DEFAULT))
      continue;
    
    (void) TT_Get_Glyph_Metrics(glyph, &metrics);
    TT_BBox& bbox = metrics.bbox;

    advance[glyphCount] = metrics.advance;
    deltaX[glyphCount] = bbox.xMin;
    deltaY[glyphCount] = bbox.yMin;
    
#define FLOOR(x)   ((x) & -64)
#define CEILING(x) (((x)+63) & -64)
    bbox.xMin= FLOOR(bbox.xMin);
    bbox.yMin= FLOOR(bbox.yMin);
    bbox.xMax= CEILING(bbox.xMax);
    bbox.yMax= CEILING(bbox.yMax);
#undef CEILING
#undef FLOOR

    wide = (bbox.xMax - bbox.xMin)/64;
    high = (bbox.yMax - bbox.yMin)/64;
    cols = (width+7) / 8;
    int length = cols * high;
    unsigned char *buffer = new unsigned char[length];
    memset((void*)buffer, 0, length);
    
    TT_Raster_Map bitmap;
    bitmap.width = wide;
    bitmap.cols = cols;
    bitmap.rows = high;
    bitmap.flow = TT_Flow_Up;
    bitmap.size = length;
    bitmap.bitmap = (void*)buffer;
    
    // bbox.xMin and yMin are xoffset and yoffset
    if (TT_Get_Glyph_Bitmap(glyph, &bitmap,
                            -bbox.xMin, -bbox.yMin)) {
      delete buffer;
      continue;
    }
    
    // set twidth and theight here
    tsize = (int) pow(2, ceil(log(MAX(wide, high)) / log(2)));
    tdata[glyphIndex] = new unsigned char[tsize*tsize*4];
    for (int y = 0; y < high; y++) {
      for (int x = 0; x < wide; x++) {
	int offset = (y*tsize + x) * 4;
	tdata[glyphCount][offset + 0] = 255;
	tdata[glyphCount][offset + 1] = 255;
	tdata[glyphCount][offset + 2] = 255;
	tdata[glyphCount][offset + 3] = buffer[y*wide + x];
      }
    }
    
    width[glyphCount] = (float)wide / (float)tsize;
    height[glyphCount] = (float)high / (float)tsize;

    glyphCount++;
  }

  tnames = new GLuint[glyphCount];
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glGenTextures(glyphCount, tnames);
    
  for (int i = 0; i < glyphCount; i++) {
    glBindTexture(GL_TEXTURE_2D, tnames[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tsize, tsize, 0,
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

float acFreeTypeFont::charBitmapWidth(char c) {
  // width of the bitmap itself
  return (float)width[c-33] / 64.0f;
}

float acFreeTypeFont::charBitmapHeight(char c) {
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
  return (c-33 < numChars);
}

void acFreeTypeFont::drawChar(char c, float x, float y) {
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


