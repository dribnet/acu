
#include "acGLWrapper.h"

class glUnwrapper
{
public:
  glUnwrapper();

  void setBuffer( unsigned char* B, long Bsize );
  void* getBuffer();
  long getBufferSize();
  
  /* data read and apply calls */
  void Apply();

protected:
  unsigned char* buffer;
  long bufferSize;
  long bufferAllocSize; 
};
