
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

GLboolean glAreTexturesResident ( GLsizei a, GLuint* b, GLboolean* c )
{
	writeGlCommand( ACW_ARETEXTURESRESIDENT );
}

GLboolean glAreTexturesResidentEXT ( GLsizei a, GLuint* b, GLboolean* c )
{
	writeGlCommand( ACW_ARETEXTURESRESIDENTEXT );
}

void glArrayElement ( GLint a )
{
	writeGlCommand( ACW_ARRAYELEMENT );
}

void glArrayElementEXT ( GLint a )
{
	writeGlCommand( ACW_ARRAYELEMENTEXT );
}


void glBegin ( GLenum a )
{
	writeGlCommand( ACW_BEGIN );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glBindTexture ( GLenum a, GLuint b )
{
	writeGlCommand( ACW_BINDTEXTURE );
}

void glBindTextureEXT ( GLenum a, GLuint b )
{
	writeGlCommand( ACW_BINDTEXTUREEXT );
}

void glBitmap ( GLsizei a, GLsizei b, GLfloat c, GLfloat d, GLfloat e, GLfloat f, GLubyte* g )
{
	writeGlCommand( ACW_BITMAP );
}

void glBlendColor ( GLclampf a, GLclampf b, GLclampf c, GLclampf d )
{
	writeGlCommand( ACW_BLENDCOLOR );
	writeValue( (void*)&a, sizeof(GLclampf) );
	writeValue( (void*)&b, sizeof(GLclampf) );
	writeValue( (void*)&c, sizeof(GLclampf) );
	writeValue( (void*)&d, sizeof(GLclampf) );
}

void glBlendColorEXT ( GLclampf a, GLclampf b, GLclampf c, GLclampf d )
{
	writeGlCommand( ACW_BLENDCOLOREXT );
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

void glCallLists ( GLsizei a, GLenum b, GLvoid* c )
{
	writeGlCommand( ACW_CALLLISTS );
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

void glClipPlane ( GLenum a, GLdouble* b )
{
	writeGlCommand( ACW_CLIPPLANE );
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

void glColorPointer ( GLint a, GLenum b, GLsizei c, GLvoid* d )
{
	writeGlCommand( ACW_COLORPOINTER );
}

void glColorPointerEXT ( GLint a, GLenum b, GLsizei c, GLsizei d, GLvoid* e )
{
	writeGlCommand( ACW_COLORPOINTEREXT );
}

void glColorSubTable ( GLenum a, GLsizei b, GLsizei c, GLenum d, GLenum e, GLvoid* f )
{
	writeGlCommand( ACW_COLORSUBTABLE );
}

void glColorTable ( GLenum a, GLenum b, GLsizei c, GLenum d, GLenum e, GLvoid* f )
{
	writeGlCommand( ACW_COLORTABLE );
}

void glColorTableParameterfv ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_COLORTABLEPARAMETERFV );
}

void glColorTableParameterfvSGI ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_COLORTABLEPARAMETERFVSGI );
}

void glColorTableParameteriv ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_COLORTABLEPARAMETERIV );
}

void glColorTableParameterivSGI ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_COLORTABLEPARAMETERIVSGI );
}

void glColorTableSGI ( GLenum a, GLenum b, GLsizei c, GLenum d, GLenum e, GLvoid* f )
{
	writeGlCommand( ACW_COLORTABLESGI );
}

void glConvolutionFilter1D ( GLenum a, GLenum b, GLsizei c, GLenum d, GLenum e, GLvoid* f )
{
	writeGlCommand( ACW_CONVOLUTIONFILTER1D );
}

void glConvolutionFilter1DEXT ( GLenum a, GLenum b, GLsizei c, GLenum d, GLenum e, GLvoid* f )
{
	writeGlCommand( ACW_CONVOLUTIONFILTER1DEXT );
}

void glConvolutionFilter2D ( GLenum a, GLenum b, GLsizei c, GLsizei d, GLenum e, GLenum f, GLvoid* g )
{
	writeGlCommand( ACW_CONVOLUTIONFILTER2D );
}

void glConvolutionFilter2DEXT ( GLenum a, GLenum b, GLsizei c, GLsizei d, GLenum e, GLenum f, GLvoid* g )
{
	writeGlCommand( ACW_CONVOLUTIONFILTER2DEXT );
}

void glConvolutionParameterf ( GLenum a, GLenum b, GLfloat c )
{
	writeGlCommand( ACW_CONVOLUTIONPARAMETERF );
}

void glConvolutionParameterfEXT ( GLenum a, GLenum b, GLfloat c )
{
	writeGlCommand( ACW_CONVOLUTIONPARAMETERFEXT );
}

void glConvolutionParameterfv ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_CONVOLUTIONPARAMETERFV );
}

void glConvolutionParameterfvEXT ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_CONVOLUTIONPARAMETERFVEXT );
}

