#include "acu.h"


/* acuVideoXXX are externs from other files (such as acu.h)
 * acuvXXX are only used within this file (video.c)
 */
boolean acuVideoOpened;
int acuVideoWidth;
int acuVideoHeight;
int acuVideoArrayWidth;
int acuVideoArrayHeight;
boolean acuVideoMirrorImage;

int acuvActualWidth;
int acuvActualHeight;

boolean acuVideoProxyRepeating;
int acuVideoProxyCount;

int acuVideoProxyRawWidth;
int acuVideoProxyRawHeight;

boolean acuvProxy;
boolean acuvProxyRaw;
int acuvFrameIndex;
char acuvFilenameTemplate[64];
char acuvFilename[64];
float acuvZoom;

#ifdef ACU_IRIX
VLServer acuvServer;
VLPath acuvPath;
VLNode acuvSrcNode;
VLNode acuvDrnNode;
VLBuffer acuvBuffer;
VLInfoPtr acuvInfoPtr;
VLControlValue acuvControlVal;
#endif /* ACU_IRIX */


void acuOpenVideo() {
#ifdef ACU_IRIX
  if (acuVideoOpened) {
    acuDebug(ACU_DEBUG_USEFUL, "acuVideo already opened");
    return;
  }

  if (!(acuvServer = vlOpenVideo(""))) {
    acuDebug(ACU_DEBUG_EMERGENCY, "vlOpenVideo problem");
    return;
  }

  acuvDrnNode = vlGetNode(acuvServer, VL_DRN, VL_MEM, VL_ANY);
  acuvSrcNode = vlGetNode(acuvServer, VL_SRC, VL_VIDEO, VL_ANY);

  acuvPath = vlCreatePath(acuvServer, VL_ANY, 
			   acuvSrcNode, acuvDrnNode); 

  if ((vlSetupPaths(acuvServer, (VLPathList)&acuvPath, 
		    1, VL_SHARE, VL_SHARE)) < 0) {
    acuDebug(ACU_DEBUG_EMERGENCY, "vlSetupPaths problem");
    return;
  }

  acuvControlVal.intVal = VL_PACKING_RGB_8;
  vlSetControl(acuvServer, acuvPath, 
	       acuvDrnNode, VL_PACKING, &acuvControlVal);

  vlGetControl(acuvServer, acuvPath, 
	       acuvDrnNode, VL_SIZE, &acuvControlVal);

  acuVideoWidth = acuvControlVal.xyVal.x;
  acuVideoHeight = acuvControlVal.xyVal.y;

  acuvActualWidth = acuVideoWidth;
  acuvActualHeight = acuVideoHeight;

  acuVideoArrayWidth = acuVideoWidth;
  acuVideoArrayHeight = acuVideoHeight;

  acuVideoOpened = TRUE;
  acuvProxy = FALSE;
#else /* ACU_IRIX */
  acuVideoOpened = FALSE;
  acuDebug(ACU_DEBUG_EMERGENCY, 
	   "Video not yet implemented on this platform.");
#endif
}


