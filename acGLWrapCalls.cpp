
#include "acGLWrapper.h"
	
extern unsigned char* buffer = NULL;
extern long bufferSize = 0;
extern long bufferAllocSize = 0;

/*-------------------- write data ----------------------------*/

void tryExpand( int size )
{
  while ( bufferAllocSize <= bufferSize+size )
    {
      if ( bufferAllocSize==0 )
	bufferAllocSize = 32;
      bufferAllocSize *= 2;
      buffer = (unsigned char*)realloc( buffer, sizeof(char)*bufferAllocSize );
    }
}

void writeValue( void* V, int size )
{
  tryExpand( size );
  memcpy( (void*)(&buffer[bufferSize]), V, size );
  bufferSize += size;
}

void writeGlCommand( glCommand C )
{
  writeValue( &C, sizeof(C) );
}

/*------------------------- the wrappers -------------------*/


void glAccum ( GLenum a, GLfloat b )
{
	writeGlCommand( ACW_ACCUM );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLfloat) );
}

void glAlphaFunc ( GLenum a, GLclampf b )
{
	writeGlCommand( ACW_ALPHAFUNC );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLclampf) );
}

void glBegin ( GLenum a )
{
	writeGlCommand( ACW_BEGIN );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glBlendColor ( GLclampf a, GLclampf b, GLclampf c, GLclampf d )
{
	writeGlCommand( ACW_BLENDCOLOR );
	writeValue( (void*)&a, sizeof(GLclampf) );
	writeValue( (void*)&b, sizeof(GLclampf) );
	writeValue( (void*)&c, sizeof(GLclampf) );
	writeValue( (void*)&d, sizeof(GLclampf) );
}

void glBlendEquation ( GLenum a )
{
	writeGlCommand( ACW_BLENDEQUATION );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glBlendEquationEXT ( GLenum a )
{
	writeGlCommand( ACW_BLENDEQUATIONEXT );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glBlendFunc ( GLenum a, GLenum b )
{
	writeGlCommand( ACW_BLENDFUNC );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
}

void glCallList ( GLuint a )
{
	writeGlCommand( ACW_CALLLIST );
	writeValue( (void*)&a, sizeof(GLuint) );
}

void glClear ( GLbitfield a )
{
	writeGlCommand( ACW_CLEAR );
	writeValue( (void*)&a, sizeof(GLbitfield) );
}

void glClearAccum ( GLfloat a, GLfloat b, GLfloat c, GLfloat d )
{
	writeGlCommand( ACW_CLEARACCUM );
	writeValue( (void*)&a, sizeof(GLfloat) );
	writeValue( (void*)&b, sizeof(GLfloat) );
	writeValue( (void*)&c, sizeof(GLfloat) );
	writeValue( (void*)&d, sizeof(GLfloat) );
}

void glClearColor ( GLclampf a, GLclampf b, GLclampf c, GLclampf d )
{
	writeGlCommand( ACW_CLEARCOLOR );
	writeValue( (void*)&a, sizeof(GLclampf) );
	writeValue( (void*)&b, sizeof(GLclampf) );
	writeValue( (void*)&c, sizeof(GLclampf) );
	writeValue( (void*)&d, sizeof(GLclampf) );
}

void glClearDepth ( GLclampd a )
{
	writeGlCommand( ACW_CLEARDEPTH );
	writeValue( (void*)&a, sizeof(GLclampd) );
}

void glClearIndex ( GLfloat a )
{
	writeGlCommand( ACW_CLEARINDEX );
	writeValue( (void*)&a, sizeof(GLfloat) );
}

void glClearStencil ( GLint a )
{
	writeGlCommand( ACW_CLEARSTENCIL );
	writeValue( (void*)&a, sizeof(GLint) );
}

void glColor3b ( GLbyte a, GLbyte b, GLbyte c )
{
	writeGlCommand( ACW_COLOR3B );
	GLbyte V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glColor3bv ( GLbyte* a )
{
	writeGlCommand( ACW_COLOR3BV );
	writeValue( (void*)a, sizeof(GLbyte)*3 );
}

void glColor3d ( GLdouble a, GLdouble b, GLdouble c )
{
	writeGlCommand( ACW_COLOR3D );
	GLdouble V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glColor3dv ( GLdouble* a )
{
	writeGlCommand( ACW_COLOR3DV );
	writeValue( (void*)a, sizeof(GLdouble)*3 );
}

void glColor3f ( GLfloat a, GLfloat b, GLfloat c )
{
	writeGlCommand( ACW_COLOR3F );
	GLfloat V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glColor3fv ( GLfloat* a )
{
	writeGlCommand( ACW_COLOR3FV );
	writeValue( (void*)a, sizeof(GLfloat)*3 );
}

void glColor3i ( GLint a, GLint b, GLint c )
{
	writeGlCommand( ACW_COLOR3I );
	GLint V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glColor3iv ( GLint* a )
{
	writeGlCommand( ACW_COLOR3IV );
	writeValue( (void*)a, sizeof(GLint)*3 );
}

void glColor3s ( GLshort a, GLshort b, GLshort c )
{
	writeGlCommand( ACW_COLOR3S );
	GLshort V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glColor3sv ( GLshort* a )
{
	writeGlCommand( ACW_COLOR3SV );
	writeValue( (void*)a, sizeof(GLshort)*3 );
}

void glColor3ub ( GLubyte a, GLubyte b, GLubyte c )
{
	writeGlCommand( ACW_COLOR3UB );
	writeValue( (void*)&a, sizeof(GLubyte) );
	writeValue( (void*)&b, sizeof(GLubyte) );
	writeValue( (void*)&c, sizeof(GLubyte) );
}

void glColor3ubv ( GLubyte* a )
{
	writeGlCommand( ACW_COLOR3UBV );
	writeValue( (void*)&a, sizeof(GLubyte*) );
}

void glColor3ui ( GLuint a, GLuint b, GLuint c )
{
	writeGlCommand( ACW_COLOR3UI );
	writeValue( (void*)&a, sizeof(GLuint) );
	writeValue( (void*)&b, sizeof(GLuint) );
	writeValue( (void*)&c, sizeof(GLuint) );
}

void glColor3uiv ( GLuint* a )
{
	writeGlCommand( ACW_COLOR3UIV );
	writeValue( (void*)&a, sizeof(GLuint*) );
}

void glColor3us ( GLushort a, GLushort b, GLushort c )
{
	writeGlCommand( ACW_COLOR3US );
	writeValue( (void*)&a, sizeof(GLushort) );
	writeValue( (void*)&b, sizeof(GLushort) );
	writeValue( (void*)&c, sizeof(GLushort) );
}

void glColor3usv ( GLushort* a )
{
	writeGlCommand( ACW_COLOR3USV );
	writeValue( (void*)&a, sizeof(GLushort*) );
}

void glColor4b ( GLbyte a, GLbyte b, GLbyte c, GLbyte d )
{
	writeGlCommand( ACW_COLOR4B );
	GLbyte V[4];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	V[3] = d;
	writeValue( (void*)V, sizeof(V) );
}

void glColor4bv ( GLbyte* a )
{
	writeGlCommand( ACW_COLOR4BV );
	writeValue( (void*)a, sizeof(GLbyte)*4 );
}

void glColor4d ( GLdouble a, GLdouble b, GLdouble c, GLdouble d )
{
	writeGlCommand( ACW_COLOR4D );
	GLdouble V[4];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	V[3] = d;
	writeValue( (void*)V, sizeof(V) );
}

void glColor4dv ( GLdouble* a )
{
	writeGlCommand( ACW_COLOR4DV );
	writeValue( (void*)a, sizeof(GLdouble)*4 );
}

void glColor4f ( GLfloat a, GLfloat b, GLfloat c, GLfloat d )
{
	writeGlCommand( ACW_COLOR4F );
	GLfloat V[4];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	V[3] = d;
	writeValue( (void*)V, sizeof(V) );
}

void glColor4fv ( GLfloat* a )
{
	writeGlCommand( ACW_COLOR4FV );
	writeValue( (void*)a, sizeof(GLfloat)*4 );
}

void glColor4i ( GLint a, GLint b, GLint c, GLint d )
{
	writeGlCommand( ACW_COLOR4I );
	GLint V[4];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	V[3] = d;
	writeValue( (void*)V, sizeof(V) );
}

void glColor4iv ( GLint* a )
{
	writeGlCommand( ACW_COLOR4IV );
	writeValue( (void*)a, sizeof(GLint)*4 );
}

void glColor4s ( GLshort a, GLshort b, GLshort c, GLshort d )
{
	writeGlCommand( ACW_COLOR4S );
	GLshort V[4];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	V[3] = d;
	writeValue( (void*)V, sizeof(V) );
}

void glColor4sv ( GLshort* a )
{
	writeGlCommand( ACW_COLOR4SV );
	writeValue( (void*)a, sizeof(GLshort)*4 );
}

void glColor4ub ( GLubyte a, GLubyte b, GLubyte c, GLubyte d )
{
	writeGlCommand( ACW_COLOR4UB );
	writeValue( (void*)&a, sizeof(GLubyte) );
	writeValue( (void*)&b, sizeof(GLubyte) );
	writeValue( (void*)&c, sizeof(GLubyte) );
	writeValue( (void*)&d, sizeof(GLubyte) );
}

void glColor4ubv ( GLubyte* a )
{
	writeGlCommand( ACW_COLOR4UBV );
	writeValue( (void*)&a, sizeof(GLubyte*) );
}

void glColor4ui ( GLuint a, GLuint b, GLuint c, GLuint d )
{
	writeGlCommand( ACW_COLOR4UI );
	writeValue( (void*)&a, sizeof(GLuint) );
	writeValue( (void*)&b, sizeof(GLuint) );
	writeValue( (void*)&c, sizeof(GLuint) );
	writeValue( (void*)&d, sizeof(GLuint) );
}

void glColor4uiv ( GLuint* a )
{
	writeGlCommand( ACW_COLOR4UIV );
	writeValue( (void*)&a, sizeof(GLuint*) );
}

void glColor4us ( GLushort a, GLushort b, GLushort c, GLushort d )
{
	writeGlCommand( ACW_COLOR4US );
	writeValue( (void*)&a, sizeof(GLushort) );
	writeValue( (void*)&b, sizeof(GLushort) );
	writeValue( (void*)&c, sizeof(GLushort) );
	writeValue( (void*)&d, sizeof(GLushort) );
}

void glColor4usv ( GLushort* a )
{
	writeGlCommand( ACW_COLOR4USV );
	writeValue( (void*)&a, sizeof(GLushort*) );
}

void glColorMask ( GLboolean a, GLboolean b, GLboolean c, GLboolean d )
{
	writeGlCommand( ACW_COLORMASK );
	writeValue( (void*)&a, sizeof(GLboolean) );
	writeValue( (void*)&b, sizeof(GLboolean) );
	writeValue( (void*)&c, sizeof(GLboolean) );
	writeValue( (void*)&d, sizeof(GLboolean) );
}

void glColorMaterial ( GLenum a, GLenum b )
{
	writeGlCommand( ACW_COLORMATERIAL );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
}

void glCopyPixels ( GLint a, GLint b, GLsizei c, GLsizei d, GLenum e )
{
	writeGlCommand( ACW_COPYPIXELS );
	writeValue( (void*)&a, sizeof(GLint) );
	writeValue( (void*)&b, sizeof(GLint) );
	writeValue( (void*)&c, sizeof(GLsizei) );
	writeValue( (void*)&d, sizeof(GLsizei) );
	writeValue( (void*)&e, sizeof(GLenum) );
}

void glCullFace ( GLenum a )
{
	writeGlCommand( ACW_CULLFACE );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glDeformSGIX ( GLbitfield a )
{
	writeGlCommand( ACW_DEFORMSGIX );
	writeValue( (void*)&a, sizeof(GLbitfield) );
}

void glDeleteLists ( GLuint a, GLsizei b )
{
	writeGlCommand( ACW_DELETELISTS );
	writeValue( (void*)&a, sizeof(GLuint) );
	writeValue( (void*)&b, sizeof(GLsizei) );
}

void glDepthFunc ( GLenum a )
{
	writeGlCommand( ACW_DEPTHFUNC );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glDepthMask ( GLboolean a )
{
	writeGlCommand( ACW_DEPTHMASK );
	writeValue( (void*)&a, sizeof(GLboolean) );
}

void glDepthRange ( GLclampd a, GLclampd b )
{
	writeGlCommand( ACW_DEPTHRANGE );
	writeValue( (void*)&a, sizeof(GLclampd) );
	writeValue( (void*)&b, sizeof(GLclampd) );
}

void glDisable ( GLenum a )
{
	writeGlCommand( ACW_DISABLE );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glDisableClientState ( GLenum a )
{
	writeGlCommand( ACW_DISABLECLIENTSTATE );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glDrawArrays ( GLenum a, GLint b, GLsizei c )
{
	writeGlCommand( ACW_DRAWARRAYS );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLint) );
	writeValue( (void*)&c, sizeof(GLsizei) );
}

void glDrawArraysEXT ( GLenum a, GLint b, GLsizei c )
{
	writeGlCommand( ACW_DRAWARRAYSEXT );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLint) );
	writeValue( (void*)&c, sizeof(GLsizei) );
}

void glDrawBuffer ( GLenum a )
{
	writeGlCommand( ACW_DRAWBUFFER );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glEdgeFlag ( GLboolean a )
{
	writeGlCommand( ACW_EDGEFLAG );
	writeValue( (void*)&a, sizeof(GLboolean) );
}

void glEnable ( GLenum a )
{
	writeGlCommand( ACW_ENABLE );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glEnableClientState ( GLenum a )
{
	writeGlCommand( ACW_ENABLECLIENTSTATE );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glEnd (  )
{
	writeGlCommand( ACW_END );
}

void glEndList (  )
{
	writeGlCommand( ACW_ENDLIST );
}

void glEvalCoord1d ( GLdouble a )
{
	writeGlCommand( ACW_EVALCOORD1D );
	GLdouble V[1];
	V[0] = a;
	writeValue( (void*)V, sizeof(V) );
}

void glEvalCoord1dv ( GLdouble* a )
{
	writeGlCommand( ACW_EVALCOORD1DV );
	writeValue( (void*)a, sizeof(GLdouble)*1 );
}

void glEvalCoord1f ( GLfloat a )
{
	writeGlCommand( ACW_EVALCOORD1F );
	GLfloat V[1];
	V[0] = a;
	writeValue( (void*)V, sizeof(V) );
}

void glEvalCoord1fv ( GLfloat* a )
{
	writeGlCommand( ACW_EVALCOORD1FV );
	writeValue( (void*)a, sizeof(GLfloat)*1 );
}

void glEvalCoord2d ( GLdouble a, GLdouble b )
{
	writeGlCommand( ACW_EVALCOORD2D );
	GLdouble V[2];
	V[0] = a;
	V[1] = b;
	writeValue( (void*)V, sizeof(V) );
}

void glEvalCoord2dv ( GLdouble* a )
{
	writeGlCommand( ACW_EVALCOORD2DV );
	writeValue( (void*)a, sizeof(GLdouble)*2 );
}

void glEvalCoord2f ( GLfloat a, GLfloat b )
{
	writeGlCommand( ACW_EVALCOORD2F );
	GLfloat V[2];
	V[0] = a;
	V[1] = b;
	writeValue( (void*)V, sizeof(V) );
}

void glEvalCoord2fv ( GLfloat* a )
{
	writeGlCommand( ACW_EVALCOORD2FV );
	writeValue( (void*)a, sizeof(GLfloat)*2 );
}

void glEvalMesh1 ( GLenum a, GLint b, GLint c )
{
	writeGlCommand( ACW_EVALMESH1 );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLint) );
	writeValue( (void*)&c, sizeof(GLint) );
}

void glEvalMesh2 ( GLenum a, GLint b, GLint c, GLint d, GLint e )
{
	writeGlCommand( ACW_EVALMESH2 );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLint) );
	writeValue( (void*)&c, sizeof(GLint) );
	writeValue( (void*)&d, sizeof(GLint) );
	writeValue( (void*)&e, sizeof(GLint) );
}

void glEvalPoint1 ( GLint a )
{
	writeGlCommand( ACW_EVALPOINT1 );
	writeValue( (void*)&a, sizeof(GLint) );
}

void glEvalPoint2 ( GLint a, GLint b )
{
	writeGlCommand( ACW_EVALPOINT2 );
	writeValue( (void*)&a, sizeof(GLint) );
	writeValue( (void*)&b, sizeof(GLint) );
}

void glFlush (  )
{
	writeGlCommand( ACW_FLUSH );
}

void glFlushRasterSGIX (  )
{
	writeGlCommand( ACW_FLUSHRASTERSGIX );
}

void glFogf ( GLenum a, GLfloat b )
{
	writeGlCommand( ACW_FOGF );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLfloat) );
}

void glFogi ( GLenum a, GLint b )
{
	writeGlCommand( ACW_FOGI );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLint) );
}

void glFrameZoomSGIX ( GLint a )
{
	writeGlCommand( ACW_FRAMEZOOMSGIX );
	writeValue( (void*)&a, sizeof(GLint) );
}

void glFrontFace ( GLenum a )
{
	writeGlCommand( ACW_FRONTFACE );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glFrustum ( GLdouble a, GLdouble b, GLdouble c, GLdouble d, GLdouble e, GLdouble f )
{
	writeGlCommand( ACW_FRUSTUM );
	writeValue( (void*)&a, sizeof(GLdouble) );
	writeValue( (void*)&b, sizeof(GLdouble) );
	writeValue( (void*)&c, sizeof(GLdouble) );
	writeValue( (void*)&d, sizeof(GLdouble) );
	writeValue( (void*)&e, sizeof(GLdouble) );
	writeValue( (void*)&f, sizeof(GLdouble) );
}

GLuint glGenLists ( GLsizei a )
{
	writeGlCommand( ACW_GENLISTS );
	writeValue( (void*)&a, sizeof(GLsizei) );
}

void glGenTextures ( GLsizei a, GLuint* b )
{
	writeGlCommand( ACW_GENTEXTURES );
	writeValue( (void*)&a, sizeof(GLsizei) );
	writeValue( (void*)&b, sizeof(GLuint*) );
}

GLenum glGetError (  )
{
	writeGlCommand( ACW_GETERROR );
}

void glHint ( GLenum a, GLenum b )
{
	writeGlCommand( ACW_HINT );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
}

void glHistogram ( GLenum a, GLsizei b, GLenum c, GLboolean d )
{
	writeGlCommand( ACW_HISTOGRAM );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLsizei) );
	writeValue( (void*)&c, sizeof(GLenum) );
	writeValue( (void*)&d, sizeof(GLboolean) );
}

void glHistogramEXT ( GLenum a, GLsizei b, GLenum c, GLboolean d )
{
	writeGlCommand( ACW_HISTOGRAMEXT );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLsizei) );
	writeValue( (void*)&c, sizeof(GLenum) );
	writeValue( (void*)&d, sizeof(GLboolean) );
}

