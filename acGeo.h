#ifndef _AC_GEO_
#define _AC_GEO_

#include "acu.h"

class acGeo {
public:
	virtual void idle();
	virtual void draw();   			
	virtual void message(const char *string);
};

/* This is some glue that connects the app to the window system */
#ifdef ACU_WIN32
#include "ansi_prefix.win32.h"
#define ExportGeo extern "C" __declspec(dllexport) acGeo
#define ExportType extern "C" __declspec(dllexport) char
#else
#define ExportGeo extern "C" acGeo
#define ExportType extern "C" char
#endif
// this is the decaration, but the function in your geo
ExportGeo *makeGeo(void);

#endif