void acuOpenVideoProxy(char *filenameTemplate) {
  FILE *fp;
  unsigned char *ignored;
  
  /* save that fer later */
  strcpy(acuvFilenameTemplate, filenameTemplate);

  /* figure out if it's raw, if so, set the flag */
  acuvProxyRaw = FALSE;
  if (strstr(filenameTemplate, ".raw"))
    acuvProxyRaw = TRUE;
  if (strstr(filenameTemplate, ".RAW"))
    acuvProxyRaw = TRUE;
  
  /* find out how many frames are available enterprising
   * individuals can set the count themselves
   */
  if (acuVideoProxyCount == -1) {
    acuVideoProxyCount = 0;
    while (TRUE) {
      sprintf(acuvFilename, acuvFilenameTemplate,
	      acuVideoProxyCount);
      fp = fopen(acuvFilename, "rb");
      if (fp == NULL) break;
      fclose(fp);
      acuVideoProxyCount++;
    }
  }
  if (acuVideoProxyCount == 0) {
    sprintf(acuDebugStr, "Could not load proxy files starting at %s", 
	    acuvFilename);
    acuDebugString(ACU_DEBUG_EMERGENCY);
  }
  
  /* figure out the dimensions of the proxy image */
  if (!acuvProxyRaw) {
    sprintf(acuvFilename, filenameTemplate, 0);
    ignored = acuReadJpegFile(acuvFilename, 
			      &acuvActualWidth, &acuvActualHeight);
    free(ignored);
  } else {
    acuvActualWidth = acuVideoProxyRawWidth;
    acuvActualHeight = acuVideoProxyRawHeight;
    printf("%d %d\n", acuvActualWidth, acuvActualHeight);
  }
  
  /* get this thing off on the right foot */
  acuvFrameIndex = 0;
  
  /* finish up */
  acuvProxy = TRUE;
  acuvZoom = 1.0;
  acuVideoWidth = acuvActualWidth;
  acuVideoHeight = acuvActualHeight;
  acuVideoArrayWidth = acuVideoWidth;
  acuVideoArrayHeight = acuVideoHeight;
  acuVideoOpened = TRUE;
}


void acuvRequestZoom(int numer, int denom) {
#ifdef ACU_IRIX
  acuvControlVal.fractVal.numerator = numer;
  acuvControlVal.fractVal.denominator = denom;
  
  vlSetControl(acuvServer, acuvPath, 
	       acuvDrnNode, VL_ZOOM, &acuvControlVal);
  vlGetControl(acuvServer, acuvPath, 
	       acuvDrnNode, VL_SIZE, &acuvControlVal);
  
  acuVideoWidth = acuvControlVal.xyVal.x;
  acuVideoHeight = acuvControlVal.xyVal.y;
#endif /* ACU_IRIX */
}


void acuRequestVideoSize(GLint *width, GLint *height) {
  int wide = *width;
  int high = *height;
  int value;

  float zoom = (((float)wide / (float)acuvActualWidth) + 
		((float)high / (float)acuvActualHeight)) / 2.0f;    
  
  if (acuvProxy) {
    acuvZoom = 1.0 / zoom;
    acuVideoWidth = (acuvActualWidth * zoom);
    acuVideoHeight = (acuvActualHeight * zoom);
    
  } else {
    int numerator, denominator;
    if (zoom < 1.0) {
      /* smaller image */
      numerator = 1;
      value = ROUND(1.0 / zoom);
      if (value == 0) value = 1;
      denominator = value;
    } else {
      /* larger image */
      numerator = ROUND(zoom);
      /*value = ROUND(zoom);
	if (value == 0) value = 1;*/
      denominator = 1;
    }
    acuvRequestZoom(numerator, denominator);
  }
  acuVideoArrayWidth = acuVideoWidth;
  acuVideoArrayHeight = acuVideoHeight;
  *width = acuVideoWidth;
  *height = acuVideoHeight;
}


void acuvGetProxyFrame(unsigned char *frame) {
  int srcOffset, srcIndex, destIndex;
  int i, j, iw, ih;
  unsigned char *data;
  
  /* load the current file into a buffer */
  sprintf(acuvFilename, acuvFilenameTemplate, acuvFrameIndex);
  if (acuvProxyRaw) {
    int ignored;
    data = acuReadRawFile(acuvFilename, &ignored);
    //acuVideoWidth*acuVideoHeight*3);
  } else {
    data = acuReadJpegFile(acuvFilename, &iw, &ih);
  }

  destIndex = acuVideoMirrorImage ? (acuVideoWidth-1)*3 : 0;
  for (j = 0; j < acuVideoHeight; j++) {
    /*srcOffset = (((j * acuvZoomDenom) / acuvZoomNumer) * 
		 acuVideoArrayWidth * 3);*/
    srcOffset = (floor((float)j * acuvZoom)) * acuvActualWidth * 3;
    for (i = 0; i < acuVideoWidth; i++) {
      /*srcIndex = srcOffset + ((i * acuvZoomDenom) / acuvZoomNumer) * 3;*/
      srcIndex = srcOffset + (floor((float)i * acuvZoom)) * 3;

      frame[destIndex+0] = data[srcIndex+0];
      frame[destIndex+1] = data[srcIndex+1];
      frame[destIndex+2] = data[srcIndex+2];

      if (acuVideoMirrorImage)
	destIndex -= 3;
      else 
	destIndex += 3;
    }
    if (acuVideoMirrorImage) {
      destIndex += (acuVideoArrayWidth*3*2 -
		    (acuVideoArrayWidth-acuVideoWidth)*3);
    } else {
      destIndex += (acuVideoArrayWidth - acuVideoWidth)*3;
    }
  }
  acuvFrameIndex++;
  if (acuvFrameIndex == acuVideoProxyCount) {
    //printf("resetting, count is %d\n", acuVideoProxyCount);
    acuVideoProxyRepeating = TRUE;
    acuvFrameIndex = 0;
  }
  free(data);
}