void glIndexMask ( GLuint a )
{
	writeGlCommand( ACW_INDEXMASK );
	writeValue( (void*)&a, sizeof(GLuint) );
}

void glIndexd ( GLdouble a )
{
	writeGlCommand( ACW_INDEXD );
	writeValue( (void*)&a, sizeof(GLdouble) );
}

void glIndexf ( GLfloat a )
{
	writeGlCommand( ACW_INDEXF );
	writeValue( (void*)&a, sizeof(GLfloat) );
}

void glIndexi ( GLint a )
{
	writeGlCommand( ACW_INDEXI );
	writeValue( (void*)&a, sizeof(GLint) );
}

void glInitNames (  )
{
	writeGlCommand( ACW_INITNAMES );
}

GLboolean glIsEnabled ( GLenum a )
{
	writeGlCommand( ACW_ISENABLED );
	writeValue( (void*)&a, sizeof(GLenum) );
}

GLboolean glIsList ( GLuint a )
{
	writeGlCommand( ACW_ISLIST );
	writeValue( (void*)&a, sizeof(GLuint) );
}

GLboolean glIsTexture ( GLuint a )
{
	writeGlCommand( ACW_ISTEXTURE );
	writeValue( (void*)&a, sizeof(GLuint) );
}

GLboolean glIsTextureEXT ( GLuint a )
{
	writeGlCommand( ACW_ISTEXTUREEXT );
	writeValue( (void*)&a, sizeof(GLuint) );
}