void glConvolutionParameteri ( GLenum a, GLenum b, GLint c )
{
	writeGlCommand( ACW_CONVOLUTIONPARAMETERI );
}

void glConvolutionParameteriEXT ( GLenum a, GLenum b, GLint c )
{
	writeGlCommand( ACW_CONVOLUTIONPARAMETERIEXT );
}

void glConvolutionParameteriv ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_CONVOLUTIONPARAMETERIV );
}

void glConvolutionParameterivEXT ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_CONVOLUTIONPARAMETERIVEXT );
}

void glCopyColorSubTable ( GLenum a, GLsizei b, GLint c, GLint d, GLsizei e )
{
	writeGlCommand( ACW_COPYCOLORSUBTABLE );
}

void glCopyColorTable ( GLenum a, GLenum b, GLint c, GLint d, GLsizei e )
{
	writeGlCommand( ACW_COPYCOLORTABLE );
}

void glCopyColorTableSGI ( GLenum a, GLenum b, GLint c, GLint d, GLsizei e )
{
	writeGlCommand( ACW_COPYCOLORTABLESGI );
}

void glCopyConvolutionFilter1D ( GLenum a, GLenum b, GLint c, GLint d, GLsizei e )
{
	writeGlCommand( ACW_COPYCONVOLUTIONFILTER1D );
}

void glCopyConvolutionFilter1DEXT ( GLenum a, GLenum b, GLint c, GLint d, GLsizei e )
{
	writeGlCommand( ACW_COPYCONVOLUTIONFILTER1DEXT );
}

void glCopyConvolutionFilter2D ( GLenum a, GLenum b, GLint c, GLint d, GLsizei e, GLsizei f )
{
	writeGlCommand( ACW_COPYCONVOLUTIONFILTER2D );
}

void glCopyConvolutionFilter2DEXT ( GLenum a, GLenum b, GLint c, GLint d, GLsizei e, GLsizei f )
{
	writeGlCommand( ACW_COPYCONVOLUTIONFILTER2DEXT );
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

void glCopyTexImage1D ( GLenum a, GLint b, GLenum c, GLint d, GLint e, GLsizei f, GLint g )
{
	writeGlCommand( ACW_COPYTEXIMAGE1D );
}

void glCopyTexImage1DEXT ( GLenum a, GLint b, GLenum c, GLint d, GLint e, GLsizei f, GLint g )
{
	writeGlCommand( ACW_COPYTEXIMAGE1DEXT );
}

void glCopyTexImage2D ( GLenum a, GLint b, GLenum c, GLint d, GLint e, GLsizei f, GLsizei g, GLint h )
{
	writeGlCommand( ACW_COPYTEXIMAGE2D );
}

void glCopyTexImage2DEXT ( GLenum a, GLint b, GLenum c, GLint d, GLint e, GLsizei f, GLsizei g, GLint h )
{
	writeGlCommand( ACW_COPYTEXIMAGE2DEXT );
}

void glCopyTexSubImage1D ( GLenum a, GLint b, GLint c, GLint d, GLint e, GLsizei f )
{
	writeGlCommand( ACW_COPYTEXSUBIMAGE1D );
}

void glCopyTexSubImage1DEXT ( GLenum a, GLint b, GLint c, GLint d, GLint e, GLsizei f )
{
	writeGlCommand( ACW_COPYTEXSUBIMAGE1DEXT );
}

void glCopyTexSubImage2D ( GLenum a, GLint b, GLint c, GLint d, GLint e, GLint f, GLsizei g, GLsizei h )
{
	writeGlCommand( ACW_COPYTEXSUBIMAGE2D );
}

void glCopyTexSubImage2DEXT ( GLenum a, GLint b, GLint c, GLint d, GLint e, GLint f, GLsizei g, GLsizei h )
{
	writeGlCommand( ACW_COPYTEXSUBIMAGE2DEXT );
}

void glCopyTexSubImage3D ( GLenum a, GLint b, GLint c, GLint d, GLint e, GLint f, GLint g, GLsizei h, GLsizei i )
{
	writeGlCommand( ACW_COPYTEXSUBIMAGE3D );
}

void glCopyTexSubImage3DEXT ( GLenum a, GLint b, GLint c, GLint d, GLint e, GLint f, GLint g, GLsizei h, GLsizei i )
{
	writeGlCommand( ACW_COPYTEXSUBIMAGE3DEXT );
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

void glDeformationMap3dSGIX ( GLenum a, GLdouble b, GLdouble c, GLint d, GLint e, GLdouble f, GLdouble g, GLint h, GLint i, GLdouble j, GLdouble k, GLint l, GLint m, GLdouble* n )
{
	writeGlCommand( ACW_DEFORMATIONMAP3DSGIX );
}

void glDeformationMap3fSGIX ( GLenum a, GLfloat b, GLfloat c, GLint d, GLint e, GLfloat f, GLfloat g, GLint h, GLint i, GLfloat j, GLfloat k, GLint l, GLint m, GLfloat* n )
{
	writeGlCommand( ACW_DEFORMATIONMAP3FSGIX );
}

void glDeleteLists ( GLuint a, GLsizei b )
{
	writeGlCommand( ACW_DELETELISTS );
	writeValue( (void*)&a, sizeof(GLuint) );
	writeValue( (void*)&b, sizeof(GLsizei) );
}

void glDeleteTextures ( GLsizei a, GLuint* b )
{
	writeGlCommand( ACW_DELETETEXTURES );
}

void glDeleteTexturesEXT ( GLsizei a, GLuint* b )
{
	writeGlCommand( ACW_DELETETEXTURESEXT );
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

void glDetailTexFuncSGIS ( GLenum a, GLsizei b, GLfloat* c )
{
	writeGlCommand( ACW_DETAILTEXFUNCSGIS );
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

void glDrawElements ( GLenum a, GLsizei b, GLenum c, GLvoid* d )
{
	writeGlCommand( ACW_DRAWELEMENTS );
}

void glDrawPixels ( GLsizei a, GLsizei b, GLenum c, GLenum d, GLvoid* e )
{
	writeGlCommand( ACW_DRAWPIXELS );
}

void glDrawRangeElements ( GLenum a, GLuint b, GLuint c, GLsizei d, GLenum e, GLvoid* f )
{
	writeGlCommand( ACW_DRAWRANGEELEMENTS );
}

void glEdgeFlag ( GLboolean a )
{
	writeGlCommand( ACW_EDGEFLAG );
	writeValue( (void*)&a, sizeof(GLboolean) );
}

void glEdgeFlagPointer ( GLsizei a, GLboolean* b )
{
	writeGlCommand( ACW_EDGEFLAGPOINTER );
}

void glEdgeFlagPointerEXT ( GLsizei a, GLsizei b, GLboolean* c )
{
	writeGlCommand( ACW_EDGEFLAGPOINTEREXT );
}

void glEdgeFlagv ( GLboolean* a )
{
	writeGlCommand( ACW_EDGEFLAGV );
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

void glFeedbackBuffer ( GLsizei a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_FEEDBACKBUFFER );
}

void glFinish (  )
{
	writeGlCommand( ACW_FINISH );
}

void glFlush (  )
{
	writeGlCommand( ACW_FLUSH );
}

void glFlushRasterSGIX (  )
{
	writeGlCommand( ACW_FLUSHRASTERSGIX );
}

void glFogFuncSGIS ( GLsizei a, GLfloat* b )
{
	writeGlCommand( ACW_FOGFUNCSGIS );
}

void glFogf ( GLenum a, GLfloat b )
{
	writeGlCommand( ACW_FOGF );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLfloat) );
}

void glFogfv ( GLenum a, GLfloat* b )
{
	writeGlCommand( ACW_FOGFV );
}

void glFogi ( GLenum a, GLint b )
{
	writeGlCommand( ACW_FOGI );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLint) );
}

