
#include "acGLUnwrapper.h"
#include <stdio.h>

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


void glUnwrapper::clearBuffer()
{
  bufferSize = 0;
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

case ACW_ARETEXTURESRESIDENT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glAreTexturesResident\n");
 break;

case ACW_ARETEXTURESRESIDENTEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glAreTexturesResidentEXT\n");
 break;

case ACW_ARRAYELEMENT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glArrayElement\n");
 break;

case ACW_ARRAYELEMENTEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glArrayElementEXT\n");
 break;

case ACW_BEGIN:
 i += sizeof(glCommand);
 GLenum* a6 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glBegin( *a6 );
 break;

case ACW_BINDTEXTURE:
 i += sizeof(glCommand);
 printf("unwrapped gl: glBindTexture\n");
 break;

case ACW_BINDTEXTUREEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glBindTextureEXT\n");
 break;

case ACW_BITMAP:
 i += sizeof(glCommand);
 printf("unwrapped gl: glBitmap\n");
 break;

case ACW_BLENDCOLOR:
 i += sizeof(glCommand);
 GLclampf* a10 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 GLclampf* b10 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 GLclampf* c10 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 GLclampf* d10 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 glBlendColor( *a10, *b10, *c10, *d10 );
 break;

case ACW_BLENDCOLOREXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glBlendColorEXT\n");
 break;

case ACW_BLENDEQUATION:
 i += sizeof(glCommand);
 GLenum* a12 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glBlendEquation( *a12 );
 break;

case ACW_BLENDEQUATIONEXT:
 i += sizeof(glCommand);
 GLenum* a13 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glBlendEquationEXT( *a13 );
 break;

case ACW_BLENDFUNC:
 i += sizeof(glCommand);
 GLenum* a14 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b14 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glBlendFunc( *a14, *b14 );
 break;

case ACW_CALLLIST:
 i += sizeof(glCommand);
 GLuint* a15 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glCallList( *a15 );
 break;

case ACW_CALLLISTS:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCallLists\n");
 break;

case ACW_CLEAR:
 i += sizeof(glCommand);
 GLbitfield* a17 = (GLbitfield*) &buffer[i];
 i += sizeof(GLbitfield);
 glClear( *a17 );
 break;

case ACW_CLEARACCUM:
 i += sizeof(glCommand);
 GLfloat* a18 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* b18 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* c18 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* d18 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glClearAccum( *a18, *b18, *c18, *d18 );
 break;

case ACW_CLEARCOLOR:
 i += sizeof(glCommand);
 GLclampf* a19 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 GLclampf* b19 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 GLclampf* c19 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 GLclampf* d19 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 glClearColor( *a19, *b19, *c19, *d19 );
 break;

case ACW_CLEARDEPTH:
 i += sizeof(glCommand);
 GLclampd* a20 = (GLclampd*) &buffer[i];
 i += sizeof(GLclampd);
 glClearDepth( *a20 );
 break;

case ACW_CLEARINDEX:
 i += sizeof(glCommand);
 GLfloat* a21 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glClearIndex( *a21 );
 break;

case ACW_CLEARSTENCIL:
 i += sizeof(glCommand);
 GLint* a22 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glClearStencil( *a22 );
 break;

case ACW_CLIPPLANE:
 i += sizeof(glCommand);
 printf("unwrapped gl: glClipPlane\n");
 break;

case ACW_COLOR3B:
 i += sizeof(glCommand);
 GLbyte* a24 = (GLbyte*) &buffer[i];
 i += sizeof(GLbyte)*3;
 glColor3bv( a24 );
 break;

case ACW_COLOR3BV:
 i += sizeof(glCommand);
 GLbyte* a25 = (GLbyte*) &buffer[i];
 i += sizeof(GLbyte)*3;
 glColor3bv( a25 );
 break;

case ACW_COLOR3D:
 i += sizeof(glCommand);
 GLdouble* a26 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glColor3dv( a26 );
 break;

case ACW_COLOR3DV:
 i += sizeof(glCommand);
 GLdouble* a27 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glColor3dv( a27 );
 break;

case ACW_COLOR3F:
 i += sizeof(glCommand);
 GLfloat* a28 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glColor3fv( a28 );
 break;

case ACW_COLOR3FV:
 i += sizeof(glCommand);
 GLfloat* a29 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glColor3fv( a29 );
 break;

case ACW_COLOR3I:
 i += sizeof(glCommand);
 GLint* a30 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glColor3iv( a30 );
 break;

case ACW_COLOR3IV:
 i += sizeof(glCommand);
 GLint* a31 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glColor3iv( a31 );
 break;

case ACW_COLOR3S:
 i += sizeof(glCommand);
 GLshort* a32 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glColor3sv( a32 );
 break;

case ACW_COLOR3SV:
 i += sizeof(glCommand);
 GLshort* a33 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glColor3sv( a33 );
 break;

case ACW_COLOR3UB:
 i += sizeof(glCommand);
 GLubyte* a34 = (GLubyte*) &buffer[i];
 i += sizeof(GLubyte);
 GLubyte* b34 = (GLubyte*) &buffer[i];
 i += sizeof(GLubyte);
 GLubyte* c34 = (GLubyte*) &buffer[i];
 i += sizeof(GLubyte);
 glColor3ub( *a34, *b34, *c34 );
 break;

case ACW_COLOR3UBV:
 i += sizeof(glCommand);
 GLubyte** a35 = (GLubyte**) &buffer[i];
 i += sizeof(GLubyte*);
 glColor3ubv( *a35 );
 break;

case ACW_COLOR3UI:
 i += sizeof(glCommand);
 GLuint* a36 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLuint* b36 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLuint* c36 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glColor3ui( *a36, *b36, *c36 );
 break;

case ACW_COLOR3UIV:
 i += sizeof(glCommand);
 GLuint** a37 = (GLuint**) &buffer[i];
 i += sizeof(GLuint*);
 glColor3uiv( *a37 );
 break;

case ACW_COLOR3US:
 i += sizeof(glCommand);
 GLushort* a38 = (GLushort*) &buffer[i];
 i += sizeof(GLushort);
 GLushort* b38 = (GLushort*) &buffer[i];
 i += sizeof(GLushort);
 GLushort* c38 = (GLushort*) &buffer[i];
 i += sizeof(GLushort);
 glColor3us( *a38, *b38, *c38 );
 break;

case ACW_COLOR3USV:
 i += sizeof(glCommand);
 GLushort** a39 = (GLushort**) &buffer[i];
 i += sizeof(GLushort*);
 glColor3usv( *a39 );
 break;

case ACW_COLOR4B:
 i += sizeof(glCommand);
 GLbyte* a40 = (GLbyte*) &buffer[i];
 i += sizeof(GLbyte)*4;
 glColor4bv( a40 );
 break;

case ACW_COLOR4BV:
 i += sizeof(glCommand);
 GLbyte* a41 = (GLbyte*) &buffer[i];
 i += sizeof(GLbyte)*4;
 glColor4bv( a41 );
 break;

case ACW_COLOR4D:
 i += sizeof(glCommand);
 GLdouble* a42 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*4;
 glColor4dv( a42 );
 break;

case ACW_COLOR4DV:
 i += sizeof(glCommand);
 GLdouble* a43 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*4;
 glColor4dv( a43 );
 break;

case ACW_COLOR4F:
 i += sizeof(glCommand);
 GLfloat* a44 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*4;
 glColor4fv( a44 );
 break;

case ACW_COLOR4FV:
 i += sizeof(glCommand);
 GLfloat* a45 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*4;
 glColor4fv( a45 );
 break;

case ACW_COLOR4I:
 i += sizeof(glCommand);
 GLint* a46 = (GLint*) &buffer[i];
 i += sizeof(GLint)*4;
 glColor4iv( a46 );
 break;

case ACW_COLOR4IV:
 i += sizeof(glCommand);
 GLint* a47 = (GLint*) &buffer[i];
 i += sizeof(GLint)*4;
 glColor4iv( a47 );
 break;

case ACW_COLOR4S:
 i += sizeof(glCommand);
 GLshort* a48 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*4;
 glColor4sv( a48 );
 break;

case ACW_COLOR4SV:
 i += sizeof(glCommand);
 GLshort* a49 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*4;
 glColor4sv( a49 );
 break;

case ACW_COLOR4UB:
 i += sizeof(glCommand);
 GLubyte* a50 = (GLubyte*) &buffer[i];
 i += sizeof(GLubyte);
 GLubyte* b50 = (GLubyte*) &buffer[i];
 i += sizeof(GLubyte);
 GLubyte* c50 = (GLubyte*) &buffer[i];
 i += sizeof(GLubyte);
 GLubyte* d50 = (GLubyte*) &buffer[i];
 i += sizeof(GLubyte);
 glColor4ub( *a50, *b50, *c50, *d50 );
 break;

case ACW_COLOR4UBV:
 i += sizeof(glCommand);
 GLubyte** a51 = (GLubyte**) &buffer[i];
 i += sizeof(GLubyte*);
 glColor4ubv( *a51 );
 break;

case ACW_COLOR4UI:
 i += sizeof(glCommand);
 GLuint* a52 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLuint* b52 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLuint* c52 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLuint* d52 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glColor4ui( *a52, *b52, *c52, *d52 );
 break;

case ACW_COLOR4UIV:
 i += sizeof(glCommand);
 GLuint** a53 = (GLuint**) &buffer[i];
 i += sizeof(GLuint*);
 glColor4uiv( *a53 );
 break;

case ACW_COLOR4US:
 i += sizeof(glCommand);
 GLushort* a54 = (GLushort*) &buffer[i];
 i += sizeof(GLushort);
 GLushort* b54 = (GLushort*) &buffer[i];
 i += sizeof(GLushort);
 GLushort* c54 = (GLushort*) &buffer[i];
 i += sizeof(GLushort);
 GLushort* d54 = (GLushort*) &buffer[i];
 i += sizeof(GLushort);
 glColor4us( *a54, *b54, *c54, *d54 );
 break;

case ACW_COLOR4USV:
 i += sizeof(glCommand);
 GLushort** a55 = (GLushort**) &buffer[i];
 i += sizeof(GLushort*);
 glColor4usv( *a55 );
 break;

case ACW_COLORMASK:
 i += sizeof(glCommand);
 GLboolean* a56 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 GLboolean* b56 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 GLboolean* c56 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 GLboolean* d56 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 glColorMask( *a56, *b56, *c56, *d56 );
 break;

case ACW_COLORMATERIAL:
 i += sizeof(glCommand);
 GLenum* a57 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b57 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glColorMaterial( *a57, *b57 );
 break;

case ACW_COLORPOINTER:
 i += sizeof(glCommand);
 printf("unwrapped gl: glColorPointer\n");
 break;

case ACW_COLORPOINTEREXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glColorPointerEXT\n");
 break;

case ACW_COLORSUBTABLE:
 i += sizeof(glCommand);
 printf("unwrapped gl: glColorSubTable\n");
 break;

case ACW_COLORTABLE:
 i += sizeof(glCommand);
 printf("unwrapped gl: glColorTable\n");
 break;

case ACW_COLORTABLEPARAMETERFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glColorTableParameterfv\n");
 break;

case ACW_COLORTABLEPARAMETERFVSGI:
 i += sizeof(glCommand);
 printf("unwrapped gl: glColorTableParameterfvSGI\n");
 break;

case ACW_COLORTABLEPARAMETERIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glColorTableParameteriv\n");
 break;

case ACW_COLORTABLEPARAMETERIVSGI:
 i += sizeof(glCommand);
 printf("unwrapped gl: glColorTableParameterivSGI\n");
 break;

case ACW_COLORTABLESGI:
 i += sizeof(glCommand);
 printf("unwrapped gl: glColorTableSGI\n");
 break;

case ACW_CONVOLUTIONFILTER1D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glConvolutionFilter1D\n");
 break;

case ACW_CONVOLUTIONFILTER1DEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glConvolutionFilter1DEXT\n");
 break;

case ACW_CONVOLUTIONFILTER2D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glConvolutionFilter2D\n");
 break;

case ACW_CONVOLUTIONFILTER2DEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glConvolutionFilter2DEXT\n");
 break;

case ACW_CONVOLUTIONPARAMETERF:
 i += sizeof(glCommand);
 printf("unwrapped gl: glConvolutionParameterf\n");
 break;

case ACW_CONVOLUTIONPARAMETERFEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glConvolutionParameterfEXT\n");
 break;

case ACW_CONVOLUTIONPARAMETERFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glConvolutionParameterfv\n");
 break;

case ACW_CONVOLUTIONPARAMETERFVEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glConvolutionParameterfvEXT\n");
 break;

case ACW_CONVOLUTIONPARAMETERI:
 i += sizeof(glCommand);
 printf("unwrapped gl: glConvolutionParameteri\n");
 break;

case ACW_CONVOLUTIONPARAMETERIEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glConvolutionParameteriEXT\n");
 break;

case ACW_CONVOLUTIONPARAMETERIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glConvolutionParameteriv\n");
 break;

case ACW_CONVOLUTIONPARAMETERIVEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glConvolutionParameterivEXT\n");
 break;

case ACW_COPYCOLORSUBTABLE:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCopyColorSubTable\n");
 break;

case ACW_COPYCOLORTABLE:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCopyColorTable\n");
 break;

case ACW_COPYCOLORTABLESGI:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCopyColorTableSGI\n");
 break;

case ACW_COPYCONVOLUTIONFILTER1D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCopyConvolutionFilter1D\n");
 break;

case ACW_COPYCONVOLUTIONFILTER1DEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCopyConvolutionFilter1DEXT\n");
 break;

case ACW_COPYCONVOLUTIONFILTER2D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCopyConvolutionFilter2D\n");
 break;

case ACW_COPYCONVOLUTIONFILTER2DEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCopyConvolutionFilter2DEXT\n");
 break;

case ACW_COPYPIXELS:
 i += sizeof(glCommand);
 GLint* a86 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* b86 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLsizei* c86 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 GLsizei* d86 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 GLenum* e86 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glCopyPixels( *a86, *b86, *c86, *d86, *e86 );
 break;

case ACW_COPYTEXIMAGE1D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCopyTexImage1D\n");
 break;

case ACW_COPYTEXIMAGE1DEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCopyTexImage1DEXT\n");
 break;

case ACW_COPYTEXIMAGE2D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCopyTexImage2D\n");
 break;

case ACW_COPYTEXIMAGE2DEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCopyTexImage2DEXT\n");
 break;

case ACW_COPYTEXSUBIMAGE1D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCopyTexSubImage1D\n");
 break;

case ACW_COPYTEXSUBIMAGE1DEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCopyTexSubImage1DEXT\n");
 break;

case ACW_COPYTEXSUBIMAGE2D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCopyTexSubImage2D\n");
 break;

case ACW_COPYTEXSUBIMAGE2DEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCopyTexSubImage2DEXT\n");
 break;

case ACW_COPYTEXSUBIMAGE3D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCopyTexSubImage3D\n");
 break;

case ACW_COPYTEXSUBIMAGE3DEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glCopyTexSubImage3DEXT\n");
 break;

case ACW_CULLFACE:
 i += sizeof(glCommand);
 GLenum* a97 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glCullFace( *a97 );
 break;

case ACW_DEFORMSGIX:
 i += sizeof(glCommand);
 GLbitfield* a98 = (GLbitfield*) &buffer[i];
 i += sizeof(GLbitfield);
 glDeformSGIX( *a98 );
 break;

case ACW_DEFORMATIONMAP3DSGIX:
 i += sizeof(glCommand);
 printf("unwrapped gl: glDeformationMap3dSGIX\n");
 break;

case ACW_DEFORMATIONMAP3FSGIX:
 i += sizeof(glCommand);
 printf("unwrapped gl: glDeformationMap3fSGIX\n");
 break;

case ACW_DELETELISTS:
 i += sizeof(glCommand);
 GLuint* a101 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLsizei* b101 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 glDeleteLists( *a101, *b101 );
 break;

case ACW_DELETETEXTURES:
 i += sizeof(glCommand);
 printf("unwrapped gl: glDeleteTextures\n");
 break;

case ACW_DELETETEXTURESEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glDeleteTexturesEXT\n");
 break;

case ACW_DEPTHFUNC:
 i += sizeof(glCommand);
 GLenum* a104 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glDepthFunc( *a104 );
 break;

case ACW_DEPTHMASK:
 i += sizeof(glCommand);
 GLboolean* a105 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 glDepthMask( *a105 );
 break;

case ACW_DEPTHRANGE:
 i += sizeof(glCommand);
 GLclampd* a106 = (GLclampd*) &buffer[i];
 i += sizeof(GLclampd);
 GLclampd* b106 = (GLclampd*) &buffer[i];
 i += sizeof(GLclampd);
 glDepthRange( *a106, *b106 );
 break;

case ACW_DETAILTEXFUNCSGIS:
 i += sizeof(glCommand);
 printf("unwrapped gl: glDetailTexFuncSGIS\n");
 break;

case ACW_DISABLE:
 i += sizeof(glCommand);
 GLenum* a108 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glDisable( *a108 );
 break;

case ACW_DISABLECLIENTSTATE:
 i += sizeof(glCommand);
 GLenum* a109 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glDisableClientState( *a109 );
 break;

case ACW_DRAWARRAYS:
 i += sizeof(glCommand);
 GLenum* a110 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b110 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLsizei* c110 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 glDrawArrays( *a110, *b110, *c110 );
 break;

case ACW_DRAWARRAYSEXT:
 i += sizeof(glCommand);
 GLenum* a111 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b111 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLsizei* c111 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 glDrawArraysEXT( *a111, *b111, *c111 );
 break;

case ACW_DRAWBUFFER:
 i += sizeof(glCommand);
 GLenum* a112 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glDrawBuffer( *a112 );
 break;

case ACW_DRAWELEMENTS:
 i += sizeof(glCommand);
 printf("unwrapped gl: glDrawElements\n");
 break;

case ACW_DRAWPIXELS:
 i += sizeof(glCommand);
 printf("unwrapped gl: glDrawPixels\n");
 break;

case ACW_DRAWRANGEELEMENTS:
 i += sizeof(glCommand);
 printf("unwrapped gl: glDrawRangeElements\n");
 break;

case ACW_EDGEFLAG:
 i += sizeof(glCommand);
 GLboolean* a116 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 glEdgeFlag( *a116 );
 break;

case ACW_EDGEFLAGPOINTER:
 i += sizeof(glCommand);
 printf("unwrapped gl: glEdgeFlagPointer\n");
 break;

case ACW_EDGEFLAGPOINTEREXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glEdgeFlagPointerEXT\n");
 break;

case ACW_EDGEFLAGV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glEdgeFlagv\n");
 break;

case ACW_ENABLE:
 i += sizeof(glCommand);
 GLenum* a120 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glEnable( *a120 );
 break;

case ACW_ENABLECLIENTSTATE:
 i += sizeof(glCommand);
 GLenum* a121 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glEnableClientState( *a121 );
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
 GLdouble* a124 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*1;
 glEvalCoord1dv( a124 );
 break;

case ACW_EVALCOORD1DV:
 i += sizeof(glCommand);
 GLdouble* a125 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*1;
 glEvalCoord1dv( a125 );
 break;

case ACW_EVALCOORD1F:
 i += sizeof(glCommand);
 GLfloat* a126 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*1;
 glEvalCoord1fv( a126 );
 break;

case ACW_EVALCOORD1FV:
 i += sizeof(glCommand);
 GLfloat* a127 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*1;
 glEvalCoord1fv( a127 );
 break;

case ACW_EVALCOORD2D:
 i += sizeof(glCommand);
 GLdouble* a128 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*2;
 glEvalCoord2dv( a128 );
 break;

case ACW_EVALCOORD2DV:
 i += sizeof(glCommand);
 GLdouble* a129 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*2;
 glEvalCoord2dv( a129 );
 break;

case ACW_EVALCOORD2F:
 i += sizeof(glCommand);
 GLfloat* a130 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*2;
 glEvalCoord2fv( a130 );
 break;

case ACW_EVALCOORD2FV:
 i += sizeof(glCommand);
 GLfloat* a131 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*2;
 glEvalCoord2fv( a131 );
 break;

case ACW_EVALMESH1:
 i += sizeof(glCommand);
 GLenum* a132 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b132 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* c132 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glEvalMesh1( *a132, *b132, *c132 );
 break;

case ACW_EVALMESH2:
 i += sizeof(glCommand);
 GLenum* a133 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b133 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* c133 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* d133 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* e133 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glEvalMesh2( *a133, *b133, *c133, *d133, *e133 );
 break;

case ACW_EVALPOINT1:
 i += sizeof(glCommand);
 GLint* a134 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glEvalPoint1( *a134 );
 break;

case ACW_EVALPOINT2:
 i += sizeof(glCommand);
 GLint* a135 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* b135 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glEvalPoint2( *a135, *b135 );
 break;

case ACW_FEEDBACKBUFFER:
 i += sizeof(glCommand);
 printf("unwrapped gl: glFeedbackBuffer\n");
 break;

case ACW_FINISH:
 i += sizeof(glCommand);
 printf("unwrapped gl: glFinish\n");
 break;

case ACW_FLUSH:
 i += sizeof(glCommand);
 glFlush( );
 break;

case ACW_FLUSHRASTERSGIX:
 i += sizeof(glCommand);
 glFlushRasterSGIX( );
 break;

case ACW_FOGFUNCSGIS:
 i += sizeof(glCommand);
 printf("unwrapped gl: glFogFuncSGIS\n");
 break;

case ACW_FOGF:
 i += sizeof(glCommand);
 GLenum* a141 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* b141 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glFogf( *a141, *b141 );
 break;

case ACW_FOGFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glFogfv\n");
 break;

case ACW_FOGI:
 i += sizeof(glCommand);
 GLenum* a143 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b143 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glFogi( *a143, *b143 );
 break;

case ACW_FOGIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glFogiv\n");
 break;

case ACW_FRAMEZOOMSGIX:
 i += sizeof(glCommand);
 GLint* a145 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glFrameZoomSGIX( *a145 );
 break;

case ACW_FRONTFACE:
 i += sizeof(glCommand);
 GLenum* a146 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glFrontFace( *a146 );
 break;

case ACW_FRUSTUM:
 i += sizeof(glCommand);
 GLdouble* a147 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* b147 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* c147 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* d147 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* e147 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* f147 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 glFrustum( *a147, *b147, *c147, *d147, *e147, *f147 );
 break;

case ACW_GENLISTS:
 i += sizeof(glCommand);
 GLsizei* a148 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 glGenLists( *a148 );
 break;

case ACW_GENTEXTURES:
 i += sizeof(glCommand);
 GLsizei* a149 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 GLuint** b149 = (GLuint**) &buffer[i];
 i += sizeof(GLuint*);
 glGenTextures( *a149, *b149 );
 break;

case ACW_GENTEXTURESEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGenTexturesEXT\n");
 break;

case ACW_GETBOOLEANV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetBooleanv\n");
 break;

case ACW_GETCLIPPLANE:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetClipPlane\n");
 break;

case ACW_GETCOLORTABLE:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetColorTable\n");
 break;

case ACW_GETCOLORTABLEPARAMETERFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetColorTableParameterfv\n");
 break;

case ACW_GETCOLORTABLEPARAMETERFVSGI:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetColorTableParameterfvSGI\n");
 break;

case ACW_GETCOLORTABLEPARAMETERIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetColorTableParameteriv\n");
 break;

case ACW_GETCOLORTABLEPARAMETERIVSGI:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetColorTableParameterivSGI\n");
 break;

case ACW_GETCOLORTABLESGI:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetColorTableSGI\n");
 break;

case ACW_GETCONVOLUTIONFILTER:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetConvolutionFilter\n");
 break;

case ACW_GETCONVOLUTIONFILTEREXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetConvolutionFilterEXT\n");
 break;

case ACW_GETCONVOLUTIONPARAMETERFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetConvolutionParameterfv\n");
 break;

case ACW_GETCONVOLUTIONPARAMETERFVEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetConvolutionParameterfvEXT\n");
 break;

case ACW_GETCONVOLUTIONPARAMETERIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetConvolutionParameteriv\n");
 break;

case ACW_GETCONVOLUTIONPARAMETERIVEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetConvolutionParameterivEXT\n");
 break;

case ACW_GETDETAILTEXFUNCSGIS:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetDetailTexFuncSGIS\n");
 break;

case ACW_GETDOUBLEV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetDoublev\n");
 break;

case ACW_GETERROR:
 i += sizeof(glCommand);
 glGetError( );
 break;

case ACW_GETFLOATV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetFloatv\n");
 break;

case ACW_GETHISTOGRAM:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetHistogram\n");
 break;

case ACW_GETHISTOGRAMEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetHistogramEXT\n");
 break;

case ACW_GETHISTOGRAMPARAMETERFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetHistogramParameterfv\n");
 break;

case ACW_GETHISTOGRAMPARAMETERFVEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetHistogramParameterfvEXT\n");
 break;

case ACW_GETHISTOGRAMPARAMETERIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetHistogramParameteriv\n");
 break;

case ACW_GETHISTOGRAMPARAMETERIVEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetHistogramParameterivEXT\n");
 break;

case ACW_GETINSTRUMENTSSGIX:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetInstrumentsSGIX\n");
 break;

case ACW_GETINTEGERV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetIntegerv\n");
 break;

case ACW_GETLIGHTFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetLightfv\n");
 break;

case ACW_GETLIGHTIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetLightiv\n");
 break;

case ACW_GETLISTPARAMETERFVSGIX:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetListParameterfvSGIX\n");
 break;

case ACW_GETLISTPARAMETERIVSGIX:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetListParameterivSGIX\n");
 break;

case ACW_GETMAPDV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetMapdv\n");
 break;

case ACW_GETMAPFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetMapfv\n");
 break;

case ACW_GETMAPIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetMapiv\n");
 break;

case ACW_GETMATERIALFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetMaterialfv\n");
 break;

case ACW_GETMATERIALIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetMaterialiv\n");
 break;

case ACW_GETMINMAX:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetMinmax\n");
 break;

case ACW_GETMINMAXEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetMinmaxEXT\n");
 break;

case ACW_GETMINMAXPARAMETERFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetMinmaxParameterfv\n");
 break;

case ACW_GETMINMAXPARAMETERFVEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetMinmaxParameterfvEXT\n");
 break;

case ACW_GETMINMAXPARAMETERIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetMinmaxParameteriv\n");
 break;

case ACW_GETMINMAXPARAMETERIVEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetMinmaxParameterivEXT\n");
 break;

case ACW_GETPIXELMAPFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetPixelMapfv\n");
 break;

case ACW_GETPIXELMAPUIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetPixelMapuiv\n");
 break;

case ACW_GETPIXELMAPUSV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetPixelMapusv\n");
 break;

case ACW_GETPOINTERV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetPointerv\n");
 break;

case ACW_GETPOINTERVEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetPointervEXT\n");
 break;

case ACW_GETPOLYGONSTIPPLE:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetPolygonStipple\n");
 break;

case ACW_GETSEPARABLEFILTER:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetSeparableFilter\n");
 break;

case ACW_GETSEPARABLEFILTEREXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetSeparableFilterEXT\n");
 break;

case ACW_GETSHARPENTEXFUNCSGIS:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetSharpenTexFuncSGIS\n");
 break;

case ACW_GETSTRING:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetString\n");
 break;

case ACW_GETTEXENVFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetTexEnvfv\n");
 break;

case ACW_GETTEXENVIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetTexEnviv\n");
 break;

case ACW_GETTEXFILTERFUNCSGIS:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetTexFilterFuncSGIS\n");
 break;

case ACW_GETTEXGENDV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetTexGendv\n");
 break;

case ACW_GETTEXGENFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetTexGenfv\n");
 break;

case ACW_GETTEXGENIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetTexGeniv\n");
 break;

case ACW_GETTEXIMAGE:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetTexImage\n");
 break;

case ACW_GETTEXLEVELPARAMETERFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetTexLevelParameterfv\n");
 break;

case ACW_GETTEXLEVELPARAMETERIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetTexLevelParameteriv\n");
 break;

case ACW_GETTEXPARAMETERFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetTexParameterfv\n");
 break;

case ACW_GETTEXPARAMETERIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glGetTexParameteriv\n");
 break;

case ACW_HINT:
 i += sizeof(glCommand);
 GLenum* a213 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b213 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glHint( *a213, *b213 );
 break;

case ACW_HISTOGRAM:
 i += sizeof(glCommand);
 GLenum* a214 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLsizei* b214 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 GLenum* c214 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLboolean* d214 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 glHistogram( *a214, *b214, *c214, *d214 );
 break;

case ACW_HISTOGRAMEXT:
 i += sizeof(glCommand);
 GLenum* a215 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLsizei* b215 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 GLenum* c215 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLboolean* d215 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 glHistogramEXT( *a215, *b215, *c215, *d215 );
 break;

case ACW_INDEXMASK:
 i += sizeof(glCommand);
 GLuint* a216 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glIndexMask( *a216 );
 break;

case ACW_INDEXPOINTER:
 i += sizeof(glCommand);
 printf("unwrapped gl: glIndexPointer\n");
 break;

case ACW_INDEXPOINTEREXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glIndexPointerEXT\n");
 break;

case ACW_INDEXD:
 i += sizeof(glCommand);
 GLdouble* a219 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 glIndexd( *a219 );
 break;

case ACW_INDEXDV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glIndexdv\n");
 break;

case ACW_INDEXF:
 i += sizeof(glCommand);
 GLfloat* a221 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glIndexf( *a221 );
 break;

case ACW_INDEXFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glIndexfv\n");
 break;

case ACW_INDEXI:
 i += sizeof(glCommand);
 GLint* a223 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glIndexi( *a223 );
 break;

case ACW_INDEXIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glIndexiv\n");
 break;

case ACW_INDEXS:
 i += sizeof(glCommand);
 printf("unwrapped gl: glIndexs\n");
 break;

case ACW_INDEXSV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glIndexsv\n");
 break;

case ACW_INDEXUB:
 i += sizeof(glCommand);
 printf("unwrapped gl: glIndexub\n");
 break;

case ACW_INDEXUBV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glIndexubv\n");
 break;

case ACW_INITNAMES:
 i += sizeof(glCommand);
 glInitNames( );
 break;

case ACW_INSTRUMENTSBUFFERSGIX:
 i += sizeof(glCommand);
 printf("unwrapped gl: glInstrumentsBufferSGIX\n");
 break;

case ACW_INTERLEAVEDARRAYS:
 i += sizeof(glCommand);
 printf("unwrapped gl: glInterleavedArrays\n");
 break;

case ACW_ISENABLED:
 i += sizeof(glCommand);
 GLenum* a232 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glIsEnabled( *a232 );
 break;

case ACW_ISLIST:
 i += sizeof(glCommand);
 GLuint* a233 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glIsList( *a233 );
 break;

case ACW_ISTEXTURE:
 i += sizeof(glCommand);
 GLuint* a234 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glIsTexture( *a234 );
 break;

case ACW_ISTEXTUREEXT:
 i += sizeof(glCommand);
 GLuint* a235 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glIsTextureEXT( *a235 );
 break;

case ACW_LIGHTMODELF:
 i += sizeof(glCommand);
 GLenum* a236 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* b236 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glLightModelf( *a236, *b236 );
 break;

case ACW_LIGHTMODELFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glLightModelfv\n");
 break;

case ACW_LIGHTMODELI:
 i += sizeof(glCommand);
 GLenum* a238 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b238 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glLightModeli( *a238, *b238 );
 break;

case ACW_LIGHTMODELIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glLightModeliv\n");
 break;

case ACW_LIGHTF:
 i += sizeof(glCommand);
 GLenum* a240 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b240 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* c240 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glLightf( *a240, *b240, *c240 );
 break;

case ACW_LIGHTFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glLightfv\n");
 break;

case ACW_LIGHTI:
 i += sizeof(glCommand);
 GLenum* a242 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b242 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* c242 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glLighti( *a242, *b242, *c242 );
 break;

case ACW_LIGHTIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glLightiv\n");
 break;

case ACW_LINESTIPPLE:
 i += sizeof(glCommand);
 GLint* a244 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLushort* b244 = (GLushort*) &buffer[i];
 i += sizeof(GLushort);
 glLineStipple( *a244, *b244 );
 break;

case ACW_LINEWIDTH:
 i += sizeof(glCommand);
 GLfloat* a245 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glLineWidth( *a245 );
 break;

case ACW_LISTBASE:
 i += sizeof(glCommand);
 GLuint* a246 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glListBase( *a246 );
 break;

case ACW_LISTPARAMETERFSGIX:
 i += sizeof(glCommand);
 GLuint* a247 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLenum* b247 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* c247 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glListParameterfSGIX( *a247, *b247, *c247 );
 break;

case ACW_LISTPARAMETERFVSGIX:
 i += sizeof(glCommand);
 printf("unwrapped gl: glListParameterfvSGIX\n");
 break;

case ACW_LISTPARAMETERISGIX:
 i += sizeof(glCommand);
 GLuint* a249 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLenum* b249 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* c249 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glListParameteriSGIX( *a249, *b249, *c249 );
 break;

case ACW_LISTPARAMETERIVSGIX:
 i += sizeof(glCommand);
 printf("unwrapped gl: glListParameterivSGIX\n");
 break;

case ACW_LOADIDENTITY:
 i += sizeof(glCommand);
 glLoadIdentity( );
 break;

case ACW_LOADIDENTITYDEFORMATIONMAPSGIX:
 i += sizeof(glCommand);
 GLbitfield* a252 = (GLbitfield*) &buffer[i];
 i += sizeof(GLbitfield);
 glLoadIdentityDeformationMapSGIX( *a252 );
 break;

case ACW_LOADMATRIXD:
 i += sizeof(glCommand);
 printf("unwrapped gl: glLoadMatrixd\n");
 break;

case ACW_LOADMATRIXF:
 i += sizeof(glCommand);
 printf("unwrapped gl: glLoadMatrixf\n");
 break;

case ACW_LOADNAME:
 i += sizeof(glCommand);
 GLuint* a255 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glLoadName( *a255 );
 break;

case ACW_LOGICOP:
 i += sizeof(glCommand);
 GLenum* a256 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glLogicOp( *a256 );
 break;

case ACW_MAP1D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glMap1d\n");
 break;

case ACW_MAP1F:
 i += sizeof(glCommand);
 printf("unwrapped gl: glMap1f\n");
 break;

case ACW_MAP2D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glMap2d\n");
 break;

case ACW_MAP2F:
 i += sizeof(glCommand);
 printf("unwrapped gl: glMap2f\n");
 break;

case ACW_MAPGRID1D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glMapGrid1d\n");
 break;

case ACW_MAPGRID1F:
 i += sizeof(glCommand);
 printf("unwrapped gl: glMapGrid1f\n");
 break;

case ACW_MAPGRID2D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glMapGrid2d\n");
 break;

case ACW_MAPGRID2F:
 i += sizeof(glCommand);
 printf("unwrapped gl: glMapGrid2f\n");
 break;

case ACW_MATERIALF:
 i += sizeof(glCommand);
 GLenum* a265 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b265 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* c265 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glMaterialf( *a265, *b265, *c265 );
 break;

case ACW_MATERIALFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glMaterialfv\n");
 break;

case ACW_MATERIALI:
 i += sizeof(glCommand);
 GLenum* a267 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b267 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* c267 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glMateriali( *a267, *b267, *c267 );
 break;

case ACW_MATERIALIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glMaterialiv\n");
 break;

case ACW_MATRIXMODE:
 i += sizeof(glCommand);
 GLenum* a269 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glMatrixMode( *a269 );
 break;

case ACW_MINMAX:
 i += sizeof(glCommand);
 GLenum* a270 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b270 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLboolean* c270 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 glMinmax( *a270, *b270, *c270 );
 break;

case ACW_MINMAXEXT:
 i += sizeof(glCommand);
 GLenum* a271 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b271 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLboolean* c271 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 glMinmaxEXT( *a271, *b271, *c271 );
 break;

case ACW_MULTMATRIXD:
 i += sizeof(glCommand);
 printf("unwrapped gl: glMultMatrixd\n");
 break;

case ACW_MULTMATRIXF:
 i += sizeof(glCommand);
 printf("unwrapped gl: glMultMatrixf\n");
 break;

case ACW_NEWLIST:
 i += sizeof(glCommand);
 GLuint* a274 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 GLenum* b274 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glNewList( *a274, *b274 );
 break;

case ACW_NORMAL3B:
 i += sizeof(glCommand);
 GLbyte* a275 = (GLbyte*) &buffer[i];
 i += sizeof(GLbyte)*3;
 glNormal3bv( a275 );
 break;

case ACW_NORMAL3BV:
 i += sizeof(glCommand);
 GLbyte* a276 = (GLbyte*) &buffer[i];
 i += sizeof(GLbyte)*3;
 glNormal3bv( a276 );
 break;

case ACW_NORMAL3D:
 i += sizeof(glCommand);
 GLdouble* a277 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glNormal3dv( a277 );
 break;

case ACW_NORMAL3DV:
 i += sizeof(glCommand);
 GLdouble* a278 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glNormal3dv( a278 );
 break;

case ACW_NORMAL3F:
 i += sizeof(glCommand);
 GLfloat* a279 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glNormal3fv( a279 );
 break;

case ACW_NORMAL3FV:
 i += sizeof(glCommand);
 GLfloat* a280 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glNormal3fv( a280 );
 break;

case ACW_NORMAL3I:
 i += sizeof(glCommand);
 GLint* a281 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glNormal3iv( a281 );
 break;

case ACW_NORMAL3IV:
 i += sizeof(glCommand);
 GLint* a282 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glNormal3iv( a282 );
 break;

case ACW_NORMAL3S:
 i += sizeof(glCommand);
 GLshort* a283 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glNormal3sv( a283 );
 break;

case ACW_NORMAL3SV:
 i += sizeof(glCommand);
 GLshort* a284 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glNormal3sv( a284 );
 break;

case ACW_NORMALPOINTER:
 i += sizeof(glCommand);
 printf("unwrapped gl: glNormalPointer\n");
 break;

case ACW_NORMALPOINTEREXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glNormalPointerEXT\n");
 break;

case ACW_ORTHO:
 i += sizeof(glCommand);
 GLdouble* a287 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* b287 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* c287 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* d287 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* e287 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* f287 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 glOrtho( *a287, *b287, *c287, *d287, *e287, *f287 );
 break;

case ACW_PASSTHROUGH:
 i += sizeof(glCommand);
 GLfloat* a288 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glPassThrough( *a288 );
 break;

case ACW_PIXELMAPFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glPixelMapfv\n");
 break;

case ACW_PIXELMAPUIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glPixelMapuiv\n");
 break;

case ACW_PIXELMAPUSV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glPixelMapusv\n");
 break;

case ACW_PIXELSTOREF:
 i += sizeof(glCommand);
 GLenum* a292 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* b292 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glPixelStoref( *a292, *b292 );
 break;

case ACW_PIXELSTOREI:
 i += sizeof(glCommand);
 GLenum* a293 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b293 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glPixelStorei( *a293, *b293 );
 break;

case ACW_PIXELTEXGENSGIX:
 i += sizeof(glCommand);
 GLenum* a294 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glPixelTexGenSGIX( *a294 );
 break;

case ACW_PIXELTRANSFERF:
 i += sizeof(glCommand);
 GLenum* a295 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* b295 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glPixelTransferf( *a295, *b295 );
 break;

case ACW_PIXELTRANSFERI:
 i += sizeof(glCommand);
 GLenum* a296 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b296 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glPixelTransferi( *a296, *b296 );
 break;

case ACW_PIXELZOOM:
 i += sizeof(glCommand);
 GLfloat* a297 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* b297 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glPixelZoom( *a297, *b297 );
 break;

case ACW_POINTPARAMETERFSGIS:
 i += sizeof(glCommand);
 GLenum* a298 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* b298 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glPointParameterfSGIS( *a298, *b298 );
 break;

case ACW_POINTPARAMETERFVSGIS:
 i += sizeof(glCommand);
 printf("unwrapped gl: glPointParameterfvSGIS\n");
 break;

case ACW_POINTSIZE:
 i += sizeof(glCommand);
 GLfloat* a300 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glPointSize( *a300 );
 break;

case ACW_POLLINSTRUMENTSSGIX:
 i += sizeof(glCommand);
 printf("unwrapped gl: glPollInstrumentsSGIX\n");
 break;

case ACW_POLYGONMODE:
 i += sizeof(glCommand);
 GLenum* a302 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b302 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glPolygonMode( *a302, *b302 );
 break;

case ACW_POLYGONOFFSET:
 i += sizeof(glCommand);
 GLfloat* a303 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* b303 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glPolygonOffset( *a303, *b303 );
 break;

case ACW_POLYGONOFFSETEXT:
 i += sizeof(glCommand);
 GLfloat* a304 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* b304 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glPolygonOffsetEXT( *a304, *b304 );
 break;

case ACW_POLYGONSTIPPLE:
 i += sizeof(glCommand);
 printf("unwrapped gl: glPolygonStipple\n");
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

case ACW_PRIORITIZETEXTURES:
 i += sizeof(glCommand);
 printf("unwrapped gl: glPrioritizeTextures\n");
 break;

case ACW_PRIORITIZETEXTURESEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glPrioritizeTexturesEXT\n");
 break;

case ACW_PUSHATTRIB:
 i += sizeof(glCommand);
 GLbitfield* a312 = (GLbitfield*) &buffer[i];
 i += sizeof(GLbitfield);
 glPushAttrib( *a312 );
 break;

case ACW_PUSHCLIENTATTRIB:
 i += sizeof(glCommand);
 GLbitfield* a313 = (GLbitfield*) &buffer[i];
 i += sizeof(GLbitfield);
 glPushClientAttrib( *a313 );
 break;

case ACW_PUSHMATRIX:
 i += sizeof(glCommand);
 glPushMatrix( );
 break;

case ACW_PUSHNAME:
 i += sizeof(glCommand);
 GLuint* a315 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glPushName( *a315 );
 break;

case ACW_RASTERPOS2D:
 i += sizeof(glCommand);
 GLdouble* a316 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*2;
 glRasterPos2dv( a316 );
 break;

case ACW_RASTERPOS2DV:
 i += sizeof(glCommand);
 GLdouble* a317 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*2;
 glRasterPos2dv( a317 );
 break;

case ACW_RASTERPOS2F:
 i += sizeof(glCommand);
 GLfloat* a318 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*2;
 glRasterPos2fv( a318 );
 break;

case ACW_RASTERPOS2FV:
 i += sizeof(glCommand);
 GLfloat* a319 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*2;
 glRasterPos2fv( a319 );
 break;

case ACW_RASTERPOS2I:
 i += sizeof(glCommand);
 GLint* a320 = (GLint*) &buffer[i];
 i += sizeof(GLint)*2;
 glRasterPos2iv( a320 );
 break;

case ACW_RASTERPOS2IV:
 i += sizeof(glCommand);
 GLint* a321 = (GLint*) &buffer[i];
 i += sizeof(GLint)*2;
 glRasterPos2iv( a321 );
 break;

case ACW_RASTERPOS2S:
 i += sizeof(glCommand);
 GLshort* a322 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*2;
 glRasterPos2sv( a322 );
 break;

case ACW_RASTERPOS2SV:
 i += sizeof(glCommand);
 GLshort* a323 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*2;
 glRasterPos2sv( a323 );
 break;

case ACW_RASTERPOS3D:
 i += sizeof(glCommand);
 GLdouble* a324 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glRasterPos3dv( a324 );
 break;

case ACW_RASTERPOS3DV:
 i += sizeof(glCommand);
 GLdouble* a325 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glRasterPos3dv( a325 );
 break;

case ACW_RASTERPOS3F:
 i += sizeof(glCommand);
 GLfloat* a326 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glRasterPos3fv( a326 );
 break;

case ACW_RASTERPOS3FV:
 i += sizeof(glCommand);
 GLfloat* a327 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glRasterPos3fv( a327 );
 break;

case ACW_RASTERPOS3I:
 i += sizeof(glCommand);
 GLint* a328 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glRasterPos3iv( a328 );
 break;

case ACW_RASTERPOS3IV:
 i += sizeof(glCommand);
 GLint* a329 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glRasterPos3iv( a329 );
 break;

case ACW_RASTERPOS3S:
 i += sizeof(glCommand);
 GLshort* a330 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glRasterPos3sv( a330 );
 break;

case ACW_RASTERPOS3SV:
 i += sizeof(glCommand);
 GLshort* a331 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glRasterPos3sv( a331 );
 break;

case ACW_RASTERPOS4D:
 i += sizeof(glCommand);
 GLdouble* a332 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*4;
 glRasterPos4dv( a332 );
 break;

case ACW_RASTERPOS4DV:
 i += sizeof(glCommand);
 GLdouble* a333 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*4;
 glRasterPos4dv( a333 );
 break;

case ACW_RASTERPOS4F:
 i += sizeof(glCommand);
 GLfloat* a334 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*4;
 glRasterPos4fv( a334 );
 break;

case ACW_RASTERPOS4FV:
 i += sizeof(glCommand);
 GLfloat* a335 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*4;
 glRasterPos4fv( a335 );
 break;

case ACW_RASTERPOS4I:
 i += sizeof(glCommand);
 GLint* a336 = (GLint*) &buffer[i];
 i += sizeof(GLint)*4;
 glRasterPos4iv( a336 );
 break;

case ACW_RASTERPOS4IV:
 i += sizeof(glCommand);
 GLint* a337 = (GLint*) &buffer[i];
 i += sizeof(GLint)*4;
 glRasterPos4iv( a337 );
 break;

case ACW_RASTERPOS4S:
 i += sizeof(glCommand);
 GLshort* a338 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*4;
 glRasterPos4sv( a338 );
 break;

case ACW_RASTERPOS4SV:
 i += sizeof(glCommand);
 GLshort* a339 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*4;
 glRasterPos4sv( a339 );
 break;

case ACW_READBUFFER:
 i += sizeof(glCommand);
 GLenum* a340 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glReadBuffer( *a340 );
 break;

case ACW_READINSTRUMENTSSGIX:
 i += sizeof(glCommand);
 GLint* a341 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glReadInstrumentsSGIX( *a341 );
 break;

case ACW_READPIXELS:
 i += sizeof(glCommand);
 printf("unwrapped gl: glReadPixels\n");
 break;

case ACW_RECTD:
 i += sizeof(glCommand);
 GLdouble* a343 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* b343 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* c343 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* d343 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 glRectd( *a343, *b343, *c343, *d343 );
 break;

case ACW_RECTDV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glRectdv\n");
 break;

case ACW_RECTF:
 i += sizeof(glCommand);
 GLfloat* a345 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* b345 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* c345 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* d345 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glRectf( *a345, *b345, *c345, *d345 );
 break;

case ACW_RECTFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glRectfv\n");
 break;

case ACW_RECTI:
 i += sizeof(glCommand);
 GLint* a347 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* b347 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* c347 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* d347 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glRecti( *a347, *b347, *c347, *d347 );
 break;

case ACW_RECTIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glRectiv\n");
 break;

case ACW_RECTS:
 i += sizeof(glCommand);
 GLshort* a349 = (GLshort*) &buffer[i];
 i += sizeof(GLshort);
 GLshort* b349 = (GLshort*) &buffer[i];
 i += sizeof(GLshort);
 GLshort* c349 = (GLshort*) &buffer[i];
 i += sizeof(GLshort);
 GLshort* d349 = (GLshort*) &buffer[i];
 i += sizeof(GLshort);
 glRects( *a349, *b349, *c349, *d349 );
 break;

case ACW_RECTSV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glRectsv\n");
 break;

case ACW_REFERENCEPLANESGIX:
 i += sizeof(glCommand);
 printf("unwrapped gl: glReferencePlaneSGIX\n");
 break;

case ACW_RENDERMODE:
 i += sizeof(glCommand);
 GLenum* a352 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glRenderMode( *a352 );
 break;

case ACW_RESETHISTOGRAM:
 i += sizeof(glCommand);
 printf("unwrapped gl: glResetHistogram\n");
 break;

case ACW_RESETHISTOGRAMEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glResetHistogramEXT\n");
 break;

case ACW_RESETMINMAX:
 i += sizeof(glCommand);
 printf("unwrapped gl: glResetMinmax\n");
 break;

case ACW_RESETMINMAXEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glResetMinmaxEXT\n");
 break;

case ACW_ROTATED:
 i += sizeof(glCommand);
 printf("unwrapped gl: glRotated\n");
 break;

case ACW_ROTATEF:
 i += sizeof(glCommand);
 GLfloat* a358 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* b358 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* c358 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* d358 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glRotatef( *a358, *b358, *c358, *d358 );
 break;

case ACW_SAMPLEMASKSGIS:
 i += sizeof(glCommand);
 GLclampf* a359 = (GLclampf*) &buffer[i];
 i += sizeof(GLclampf);
 GLboolean* b359 = (GLboolean*) &buffer[i];
 i += sizeof(GLboolean);
 glSampleMaskSGIS( *a359, *b359 );
 break;

case ACW_SAMPLEPATTERNSGIS:
 i += sizeof(glCommand);
 GLenum* a360 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glSamplePatternSGIS( *a360 );
 break;

case ACW_SCALED:
 i += sizeof(glCommand);
 GLdouble* a361 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* b361 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* c361 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 glScaled( *a361, *b361, *c361 );
 break;

case ACW_SCALEF:
 i += sizeof(glCommand);
 GLfloat* a362 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* b362 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* c362 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glScalef( *a362, *b362, *c362 );
 break;

case ACW_SCISSOR:
 i += sizeof(glCommand);
 GLint* a363 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* b363 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLsizei* c363 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 GLsizei* d363 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 glScissor( *a363, *b363, *c363, *d363 );
 break;

case ACW_SELECTBUFFER:
 i += sizeof(glCommand);
 printf("unwrapped gl: glSelectBuffer\n");
 break;

case ACW_SEPARABLEFILTER2D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glSeparableFilter2D\n");
 break;

case ACW_SEPARABLEFILTER2DEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glSeparableFilter2DEXT\n");
 break;

case ACW_SHADEMODEL:
 i += sizeof(glCommand);
 GLenum* a367 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glShadeModel( *a367 );
 break;

case ACW_SHARPENTEXFUNCSGIS:
 i += sizeof(glCommand);
 printf("unwrapped gl: glSharpenTexFuncSGIS\n");
 break;

case ACW_SPRITEPARAMETERFSGIX:
 i += sizeof(glCommand);
 printf("unwrapped gl: glSpriteParameterfSGIX\n");
 break;

case ACW_SPRITEPARAMETERFVSGIX:
 i += sizeof(glCommand);
 printf("unwrapped gl: glSpriteParameterfvSGIX\n");
 break;

case ACW_SPRITEPARAMETERISGIX:
 i += sizeof(glCommand);
 printf("unwrapped gl: glSpriteParameteriSGIX\n");
 break;

case ACW_SPRITEPARAMETERIVSGIX:
 i += sizeof(glCommand);
 printf("unwrapped gl: glSpriteParameterivSGIX\n");
 break;

case ACW_STARTINSTRUMENTSSGIX:
 i += sizeof(glCommand);
 glStartInstrumentsSGIX( );
 break;

case ACW_STENCILFUNC:
 i += sizeof(glCommand);
 GLenum* a374 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* b374 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLuint* c374 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glStencilFunc( *a374, *b374, *c374 );
 break;

case ACW_STENCILMASK:
 i += sizeof(glCommand);
 GLuint* a375 = (GLuint*) &buffer[i];
 i += sizeof(GLuint);
 glStencilMask( *a375 );
 break;

case ACW_STENCILOP:
 i += sizeof(glCommand);
 GLenum* a376 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b376 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* c376 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 glStencilOp( *a376, *b376, *c376 );
 break;

case ACW_STOPINSTRUMENTSSGIX:
 i += sizeof(glCommand);
 GLint* a377 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glStopInstrumentsSGIX( *a377 );
 break;

case ACW_TAGSAMPLEBUFFERSGIX:
 i += sizeof(glCommand);
 glTagSampleBufferSGIX( );
 break;

case ACW_TEXCOORD1D:
 i += sizeof(glCommand);
 GLdouble* a379 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*1;
 glTexCoord1dv( a379 );
 break;

case ACW_TEXCOORD1DV:
 i += sizeof(glCommand);
 GLdouble* a380 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*1;
 glTexCoord1dv( a380 );
 break;

case ACW_TEXCOORD1F:
 i += sizeof(glCommand);
 GLfloat* a381 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*1;
 glTexCoord1fv( a381 );
 break;

case ACW_TEXCOORD1FV:
 i += sizeof(glCommand);
 GLfloat* a382 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*1;
 glTexCoord1fv( a382 );
 break;

case ACW_TEXCOORD1I:
 i += sizeof(glCommand);
 GLint* a383 = (GLint*) &buffer[i];
 i += sizeof(GLint)*1;
 glTexCoord1iv( a383 );
 break;

case ACW_TEXCOORD1IV:
 i += sizeof(glCommand);
 GLint* a384 = (GLint*) &buffer[i];
 i += sizeof(GLint)*1;
 glTexCoord1iv( a384 );
 break;

case ACW_TEXCOORD1S:
 i += sizeof(glCommand);
 GLshort* a385 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*1;
 glTexCoord1sv( a385 );
 break;

case ACW_TEXCOORD1SV:
 i += sizeof(glCommand);
 GLshort* a386 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*1;
 glTexCoord1sv( a386 );
 break;

case ACW_TEXCOORD2D:
 i += sizeof(glCommand);
 GLdouble* a387 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*2;
 glTexCoord2dv( a387 );
 break;

case ACW_TEXCOORD2DV:
 i += sizeof(glCommand);
 GLdouble* a388 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*2;
 glTexCoord2dv( a388 );
 break;

case ACW_TEXCOORD2F:
 i += sizeof(glCommand);
 GLfloat* a389 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*2;
 glTexCoord2fv( a389 );
 break;

case ACW_TEXCOORD2FV:
 i += sizeof(glCommand);
 GLfloat* a390 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*2;
 glTexCoord2fv( a390 );
 break;

case ACW_TEXCOORD2I:
 i += sizeof(glCommand);
 GLint* a391 = (GLint*) &buffer[i];
 i += sizeof(GLint)*2;
 glTexCoord2iv( a391 );
 break;

case ACW_TEXCOORD2IV:
 i += sizeof(glCommand);
 GLint* a392 = (GLint*) &buffer[i];
 i += sizeof(GLint)*2;
 glTexCoord2iv( a392 );
 break;

case ACW_TEXCOORD2S:
 i += sizeof(glCommand);
 GLshort* a393 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*2;
 glTexCoord2sv( a393 );
 break;

case ACW_TEXCOORD2SV:
 i += sizeof(glCommand);
 GLshort* a394 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*2;
 glTexCoord2sv( a394 );
 break;

case ACW_TEXCOORD3D:
 i += sizeof(glCommand);
 GLdouble* a395 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glTexCoord3dv( a395 );
 break;

case ACW_TEXCOORD3DV:
 i += sizeof(glCommand);
 GLdouble* a396 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glTexCoord3dv( a396 );
 break;

case ACW_TEXCOORD3F:
 i += sizeof(glCommand);
 GLfloat* a397 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glTexCoord3fv( a397 );
 break;

case ACW_TEXCOORD3FV:
 i += sizeof(glCommand);
 GLfloat* a398 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glTexCoord3fv( a398 );
 break;

case ACW_TEXCOORD3I:
 i += sizeof(glCommand);
 GLint* a399 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glTexCoord3iv( a399 );
 break;

case ACW_TEXCOORD3IV:
 i += sizeof(glCommand);
 GLint* a400 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glTexCoord3iv( a400 );
 break;

case ACW_TEXCOORD3S:
 i += sizeof(glCommand);
 GLshort* a401 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glTexCoord3sv( a401 );
 break;

case ACW_TEXCOORD3SV:
 i += sizeof(glCommand);
 GLshort* a402 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glTexCoord3sv( a402 );
 break;

case ACW_TEXCOORD4D:
 i += sizeof(glCommand);
 GLdouble* a403 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*4;
 glTexCoord4dv( a403 );
 break;

case ACW_TEXCOORD4DV:
 i += sizeof(glCommand);
 GLdouble* a404 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*4;
 glTexCoord4dv( a404 );
 break;

case ACW_TEXCOORD4F:
 i += sizeof(glCommand);
 GLfloat* a405 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*4;
 glTexCoord4fv( a405 );
 break;

case ACW_TEXCOORD4FV:
 i += sizeof(glCommand);
 GLfloat* a406 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*4;
 glTexCoord4fv( a406 );
 break;

case ACW_TEXCOORD4I:
 i += sizeof(glCommand);
 GLint* a407 = (GLint*) &buffer[i];
 i += sizeof(GLint)*4;
 glTexCoord4iv( a407 );
 break;

case ACW_TEXCOORD4IV:
 i += sizeof(glCommand);
 GLint* a408 = (GLint*) &buffer[i];
 i += sizeof(GLint)*4;
 glTexCoord4iv( a408 );
 break;

case ACW_TEXCOORD4S:
 i += sizeof(glCommand);
 GLshort* a409 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*4;
 glTexCoord4sv( a409 );
 break;

case ACW_TEXCOORD4SV:
 i += sizeof(glCommand);
 GLshort* a410 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*4;
 glTexCoord4sv( a410 );
 break;

case ACW_TEXCOORDPOINTER:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexCoordPointer\n");
 break;

case ACW_TEXCOORDPOINTEREXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexCoordPointerEXT\n");
 break;

case ACW_TEXENVF:
 i += sizeof(glCommand);
 GLenum* a413 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b413 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* c413 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glTexEnvf( *a413, *b413, *c413 );
 break;

case ACW_TEXENVFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexEnvfv\n");
 break;

case ACW_TEXENVI:
 i += sizeof(glCommand);
 GLenum* a415 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b415 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* c415 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glTexEnvi( *a415, *b415, *c415 );
 break;

case ACW_TEXENVIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexEnviv\n");
 break;

case ACW_TEXFILTERFUNCSGIS:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexFilterFuncSGIS\n");
 break;

case ACW_TEXGEND:
 i += sizeof(glCommand);
 GLenum* a418 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b418 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLdouble* c418 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 glTexGend( *a418, *b418, *c418 );
 break;

case ACW_TEXGENDV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexGendv\n");
 break;

case ACW_TEXGENF:
 i += sizeof(glCommand);
 GLenum* a420 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b420 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* c420 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glTexGenf( *a420, *b420, *c420 );
 break;

case ACW_TEXGENFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexGenfv\n");
 break;

case ACW_TEXGENI:
 i += sizeof(glCommand);
 GLenum* a422 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b422 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* c422 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glTexGeni( *a422, *b422, *c422 );
 break;

case ACW_TEXGENIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexGeniv\n");
 break;

case ACW_TEXIMAGE1D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexImage1D\n");
 break;

case ACW_TEXIMAGE2D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexImage2D\n");
 break;

case ACW_TEXIMAGE3D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexImage3D\n");
 break;

case ACW_TEXIMAGE3DEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexImage3DEXT\n");
 break;

case ACW_TEXIMAGE4DSGIS:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexImage4DSGIS\n");
 break;

case ACW_TEXPARAMETERF:
 i += sizeof(glCommand);
 GLenum* a429 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b429 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLfloat* c429 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glTexParameterf( *a429, *b429, *c429 );
 break;

case ACW_TEXPARAMETERFV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexParameterfv\n");
 break;

case ACW_TEXPARAMETERI:
 i += sizeof(glCommand);
 GLenum* a431 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLenum* b431 = (GLenum*) &buffer[i];
 i += sizeof(GLenum);
 GLint* c431 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 glTexParameteri( *a431, *b431, *c431 );
 break;

case ACW_TEXPARAMETERIV:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexParameteriv\n");
 break;

case ACW_TEXSUBIMAGE1D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexSubImage1D\n");
 break;

case ACW_TEXSUBIMAGE1DEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexSubImage1DEXT\n");
 break;

case ACW_TEXSUBIMAGE2D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexSubImage2D\n");
 break;

case ACW_TEXSUBIMAGE2DEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexSubImage2DEXT\n");
 break;

case ACW_TEXSUBIMAGE3D:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexSubImage3D\n");
 break;

case ACW_TEXSUBIMAGE3DEXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexSubImage3DEXT\n");
 break;

case ACW_TEXSUBIMAGE4DSGIS:
 i += sizeof(glCommand);
 printf("unwrapped gl: glTexSubImage4DSGIS\n");
 break;

case ACW_TRANSLATED:
 i += sizeof(glCommand);
 GLdouble* a440 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* b440 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 GLdouble* c440 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble);
 glTranslated( *a440, *b440, *c440 );
 break;