void glLightModelf ( GLenum a, GLfloat b )
{
	writeGlCommand( ACW_LIGHTMODELF );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLfloat) );
}

void glLightModeli ( GLenum a, GLint b )
{
	writeGlCommand( ACW_LIGHTMODELI );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLint) );
}

void glLightf ( GLenum a, GLenum b, GLfloat c )
{
	writeGlCommand( ACW_LIGHTF );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLfloat) );
}

void glLighti ( GLenum a, GLenum b, GLint c )
{
	writeGlCommand( ACW_LIGHTI );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLint) );
}

void glLineStipple ( GLint a, GLushort b )
{
	writeGlCommand( ACW_LINESTIPPLE );
	writeValue( (void*)&a, sizeof(GLint) );
	writeValue( (void*)&b, sizeof(GLushort) );
}

void glLineWidth ( GLfloat a )
{
	writeGlCommand( ACW_LINEWIDTH );
	writeValue( (void*)&a, sizeof(GLfloat) );
}

void glListBase ( GLuint a )
{
	writeGlCommand( ACW_LISTBASE );
	writeValue( (void*)&a, sizeof(GLuint) );
}

void glListParameterfSGIX ( GLuint a, GLenum b, GLfloat c )
{
	writeGlCommand( ACW_LISTPARAMETERFSGIX );
	writeValue( (void*)&a, sizeof(GLuint) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLfloat) );
}