void acuvGetFrame(unsigned char *frame) {
#ifdef ACU_IRIX
  unsigned long *dataPtr;
  unsigned long *pixelPtr;
  unsigned char *part; 
  int i, j, destIndex;
  
  if (acuvBuffer == NULL) {
    acuvBuffer = vlCreateBuffer(acuvServer, acuvPath, acuvDrnNode, 2);
    if (acuvBuffer != NULL) {
      vlRegisterBuffer(acuvServer, acuvPath, acuvDrnNode, acuvBuffer);  
      if (vlBeginTransfer(acuvServer, acuvPath, 0, NULL) == 0) {
	return;
      } else {
	acuDebug(ACU_DEBUG_EMERGENCY, "vlBeginTransfer problem");
      }
    } else {
      acuDebug(ACU_DEBUG_EMERGENCY, "vlCreateBuffer problem");
    }
  }
  
  acuvInfoPtr = vlGetNextValid(acuvServer, acuvBuffer);
  if (!acuvInfoPtr) return;
  
  dataPtr = (unsigned long *) 
    vlGetActiveRegion(acuvServer, acuvBuffer, acuvInfoPtr);
  pixelPtr = dataPtr;
  // part; // = (unsigned char *)dataPtr;
  
  destIndex = (acuVideoMirrorImage ? (acuVideoWidth-1)*3 : 0);  
  for (j = 0; j < acuVideoHeight; j++) {  
    for(i = 0; i < acuVideoWidth; i++) {
      part = (unsigned char *)pixelPtr;
      ++part; // skip AA;
      frame[destIndex + 2] = (*part++);
      frame[destIndex + 1] = (*part++);
      frame[destIndex + 0] = (*part++);
      
      // advance to next pixel;
      pixelPtr++;
      
      if (acuVideoMirrorImage)
	destIndex -= 3;
      else
	destIndex += 3;
    }
    if (acuVideoMirrorImage)
      destIndex += (acuVideoArrayWidth*3*2 - 
		    (acuVideoArrayWidth-acuVideoWidth)*3);
    else
      destIndex += (acuVideoArrayWidth - acuVideoWidth)*3;
  }
  /* discard current frame */
  vlPutFree(acuvServer, acuvBuffer);  
  acuvInfoPtr = 0;
#endif /* ACU_IRIX */
}


void acuGetVideoFrame(unsigned char *frame) {
  if (!acuVideoOpened) {
    acuDebug(ACU_DEBUG_PROBLEM, "Video not opened");
  }
  
  if (acuvProxy) {
    acuvGetProxyFrame(frame);
  } else {
    acuvGetFrame(frame);
  }
}


void acuCloseVideo() {
  if (acuvProxy) {	
    acuVideoProxyCount = -1;
    
  } else {
#ifdef ACU_IRIX
    vlEndTransfer(acuvServer, acuvPath);     
    vlDeregisterBuffer(acuvServer, acuvPath, acuvDrnNode, acuvBuffer);
    vlDestroyBuffer(acuvServer, acuvBuffer);
    vlDestroyPath(acuvServer, acuvPath);
    vlCloseVideo(acuvServer);
#endif /* ACU_IRIX */
  }
}