case ACW_TRANSLATEF:
 i += sizeof(glCommand);
 GLfloat* a441 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* b441 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 GLfloat* c441 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat);
 glTranslatef( *a441, *b441, *c441 );
 break;

case ACW_VERTEX2D:
 i += sizeof(glCommand);
 GLdouble* a442 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*2;
 glVertex2dv( a442 );
 break;

case ACW_VERTEX2DV:
 i += sizeof(glCommand);
 GLdouble* a443 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*2;
 glVertex2dv( a443 );
 break;

case ACW_VERTEX2F:
 i += sizeof(glCommand);
 GLfloat* a444 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*2;
 glVertex2fv( a444 );
 break;

case ACW_VERTEX2FV:
 i += sizeof(glCommand);
 GLfloat* a445 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*2;
 glVertex2fv( a445 );
 break;

case ACW_VERTEX2I:
 i += sizeof(glCommand);
 GLint* a446 = (GLint*) &buffer[i];
 i += sizeof(GLint)*2;
 glVertex2iv( a446 );
 break;

case ACW_VERTEX2IV:
 i += sizeof(glCommand);
 GLint* a447 = (GLint*) &buffer[i];
 i += sizeof(GLint)*2;
 glVertex2iv( a447 );
 break;

case ACW_VERTEX2S:
 i += sizeof(glCommand);
 GLshort* a448 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*2;
 glVertex2sv( a448 );
 break;