void glFogiv ( GLenum a, GLint* b )
{
	writeGlCommand( ACW_FOGIV );
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

void glGenTexturesEXT ( GLsizei a, GLuint* b )
{
	writeGlCommand( ACW_GENTEXTURESEXT );
}

void glGetBooleanv ( GLenum a, GLboolean* b )
{
	writeGlCommand( ACW_GETBOOLEANV );
}

void glGetClipPlane ( GLenum a, GLdouble* b )
{
	writeGlCommand( ACW_GETCLIPPLANE );
}

void glGetColorTable ( GLenum a, GLenum b, GLenum c, GLvoid* d )
{
	writeGlCommand( ACW_GETCOLORTABLE );
}

void glGetColorTableParameterfv ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_GETCOLORTABLEPARAMETERFV );
}

void glGetColorTableParameterfvSGI ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_GETCOLORTABLEPARAMETERFVSGI );
}

void glGetColorTableParameteriv ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_GETCOLORTABLEPARAMETERIV );
}

void glGetColorTableParameterivSGI ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_GETCOLORTABLEPARAMETERIVSGI );
}

void glGetColorTableSGI ( GLenum a, GLenum b, GLenum c, GLvoid* d )
{
	writeGlCommand( ACW_GETCOLORTABLESGI );
}

void glGetConvolutionFilter ( GLenum a, GLenum b, GLenum c, GLvoid* d )
{
	writeGlCommand( ACW_GETCONVOLUTIONFILTER );
}

void glGetConvolutionFilterEXT ( GLenum a, GLenum b, GLenum c, GLvoid* d )
{
	writeGlCommand( ACW_GETCONVOLUTIONFILTEREXT );
}

void glGetConvolutionParameterfv ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_GETCONVOLUTIONPARAMETERFV );
}

void glGetConvolutionParameterfvEXT ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_GETCONVOLUTIONPARAMETERFVEXT );
}

void glGetConvolutionParameteriv ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_GETCONVOLUTIONPARAMETERIV );
}

