#include "acu.h"


GLUtriangulatorObj *acuTesselator;


/**
 * Make sure that texWidth and texHeight are a power
 * of two. If not, things won't work. This function does
 * no error checking so as not to waste any time.
 *
 * components is 3 for RGB and 4 for RGBA
 * format is GL_RGB or GL_RGBA or whatever
 */
void acuTexRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2,
		 unsigned char *texImage, GLenum format, GLint components,
		 GLsizei texWidth, GLsizei texHeight,
		 GLfloat maxU, GLfloat maxV) {
  glEnable(GL_TEXTURE_2D);

  glTexImage2D(GL_TEXTURE_2D, 0, components, texWidth, texHeight,
	       0, format, GL_UNSIGNED_BYTE, texImage);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  glNormal3f(0, 0, 1);

  glBegin(GL_QUADS);  

  glTexCoord2f(0.0, 0.0);
  glVertex3f(x1, y1, 0.0);

  glTexCoord2f(0.0, maxV);
  glVertex3f(x1, y2, 0.0);

  glTexCoord2f(maxU, maxV);
  glVertex3f(x2, y2, 0.0);

  glTexCoord2f(maxU, 0.0);
  glVertex3f(x2, y1, 0.0);

  glEnd();

  glDisable(GL_TEXTURE_2D);
}


/**
 * Same as above, but works with a texture that has
 * been bound to a name, using glBindTexture. See the
 * GL docs on glBindTexture if that don't make sense.
 */
void acuNamedTexRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2,
		      GLint name, GLfloat maxU, GLfloat maxV) {
  glEnable(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, name);

  glNormal3f(0, 0, 1);

  glBegin(GL_QUADS);
  
  glTexCoord2f(0.0, 0.0);
  glVertex3f(x1, y1, 0.0);

  glTexCoord2f(0.0, maxV);
  glVertex3f(x1, y2, 0.0);

  glTexCoord2f(maxU, maxV);
  glVertex3f(x2, y2, 0.0);

  glTexCoord2f(maxU, 0.0);
  glVertex3f(x2, y1, 0.0);

  glEnd();
  
  glDisable(GL_TEXTURE_2D);
}


/**
 * Draw a tesselated polygon, concave or convex.
 * The array passed in takes the format:
 * { x1, y1, z1, x2, y2, z2, ... , xN-1, yN-1, zN-1 }
 */
void acuPolygon(int count, GLfloat *vertices) {
  GLdouble *p, *pts;
  int i;

  if (acuTesselator == NULL) {
    acuPolygonOpen();
    // if it fails, then the program dies (ha ha ha, sorry)
  }

  gluBeginPolygon(acuTesselator);

  //GLdouble *pts = new GLdouble[count*3];
  pts = (GLdouble*) malloc(sizeof(GLdouble) * count*3);
  for (i = 0; i < count*3; i++) {
    pts[i] = (double)vertices[i];
  }

  for (i = 0; i < count; i++) {
    //GLdouble *p = &pts[i*3];
    p = &pts[i*3];
    gluTessVertex(acuTesselator, p, p); 
  }
  gluEndPolygon(acuTesselator);  
  //delete pts;
  free(pts);
}


static void polygonBegin(GLenum type) {
  glBegin(type);
}

static void polygonVertex(void* data) {
  GLdouble* pts = (GLdouble*) data;
  glVertex3dv(pts);
}

static void polygonEdgeFlag(GLboolean flag) {
  glEdgeFlag(flag);
}

static void polygonEnd(void) {
  glEnd();
}

static void polygonError(GLenum code) {
  const GLubyte* error = gluErrorString(code);
  // should pass error as a char* using sprintf, but too lazy
  acuDebug(ACU_DEBUG_PROBLEM, "Error while tesselating.");
}

/**
 * Called only once, creates the tesselator object that
 * will be used for triangulating all them triangles.
 */
void acuPolygonOpen() {
  //GLUtriangulatorObj *tesselator;
  if (acuTesselator != NULL) {
    acuDebug(ACU_DEBUG_PROBLEM, 
	     "No need to call acuPolygonOpen more than once.");
  }

  acuTesselator = gluNewTess();
  if (acuTesselator == NULL) {
    acuDebug(ACU_DEBUG_EMERGENCY,
	     "Could not create tesselator object.");
  }

  gluTessCallback(acuTesselator, (GLenum)GLU_BEGIN,    
		  (void (*)())polygonBegin);

  gluTessCallback(acuTesselator, (GLenum)GLU_END,      
		  (void (*)())polygonEnd);

  gluTessCallback(acuTesselator, (GLenum)GLU_EDGE_FLAG,
		  (void (*)())polygonEdgeFlag);

  gluTessCallback(acuTesselator, (GLenum)GLU_ERROR,    
		  (void (*)())polygonError);

  gluTessCallback(acuTesselator, (GLenum)GLU_VERTEX,   
		  (void (*)())polygonVertex); 
}

/**
 * Deallocates the tesselator at the end of a program
 */
void acuPolygonClose() {
  gluDeleteTess(acuTesselator);
}


void acuLine2f(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
  glBegin(GL_LINES);
  glVertex3f(x1, y1, 0);
  glVertex3f(x2, y2, 0);
  glEnd();
}


void acuLine2fv(int count, GLfloat *x, GLfloat *y) {
  int i;
  glBegin(GL_LINE_STRIP);
  for (i = 0; i < count; i++) {
    glVertex3f(x[i], y[i], 0);
  }
  glEnd();
}


void acuLine3f(float x1, float y1, float z1, float x2, float y2, float z2) {
  glBegin(GL_LINES);
  //glNormal3f(1.0, 1.0, 1.0);
  glVertex3f(x1, y1, z1);
  glVertex3f(x2, y2, z2);
  glEnd();
}


void acuLine3fv(int count, GLfloat *x, GLfloat *y, GLfloat *z) {
  int i;
  glBegin(GL_LINE_STRIP);
  for (i = 0; i < count; i++) {
    glVertex3f(x[i], y[i], z[i]);
  }
  glEnd();
}