case ACW_VERTEX2SV:
 i += sizeof(glCommand);
 GLshort* a449 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*2;
 glVertex2sv( a449 );
 break;

case ACW_VERTEX3D:
 i += sizeof(glCommand);
 GLdouble* a450 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glVertex3dv( a450 );
 break;

case ACW_VERTEX3DV:
 i += sizeof(glCommand);
 GLdouble* a451 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*3;
 glVertex3dv( a451 );
 break;

case ACW_VERTEX3F:
 i += sizeof(glCommand);
 GLfloat* a452 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glVertex3fv( a452 );
 break;

case ACW_VERTEX3FV:
 i += sizeof(glCommand);
 GLfloat* a453 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*3;
 glVertex3fv( a453 );
 break;

case ACW_VERTEX3I:
 i += sizeof(glCommand);
 GLint* a454 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glVertex3iv( a454 );
 break;

case ACW_VERTEX3IV:
 i += sizeof(glCommand);
 GLint* a455 = (GLint*) &buffer[i];
 i += sizeof(GLint)*3;
 glVertex3iv( a455 );
 break;

case ACW_VERTEX3S:
 i += sizeof(glCommand);
 GLshort* a456 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glVertex3sv( a456 );
 break;

case ACW_VERTEX3SV:
 i += sizeof(glCommand);
 GLshort* a457 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*3;
 glVertex3sv( a457 );
 break;