void glListParameteriSGIX ( GLuint a, GLenum b, GLint c )
{
	writeGlCommand( ACW_LISTPARAMETERISGIX );
	writeValue( (void*)&a, sizeof(GLuint) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLint) );
}

void glLoadIdentity (  )
{
	writeGlCommand( ACW_LOADIDENTITY );
}

void glLoadIdentityDeformationMapSGIX ( GLbitfield a )
{
	writeGlCommand( ACW_LOADIDENTITYDEFORMATIONMAPSGIX );
	writeValue( (void*)&a, sizeof(GLbitfield) );
}

void glLoadName ( GLuint a )
{
	writeGlCommand( ACW_LOADNAME );
	writeValue( (void*)&a, sizeof(GLuint) );
}

void glLogicOp ( GLenum a )
{
	writeGlCommand( ACW_LOGICOP );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glMaterialf ( GLenum a, GLenum b, GLfloat c )
{
	writeGlCommand( ACW_MATERIALF );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLfloat) );
}

void glMateriali ( GLenum a, GLenum b, GLint c )
{
	writeGlCommand( ACW_MATERIALI );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLint) );
}

void glMatrixMode ( GLenum a )
{
	writeGlCommand( ACW_MATRIXMODE );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glMinmax ( GLenum a, GLenum b, GLboolean c )
{
	writeGlCommand( ACW_MINMAX );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLboolean) );
}

void glMinmaxEXT ( GLenum a, GLenum b, GLboolean c )
{
	writeGlCommand( ACW_MINMAXEXT );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLboolean) );
}

void glNewList ( GLuint a, GLenum b )
{
	writeGlCommand( ACW_NEWLIST );
	writeValue( (void*)&a, sizeof(GLuint) );
	writeValue( (void*)&b, sizeof(GLenum) );
}

void glNormal3b ( GLbyte a, GLbyte b, GLbyte c )
{
	writeGlCommand( ACW_NORMAL3B );
	GLbyte V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glNormal3bv ( GLbyte* a )
{
	writeGlCommand( ACW_NORMAL3BV );
	writeValue( (void*)a, sizeof(GLbyte)*3 );
}

void glNormal3d ( GLdouble a, GLdouble b, GLdouble c )
{
	writeGlCommand( ACW_NORMAL3D );
	GLdouble V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glNormal3dv ( GLdouble* a )
{
	writeGlCommand( ACW_NORMAL3DV );
	writeValue( (void*)a, sizeof(GLdouble)*3 );
}

void glNormal3f ( GLfloat a, GLfloat b, GLfloat c )
{
	writeGlCommand( ACW_NORMAL3F );
	GLfloat V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glNormal3fv ( GLfloat* a )
{
	writeGlCommand( ACW_NORMAL3FV );
	writeValue( (void*)a, sizeof(GLfloat)*3 );
}

void glNormal3i ( GLint a, GLint b, GLint c )
{
	writeGlCommand( ACW_NORMAL3I );
	GLint V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glNormal3iv ( GLint* a )
{
	writeGlCommand( ACW_NORMAL3IV );
	writeValue( (void*)a, sizeof(GLint)*3 );
}

void glNormal3s ( GLshort a, GLshort b, GLshort c )
{
	writeGlCommand( ACW_NORMAL3S );
	GLshort V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glNormal3sv ( GLshort* a )
{
	writeGlCommand( ACW_NORMAL3SV );
	writeValue( (void*)a, sizeof(GLshort)*3 );
}

void glOrtho ( GLdouble a, GLdouble b, GLdouble c, GLdouble d, GLdouble e, GLdouble f )
{
	writeGlCommand( ACW_ORTHO );
	writeValue( (void*)&a, sizeof(GLdouble) );
	writeValue( (void*)&b, sizeof(GLdouble) );
	writeValue( (void*)&c, sizeof(GLdouble) );
	writeValue( (void*)&d, sizeof(GLdouble) );
	writeValue( (void*)&e, sizeof(GLdouble) );
	writeValue( (void*)&f, sizeof(GLdouble) );
}

void glPassThrough ( GLfloat a )
{
	writeGlCommand( ACW_PASSTHROUGH );
	writeValue( (void*)&a, sizeof(GLfloat) );
}

void glPixelStoref ( GLenum a, GLfloat b )
{
	writeGlCommand( ACW_PIXELSTOREF );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLfloat) );
}

void glPixelStorei ( GLenum a, GLint b )
{
	writeGlCommand( ACW_PIXELSTOREI );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLint) );
}

void glPixelTexGenSGIX ( GLenum a )
{
	writeGlCommand( ACW_PIXELTEXGENSGIX );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glPixelTransferf ( GLenum a, GLfloat b )
{
	writeGlCommand( ACW_PIXELTRANSFERF );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLfloat) );
}

