
#include "acGLUnwrapper.h"

glUnwrapper::glUnwrapper()
{
  buffer = NULL;
  bufferSize = 0;
  bufferAllocSize = 0;
}

void glUnwrapper::setBuffer( unsigned char* B, long Bsize )
{
  while ( bufferAllocSize <= Bsize )
    {
      if ( bufferAllocSize==0 )
	bufferAllocSize = 32;
      bufferAllocSize *= 2;
      buffer = (unsigned char*)realloc( buffer, sizeof(char)*bufferAllocSize );
    }
  bufferSize = Bsize;
  memcpy( buffer, B, Bsize );
}

void* glUnwrapper::getBuffer() 
{ 
  return buffer; 
}

long glUnwrapper::getBufferSize() 
{ 
  return bufferSize;
}




















void glUnwrapper::Apply()
{
long i=0;
GLenum* E;
while( i < bufferSize )
{
glCommand* G = (glCommand*) &buffer[i];
switch( *G )
{

case ACW_ACCUM:
 i += sizeof(glCommand);
 GLenum* a0 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* b0 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glAccum( *a0, *b0 );
 break;

case ACW_ALPHAFUNC:
 i += sizeof(glCommand);
 GLenum* a1 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLclampf* b1 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 glAlphaFunc( *a1, *b1 );
 break;

case ACW_BEGIN:
 i += sizeof(glCommand);
 GLenum* a2 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glBegin( *a2 );
 break;

case ACW_BLENDCOLOR:
 i += sizeof(glCommand);
 GLclampf* a3 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 GLclampf* b3 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 GLclampf* c3 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 GLclampf* d3 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 glBlendColor( *a3, *b3, *c3, *d3 );
 break;

case ACW_BLENDEQUATION:
 i += sizeof(glCommand);
 GLenum* a4 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glBlendEquation( *a4 );
 break;

case ACW_BLENDEQUATIONEXT:
 i += sizeof(glCommand);
 GLenum* a5 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glBlendEquationEXT( *a5 );
 break;

case ACW_BLENDFUNC:
 i += sizeof(glCommand);
 GLenum* a6 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b6 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glBlendFunc( *a6, *b6 );
 break;

case ACW_CALLLIST:
 i += sizeof(glCommand);
 GLuint* a7 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glCallList( *a7 );
 break;

case ACW_CLEAR:
 i += sizeof(glCommand);
 GLbitfield* a8 = (GLbitfield*) &buffer[i];
 i += sizeof(GLbitfield);
 glClear( *a8 );
 break;

case ACW_CLEARACCUM:
 i += sizeof(glCommand);
 GLfloat* a9 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* b9 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* c9 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* d9 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glClearAccum( *a9, *b9, *c9, *d9 );
 break;

case ACW_CLEARCOLOR:
 i += sizeof(glCommand);
 GLclampf* a10 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 GLclampf* b10 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 GLclampf* c10 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 GLclampf* d10 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 glClearColor( *a10, *b10, *c10, *d10 );
 break;

case ACW_CLEARDEPTH:
 i += sizeof(glCommand);
 GLclampd* a11 = (GLclampd*) &buffer[i];
 i += sizeof(GLclampd);
 glClearDepth( *a11 );
 break;

case ACW_CLEARINDEX:
 i += sizeof(glCommand);
 GLfloat* a12 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glClearIndex( *a12 );
 break;

case ACW_CLEARSTENCIL:
 i += sizeof(glCommand);
 GLint* a13 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glClearStencil( *a13 );
 break;

case ACW_COLOR3B:
 i += sizeof(glCommand);
 GLbyte* a14 = (GLbyte*) &buffer[i];
 i += sizeof(GLbyte)*3;
 glColor3bv( a14 );
 break;

case ACW_COLOR3BV:
 i += sizeof(glCommand);
 GLbyte* a15 = (GLbyte*) &buffer[i];
 i += sizeof(GLbyte)*3;
 glColor3bv( a15 );
 break;

case ACW_COLOR3D:
 i += sizeof(glCommand);
 GLdouble* a16 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glColor3dv( a16 );
 break;

case ACW_COLOR3DV:
 i += sizeof(glCommand);
 GLdouble* a17 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glColor3dv( a17 );
 break;

case ACW_COLOR3F:
 i += sizeof(glCommand);
 GLfloat* a18 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glColor3fv( a18 );
 break;

case ACW_COLOR3FV:
 i += sizeof(glCommand);
 GLfloat* a19 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glColor3fv( a19 );
 break;

case ACW_COLOR3I:
 i += sizeof(glCommand);
 GLint* a20 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glColor3iv( a20 );
 break;

case ACW_COLOR3IV:
 i += sizeof(glCommand);
 GLint* a21 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glColor3iv( a21 );
 break;

case ACW_COLOR3S:
 i += sizeof(glCommand);
 GLshort* a22 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glColor3sv( a22 );
 break;

case ACW_COLOR3SV:
 i += sizeof(glCommand);
 GLshort* a23 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glColor3sv( a23 );
 break;

case ACW_COLOR3UB:
 i += sizeof(glCommand);
 GLubyte* a24 = (GLubyte*) &buffer[i];
 i += sizeof(GLubyte);
 GLubyte* b24 = (GLubyte*) &buffer[i];
 i += sizeof(GLubyte);
 GLubyte* c24 = (GLubyte*) &buffer[i];
 i += sizeof(GLubyte);
 glColor3ub( *a24, *b24, *c24 );
 break;

case ACW_COLOR3UBV:
 i += sizeof(glCommand);
 GLubyte** a25 = (GLubyte**) &buffer[i];
 i += sizeof(GLubyte*);
 glColor3ubv( *a25 );
 break;

case ACW_COLOR3UI:
 i += sizeof(glCommand);
 GLuint* a26 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLuint* b26 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLuint* c26 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glColor3ui( *a26, *b26, *c26 );
 break;

case ACW_COLOR3UIV:
 i += sizeof(glCommand);
 GLuint** a27 = (GLuint**) &buffer[i];
 i += sizeof(GLuint*);
 glColor3uiv( *a27 );
 break;

case ACW_COLOR3US:
 i += sizeof(glCommand);
 GLushort* a28 = (GLushort*) &buffer[i];
 i += sizeof(GLushort);
 GLushort* b28 = (GLushort*) &buffer[i];
 i += sizeof(GLushort);
 GLushort* c28 = (GLushort*) &buffer[i];
 i += sizeof(GLushort);
 glColor3us( *a28, *b28, *c28 );
 break;

case ACW_COLOR3USV:
 i += sizeof(glCommand);
 GLushort** a29 = (GLushort**) &buffer[i];
 i += sizeof(GLushort*);
 glColor3usv( *a29 );
 break;

case ACW_COLOR4B:
 i += sizeof(glCommand);
 GLbyte* a30 = (GLbyte*) &buffer[i];
 i += sizeof(GLbyte)*4;
 glColor4bv( a30 );
 break;

case ACW_COLOR4BV:
 i += sizeof(glCommand);
 GLbyte* a31 = (GLbyte*) &buffer[i];
 i += sizeof(GLbyte)*4;
 glColor4bv( a31 );
 break;

case ACW_COLOR4D:
 i += sizeof(glCommand);
 GLdouble* a32 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*4;
 glColor4dv( a32 );
 break;

case ACW_COLOR4DV:
 i += sizeof(glCommand);
 GLdouble* a33 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*4;
 glColor4dv( a33 );
 break;

case ACW_COLOR4F:
 i += sizeof(glCommand);
 GLfloat* a34 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*4;
 glColor4fv( a34 );
 break;

case ACW_COLOR4FV:
 i += sizeof(glCommand);
 GLfloat* a35 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*4;
 glColor4fv( a35 );
 break;

case ACW_COLOR4I:
 i += sizeof(glCommand);
 GLint* a36 = (GLint*) &buffer[i];
 i += sizeof(GLint)*4;
 glColor4iv( a36 );
 break;

case ACW_COLOR4IV:
 i += sizeof(glCommand);
 GLint* a37 = (GLint*) &buffer[i];
 i += sizeof(GLint)*4;
 glColor4iv( a37 );
 break;

case ACW_COLOR4S:
 i += sizeof(glCommand);
 GLshort* a38 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*4;
 glColor4sv( a38 );
 break;

case ACW_COLOR4SV:
 i += sizeof(glCommand);
 GLshort* a39 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*4;
 glColor4sv( a39 );
 break;

case ACW_COLOR4UB:
 i += sizeof(glCommand);
 GLubyte* a40 = (GLubyte*) &buffer[i];
 i += sizeof(GLubyte);
 GLubyte* b40 = (GLubyte*) &buffer[i];
 i += sizeof(GLubyte);
 GLubyte* c40 = (GLubyte*) &buffer[i];
 i += sizeof(GLubyte);
 GLubyte* d40 = (GLubyte*) &buffer[i];
 i += sizeof(GLubyte);
 glColor4ub( *a40, *b40, *c40, *d40 );
 break;

case ACW_COLOR4UBV:
 i += sizeof(glCommand);
 GLubyte** a41 = (GLubyte**) &buffer[i];
 i += sizeof(GLubyte*);
 glColor4ubv( *a41 );
 break;

case ACW_COLOR4UI:
 i += sizeof(glCommand);
 GLuint* a42 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLuint* b42 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLuint* c42 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLuint* d42 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glColor4ui( *a42, *b42, *c42, *d42 );
 break;

case ACW_COLOR4UIV:
 i += sizeof(glCommand);
 GLuint** a43 = (GLuint**) &buffer[i];
 i += sizeof(GLuint*);
 glColor4uiv( *a43 );
 break;

case ACW_COLOR4US:
 i += sizeof(glCommand);
 GLushort* a44 = (GLushort*) &buffer[i];
 i += sizeof(GLushort);
 GLushort* b44 = (GLushort*) &buffer[i];
 i += sizeof(GLushort);
 GLushort* c44 = (GLushort*) &buffer[i];
 i += sizeof(GLushort);
 GLushort* d44 = (GLushort*) &buffer[i];
 i += sizeof(GLushort);
 glColor4us( *a44, *b44, *c44, *d44 );
 break;

case ACW_COLOR4USV:
 i += sizeof(glCommand);
 GLushort** a45 = (GLushort**) &buffer[i];
 i += sizeof(GLushort*);
 glColor4usv( *a45 );
 break;

case ACW_COLORMASK:
 i += sizeof(glCommand);
 GLboolean* a46 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 GLboolean* b46 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 GLboolean* c46 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 GLboolean* d46 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 glColorMask( *a46, *b46, *c46, *d46 );
 break;

case ACW_COLORMATERIAL:
 i += sizeof(glCommand);
 GLenum* a47 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b47 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glColorMaterial( *a47, *b47 );
 break;

case ACW_COPYPIXELS:
 i += sizeof(glCommand);
 GLint* a48 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* b48 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLsizei* c48 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 GLsizei* d48 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 GLenum* e48 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glCopyPixels( *a48, *b48, *c48, *d48, *e48 );
 break;

case ACW_CULLFACE:
 i += sizeof(glCommand);
 GLenum* a49 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glCullFace( *a49 );
 break;

case ACW_DEFORMSGIX:
 i += sizeof(glCommand);
 GLbitfield* a50 = (GLbitfield*) &buffer[i];
 i += sizeof(GLbitfield);
 glDeformSGIX( *a50 );
 break;

case ACW_DELETELISTS:
 i += sizeof(glCommand);
 GLuint* a51 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLsizei* b51 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 glDeleteLists( *a51, *b51 );
 break;

case ACW_DEPTHFUNC:
 i += sizeof(glCommand);
 GLenum* a52 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glDepthFunc( *a52 );
 break;

case ACW_DEPTHMASK:
 i += sizeof(glCommand);
 GLboolean* a53 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 glDepthMask( *a53 );
 break;

case ACW_DEPTHRANGE:
 i += sizeof(glCommand);
 GLclampd* a54 = (GLclampd*) &buffer[i];
 i += sizeof(GLclampd);
 GLclampd* b54 = (GLclampd*) &buffer[i];
 i += sizeof(GLclampd);
 glDepthRange( *a54, *b54 );
 break;

case ACW_DISABLE:
 i += sizeof(glCommand);
 GLenum* a55 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glDisable( *a55 );
 break;

case ACW_DISABLECLIENTSTATE:
 i += sizeof(glCommand);
 GLenum* a56 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glDisableClientState( *a56 );
 break;

case ACW_DRAWARRAYS:
 i += sizeof(glCommand);
 GLenum* a57 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b57 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLsizei* c57 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 glDrawArrays( *a57, *b57, *c57 );
 break;

case ACW_DRAWARRAYSEXT:
 i += sizeof(glCommand);
 GLenum* a58 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b58 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLsizei* c58 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 glDrawArraysEXT( *a58, *b58, *c58 );
 break;

case ACW_DRAWBUFFER:
 i += sizeof(glCommand);
 GLenum* a59 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glDrawBuffer( *a59 );
 break;

case ACW_EDGEFLAG:
 i += sizeof(glCommand);
 GLboolean* a60 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 glEdgeFlag( *a60 );
 break;

case ACW_ENABLE:
 i += sizeof(glCommand);
 GLenum* a61 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glEnable( *a61 );
 break;

case ACW_ENABLECLIENTSTATE:
 i += sizeof(glCommand);
 GLenum* a62 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glEnableClientState( *a62 );
 break;

case ACW_END:
 i += sizeof(glCommand);
 glEnd( );
 break;

case ACW_ENDLIST:
 i += sizeof(glCommand);
 glEndList( );
 break;

case ACW_EVALCOORD1D:
 i += sizeof(glCommand);
 GLdouble* a65 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*1;
 glEvalCoord1dv( a65 );
 break;

case ACW_EVALCOORD1DV:
 i += sizeof(glCommand);
 GLdouble* a66 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*1;
 glEvalCoord1dv( a66 );
 break;

case ACW_EVALCOORD1F:
 i += sizeof(glCommand);
 GLfloat* a67 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*1;
 glEvalCoord1fv( a67 );
 break;

case ACW_EVALCOORD1FV:
 i += sizeof(glCommand);
 GLfloat* a68 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*1;
 glEvalCoord1fv( a68 );
 break;

case ACW_EVALCOORD2D:
 i += sizeof(glCommand);
 GLdouble* a69 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*2;
 glEvalCoord2dv( a69 );
 break;

case ACW_EVALCOORD2DV:
 i += sizeof(glCommand);
 GLdouble* a70 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*2;
 glEvalCoord2dv( a70 );
 break;

case ACW_EVALCOORD2F:
 i += sizeof(glCommand);
 GLfloat* a71 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*2;
 glEvalCoord2fv( a71 );
 break;

case ACW_EVALCOORD2FV:
 i += sizeof(glCommand);
 GLfloat* a72 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*2;
 glEvalCoord2fv( a72 );
 break;

case ACW_EVALMESH1:
 i += sizeof(glCommand);
 GLenum* a73 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b73 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* c73 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glEvalMesh1( *a73, *b73, *c73 );
 break;

case ACW_EVALMESH2:
 i += sizeof(glCommand);
 GLenum* a74 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b74 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* c74 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* d74 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* e74 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glEvalMesh2( *a74, *b74, *c74, *d74, *e74 );
 break;

case ACW_EVALPOINT1:
 i += sizeof(glCommand);
 GLint* a75 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glEvalPoint1( *a75 );
 break;

case ACW_EVALPOINT2:
 i += sizeof(glCommand);
 GLint* a76 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* b76 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glEvalPoint2( *a76, *b76 );
 break;

case ACW_FLUSH:
 i += sizeof(glCommand);
 glFlush( );
 break;

case ACW_FLUSHRASTERSGIX:
 i += sizeof(glCommand);
 glFlushRasterSGIX( );
 break;

case ACW_FOGF:
 i += sizeof(glCommand);
 GLenum* a79 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* b79 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glFogf( *a79, *b79 );
 break;

case ACW_FOGI:
 i += sizeof(glCommand);
 GLenum* a80 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b80 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glFogi( *a80, *b80 );
 break;

case ACW_FRAMEZOOMSGIX:
 i += sizeof(glCommand);
 GLint* a81 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glFrameZoomSGIX( *a81 );
 break;

case ACW_FRONTFACE:
 i += sizeof(glCommand);
 GLenum* a82 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glFrontFace( *a82 );
 break;

case ACW_FRUSTUM:
 i += sizeof(glCommand);
 GLdouble* a83 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* b83 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* c83 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* d83 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* e83 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* f83 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 glFrustum( *a83, *b83, *c83, *d83, *e83, *f83 );
 break;

case ACW_GENLISTS:
 i += sizeof(glCommand);
 GLsizei* a84 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 glGenLists( *a84 );
 break;

case ACW_GENTEXTURES:
 i += sizeof(glCommand);
 GLsizei* a85 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 GLuint** b85 = (GLuint**) &buffer[i];
 i += sizeof(GLuint*);
 glGenTextures( *a85, *b85 );
 break;

case ACW_GETERROR:
 i += sizeof(glCommand);
 glGetError( );
 break;

case ACW_HINT:
 i += sizeof(glCommand);
 GLenum* a87 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b87 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glHint( *a87, *b87 );
 break;

case ACW_HISTOGRAM:
 i += sizeof(glCommand);
 GLenum* a88 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLsizei* b88 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 GLenum* c88 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLboolean* d88 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 glHistogram( *a88, *b88, *c88, *d88 );
 break;

case ACW_HISTOGRAMEXT:
 i += sizeof(glCommand);
 GLenum* a89 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLsizei* b89 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 GLenum* c89 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLboolean* d89 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 glHistogramEXT( *a89, *b89, *c89, *d89 );
 break;

case ACW_INDEXMASK:
 i += sizeof(glCommand);
 GLuint* a90 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glIndexMask( *a90 );
 break;

case ACW_INDEXD:
 i += sizeof(glCommand);
 GLdouble* a91 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 glIndexd( *a91 );
 break;

case ACW_INDEXF:
 i += sizeof(glCommand);
 GLfloat* a92 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glIndexf( *a92 );
 break;

case ACW_INDEXI:
 i += sizeof(glCommand);
 GLint* a93 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glIndexi( *a93 );
 break;

case ACW_INITNAMES:
 i += sizeof(glCommand);
 glInitNames( );
 break;

case ACW_ISENABLED:
 i += sizeof(glCommand);
 GLenum* a95 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glIsEnabled( *a95 );
 break;

case ACW_ISLIST:
 i += sizeof(glCommand);
 GLuint* a96 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glIsList( *a96 );
 break;

case ACW_ISTEXTURE:
 i += sizeof(glCommand);
 GLuint* a97 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glIsTexture( *a97 );
 break;

case ACW_ISTEXTUREEXT:
 i += sizeof(glCommand);
 GLuint* a98 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glIsTextureEXT( *a98 );
 break;

case ACW_LIGHTMODELF:
 i += sizeof(glCommand);
 GLenum* a99 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* b99 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glLightModelf( *a99, *b99 );
 break;

case ACW_LIGHTMODELI:
 i += sizeof(glCommand);
 GLenum* a100 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b100 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glLightModeli( *a100, *b100 );
 break;

case ACW_LIGHTF:
 i += sizeof(glCommand);
 GLenum* a101 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b101 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* c101 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glLightf( *a101, *b101, *c101 );
 break;

case ACW_LIGHTI:
 i += sizeof(glCommand);
 GLenum* a102 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b102 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* c102 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glLighti( *a102, *b102, *c102 );
 break;

case ACW_LINESTIPPLE:
 i += sizeof(glCommand);
 GLint* a103 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLushort* b103 = (GLushort*) &buffer[i];
 i += sizeof(GLushort);
 glLineStipple( *a103, *b103 );
 break;

case ACW_LINEWIDTH:
 i += sizeof(glCommand);
 GLfloat* a104 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glLineWidth( *a104 );
 break;

case ACW_LISTBASE:
 i += sizeof(glCommand);
 GLuint* a105 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glListBase( *a105 );
 break;

case ACW_LISTPARAMETERFSGIX:
 i += sizeof(glCommand);
 GLuint* a106 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLenum* b106 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* c106 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glListParameterfSGIX( *a106, *b106, *c106 );
 break;

case ACW_LISTPARAMETERISGIX:
 i += sizeof(glCommand);
 GLuint* a107 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLenum* b107 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* c107 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glListParameteriSGIX( *a107, *b107, *c107 );
 break;

case ACW_LOADIDENTITY:
 i += sizeof(glCommand);
 glLoadIdentity( );
 break;

case ACW_LOADIDENTITYDEFORMATIONMAPSGIX:
 i += sizeof(glCommand);
 GLbitfield* a109 = (GLbitfield*) &buffer[i];
 i += sizeof(GLbitfield);
 glLoadIdentityDeformationMapSGIX( *a109 );
 break;

case ACW_LOADNAME:
 i += sizeof(glCommand);
 GLuint* a110 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glLoadName( *a110 );
 break;

case ACW_LOGICOP:
 i += sizeof(glCommand);
 GLenum* a111 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glLogicOp( *a111 );
 break;

case ACW_MATERIALF:
 i += sizeof(glCommand);
 GLenum* a112 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b112 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* c112 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glMaterialf( *a112, *b112, *c112 );
 break;

case ACW_MATERIALI:
 i += sizeof(glCommand);
 GLenum* a113 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b113 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* c113 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glMateriali( *a113, *b113, *c113 );
 break;

case ACW_MATRIXMODE:
 i += sizeof(glCommand);
 GLenum* a114 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glMatrixMode( *a114 );
 break;

case ACW_MINMAX:
 i += sizeof(glCommand);
 GLenum* a115 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b115 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLboolean* c115 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 glMinmax( *a115, *b115, *c115 );
 break;

case ACW_MINMAXEXT:
 i += sizeof(glCommand);
 GLenum* a116 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b116 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLboolean* c116 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 glMinmaxEXT( *a116, *b116, *c116 );
 break;

case ACW_NEWLIST:
 i += sizeof(glCommand);
 GLuint* a117 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLenum* b117 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glNewList( *a117, *b117 );
 break;

case ACW_NORMAL3B:
 i += sizeof(glCommand);
 GLbyte* a118 = (GLbyte*) &buffer[i];
 i += sizeof(GLbyte)*3;
 glNormal3bv( a118 );
 break;

case ACW_NORMAL3BV:
 i += sizeof(glCommand);
 GLbyte* a119 = (GLbyte*) &buffer[i];
 i += sizeof(GLbyte)*3;
 glNormal3bv( a119 );
 break;

case ACW_NORMAL3D:
 i += sizeof(glCommand);
 GLdouble* a120 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glNormal3dv( a120 );
 break;

case ACW_NORMAL3DV:
 i += sizeof(glCommand);
 GLdouble* a121 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glNormal3dv( a121 );
 break;

case ACW_NORMAL3F:
 i += sizeof(glCommand);
 GLfloat* a122 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glNormal3fv( a122 );
 break;

case ACW_NORMAL3FV:
 i += sizeof(glCommand);
 GLfloat* a123 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glNormal3fv( a123 );
 break;

case ACW_NORMAL3I:
 i += sizeof(glCommand);
 GLint* a124 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glNormal3iv( a124 );
 break;

case ACW_NORMAL3IV:
 i += sizeof(glCommand);
 GLint* a125 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glNormal3iv( a125 );
 break;

case ACW_NORMAL3S:
 i += sizeof(glCommand);
 GLshort* a126 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glNormal3sv( a126 );
 break;

case ACW_NORMAL3SV:
 i += sizeof(glCommand);
 GLshort* a127 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glNormal3sv( a127 );
 break;

case ACW_ORTHO:
 i += sizeof(glCommand);
 GLdouble* a128 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* b128 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* c128 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* d128 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* e128 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* f128 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 glOrtho( *a128, *b128, *c128, *d128, *e128, *f128 );
 break;

case ACW_PASSTHROUGH:
 i += sizeof(glCommand);
 GLfloat* a129 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glPassThrough( *a129 );
 break;

case ACW_PIXELSTOREF:
 i += sizeof(glCommand);
 GLenum* a130 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* b130 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glPixelStoref( *a130, *b130 );
 break;

case ACW_PIXELSTOREI:
 i += sizeof(glCommand);
 GLenum* a131 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b131 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glPixelStorei( *a131, *b131 );
 break;

case ACW_PIXELTEXGENSGIX:
 i += sizeof(glCommand);
 GLenum* a132 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glPixelTexGenSGIX( *a132 );
 break;

case ACW_PIXELTRANSFERF:
 i += sizeof(glCommand);
 GLenum* a133 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* b133 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glPixelTransferf( *a133, *b133 );
 break;

case ACW_PIXELTRANSFERI:
 i += sizeof(glCommand);
 GLenum* a134 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b134 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glPixelTransferi( *a134, *b134 );
 break;

case ACW_PIXELZOOM:
 i += sizeof(glCommand);
 GLfloat* a135 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* b135 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glPixelZoom( *a135, *b135 );
 break;

case ACW_POINTPARAMETERFSGIS:
 i += sizeof(glCommand);
 GLenum* a136 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* b136 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glPointParameterfSGIS( *a136, *b136 );
 break;

case ACW_POINTSIZE:
 i += sizeof(glCommand);
 GLfloat* a137 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glPointSize( *a137 );
 break;

case ACW_POLYGONMODE:
 i += sizeof(glCommand);
 GLenum* a138 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b138 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glPolygonMode( *a138, *b138 );
 break;

case ACW_POLYGONOFFSET:
 i += sizeof(glCommand);
 GLfloat* a139 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* b139 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glPolygonOffset( *a139, *b139 );
 break;

case ACW_POLYGONOFFSETEXT:
 i += sizeof(glCommand);
 GLfloat* a140 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* b140 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glPolygonOffsetEXT( *a140, *b140 );
 break;

case ACW_POPATTRIB:
 i += sizeof(glCommand);
 glPopAttrib( );
 break;

case ACW_POPCLIENTATTRIB:
 i += sizeof(glCommand);
 glPopClientAttrib( );
 break;

case ACW_POPMATRIX:
 i += sizeof(glCommand);
 glPopMatrix( );
 break;

case ACW_POPNAME:
 i += sizeof(glCommand);
 glPopName( );
 break;

case ACW_PUSHATTRIB:
 i += sizeof(glCommand);
 GLbitfield* a145 = (GLbitfield*) &buffer[i];
 i += sizeof(GLbitfield);
 glPushAttrib( *a145 );
 break;

case ACW_PUSHCLIENTATTRIB:
 i += sizeof(glCommand);
 GLbitfield* a146 = (GLbitfield*) &buffer[i];
 i += sizeof(GLbitfield);
 glPushClientAttrib( *a146 );
 break;

case ACW_PUSHMATRIX:
 i += sizeof(glCommand);
 glPushMatrix( );
 break;

case ACW_PUSHNAME:
 i += sizeof(glCommand);
 GLuint* a148 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glPushName( *a148 );
 break;

case ACW_RASTERPOS2D:
 i += sizeof(glCommand);
 GLdouble* a149 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*2;
 glRasterPos2dv( a149 );
 break;

case ACW_RASTERPOS2DV:
 i += sizeof(glCommand);
 GLdouble* a150 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*2;
 glRasterPos2dv( a150 );
 break;

case ACW_RASTERPOS2F:
 i += sizeof(glCommand);
 GLfloat* a151 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*2;
 glRasterPos2fv( a151 );
 break;

case ACW_RASTERPOS2FV:
 i += sizeof(glCommand);
 GLfloat* a152 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*2;
 glRasterPos2fv( a152 );
 break;

case ACW_RASTERPOS2I:
 i += sizeof(glCommand);
 GLint* a153 = (GLint*) &buffer[i];
 i += sizeof(GLint)*2;
 glRasterPos2iv( a153 );
 break;

case ACW_RASTERPOS2IV:
 i += sizeof(glCommand);
 GLint* a154 = (GLint*) &buffer[i];
 i += sizeof(GLint)*2;
 glRasterPos2iv( a154 );
 break;

case ACW_RASTERPOS2S:
 i += sizeof(glCommand);
 GLshort* a155 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*2;
 glRasterPos2sv( a155 );
 break;

case ACW_RASTERPOS2SV:
 i += sizeof(glCommand);
 GLshort* a156 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*2;
 glRasterPos2sv( a156 );
 break;

case ACW_RASTERPOS3D:
 i += sizeof(glCommand);
 GLdouble* a157 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glRasterPos3dv( a157 );
 break;

case ACW_RASTERPOS3DV:
 i += sizeof(glCommand);
 GLdouble* a158 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glRasterPos3dv( a158 );
 break;

case ACW_RASTERPOS3F:
 i += sizeof(glCommand);
 GLfloat* a159 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glRasterPos3fv( a159 );
 break;

case ACW_RASTERPOS3FV:
 i += sizeof(glCommand);
 GLfloat* a160 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glRasterPos3fv( a160 );
 break;

case ACW_RASTERPOS3I:
 i += sizeof(glCommand);
 GLint* a161 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glRasterPos3iv( a161 );
 break;

case ACW_RASTERPOS3IV:
 i += sizeof(glCommand);
 GLint* a162 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glRasterPos3iv( a162 );
 break;

case ACW_RASTERPOS3S:
 i += sizeof(glCommand);
 GLshort* a163 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glRasterPos3sv( a163 );
 break;

case ACW_RASTERPOS3SV:
 i += sizeof(glCommand);
 GLshort* a164 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glRasterPos3sv( a164 );
 break;

case ACW_RASTERPOS4D:
 i += sizeof(glCommand);
 GLdouble* a165 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*4;
 glRasterPos4dv( a165 );
 break;

case ACW_RASTERPOS4DV:
 i += sizeof(glCommand);
 GLdouble* a166 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*4;
 glRasterPos4dv( a166 );
 break;

case ACW_RASTERPOS4F:
 i += sizeof(glCommand);
 GLfloat* a167 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*4;
 glRasterPos4fv( a167 );
 break;

case ACW_RASTERPOS4FV:
 i += sizeof(glCommand);
 GLfloat* a168 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*4;
 glRasterPos4fv( a168 );
 break;

case ACW_RASTERPOS4I:
 i += sizeof(glCommand);
 GLint* a169 = (GLint*) &buffer[i];
 i += sizeof(GLint)*4;
 glRasterPos4iv( a169 );
 break;

case ACW_RASTERPOS4IV:
 i += sizeof(glCommand);
 GLint* a170 = (GLint*) &buffer[i];
 i += sizeof(GLint)*4;
 glRasterPos4iv( a170 );
 break;

case ACW_RASTERPOS4S:
 i += sizeof(glCommand);
 GLshort* a171 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*4;
 glRasterPos4sv( a171 );
 break;

case ACW_RASTERPOS4SV:
 i += sizeof(glCommand);
 GLshort* a172 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*4;
 glRasterPos4sv( a172 );
 break;

case ACW_READBUFFER:
 i += sizeof(glCommand);
 GLenum* a173 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glReadBuffer( *a173 );
 break;

case ACW_READINSTRUMENTSSGIX:
 i += sizeof(glCommand);
 GLint* a174 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glReadInstrumentsSGIX( *a174 );
 break;

case ACW_RECTD:
 i += sizeof(glCommand);
 GLdouble* a175 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* b175 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* c175 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* d175 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 glRectd( *a175, *b175, *c175, *d175 );
 break;

case ACW_RECTF:
 i += sizeof(glCommand);
 GLfloat* a176 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* b176 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* c176 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* d176 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glRectf( *a176, *b176, *c176, *d176 );
 break;

case ACW_RECTI:
 i += sizeof(glCommand);
 GLint* a177 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* b177 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* c177 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* d177 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glRecti( *a177, *b177, *c177, *d177 );
 break;

case ACW_RECTS:
 i += sizeof(glCommand);
 GLshort* a178 = (GLshort*) &buffer[i];
 i += sizeof(GLshort);
 GLshort* b178 = (GLshort*) &buffer[i];
 i += sizeof(GLshort);
 GLshort* c178 = (GLshort*) &buffer[i];
 i += sizeof(GLshort);
 GLshort* d178 = (GLshort*) &buffer[i];
 i += sizeof(GLshort);
 glRects( *a178, *b178, *c178, *d178 );
 break;

case ACW_RENDERMODE:
 i += sizeof(glCommand);
 GLenum* a179 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glRenderMode( *a179 );
 break;

case ACW_ROTATEF:
 i += sizeof(glCommand);
 GLfloat* a180 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* b180 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* c180 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* d180 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glRotatef( *a180, *b180, *c180, *d180 );
 break;

case ACW_SAMPLEMASKSGIS:
 i += sizeof(glCommand);
 GLclampf* a181 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 GLboolean* b181 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 glSampleMaskSGIS( *a181, *b181 );
 break;

case ACW_SAMPLEPATTERNSGIS:
 i += sizeof(glCommand);
 GLenum* a182 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glSamplePatternSGIS( *a182 );
 break;

case ACW_SCALED:
 i += sizeof(glCommand);
 GLdouble* a183 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* b183 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* c183 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 glScaled( *a183, *b183, *c183 );
 break;

case ACW_SCALEF:
 i += sizeof(glCommand);
 GLfloat* a184 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* b184 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* c184 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glScalef( *a184, *b184, *c184 );
 break;

case ACW_SCISSOR:
 i += sizeof(glCommand);
 GLint* a185 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* b185 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLsizei* c185 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 GLsizei* d185 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 glScissor( *a185, *b185, *c185, *d185 );
 break;

case ACW_SHADEMODEL:
 i += sizeof(glCommand);
 GLenum* a186 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glShadeModel( *a186 );
 break;

case ACW_STARTINSTRUMENTSSGIX:
 i += sizeof(glCommand);
 glStartInstrumentsSGIX( );
 break;

case ACW_STENCILFUNC:
 i += sizeof(glCommand);
 GLenum* a188 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b188 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLuint* c188 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glStencilFunc( *a188, *b188, *c188 );
 break;

case ACW_STENCILMASK:
 i += sizeof(glCommand);
 GLuint* a189 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glStencilMask( *a189 );
 break;

case ACW_STENCILOP:
 i += sizeof(glCommand);
 GLenum* a190 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b190 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* c190 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glStencilOp( *a190, *b190, *c190 );
 break;

case ACW_STOPINSTRUMENTSSGIX:
 i += sizeof(glCommand);
 GLint* a191 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glStopInstrumentsSGIX( *a191 );
 break;

case ACW_TAGSAMPLEBUFFERSGIX:
 i += sizeof(glCommand);
 glTagSampleBufferSGIX( );
 break;

case ACW_TEXCOORD1D:
 i += sizeof(glCommand);
 GLdouble* a193 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*1;
 glTexCoord1dv( a193 );
 break;

case ACW_TEXCOORD1DV:
 i += sizeof(glCommand);
 GLdouble* a194 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*1;
 glTexCoord1dv( a194 );
 break;

case ACW_TEXCOORD1F:
 i += sizeof(glCommand);
 GLfloat* a195 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*1;
 glTexCoord1fv( a195 );
 break;

case ACW_TEXCOORD1FV:
 i += sizeof(glCommand);
 GLfloat* a196 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*1;
 glTexCoord1fv( a196 );
 break;

case ACW_TEXCOORD1I:
 i += sizeof(glCommand);
 GLint* a197 = (GLint*) &buffer[i];
 i += sizeof(GLint)*1;
 glTexCoord1iv( a197 );
 break;

case ACW_TEXCOORD1IV:
 i += sizeof(glCommand);
 GLint* a198 = (GLint*) &buffer[i];
 i += sizeof(GLint)*1;
 glTexCoord1iv( a198 );
 break;

case ACW_TEXCOORD1S:
 i += sizeof(glCommand);
 GLshort* a199 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*1;
 glTexCoord1sv( a199 );
 break;

case ACW_TEXCOORD1SV:
 i += sizeof(glCommand);
 GLshort* a200 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*1;
 glTexCoord1sv( a200 );
 break;

case ACW_TEXCOORD2D:
 i += sizeof(glCommand);
 GLdouble* a201 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*2;
 glTexCoord2dv( a201 );
 break;

case ACW_TEXCOORD2DV:
 i += sizeof(glCommand);
 GLdouble* a202 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*2;
 glTexCoord2dv( a202 );
 break;

case ACW_TEXCOORD2F:
 i += sizeof(glCommand);
 GLfloat* a203 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*2;
 glTexCoord2fv( a203 );
 break;

case ACW_TEXCOORD2FV:
 i += sizeof(glCommand);
 GLfloat* a204 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*2;
 glTexCoord2fv( a204 );
 break;

case ACW_TEXCOORD2I:
 i += sizeof(glCommand);
 GLint* a205 = (GLint*) &buffer[i];
 i += sizeof(GLint)*2;
 glTexCoord2iv( a205 );
 break;

case ACW_TEXCOORD2IV:
 i += sizeof(glCommand);
 GLint* a206 = (GLint*) &buffer[i];
 i += sizeof(GLint)*2;
 glTexCoord2iv( a206 );
 break;

case ACW_TEXCOORD2S:
 i += sizeof(glCommand);
 GLshort* a207 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*2;
 glTexCoord2sv( a207 );
 break;

case ACW_TEXCOORD2SV:
 i += sizeof(glCommand);
 GLshort* a208 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*2;
 glTexCoord2sv( a208 );
 break;

case ACW_TEXCOORD3D:
 i += sizeof(glCommand);
 GLdouble* a209 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glTexCoord3dv( a209 );
 break;

case ACW_TEXCOORD3DV:
 i += sizeof(glCommand);
 GLdouble* a210 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glTexCoord3dv( a210 );
 break;

case ACW_TEXCOORD3F:
 i += sizeof(glCommand);
 GLfloat* a211 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glTexCoord3fv( a211 );
 break;

case ACW_TEXCOORD3FV:
 i += sizeof(glCommand);
 GLfloat* a212 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glTexCoord3fv( a212 );
 break;

case ACW_TEXCOORD3I:
 i += sizeof(glCommand);
 GLint* a213 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glTexCoord3iv( a213 );
 break;

case ACW_TEXCOORD3IV:
 i += sizeof(glCommand);
 GLint* a214 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glTexCoord3iv( a214 );
 break;

case ACW_TEXCOORD3S:
 i += sizeof(glCommand);
 GLshort* a215 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glTexCoord3sv( a215 );
 break;

case ACW_TEXCOORD3SV:
 i += sizeof(glCommand);
 GLshort* a216 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glTexCoord3sv( a216 );
 break;

case ACW_TEXCOORD4D:
 i += sizeof(glCommand);
 GLdouble* a217 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*4;
 glTexCoord4dv( a217 );
 break;

case ACW_TEXCOORD4DV:
 i += sizeof(glCommand);
 GLdouble* a218 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*4;
 glTexCoord4dv( a218 );
 break;

case ACW_TEXCOORD4F:
 i += sizeof(glCommand);
 GLfloat* a219 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*4;
 glTexCoord4fv( a219 );
 break;

case ACW_TEXCOORD4FV:
 i += sizeof(glCommand);
 GLfloat* a220 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*4;
 glTexCoord4fv( a220 );
 break;

case ACW_TEXCOORD4I:
 i += sizeof(glCommand);
 GLint* a221 = (GLint*) &buffer[i];
 i += sizeof(GLint)*4;
 glTexCoord4iv( a221 );
 break;

case ACW_TEXCOORD4IV:
 i += sizeof(glCommand);
 GLint* a222 = (GLint*) &buffer[i];
 i += sizeof(GLint)*4;
 glTexCoord4iv( a222 );
 break;

case ACW_TEXCOORD4S:
 i += sizeof(glCommand);
 GLshort* a223 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*4;
 glTexCoord4sv( a223 );
 break;

case ACW_TEXCOORD4SV:
 i += sizeof(glCommand);
 GLshort* a224 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*4;
 glTexCoord4sv( a224 );
 break;

case ACW_TEXENVF:
 i += sizeof(glCommand);
 GLenum* a225 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b225 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* c225 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glTexEnvf( *a225, *b225, *c225 );
 break;

case ACW_TEXENVI:
 i += sizeof(glCommand);
 GLenum* a226 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b226 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* c226 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glTexEnvi( *a226, *b226, *c226 );
 break;

case ACW_TEXGEND:
 i += sizeof(glCommand);
 GLenum* a227 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b227 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLdouble* c227 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 glTexGend( *a227, *b227, *c227 );
 break;

case ACW_TEXGENF:
 i += sizeof(glCommand);
 GLenum* a228 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b228 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* c228 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glTexGenf( *a228, *b228, *c228 );
 break;

case ACW_TEXGENI:
 i += sizeof(glCommand);
 GLenum* a229 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b229 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* c229 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glTexGeni( *a229, *b229, *c229 );
 break;

case ACW_TEXPARAMETERF:
 i += sizeof(glCommand);
 GLenum* a230 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b230 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* c230 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glTexParameterf( *a230, *b230, *c230 );
 break;

case ACW_TEXPARAMETERI:
 i += sizeof(glCommand);
 GLenum* a231 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b231 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* c231 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glTexParameteri( *a231, *b231, *c231 );
 break;

case ACW_TRANSLATED:
 i += sizeof(glCommand);
 GLdouble* a232 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* b232 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* c232 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 glTranslated( *a232, *b232, *c232 );
 break;

case ACW_TRANSLATEF:
 i += sizeof(glCommand);
 GLfloat* a233 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* b233 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* c233 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glTranslatef( *a233, *b233, *c233 );
 break;

case ACW_VERTEX2D:
 i += sizeof(glCommand);
 GLdouble* a234 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*2;
 glVertex2dv( a234 );
 break;

case ACW_VERTEX2DV:
 i += sizeof(glCommand);
 GLdouble* a235 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*2;
 glVertex2dv( a235 );
 break;

case ACW_VERTEX2F:
 i += sizeof(glCommand);
 GLfloat* a236 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*2;
 glVertex2fv( a236 );
 break;

case ACW_VERTEX2FV:
 i += sizeof(glCommand);
 GLfloat* a237 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*2;
 glVertex2fv( a237 );
 break;

case ACW_VERTEX2I:
 i += sizeof(glCommand);
 GLint* a238 = (GLint*) &buffer[i];
 i += sizeof(GLint)*2;
 glVertex2iv( a238 );
 break;

case ACW_VERTEX2IV:
 i += sizeof(glCommand);
 GLint* a239 = (GLint*) &buffer[i];
 i += sizeof(GLint)*2;
 glVertex2iv( a239 );
 break;

case ACW_VERTEX2S:
 i += sizeof(glCommand);
 GLshort* a240 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*2;
 glVertex2sv( a240 );
 break;

case ACW_VERTEX2SV:
 i += sizeof(glCommand);
 GLshort* a241 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*2;
 glVertex2sv( a241 );
 break;

case ACW_VERTEX3D:
 i += sizeof(glCommand);
 GLdouble* a242 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glVertex3dv( a242 );
 break;

case ACW_VERTEX3DV:
 i += sizeof(glCommand);
 GLdouble* a243 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glVertex3dv( a243 );
 break;

case ACW_VERTEX3F:
 i += sizeof(glCommand);
 GLfloat* a244 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glVertex3fv( a244 );
 break;

case ACW_VERTEX3FV:
 i += sizeof(glCommand);
 GLfloat* a245 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glVertex3fv( a245 );
 break;

case ACW_VERTEX3I:
 i += sizeof(glCommand);
 GLint* a246 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glVertex3iv( a246 );
 break;

case ACW_VERTEX3IV:
 i += sizeof(glCommand);
 GLint* a247 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glVertex3iv( a247 );
 break;

case ACW_VERTEX3S:
 i += sizeof(glCommand);
 GLshort* a248 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glVertex3sv( a248 );
 break;

case ACW_VERTEX3SV:
 i += sizeof(glCommand);
 GLshort* a249 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glVertex3sv( a249 );
 break;

case ACW_VERTEX4D:
 i += sizeof(glCommand);
 GLdouble* a250 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*4;
 glVertex4dv( a250 );
 break;

case ACW_VERTEX4DV:
 i += sizeof(glCommand);
 GLdouble* a251 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*4;
 glVertex4dv( a251 );
 break;

case ACW_VERTEX4F:
 i += sizeof(glCommand);
 GLfloat* a252 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*4;
 glVertex4fv( a252 );
 break;

case ACW_VERTEX4FV:
 i += sizeof(glCommand);
 GLfloat* a253 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*4;
 glVertex4fv( a253 );
 break;

case ACW_VERTEX4I:
 i += sizeof(glCommand);
 GLint* a254 = (GLint*) &buffer[i];
 i += sizeof(GLint)*4;
 glVertex4iv( a254 );
 break;

case ACW_VERTEX4IV:
 i += sizeof(glCommand);
 GLint* a255 = (GLint*) &buffer[i];
 i += sizeof(GLint)*4;
 glVertex4iv( a255 );
 break;

case ACW_VERTEX4S:
 i += sizeof(glCommand);
 GLshort* a256 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*4;
 glVertex4sv( a256 );
 break;

case ACW_VERTEX4SV:
 i += sizeof(glCommand);
 GLshort* a257 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*4;
 glVertex4sv( a257 );
 break;

case ACW_VIEWPORT:
 i += sizeof(glCommand);
 GLint* a258 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* b258 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLsizei* c258 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 GLsizei* d258 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 glViewport( *a258, *b258, *c258, *d258 );
 break;

}
}
}
