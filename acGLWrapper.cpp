
#include "acGLWrapper.h"
	
static unsigned char* buffer = NULL;
static long bufferSize = 0;
static long bufferAllocSize = 0; 

/*---------------------- wrapper utility ---------------*/

void acGLWrapStart()
{
  bufferSize = 0;
}

void acGLWrapFinish()
{
  
}

void acGLWrapSetBuffer( unsigned char* B, long Bsize )
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

void* acGLWrapGetBuffer() 
{ 
  return buffer; 
}

long acGLWrapGetBufferSize() 
{ 
  return bufferSize;
}