void glPixelTransferi ( GLenum a, GLint b )
{
	writeGlCommand( ACW_PIXELTRANSFERI );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLint) );
}

void glPixelZoom ( GLfloat a, GLfloat b )
{
	writeGlCommand( ACW_PIXELZOOM );
	writeValue( (void*)&a, sizeof(GLfloat) );
	writeValue( (void*)&b, sizeof(GLfloat) );
}

void glPointParameterfSGIS ( GLenum a, GLfloat b )
{
	writeGlCommand( ACW_POINTPARAMETERFSGIS );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLfloat) );
}

void glPointSize ( GLfloat a )
{
	writeGlCommand( ACW_POINTSIZE );
	writeValue( (void*)&a, sizeof(GLfloat) );
}

void glPolygonMode ( GLenum a, GLenum b )
{
	writeGlCommand( ACW_POLYGONMODE );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
}

void glPolygonOffset ( GLfloat a, GLfloat b )
{
	writeGlCommand( ACW_POLYGONOFFSET );
	writeValue( (void*)&a, sizeof(GLfloat) );
	writeValue( (void*)&b, sizeof(GLfloat) );
}

void glPolygonOffsetEXT ( GLfloat a, GLfloat b )
{
	writeGlCommand( ACW_POLYGONOFFSETEXT );
	writeValue( (void*)&a, sizeof(GLfloat) );
	writeValue( (void*)&b, sizeof(GLfloat) );
}

void glPopAttrib (  )
{
	writeGlCommand( ACW_POPATTRIB );
}

void glPopClientAttrib (  )
{
	writeGlCommand( ACW_POPCLIENTATTRIB );
}

void glPopMatrix (  )
{
	writeGlCommand( ACW_POPMATRIX );
}

void glPopName (  )
{
	writeGlCommand( ACW_POPNAME );
}

void glPushAttrib ( GLbitfield a )
{
	writeGlCommand( ACW_PUSHATTRIB );
	writeValue( (void*)&a, sizeof(GLbitfield) );
}

void glPushClientAttrib ( GLbitfield a )
{
	writeGlCommand( ACW_PUSHCLIENTATTRIB );
	writeValue( (void*)&a, sizeof(GLbitfield) );
}

void glPushMatrix (  )
{
	writeGlCommand( ACW_PUSHMATRIX );
}

void glPushName ( GLuint a )
{
	writeGlCommand( ACW_PUSHNAME );
	writeValue( (void*)&a, sizeof(GLuint) );
}

void glRasterPos2d ( GLdouble a, GLdouble b )
{
	writeGlCommand( ACW_RASTERPOS2D );
	GLdouble V[2];
	V[0] = a;
	V[1] = b;
	writeValue( (void*)V, sizeof(V) );
}

void glRasterPos2dv ( GLdouble* a )
{
	writeGlCommand( ACW_RASTERPOS2DV );
	writeValue( (void*)a, sizeof(GLdouble)*2 );
}

void glRasterPos2f ( GLfloat a, GLfloat b )
{
	writeGlCommand( ACW_RASTERPOS2F );
	GLfloat V[2];
	V[0] = a;
	V[1] = b;
	writeValue( (void*)V, sizeof(V) );
}

void glRasterPos2fv ( GLfloat* a )
{
	writeGlCommand( ACW_RASTERPOS2FV );
	writeValue( (void*)a, sizeof(GLfloat)*2 );
}

void glRasterPos2i ( GLint a, GLint b )
{
	writeGlCommand( ACW_RASTERPOS2I );
	GLint V[2];
	V[0] = a;
	V[1] = b;
	writeValue( (void*)V, sizeof(V) );
}

void glRasterPos2iv ( GLint* a )
{
	writeGlCommand( ACW_RASTERPOS2IV );
	writeValue( (void*)a, sizeof(GLint)*2 );
}

void glRasterPos2s ( GLshort a, GLshort b )
{
	writeGlCommand( ACW_RASTERPOS2S );
	GLshort V[2];
	V[0] = a;
	V[1] = b;
	writeValue( (void*)V, sizeof(V) );
}

void glRasterPos2sv ( GLshort* a )
{
	writeGlCommand( ACW_RASTERPOS2SV );
	writeValue( (void*)a, sizeof(GLshort)*2 );
}