void glGetConvolutionParameterivEXT ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_GETCONVOLUTIONPARAMETERIVEXT );
}

void glGetDetailTexFuncSGIS ( GLenum a, GLfloat* b )
{
	writeGlCommand( ACW_GETDETAILTEXFUNCSGIS );
}

void glGetDoublev ( GLenum a, GLdouble* b )
{
	writeGlCommand( ACW_GETDOUBLEV );
}

GLenum glGetError (  )
{
	writeGlCommand( ACW_GETERROR );
}

void glGetFloatv ( GLenum a, GLfloat* b )
{
	writeGlCommand( ACW_GETFLOATV );
}

void glGetHistogram ( GLenum a, GLboolean b, GLenum c, GLenum d, GLvoid* e )
{
	writeGlCommand( ACW_GETHISTOGRAM );
}

void glGetHistogramEXT ( GLenum a, GLboolean b, GLenum c, GLenum d, GLvoid* e )
{
	writeGlCommand( ACW_GETHISTOGRAMEXT );
}

void glGetHistogramParameterfv ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_GETHISTOGRAMPARAMETERFV );
}

void glGetHistogramParameterfvEXT ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_GETHISTOGRAMPARAMETERFVEXT );
}

void glGetHistogramParameteriv ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_GETHISTOGRAMPARAMETERIV );
}

void glGetHistogramParameterivEXT ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_GETHISTOGRAMPARAMETERIVEXT );
}

GLint glGetInstrumentsSGIX (  )
{
	writeGlCommand( ACW_GETINSTRUMENTSSGIX );
}

void glGetIntegerv ( GLenum a, GLint* b )
{
	writeGlCommand( ACW_GETINTEGERV );
}

void glGetLightfv ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_GETLIGHTFV );
}

void glGetLightiv ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_GETLIGHTIV );
}

void glGetListParameterfvSGIX ( GLuint a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_GETLISTPARAMETERFVSGIX );
}

void glGetListParameterivSGIX ( GLuint a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_GETLISTPARAMETERIVSGIX );
}

void glGetMapdv ( GLenum a, GLenum b, GLdouble* c )
{
	writeGlCommand( ACW_GETMAPDV );
}

void glGetMapfv ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_GETMAPFV );
}

void glGetMapiv ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_GETMAPIV );
}

void glGetMaterialfv ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_GETMATERIALFV );
}

void glGetMaterialiv ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_GETMATERIALIV );
}

void glGetMinmax ( GLenum a, GLboolean b, GLenum c, GLenum d, GLvoid* e )
{
	writeGlCommand( ACW_GETMINMAX );
}

void glGetMinmaxEXT ( GLenum a, GLboolean b, GLenum c, GLenum d, GLvoid* e )
{
	writeGlCommand( ACW_GETMINMAXEXT );
}

void glGetMinmaxParameterfv ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_GETMINMAXPARAMETERFV );
}

void glGetMinmaxParameterfvEXT ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_GETMINMAXPARAMETERFVEXT );
}

void glGetMinmaxParameteriv ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_GETMINMAXPARAMETERIV );
}

void glGetMinmaxParameterivEXT ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_GETMINMAXPARAMETERIVEXT );
}

void glGetPixelMapfv ( GLenum a, GLfloat* b )
{
	writeGlCommand( ACW_GETPIXELMAPFV );
}

void glGetPixelMapuiv ( GLenum a, GLuint* b )
{
	writeGlCommand( ACW_GETPIXELMAPUIV );
}

void glGetPixelMapusv ( GLenum a, GLushort* b )
{
	writeGlCommand( ACW_GETPIXELMAPUSV );
}

void glGetPointerv ( GLenum a, GLvoid** b )
{
	writeGlCommand( ACW_GETPOINTERV );
}

void glGetPointervEXT ( GLenum a, GLvoid** b )
{
	writeGlCommand( ACW_GETPOINTERVEXT );
}

void glGetPolygonStipple ( GLubyte* a )
{
	writeGlCommand( ACW_GETPOLYGONSTIPPLE );
}

void glGetSeparableFilter ( GLenum a, GLenum b, GLenum c, GLvoid* d, GLvoid* e, GLvoid* f )
{
	writeGlCommand( ACW_GETSEPARABLEFILTER );
}

void glGetSeparableFilterEXT ( GLenum a, GLenum b, GLenum c, GLvoid* d, GLvoid* e, GLvoid* f )
{
	writeGlCommand( ACW_GETSEPARABLEFILTEREXT );
}

void glGetSharpenTexFuncSGIS ( GLenum a, GLfloat* b )
{
	writeGlCommand( ACW_GETSHARPENTEXFUNCSGIS );
}

const GLubyte* glGetString ( GLenum a )
{
	writeGlCommand( ACW_GETSTRING );
} 

void glGetTexEnvfv ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_GETTEXENVFV );
}

void glGetTexEnviv ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_GETTEXENVIV );
}

