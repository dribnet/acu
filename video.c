#include "acu.h"


/* acu2: acuOpenVideo(&width, &height) instead of requesting size 
   gets rid of acuVideoRequestSize, since a size is always specified
   by the programmer anyways */

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

int acuVideoFPS;

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


#ifdef ACU_LINUX
FILE *acuvStream = NULL;
int acuvTempBufferCount;
unsigned char *acuvTempBuffer = NULL;
#endif


#ifdef ACU_WIN32
#ifndef __CYGWIN__
/* cygwin doesn't know what Vfw.h is */
/* including windows.h causes a lot of errors to spew out.. but
   it appears to be harmless (and unavoidable without a lotta hacking) */
#include <windows.h>
#include <Vfw.h>
int acuvTempBufferCount;
unsigned char *acuvTempBuffer = NULL;
boolean acuvWindowsInited = FALSE;
boolean acuvGotFrame = FALSE;
HWND acuvVideoWindow;
#endif
#endif


void acuOpenVideo() {
  if (acuVideoOpened) {
    acuDebug(ACU_DEBUG_USEFUL, "acuVideo already opened");
    return;
  }

#ifdef ACU_IRIX
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
#endif /* ACU_IRIX */

#ifdef ACU_LINUX
  /* doesn't need any setup, acuVideoRequestZoom() does it all,
     and is required before starting under linux */

  /* i'm guessing this is what the hauppage would default to..
     though it might use 'more exact' numbers (576x434 or whatever) */
  /*
  acuvActualWidth = 640;
  acuvActualHeight = 480;  
  */
  /* this may be a little silly, so it might be better to 
     require that linux request a video size before capturing */
  /*acuRequestVideoSize(&ignored1, &ignored2); */
  /*
  acuVideoArrayWidth = acuVideoWidth;
  acuVideoArrayHeight = acuVideoHeight;
  */
  acuVideoOpened = TRUE;
  acuvProxy = FALSE;
#endif

#ifdef ACU_WIN32
  acuVideoOpened = TRUE;
  acuvProxy = FALSE;
#endif

  /* this is ugly but it works, and the solution is uglier */
#ifndef ACU_LINUX
#ifndef ACU_IRIX
#ifndef ACU_WIN32
  acuVideoOpened = FALSE;
  acuDebug(ACU_DEBUG_EMERGENCY, 
	   "Video not implemented on this platform.");
#endif /* ACU_WIN32 */
#endif /* ACU_IRIX */
#endif /* ACU_LINUX */
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


void acuvIrixRequestZoom(int numer, int denom) {
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


void acuvLinuxRequestSize(int width, int height) {
#ifdef ACU_LINUX
  char command[128];

  if (acuvStream != NULL) {
    acuCloseVideo();
  }
  if ((width < 40) || (height < 40)) {
    width = 60;
    height = 40;
  }
  /* -r 10 means 10 fps, -t 100 means 100 times */
  /* -b 1 means just 1 buffer */
  sprintf(command, "streamer -b 2 -r %d -f rgb -n ntsc -i 1 -t 100000000 -s %dx%d", acuVideoFPS, width, height);
  //sprintf(command, "cat /acg/hsvspace/streamer.out");
  acuvStream = popen(command, "r");
  if (acuvStream == NULL) {
    acuDebug(ACU_DEBUG_EMERGENCY, "Video could not be opened");
  }
  acuVideoWidth = width;
  acuVideoHeight = height;

  if (acuvTempBuffer != NULL) free(acuvTempBuffer);
  acuvTempBufferCount = width * height * 3;
  acuvTempBuffer = malloc(acuvTempBufferCount);
#endif /* ACU_LINUX */
}


void acuvWindowsRequestSize(int width, int height) {
#ifdef ACU_WIN32
#ifndef __CYGWIN__
  acuVideoWidth = width;
  acuVideoHeight = height;

  //if (acuvTempBuffer != NULL) free(acuvTempBuffer);
  acuvTempBufferCount = width * height * 3;
  acuvTempBuffer = malloc(acuvTempBufferCount);
#endif
#endif
}


void acuRequestVideoSize(GLint *width, GLint *height) {
  int wide = *width;
  int high = *height;

  float zoom = (((float)wide / (float)acuvActualWidth) + 
		((float)high / (float)acuvActualHeight)) / 2.0f;    
  
  if (acuvProxy) {
    acuvZoom = 1.0 / zoom;
    acuVideoWidth = (acuvActualWidth * zoom);
    acuVideoHeight = (acuvActualHeight * zoom);
    
  } else {
#ifdef ACU_IRIX
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
    acuvIrixRequestZoom(numerator, denominator);
#endif

#ifdef ACU_LINUX
    acuvLinuxRequestSize(*width, *height);
#endif

#ifdef ACU_WIN32
    acuvWindowsRequestSize(*width, *height);
#endif
  }
  acuVideoArrayWidth = acuVideoWidth;
  acuVideoArrayHeight = acuVideoHeight;
  *width = acuVideoWidth;
  *height = acuVideoHeight;
}


void acuvProxyGetFrame(unsigned char *frame) {
  int srcOffset, srcIndex, destIndex;
  int i, j, iw, ih;
  unsigned char *data;
  
  /* load the current file into a buffer */
  sprintf(acuvFilename, acuvFilenameTemplate, acuvFrameIndex);
  if (acuvProxyRaw) {
    int ignored;
    data = (unsigned char *)acuReadRawFile(acuvFilename, &ignored);
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


void acuvIrixGetFrame(unsigned char *frame) {
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


void acuvLinuxGetFrame(unsigned char *frame) {
#ifdef ACU_LINUX
  int srcOffset, srcIndex, destIndex;
  int i, j, iw, ih;
  int bytesRead;
  unsigned char *data = acuvTempBuffer;

  if ((!acuVideoMirrorImage) &&
      (acuVideoArrayWidth == acuVideoWidth) &&
      (acuVideoArrayHeight == acuVideoHeight)) {
    fread(frame, 1, acuvTempBufferCount-3, acuvStream);
    return;
  }
  printf("the slow way\n");
  /* do an fread to get *data from the file */
  //printf("reading\n");
  bytesRead = fread(acuvTempBuffer, 1, acuvTempBufferCount-3, acuvStream);
  if (bytesRead == 0) {
    printf("bytes read, needed = %d, %d\n", bytesRead, acuvTempBufferCount);
    //printf("no bytes ready, skipping\n");
    return;
    //} else {
    //printf("got frame\n");
  }
  //printf("done reading\n");

  destIndex = acuVideoMirrorImage ? (acuVideoWidth-1)*3 : 0;
  for (j = 0; j < acuVideoHeight; j++) {
    /*srcOffset = (((j * acuvZoomDenom) / acuvZoomNumer) * 
		 acuVideoArrayWidth * 3);*/
    /*srcOffset = (floor((float)j * acuvZoom)) * acuvActualWidth * 3;*/
    srcOffset = acuVideoWidth * 3;

    for (i = 0; i < acuVideoWidth; i++) {
      /*srcIndex = srcOffset + ((i * acuvZoomDenom) / acuvZoomNumer) * 3;*/
      /*srcIndex = srcOffset + (floor((float)i * acuvZoom)) * 3;*/
      srcIndex = srcOffset + i;

      //printf("%03d ", frame[destIndex]);
      frame[destIndex+0] = data[srcIndex+0];
      frame[destIndex+1] = data[srcIndex+1];
      frame[destIndex+2] = data[srcIndex+2];

      if (acuVideoMirrorImage)
	destIndex -= 3;
      else 
	destIndex += 3;
    }
    //printf("\n");
    if (acuVideoMirrorImage) {
      destIndex += (acuVideoArrayWidth*3*2 -
		    (acuVideoArrayWidth-acuVideoWidth)*3);
    } else {
      destIndex += (acuVideoArrayWidth - acuVideoWidth)*3;
    }
  }
#endif
}


#ifdef ACU_WIN32
#ifndef __CYGWIN__
/* cygwin doens't know about any of this */
//#include <gl/glut.h>
LRESULT CALLBACK capVideoStreamCallback(HWND capWnd, LPVIDEOHDR lpVHdr) {
  memcpy(acuvTempBuffer, lpVHdr->lpData, acuvTempBufferCount);  
  acuvGotFrame = true;
  return (LRESULT) TRUE;
}
#endif
#endif

void acuvWindowsGetFrame(unsigned char *frame) {
#ifdef ACU_WIN32
#ifndef __CYGWIN__
  int i, j;
  int srcIndex, destIndex;

  if (!acuvWindowsInited) {  /* actually do the setup here */
    HINSTANCE hInstance; 
    HWND videoWindowParent;
    CAPTUREPARMS captureParms;
    LPBITMAPINFO lpbi;
    DWORD dwSize;

    hInstance = GetModuleHandle(NULL);
    videoWindowParent = GetActiveWindow();

    if (videoWindowParent == NULL) {
      return;
    }

    /* videoWidth and videoHeight don't actually affect anything here */
    acuvVideoWindow = 
      capCreateCaptureWindow((LPSTR) "My Capture Window",
			     WS_CHILD,
			     0, 0, acuVideoWidth, acuVideoHeight,
			     videoWindowParent,
			     18); /* child ID.. simon made up "18" */

    capDriverConnect(acuvVideoWindow,0);
    capSetCallbackOnVideoStream(acuvVideoWindow, capVideoStreamCallback);

    capCaptureGetSetup(acuvVideoWindow, &captureParms, sizeof(CAPTUREPARMS));
    //CaptureParms.dwRequestMicroSecPerFrame = (DWORD) (1.0e6 / FramesPerSec);
    captureParms.dwRequestMicroSecPerFrame = (DWORD) (1.0e6 / acuVideoFPS);
    captureParms.fYield = true;
    captureParms.fAbortLeftMouse = false;
    captureParms.fAbortRightMouse = false;
    captureParms.fCaptureAudio = false;
    capCaptureSetSetup(acuvVideoWindow, &captureParms, sizeof (CAPTUREPARMS));

    dwSize = capGetVideoFormatSize(acuvVideoWindow);
    lpbi = (LPBITMAPINFO)GlobalAlloc (GHND, dwSize);
    capGetVideoFormat(acuvVideoWindow, lpbi, dwSize);
    lpbi->bmiHeader.biWidth = acuVideoWidth;
    lpbi->bmiHeader.biHeight = acuVideoHeight;
    capSetVideoFormat(acuvVideoWindow, lpbi, dwSize);	
    GlobalFree(lpbi);

    capCaptureSequenceNoFile(acuvVideoWindow);

    acuvWindowsInited = true;
  }
  if (!acuvGotFrame) return;
  
  destIndex = acuVideoMirrorImage ? (acuVideoWidth-1)*3 : 0;

  srcIndex = 0;
  
  for (j = 0; j < acuVideoHeight; j++) {
    for (i = 0; i < acuVideoWidth; i++) {
      
      frame[destIndex+0] = acuvTempBuffer[srcIndex+2];
      frame[destIndex+1] = acuvTempBuffer[srcIndex+1];
      frame[destIndex+2] = acuvTempBuffer[srcIndex+0];
	  srcIndex += 3;
      destIndex = (acuVideoMirrorImage) ? destIndex-3 : destIndex+3;
    }
    
    if (acuVideoMirrorImage) {
      destIndex += (acuVideoArrayWidth * 3 * 2 -
		    (acuVideoArrayWidth-acuVideoWidth) * 3);
    } else {
      destIndex += (acuVideoArrayWidth - acuVideoWidth) * 3;
    }
  }
#endif
#endif
}


void acuGetVideoFrame(unsigned char *frame) {
  if (!acuVideoOpened) {
    acuDebug(ACU_DEBUG_PROBLEM, "Video not opened");
  }
  
  if (acuvProxy) {
    acuvProxyGetFrame(frame);

  } else {
#ifdef ACU_IRIX
    acuvIrixGetFrame(frame);
#endif

#ifdef ACU_LINUX
    if (acuvStream == NULL) {
      acuDebug(ACU_DEBUG_EMERGENCY, "must call acuRequestVideoSize() before getting frames on linux\n");
    }
    acuvLinuxGetFrame(frame);
#endif
#ifdef ACU_WIN32
	acuvWindowsGetFrame(frame);
#endif

  }
}


void acuCloseVideo() {
  if (!acuVideoOpened) return;

  if (acuvProxy) {
    acuVideoProxyCount = -1;
    return;
  }

#ifdef ACU_IRIX
  vlEndTransfer(acuvServer, acuvPath);     
  vlDeregisterBuffer(acuvServer, acuvPath, acuvDrnNode, acuvBuffer);
  vlDestroyBuffer(acuvServer, acuvBuffer);
  vlDestroyPath(acuvServer, acuvPath);
  vlCloseVideo(acuvServer);
#endif /* ACU_IRIX */

#ifdef ACU_LINUX
  if (acuvStream != NULL) {
    pclose(acuvStream);
  }
#endif /* ACU_LINUX */

#ifdef ACU_WIN32
#ifndef __CYGWIN__
  acuvGotFrame = false;
  capCaptureStop(acuvVideoWindow);
  capDriverDisconnect(acuvVideoWindow);
  CloseWindow(acuvVideoWindow);
  DestroyWindow(acuvVideoWindow);
#endif
#endif /* ACU_WIN32 */

  acuVideoOpened = FALSE;
}