void glRasterPos3d ( GLdouble a, GLdouble b, GLdouble c )
{
	writeGlCommand( ACW_RASTERPOS3D );
	GLdouble V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glRasterPos3dv ( GLdouble* a )
{
	writeGlCommand( ACW_RASTERPOS3DV );
	writeValue( (void*)a, sizeof(GLdouble)*3 );
}

void glRasterPos3f ( GLfloat a, GLfloat b, GLfloat c )
{
	writeGlCommand( ACW_RASTERPOS3F );
	GLfloat V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glRasterPos3fv ( GLfloat* a )
{
	writeGlCommand( ACW_RASTERPOS3FV );
	writeValue( (void*)a, sizeof(GLfloat)*3 );
}

void glRasterPos3i ( GLint a, GLint b, GLint c )
{
	writeGlCommand( ACW_RASTERPOS3I );
	GLint V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glRasterPos3iv ( GLint* a )
{
	writeGlCommand( ACW_RASTERPOS3IV );
	writeValue( (void*)a, sizeof(GLint)*3 );
}

void glRasterPos3s ( GLshort a, GLshort b, GLshort c )
{
	writeGlCommand( ACW_RASTERPOS3S );
	GLshort V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glRasterPos3sv ( GLshort* a )
{
	writeGlCommand( ACW_RASTERPOS3SV );
	writeValue( (void*)a, sizeof(GLshort)*3 );
}

void glRasterPos4d ( GLdouble a, GLdouble b, GLdouble c, GLdouble d )
{
	writeGlCommand( ACW_RASTERPOS4D );
	GLdouble V[4];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	V[3] = d;
	writeValue( (void*)V, sizeof(V) );
}

void glRasterPos4dv ( GLdouble* a )
{
	writeGlCommand( ACW_RASTERPOS4DV );
	writeValue( (void*)a, sizeof(GLdouble)*4 );
}

void glRasterPos4f ( GLfloat a, GLfloat b, GLfloat c, GLfloat d )
{
	writeGlCommand( ACW_RASTERPOS4F );
	GLfloat V[4];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	V[3] = d;
	writeValue( (void*)V, sizeof(V) );
}

void glRasterPos4fv ( GLfloat* a )
{
	writeGlCommand( ACW_RASTERPOS4FV );
	writeValue( (void*)a, sizeof(GLfloat)*4 );
}

void glRasterPos4i ( GLint a, GLint b, GLint c, GLint d )
{
	writeGlCommand( ACW_RASTERPOS4I );
	GLint V[4];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	V[3] = d;
	writeValue( (void*)V, sizeof(V) );
}

void glRasterPos4iv ( GLint* a )
{
	writeGlCommand( ACW_RASTERPOS4IV );
	writeValue( (void*)a, sizeof(GLint)*4 );
}

void glRasterPos4s ( GLshort a, GLshort b, GLshort c, GLshort d )
{
	writeGlCommand( ACW_RASTERPOS4S );
	GLshort V[4];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	V[3] = d;
	writeValue( (void*)V, sizeof(V) );
}

void glRasterPos4sv ( GLshort* a )
{
	writeGlCommand( ACW_RASTERPOS4SV );
	writeValue( (void*)a, sizeof(GLshort)*4 );
}

void glReadBuffer ( GLenum a )
{
	writeGlCommand( ACW_READBUFFER );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glReadInstrumentsSGIX ( GLint a )
{
	writeGlCommand( ACW_READINSTRUMENTSSGIX );
	writeValue( (void*)&a, sizeof(GLint) );
}

void glRectd ( GLdouble a, GLdouble b, GLdouble c, GLdouble d )
{
	writeGlCommand( ACW_RECTD );
	writeValue( (void*)&a, sizeof(GLdouble) );
	writeValue( (void*)&b, sizeof(GLdouble) );
	writeValue( (void*)&c, sizeof(GLdouble) );
	writeValue( (void*)&d, sizeof(GLdouble) );
}

void glRectf ( GLfloat a, GLfloat b, GLfloat c, GLfloat d )
{
	writeGlCommand( ACW_RECTF );
	writeValue( (void*)&a, sizeof(GLfloat) );
	writeValue( (void*)&b, sizeof(GLfloat) );
	writeValue( (void*)&c, sizeof(GLfloat) );
	writeValue( (void*)&d, sizeof(GLfloat) );
}

void glRecti ( GLint a, GLint b, GLint c, GLint d )
{
	writeGlCommand( ACW_RECTI );
	writeValue( (void*)&a, sizeof(GLint) );
	writeValue( (void*)&b, sizeof(GLint) );
	writeValue( (void*)&c, sizeof(GLint) );
	writeValue( (void*)&d, sizeof(GLint) );
}

void glRects ( GLshort a, GLshort b, GLshort c, GLshort d )
{
	writeGlCommand( ACW_RECTS );
	writeValue( (void*)&a, sizeof(GLshort) );
	writeValue( (void*)&b, sizeof(GLshort) );
	writeValue( (void*)&c, sizeof(GLshort) );
	writeValue( (void*)&d, sizeof(GLshort) );
}

GLint glRenderMode ( GLenum a )
{
	writeGlCommand( ACW_RENDERMODE );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glRotatef ( GLfloat a, GLfloat b, GLfloat c, GLfloat d )
{
	writeGlCommand( ACW_ROTATEF );
	writeValue( (void*)&a, sizeof(GLfloat) );
	writeValue( (void*)&b, sizeof(GLfloat) );
	writeValue( (void*)&c, sizeof(GLfloat) );
	writeValue( (void*)&d, sizeof(GLfloat) );
}

void glSampleMaskSGIS ( GLclampf a, GLboolean b )
{
	writeGlCommand( ACW_SAMPLEMASKSGIS );
	writeValue( (void*)&a, sizeof(GLclampf) );
	writeValue( (void*)&b, sizeof(GLboolean) );
}

void glSamplePatternSGIS ( GLenum a )
{
	writeGlCommand( ACW_SAMPLEPATTERNSGIS );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glScaled ( GLdouble a, GLdouble b, GLdouble c )
{
	writeGlCommand( ACW_SCALED );
	writeValue( (void*)&a, sizeof(GLdouble) );
	writeValue( (void*)&b, sizeof(GLdouble) );
	writeValue( (void*)&c, sizeof(GLdouble) );
}

void glScalef ( GLfloat a, GLfloat b, GLfloat c )
{
	writeGlCommand( ACW_SCALEF );
	writeValue( (void*)&a, sizeof(GLfloat) );
	writeValue( (void*)&b, sizeof(GLfloat) );
	writeValue( (void*)&c, sizeof(GLfloat) );
}

void glScissor ( GLint a, GLint b, GLsizei c, GLsizei d )
{
	writeGlCommand( ACW_SCISSOR );
	writeValue( (void*)&a, sizeof(GLint) );
	writeValue( (void*)&b, sizeof(GLint) );
	writeValue( (void*)&c, sizeof(GLsizei) );
	writeValue( (void*)&d, sizeof(GLsizei) );
}

void glShadeModel ( GLenum a )
{
	writeGlCommand( ACW_SHADEMODEL );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glStartInstrumentsSGIX (  )
{
	writeGlCommand( ACW_STARTINSTRUMENTSSGIX );
}

void glStencilFunc ( GLenum a, GLint b, GLuint c )
{
	writeGlCommand( ACW_STENCILFUNC );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLint) );
	writeValue( (void*)&c, sizeof(GLuint) );
}

void glStencilMask ( GLuint a )
{
	writeGlCommand( ACW_STENCILMASK );
	writeValue( (void*)&a, sizeof(GLuint) );
}

void glStencilOp ( GLenum a, GLenum b, GLenum c )
{
	writeGlCommand( ACW_STENCILOP );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLenum) );
}

void glStopInstrumentsSGIX ( GLint a )
{
	writeGlCommand( ACW_STOPINSTRUMENTSSGIX );
	writeValue( (void*)&a, sizeof(GLint) );
}

void glTagSampleBufferSGIX (  )
{
	writeGlCommand( ACW_TAGSAMPLEBUFFERSGIX );
}

void glTexCoord1d ( GLdouble a )
{
	writeGlCommand( ACW_TEXCOORD1D );
	GLdouble V[1];
	V[0] = a;
	writeValue( (void*)V, sizeof(V) );
}

void glTexCoord1dv ( GLdouble* a )
{
	writeGlCommand( ACW_TEXCOORD1DV );
	writeValue( (void*)a, sizeof(GLdouble)*1 );
}

void glTexCoord1f ( GLfloat a )
{
	writeGlCommand( ACW_TEXCOORD1F );
	GLfloat V[1];
	V[0] = a;
	writeValue( (void*)V, sizeof(V) );
}

void glTexCoord1fv ( GLfloat* a )
{
	writeGlCommand( ACW_TEXCOORD1FV );
	writeValue( (void*)a, sizeof(GLfloat)*1 );
}

void glTexCoord1i ( GLint a )
{
	writeGlCommand( ACW_TEXCOORD1I );
	GLint V[1];
	V[0] = a;
	writeValue( (void*)V, sizeof(V) );
}

void glTexCoord1iv ( GLint* a )
{
	writeGlCommand( ACW_TEXCOORD1IV );
	writeValue( (void*)a, sizeof(GLint)*1 );
}

void glTexCoord1s ( GLshort a )
{
	writeGlCommand( ACW_TEXCOORD1S );
	GLshort V[1];
	V[0] = a;
	writeValue( (void*)V, sizeof(V) );
}

void glTexCoord1sv ( GLshort* a )
{
	writeGlCommand( ACW_TEXCOORD1SV );
	writeValue( (void*)a, sizeof(GLshort)*1 );
}

void glTexCoord2d ( GLdouble a, GLdouble b )
{
	writeGlCommand( ACW_TEXCOORD2D );
	GLdouble V[2];
	V[0] = a;
	V[1] = b;
	writeValue( (void*)V, sizeof(V) );
}

void glTexCoord2dv ( GLdouble* a )
{
	writeGlCommand( ACW_TEXCOORD2DV );
	writeValue( (void*)a, sizeof(GLdouble)*2 );
}

void glTexCoord2f ( GLfloat a, GLfloat b )
{
	writeGlCommand( ACW_TEXCOORD2F );
	GLfloat V[2];
	V[0] = a;
	V[1] = b;
	writeValue( (void*)V, sizeof(V) );
}

void glTexCoord2fv ( GLfloat* a )
{
	writeGlCommand( ACW_TEXCOORD2FV );
	writeValue( (void*)a, sizeof(GLfloat)*2 );
}

void glTexCoord2i ( GLint a, GLint b )
{
	writeGlCommand( ACW_TEXCOORD2I );
	GLint V[2];
	V[0] = a;
	V[1] = b;
	writeValue( (void*)V, sizeof(V) );
}

void glTexCoord2iv ( GLint* a )
{
	writeGlCommand( ACW_TEXCOORD2IV );
	writeValue( (void*)a, sizeof(GLint)*2 );
}

void glTexCoord2s ( GLshort a, GLshort b )
{
	writeGlCommand( ACW_TEXCOORD2S );
	GLshort V[2];
	V[0] = a;
	V[1] = b;
	writeValue( (void*)V, sizeof(V) );
}

void glTexCoord2sv ( GLshort* a )
{
	writeGlCommand( ACW_TEXCOORD2SV );
	writeValue( (void*)a, sizeof(GLshort)*2 );
}

void glTexCoord3d ( GLdouble a, GLdouble b, GLdouble c )
{
	writeGlCommand( ACW_TEXCOORD3D );
	GLdouble V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glTexCoord3dv ( GLdouble* a )
{
	writeGlCommand( ACW_TEXCOORD3DV );
	writeValue( (void*)a, sizeof(GLdouble)*3 );
}

void glTexCoord3f ( GLfloat a, GLfloat b, GLfloat c )
{
	writeGlCommand( ACW_TEXCOORD3F );
	GLfloat V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glTexCoord3fv ( GLfloat* a )
{
	writeGlCommand( ACW_TEXCOORD3FV );
	writeValue( (void*)a, sizeof(GLfloat)*3 );
}

void glTexCoord3i ( GLint a, GLint b, GLint c )
{
	writeGlCommand( ACW_TEXCOORD3I );
	GLint V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glTexCoord3iv ( GLint* a )
{
	writeGlCommand( ACW_TEXCOORD3IV );
	writeValue( (void*)a, sizeof(GLint)*3 );
}

void glTexCoord3s ( GLshort a, GLshort b, GLshort c )
{
	writeGlCommand( ACW_TEXCOORD3S );
	GLshort V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glTexCoord3sv ( GLshort* a )
{
	writeGlCommand( ACW_TEXCOORD3SV );
	writeValue( (void*)a, sizeof(GLshort)*3 );
}

void glTexCoord4d ( GLdouble a, GLdouble b, GLdouble c, GLdouble d )
{
	writeGlCommand( ACW_TEXCOORD4D );
	GLdouble V[4];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	V[3] = d;
	writeValue( (void*)V, sizeof(V) );
}

void glTexCoord4dv ( GLdouble* a )
{
	writeGlCommand( ACW_TEXCOORD4DV );
	writeValue( (void*)a, sizeof(GLdouble)*4 );
}

void glTexCoord4f ( GLfloat a, GLfloat b, GLfloat c, GLfloat d )
{
	writeGlCommand( ACW_TEXCOORD4F );
	GLfloat V[4];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	V[3] = d;
	writeValue( (void*)V, sizeof(V) );
}

void glTexCoord4fv ( GLfloat* a )
{
	writeGlCommand( ACW_TEXCOORD4FV );
	writeValue( (void*)a, sizeof(GLfloat)*4 );
}

void glTexCoord4i ( GLint a, GLint b, GLint c, GLint d )
{
	writeGlCommand( ACW_TEXCOORD4I );
	GLint V[4];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	V[3] = d;
	writeValue( (void*)V, sizeof(V) );
}

void glTexCoord4iv ( GLint* a )
{
	writeGlCommand( ACW_TEXCOORD4IV );
	writeValue( (void*)a, sizeof(GLint)*4 );
}

void glTexCoord4s ( GLshort a, GLshort b, GLshort c, GLshort d )
{
	writeGlCommand( ACW_TEXCOORD4S );
	GLshort V[4];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	V[3] = d;
	writeValue( (void*)V, sizeof(V) );
}

void glTexCoord4sv ( GLshort* a )
{
	writeGlCommand( ACW_TEXCOORD4SV );
	writeValue( (void*)a, sizeof(GLshort)*4 );
}

void glTexEnvf ( GLenum a, GLenum b, GLfloat c )
{
	writeGlCommand( ACW_TEXENVF );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLfloat) );
}

void glTexEnvi ( GLenum a, GLenum b, GLint c )
{
	writeGlCommand( ACW_TEXENVI );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLint) );
}

void glTexGend ( GLenum a, GLenum b, GLdouble c )
{
	writeGlCommand( ACW_TEXGEND );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLdouble) );
}

void glTexGenf ( GLenum a, GLenum b, GLfloat c )
{
	writeGlCommand( ACW_TEXGENF );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLfloat) );
}