void glGetTexFilterFuncSGIS ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_GETTEXFILTERFUNCSGIS );
}

void glGetTexGendv ( GLenum a, GLenum b, GLdouble* c )
{
	writeGlCommand( ACW_GETTEXGENDV );
}

void glGetTexGenfv ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_GETTEXGENFV );
}

void glGetTexGeniv ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_GETTEXGENIV );
}

void glGetTexImage ( GLenum a, GLint b, GLenum c, GLenum d, GLvoid* e )
{
	writeGlCommand( ACW_GETTEXIMAGE );
}

void glGetTexLevelParameterfv ( GLenum a, GLint b, GLenum c, GLfloat* d )
{
	writeGlCommand( ACW_GETTEXLEVELPARAMETERFV );
}

void glGetTexLevelParameteriv ( GLenum a, GLint b, GLenum c, GLint* d )
{
	writeGlCommand( ACW_GETTEXLEVELPARAMETERIV );
}

void glGetTexParameterfv ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_GETTEXPARAMETERFV );
}

void glGetTexParameteriv ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_GETTEXPARAMETERIV );
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

void glIndexPointer ( GLenum a, GLsizei b, GLvoid* c )
{
	writeGlCommand( ACW_INDEXPOINTER );
}

void glIndexPointerEXT ( GLenum a, GLsizei b, GLsizei c, GLvoid* d )
{
	writeGlCommand( ACW_INDEXPOINTEREXT );
}

void glIndexd ( GLdouble a )
{
	writeGlCommand( ACW_INDEXD );
	writeValue( (void*)&a, sizeof(GLdouble) );
}

void glIndexdv ( GLdouble* a )
{
	writeGlCommand( ACW_INDEXDV );
}

void glIndexf ( GLfloat a )
{
	writeGlCommand( ACW_INDEXF );
	writeValue( (void*)&a, sizeof(GLfloat) );
}

void glIndexfv ( GLfloat* a )
{
	writeGlCommand( ACW_INDEXFV );
}

void glIndexi ( GLint a )
{
	writeGlCommand( ACW_INDEXI );
	writeValue( (void*)&a, sizeof(GLint) );
}

void glIndexiv ( GLint* a )
{
	writeGlCommand( ACW_INDEXIV );
}

void glIndexs ( GLshort a )
{
	writeGlCommand( ACW_INDEXS );
}

void glIndexsv ( GLshort* a )
{
	writeGlCommand( ACW_INDEXSV );
}

void glIndexub ( GLubyte a )
{
	writeGlCommand( ACW_INDEXUB );
}

void glIndexubv ( GLubyte* a )
{
	writeGlCommand( ACW_INDEXUBV );
}

void glInitNames (  )
{
	writeGlCommand( ACW_INITNAMES );
}

void glInstrumentsBufferSGIX ( GLsizei a, GLint* b )
{
	writeGlCommand( ACW_INSTRUMENTSBUFFERSGIX );
}

void glInterleavedArrays ( GLenum a, GLsizei b, GLvoid* c )
{
	writeGlCommand( ACW_INTERLEAVEDARRAYS );
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

void glLightModelfv ( GLenum a, GLfloat* b )
{
	writeGlCommand( ACW_LIGHTMODELFV );
}

void glLightModeli ( GLenum a, GLint b )
{
	writeGlCommand( ACW_LIGHTMODELI );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLint) );
}

void glLightModeliv ( GLenum a, GLint* b )
{
	writeGlCommand( ACW_LIGHTMODELIV );
}

void glLightf ( GLenum a, GLenum b, GLfloat c )
{
	writeGlCommand( ACW_LIGHTF );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLfloat) );
}

void glLightfv ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_LIGHTFV );
}

void glLighti ( GLenum a, GLenum b, GLint c )
{
	writeGlCommand( ACW_LIGHTI );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLint) );
}

void glLightiv ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_LIGHTIV );
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

void glListParameterfvSGIX ( GLuint a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_LISTPARAMETERFVSGIX );
}

void glListParameteriSGIX ( GLuint a, GLenum b, GLint c )
{
	writeGlCommand( ACW_LISTPARAMETERISGIX );
	writeValue( (void*)&a, sizeof(GLuint) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLint) );
}

void glListParameterivSGIX ( GLuint a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_LISTPARAMETERIVSGIX );
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

void glLoadMatrixd ( GLdouble* a )
{
	writeGlCommand( ACW_LOADMATRIXD );
}