case ACW_VERTEX4D:
 i += sizeof(glCommand);
 GLdouble* a458 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*4;
 glVertex4dv( a458 );
 break;

case ACW_VERTEX4DV:
 i += sizeof(glCommand);
 GLdouble* a459 = (GLdouble*) &buffer[i];
 i += sizeof(GLdouble)*4;
 glVertex4dv( a459 );
 break;

case ACW_VERTEX4F:
 i += sizeof(glCommand);
 GLfloat* a460 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*4;
 glVertex4fv( a460 );
 break;

case ACW_VERTEX4FV:
 i += sizeof(glCommand);
 GLfloat* a461 = (GLfloat*) &buffer[i];
 i += sizeof(GLfloat)*4;
 glVertex4fv( a461 );
 break;

case ACW_VERTEX4I:
 i += sizeof(glCommand);
 GLint* a462 = (GLint*) &buffer[i];
 i += sizeof(GLint)*4;
 glVertex4iv( a462 );
 break;

case ACW_VERTEX4IV:
 i += sizeof(glCommand);
 GLint* a463 = (GLint*) &buffer[i];
 i += sizeof(GLint)*4;
 glVertex4iv( a463 );
 break;

case ACW_VERTEX4S:
 i += sizeof(glCommand);
 GLshort* a464 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*4;
 glVertex4sv( a464 );
 break;

case ACW_VERTEX4SV:
 i += sizeof(glCommand);
 GLshort* a465 = (GLshort*) &buffer[i];
 i += sizeof(GLshort)*4;
 glVertex4sv( a465 );
 break;

case ACW_VERTEXPOINTER:
 i += sizeof(glCommand);
 printf("unwrapped gl: glVertexPointer\n");
 break;

case ACW_VERTEXPOINTEREXT:
 i += sizeof(glCommand);
 printf("unwrapped gl: glVertexPointerEXT\n");
 break;

case ACW_VIEWPORT:
 i += sizeof(glCommand);
 GLint* a468 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLint* b468 = (GLint*) &buffer[i];
 i += sizeof(GLint);
 GLsizei* c468 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 GLsizei* d468 = (GLsizei*) &buffer[i];
 i += sizeof(GLsizei);
 glViewport( *a468, *b468, *c468, *d468 );
 break;

}
}
}