void glTexGeni ( GLenum a, GLenum b, GLint c )
{
	writeGlCommand( ACW_TEXGENI );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLint) );
}

void glTexParameterf ( GLenum a, GLenum b, GLfloat c )
{
	writeGlCommand( ACW_TEXPARAMETERF );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLfloat) );
}

void glTexParameteri ( GLenum a, GLenum b, GLint c )
{
	writeGlCommand( ACW_TEXPARAMETERI );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLint) );
}

void glTranslated ( GLdouble a, GLdouble b, GLdouble c )
{
	writeGlCommand( ACW_TRANSLATED );
	writeValue( (void*)&a, sizeof(GLdouble) );
	writeValue( (void*)&b, sizeof(GLdouble) );
	writeValue( (void*)&c, sizeof(GLdouble) );
}

void glTranslatef ( GLfloat a, GLfloat b, GLfloat c )
{
	writeGlCommand( ACW_TRANSLATEF );
	writeValue( (void*)&a, sizeof(GLfloat) );
	writeValue( (void*)&b, sizeof(GLfloat) );
	writeValue( (void*)&c, sizeof(GLfloat) );
}

void glVertex2d ( GLdouble a, GLdouble b )
{
	writeGlCommand( ACW_VERTEX2D );
	GLdouble V[2];
	V[0] = a;
	V[1] = b;
	writeValue( (void*)V, sizeof(V) );
}