void glLoadMatrixf ( GLfloat* a )
{
	writeGlCommand( ACW_LOADMATRIXF );
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

void glMap1d ( GLenum a, GLdouble b, GLdouble c, GLint d, GLint e, GLdouble* f )
{
	writeGlCommand( ACW_MAP1D );
}

void glMap1f ( GLenum a, GLfloat b, GLfloat c, GLint d, GLint e, GLfloat* f )
{
	writeGlCommand( ACW_MAP1F );
}

void glMap2d ( GLenum a, GLdouble b, GLdouble c, GLint d, GLint e, GLdouble f, GLdouble g, GLint h, GLint i, GLdouble* j )
{
	writeGlCommand( ACW_MAP2D );
}

void glMap2f ( GLenum a, GLfloat b, GLfloat c, GLint d, GLint e, GLfloat f, GLfloat g, GLint h, GLint i, GLfloat* j )
{
	writeGlCommand( ACW_MAP2F );
}

void glMapGrid1d ( GLint a, GLdouble b, GLdouble c )
{
	writeGlCommand( ACW_MAPGRID1D );
}

void glMapGrid1f ( GLint a, GLfloat b, GLfloat c )
{
	writeGlCommand( ACW_MAPGRID1F );
}

void glMapGrid2d ( GLint a, GLdouble b, GLdouble c, GLint d, GLdouble e, GLdouble f )
{
	writeGlCommand( ACW_MAPGRID2D );
}

void glMapGrid2f ( GLint a, GLfloat b, GLfloat c, GLint d, GLfloat e, GLfloat f )
{
	writeGlCommand( ACW_MAPGRID2F );
}

void glMaterialf ( GLenum a, GLenum b, GLfloat c )
{
	writeGlCommand( ACW_MATERIALF );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLfloat) );
}

void glMaterialfv ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_MATERIALFV );
}

void glMateriali ( GLenum a, GLenum b, GLint c )
{
	writeGlCommand( ACW_MATERIALI );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLint) );
}

void glMaterialiv ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_MATERIALIV );
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

void glMultMatrixd ( GLdouble* a )
{
	writeGlCommand( ACW_MULTMATRIXD );
}