void glVertex2dv ( GLdouble* a )
{
	writeGlCommand( ACW_VERTEX2DV );
	writeValue( (void*)a, sizeof(GLdouble)*2 );
}

void glVertex2f ( GLfloat a, GLfloat b )
{
	writeGlCommand( ACW_VERTEX2F );
	GLfloat V[2];
	V[0] = a;
	V[1] = b;
	writeValue( (void*)V, sizeof(V) );
}

void glVertex2fv ( GLfloat* a )
{
	writeGlCommand( ACW_VERTEX2FV );
	writeValue( (void*)a, sizeof(GLfloat)*2 );
}

void glVertex2i ( GLint a, GLint b )
{
	writeGlCommand( ACW_VERTEX2I );
	GLint V[2];
	V[0] = a;
	V[1] = b;
	writeValue( (void*)V, sizeof(V) );
}

void glVertex2iv ( GLint* a )
{
	writeGlCommand( ACW_VERTEX2IV );
	writeValue( (void*)a, sizeof(GLint)*2 );
}

void glVertex2s ( GLshort a, GLshort b )
{
	writeGlCommand( ACW_VERTEX2S );
	GLshort V[2];
	V[0] = a;
	V[1] = b;
	writeValue( (void*)V, sizeof(V) );
}

void glVertex2sv ( GLshort* a )
{
	writeGlCommand( ACW_VERTEX2SV );
	writeValue( (void*)a, sizeof(GLshort)*2 );
}

void glVertex3d ( GLdouble a, GLdouble b, GLdouble c )
{
	writeGlCommand( ACW_VERTEX3D );
	GLdouble V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glVertex3dv ( GLdouble* a )
{
	writeGlCommand( ACW_VERTEX3DV );
	writeValue( (void*)a, sizeof(GLdouble)*3 );
}

void glVertex3f ( GLfloat a, GLfloat b, GLfloat c )
{
	writeGlCommand( ACW_VERTEX3F );
	GLfloat V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glVertex3fv ( GLfloat* a )
{
	writeGlCommand( ACW_VERTEX3FV );
	writeValue( (void*)a, sizeof(GLfloat)*3 );
}

void glVertex3i ( GLint a, GLint b, GLint c )
{
	writeGlCommand( ACW_VERTEX3I );
	GLint V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glVertex3iv ( GLint* a )
{
	writeGlCommand( ACW_VERTEX3IV );
	writeValue( (void*)a, sizeof(GLint)*3 );
}

void glVertex3s ( GLshort a, GLshort b, GLshort c )
{
	writeGlCommand( ACW_VERTEX3S );
	GLshort V[3];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	writeValue( (void*)V, sizeof(V) );
}

void glVertex3sv ( GLshort* a )
{
	writeGlCommand( ACW_VERTEX3SV );
	writeValue( (void*)a, sizeof(GLshort)*3 );
}

void glVertex4d ( GLdouble a, GLdouble b, GLdouble c, GLdouble d )
{
	writeGlCommand( ACW_VERTEX4D );
	GLdouble V[4];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	V[3] = d;
	writeValue( (void*)V, sizeof(V) );
}

void glVertex4dv ( GLdouble* a )
{
	writeGlCommand( ACW_VERTEX4DV );
	writeValue( (void*)a, sizeof(GLdouble)*4 );
}

void glVertex4f ( GLfloat a, GLfloat b, GLfloat c, GLfloat d )
{
	writeGlCommand( ACW_VERTEX4F );
	GLfloat V[4];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	V[3] = d;
	writeValue( (void*)V, sizeof(V) );
}

void glVertex4fv ( GLfloat* a )
{
	writeGlCommand( ACW_VERTEX4FV );
	writeValue( (void*)a, sizeof(GLfloat)*4 );
}

void glVertex4i ( GLint a, GLint b, GLint c, GLint d )
{
	writeGlCommand( ACW_VERTEX4I );
	GLint V[4];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	V[3] = d;
	writeValue( (void*)V, sizeof(V) );
}

void glVertex4iv ( GLint* a )
{
	writeGlCommand( ACW_VERTEX4IV );
	writeValue( (void*)a, sizeof(GLint)*4 );
}

void glVertex4s ( GLshort a, GLshort b, GLshort c, GLshort d )
{
	writeGlCommand( ACW_VERTEX4S );
	GLshort V[4];
	V[0] = a;
	V[1] = b;
	V[2] = c;
	V[3] = d;
	writeValue( (void*)V, sizeof(V) );
}

void glVertex4sv ( GLshort* a )
{
	writeGlCommand( ACW_VERTEX4SV );
	writeValue( (void*)a, sizeof(GLshort)*4 );
}

void glViewport ( GLint a, GLint b, GLsizei c, GLsizei d )
{
	writeGlCommand( ACW_VIEWPORT );
	writeValue( (void*)&a, sizeof(GLint) );
	writeValue( (void*)&b, sizeof(GLint) );
	writeValue( (void*)&c, sizeof(GLsizei) );
	writeValue( (void*)&d, sizeof(GLsizei) );
}