void glMultMatrixf ( GLfloat* a )
{
	writeGlCommand( ACW_MULTMATRIXF );
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

void glNormalPointer ( GLenum a, GLsizei b, GLvoid* c )
{
	writeGlCommand( ACW_NORMALPOINTER );
}

void glNormalPointerEXT ( GLenum a, GLsizei b, GLsizei c, GLvoid* d )
{
	writeGlCommand( ACW_NORMALPOINTEREXT );
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

void glPixelMapfv ( GLenum a, GLint b, GLfloat* c )
{
	writeGlCommand( ACW_PIXELMAPFV );
}

void glPixelMapuiv ( GLenum a, GLint b, GLuint* c )
{
	writeGlCommand( ACW_PIXELMAPUIV );
}

void glPixelMapusv ( GLenum a, GLint b, GLushort* c )
{
	writeGlCommand( ACW_PIXELMAPUSV );
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

void glPointParameterfvSGIS ( GLenum a, GLfloat* b )
{
	writeGlCommand( ACW_POINTPARAMETERFVSGIS );
}

void glPointSize ( GLfloat a )
{
	writeGlCommand( ACW_POINTSIZE );
	writeValue( (void*)&a, sizeof(GLfloat) );
}

GLint glPollInstrumentsSGIX ( GLint* a )
{
	writeGlCommand( ACW_POLLINSTRUMENTSSGIX );
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

void glPolygonStipple ( GLubyte* a )
{
	writeGlCommand( ACW_POLYGONSTIPPLE );
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

void glPrioritizeTextures ( GLsizei a, GLuint* b, GLclampf* c )
{
	writeGlCommand( ACW_PRIORITIZETEXTURES );
}

void glPrioritizeTexturesEXT ( GLsizei a, GLuint* b, GLclampf* c )
{
	writeGlCommand( ACW_PRIORITIZETEXTURESEXT );
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

void glReadPixels ( GLint a, GLint b, GLsizei c, GLsizei d, GLenum e, GLenum f, GLvoid* g )
{
	writeGlCommand( ACW_READPIXELS );
}

void glRectd ( GLdouble a, GLdouble b, GLdouble c, GLdouble d )
{
	writeGlCommand( ACW_RECTD );
	writeValue( (void*)&a, sizeof(GLdouble) );
	writeValue( (void*)&b, sizeof(GLdouble) );
	writeValue( (void*)&c, sizeof(GLdouble) );
	writeValue( (void*)&d, sizeof(GLdouble) );
}

void glRectdv ( GLdouble* a, GLdouble* b )
{
	writeGlCommand( ACW_RECTDV );
}

void glRectf ( GLfloat a, GLfloat b, GLfloat c, GLfloat d )
{
	writeGlCommand( ACW_RECTF );
	writeValue( (void*)&a, sizeof(GLfloat) );
	writeValue( (void*)&b, sizeof(GLfloat) );
	writeValue( (void*)&c, sizeof(GLfloat) );
	writeValue( (void*)&d, sizeof(GLfloat) );
}

void glRectfv ( GLfloat* a, GLfloat* b )
{
	writeGlCommand( ACW_RECTFV );
}

void glRecti ( GLint a, GLint b, GLint c, GLint d )
{
	writeGlCommand( ACW_RECTI );
	writeValue( (void*)&a, sizeof(GLint) );
	writeValue( (void*)&b, sizeof(GLint) );
	writeValue( (void*)&c, sizeof(GLint) );
	writeValue( (void*)&d, sizeof(GLint) );
}

void glRectiv ( GLint* a, GLint* b )
{
	writeGlCommand( ACW_RECTIV );
}

void glRects ( GLshort a, GLshort b, GLshort c, GLshort d )
{
	writeGlCommand( ACW_RECTS );
	writeValue( (void*)&a, sizeof(GLshort) );
	writeValue( (void*)&b, sizeof(GLshort) );
	writeValue( (void*)&c, sizeof(GLshort) );
	writeValue( (void*)&d, sizeof(GLshort) );
}

void glRectsv ( GLshort* a, GLshort* b )
{
	writeGlCommand( ACW_RECTSV );
}

void glReferencePlaneSGIX ( GLdouble* a )
{
	writeGlCommand( ACW_REFERENCEPLANESGIX );
}

GLint glRenderMode ( GLenum a )
{
	writeGlCommand( ACW_RENDERMODE );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glResetHistogram ( GLenum a )
{
	writeGlCommand( ACW_RESETHISTOGRAM );
}

void glResetHistogramEXT ( GLenum a )
{
	writeGlCommand( ACW_RESETHISTOGRAMEXT );
}

void glResetMinmax ( GLenum a )
{
	writeGlCommand( ACW_RESETMINMAX );
}

void glResetMinmaxEXT ( GLenum a )
{
	writeGlCommand( ACW_RESETMINMAXEXT );
}

void glRotated ( GLdouble a, GLdouble b, GLdouble c, GLdouble d )
{
	writeGlCommand( ACW_ROTATED );
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

void glSelectBuffer ( GLsizei a, GLuint* b )
{
	writeGlCommand( ACW_SELECTBUFFER );
}

void glSeparableFilter2D ( GLenum a, GLenum b, GLsizei c, GLsizei d, GLenum e, GLenum f, GLvoid* g, GLvoid* h )
{
	writeGlCommand( ACW_SEPARABLEFILTER2D );
}

void glSeparableFilter2DEXT ( GLenum a, GLenum b, GLsizei c, GLsizei d, GLenum e, GLenum f, GLvoid* g, GLvoid* h )
{
	writeGlCommand( ACW_SEPARABLEFILTER2DEXT );
}

void glShadeModel ( GLenum a )
{
	writeGlCommand( ACW_SHADEMODEL );
	writeValue( (void*)&a, sizeof(GLenum) );
}

void glSharpenTexFuncSGIS ( GLenum a, GLsizei b, GLfloat* c )
{
	writeGlCommand( ACW_SHARPENTEXFUNCSGIS );
}

void glSpriteParameterfSGIX ( GLenum a, GLfloat b )
{
	writeGlCommand( ACW_SPRITEPARAMETERFSGIX );
}

void glSpriteParameterfvSGIX ( GLenum a, GLfloat* b )
{
	writeGlCommand( ACW_SPRITEPARAMETERFVSGIX );
}

void glSpriteParameteriSGIX ( GLenum a, GLint b )
{
	writeGlCommand( ACW_SPRITEPARAMETERISGIX );
}

void glSpriteParameterivSGIX ( GLenum a, GLint* b )
{
	writeGlCommand( ACW_SPRITEPARAMETERIVSGIX );
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

void glTexCoordPointer ( GLint a, GLenum b, GLsizei c, GLvoid* d )
{
	writeGlCommand( ACW_TEXCOORDPOINTER );
}

void glTexCoordPointerEXT ( GLint a, GLenum b, GLsizei c, GLsizei d, GLvoid* e )
{
	writeGlCommand( ACW_TEXCOORDPOINTEREXT );
}

void glTexEnvf ( GLenum a, GLenum b, GLfloat c )
{
	writeGlCommand( ACW_TEXENVF );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLfloat) );
}

void glTexEnvfv ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_TEXENVFV );
}

void glTexEnvi ( GLenum a, GLenum b, GLint c )
{
	writeGlCommand( ACW_TEXENVI );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLint) );
}

void glTexEnviv ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_TEXENVIV );
}

void glTexFilterFuncSGIS ( GLenum a, GLenum b, GLsizei c, GLfloat* d )
{
	writeGlCommand( ACW_TEXFILTERFUNCSGIS );
}

void glTexGend ( GLenum a, GLenum b, GLdouble c )
{
	writeGlCommand( ACW_TEXGEND );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLdouble) );
}

void glTexGendv ( GLenum a, GLenum b, GLdouble* c )
{
	writeGlCommand( ACW_TEXGENDV );
}

void glTexGenf ( GLenum a, GLenum b, GLfloat c )
{
	writeGlCommand( ACW_TEXGENF );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLfloat) );
}

void glTexGenfv ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_TEXGENFV );
}

void glTexGeni ( GLenum a, GLenum b, GLint c )
{
	writeGlCommand( ACW_TEXGENI );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLint) );
}

void glTexGeniv ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_TEXGENIV );
}

void glTexImage1D ( GLenum a, GLint b, GLint c, GLsizei d, GLint e, GLenum f, GLenum g, GLvoid* h )
{
	writeGlCommand( ACW_TEXIMAGE1D );
}

void glTexImage2D ( GLenum a, GLint b, GLint c, GLsizei d, GLsizei e, GLint f, GLenum g, GLenum h, GLvoid* i )
{
	writeGlCommand( ACW_TEXIMAGE2D );
}

void glTexImage3D ( GLenum a, GLint b, GLenum c, GLsizei d, GLsizei e, GLsizei f, GLint g, GLenum h, GLenum i, GLvoid* j )
{
	writeGlCommand( ACW_TEXIMAGE3D );
}

void glTexImage3DEXT ( GLenum a, GLint b, GLenum c, GLsizei d, GLsizei e, GLsizei f, GLint g, GLenum h, GLenum i, GLvoid* j )
{
	writeGlCommand( ACW_TEXIMAGE3DEXT );
}

void glTexImage4DSGIS ( GLenum a, GLint b, GLenum c, GLsizei d, GLsizei e, GLsizei f, GLsizei g, GLint h, GLenum i, GLenum j, GLvoid* k )
{
	writeGlCommand( ACW_TEXIMAGE4DSGIS );
}

void glTexParameterf ( GLenum a, GLenum b, GLfloat c )
{
	writeGlCommand( ACW_TEXPARAMETERF );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLfloat) );
}

void glTexParameterfv ( GLenum a, GLenum b, GLfloat* c )
{
	writeGlCommand( ACW_TEXPARAMETERFV );
}

void glTexParameteri ( GLenum a, GLenum b, GLint c )
{
	writeGlCommand( ACW_TEXPARAMETERI );
	writeValue( (void*)&a, sizeof(GLenum) );
	writeValue( (void*)&b, sizeof(GLenum) );
	writeValue( (void*)&c, sizeof(GLint) );
}

void glTexParameteriv ( GLenum a, GLenum b, GLint* c )
{
	writeGlCommand( ACW_TEXPARAMETERIV );
}

void glTexSubImage1D ( GLenum a, GLint b, GLint c, GLsizei d, GLenum e, GLenum f, GLvoid* g )
{
	writeGlCommand( ACW_TEXSUBIMAGE1D );
}

void glTexSubImage1DEXT ( GLenum a, GLint b, GLint c, GLsizei d, GLenum e, GLenum f, GLvoid* g )
{
	writeGlCommand( ACW_TEXSUBIMAGE1DEXT );
}

void glTexSubImage2D ( GLenum a, GLint b, GLint c, GLint d, GLsizei e, GLsizei f, GLenum g, GLenum h, GLvoid* i )
{
	writeGlCommand( ACW_TEXSUBIMAGE2D );
}

void glTexSubImage2DEXT ( GLenum a, GLint b, GLint c, GLint d, GLsizei e, GLsizei f, GLenum g, GLenum h, GLvoid* i )
{
	writeGlCommand( ACW_TEXSUBIMAGE2DEXT );
}

void glTexSubImage3D ( GLenum a, GLint b, GLint c, GLint d, GLint e, GLsizei f, GLsizei g, GLsizei h, GLenum i, GLenum j, GLvoid* k )
{
	writeGlCommand( ACW_TEXSUBIMAGE3D );
}

void glTexSubImage3DEXT ( GLenum a, GLint b, GLint c, GLint d, GLint e, GLsizei f, GLsizei g, GLsizei h, GLenum i, GLenum j, GLvoid* k )
{
	writeGlCommand( ACW_TEXSUBIMAGE3DEXT );
}

void glTexSubImage4DSGIS ( GLenum a, GLint b, GLint c, GLint d, GLint e, GLint f, GLsizei g, GLsizei h, GLsizei i, GLsizei j, GLenum k, GLenum l, GLvoid* m )
{
	writeGlCommand( ACW_TEXSUBIMAGE4DSGIS );
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

void glVertexPointer ( GLint a, GLenum b, GLsizei c, GLvoid* d )
{
	writeGlCommand( ACW_VERTEXPOINTER );
}

void glVertexPointerEXT ( GLint a, GLenum b, GLsizei c, GLsizei d, GLvoid* e )
{
	writeGlCommand( ACW_VERTEXPOINTEREXT );
}

void glViewport ( GLint a, GLint b, GLsizei c, GLsizei d )
{
	writeGlCommand( ACW_VIEWPORT );
	writeValue( (void*)&a, sizeof(GLint) );
	writeValue( (void*)&b, sizeof(GLint) );
	writeValue( (void*)&c, sizeof(GLsizei) );
	writeValue( (void*)&d, sizeof(GLsizei) );
}

