#ifndef ACU_H
#define ACU_H

/* Welcome to acu.h
 * It's not just a .h file, it's the documentation.
 * 
 * Most of the secrets of acu can be found here. If you have
 * further questions, consult the actual code. The functions
 * listed below are all grouped by the .c file that they 
 * came from.
 * 
 * acApp.h also has some of useful information. 
 *
 * I haven't documented all of the acuGet/acuSet features
 * yet. I'll take care of that. maybe. someday.
 *
 * 
 * notes about the design of acu:
 *
 * The interface for all of this code is straight C. This
 * is because it's easy to bind that to other languages:
 * be they Python, Scheme, Perl, Objective C or Java. Parts
 * of the actual implementation are C++, but that's hidden 
 * from the user.
 *
 * An attempt has been made to minimize the number of actual
 * function calls in the acu library. As a result, things might 
 * appear to be needlessly ugly, requiring calls to acuSetInteger
 * and other like-minded procedures. This is *intentional*,
 * it's very easy to write a 'prettier' library on top of this 
 * one, but that should be done in the host language: Be it
 * C++ or Java or whatever, and done to the suiting of its author.
 * More importantly, this makes it far easier to port to other 
 * platforms and other languages. 
 *
 * Warning to would-be code purist bigots: Don't separate 
 * this into multiple files, lest you find yourself 
 * needlessly encumbered with a high file count and one
 * complete mess of 'extern' values. It's just not necessary.
 */

#ifdef __cplusplus
extern "C" {
#endif

/* on irix, ACU_IRIX is defined by the Makefile,
 * (on mac it should just be un-commented)
 * and since all the versions share the same .h
 * we get the following silliness:
 */

/* uncomment this for macintosh */
/* #define ACU_MAC */

#ifndef ACU_MAC
#define ACU_WIN32
#endif

#ifdef ACU_IRIX
#undef ACU_WIN32
#endif

#ifdef ACU_MAC
#define NO_JPEG
#endif

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

#include <math.h>
#include <time.h>
#include <string.h>

#ifdef ACU_IRIX
#include <dmedia/vl.h>
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef boolean
typedef int boolean;
#endif


typedef enum acuEnum {
  ACU_NO_ERROR = 0,
  ACU_ERROR = -1, 
  ACU_UNKNOWN = -1, 
  ACU_FILE_NOT_FOUND = -2,
  ACU_HOST_NOT_FOUND = -3,

  ACU_DEBUG_LEVEL = 10, // constant for get/set
  ACU_DEBUG_EMERGENCY = 1,
  ACU_DEBUG_PROBLEM = 2,
  ACU_DEBUG_USEFUL = 3,

  ACU_DEBUG_MUMBLE = 4,
  ACU_DEBUG_CHATTER = 5,

  ACU_WINDOW_BG_COLOR = 20,
  ACU_WINDOW_CLEAR,
  ACU_WINDOW_WIDTH,
  ACU_WINDOW_HEIGHT,
  ACU_WINDOW_SIZE,

  ACU_SCREEN_FOV,
  ACU_SCREEN_NEAR,
  ACU_SCREEN_FAR,
  ACU_SCREEN_EYE,
  
  ACU_SCREEN_GRAB_QUALITY,
  ACU_SCREEN_GRAB_FLIP,
  ACU_SCREEN_GRAB_FORMAT,

  ACU_FILE_FORMAT_JPEG,
  ACU_FILE_FORMAT_RAW,
  ACU_FILE_FORMAT_PPM,
  ACU_FILE_FORMAT_TIFF,

  ACU_TIME_STEP,

  ACU_BITMAP_FONT,
  ACU_VECTOR_FONT,
  ACU_TRUETYPE_FONT,

  ACU_FONT_ASCENT = 100,
  ACU_FONT_DESCENT = 101,
  ACU_FONT_X_HEIGHT = 102,
  ACU_FONT_HEIGHT = 103,
  ACU_FONT_EM_WIDTH = 104,
  ACU_FONT_LEADING = 105,
  ACU_FONT_ENABLE_KERNING = 106, 

  ACU_FONT_NORMALIZE,

  ACU_CHAR_WIDTH,
  ACU_CHAR_HEIGHT,
  ACU_CHAR_EXISTS,
  ACU_CHAR_KERN_WIDTH,
  ACU_STRING_WIDTH,

  ACU_VIDEO_WIDTH = 200,
  ACU_VIDEO_HEIGHT,
  ACU_VIDEO_SIZE,
  ACU_VIDEO_ARRAY_WIDTH,
  ACU_VIDEO_ARRAY_HEIGHT,
  ACU_VIDEO_ARRAY_SIZE,
  ACU_VIDEO_MIRROR_IMAGE,

  ACU_VIDEO_PROXY_COUNT,
  ACU_VIDEO_PROXY_REPEATING,
  ACU_VIDEO_PROXY_RAW_WIDTH,
  ACU_VIDEO_PROXY_RAW_HEIGHT
  
} acuEnum;


/******************* main.c *******************/

extern char *acuDebugStr;
extern int acuScreenGrabQuality;
extern boolean acuScreenGrabFlip;

/* Call these at the beginning (and end) of an acu application.
 * if you're using acApp, this is done for you.
 */
void acuOpen();
void acuClose();

/* Inside your applications 'draw' function, call acuOpenFrame
 * first, and finish up with acuCloseFrame. All your GL calls
 * go in-between. These set up your viewing matrix and other
 * nasty things you shouldn't have to think about.
 */
void acuOpenFrame();
void acuCloseFrame();

/* Same thing as acuOpenFrame, but for a flat, 2D frame instead */
void acuOpenFrame2D();
void acuCloseFrame2D();

/* this opens a frame for drawing an acGeo */
/* ie: centered around origin and can see the unit sphere or so */
void acuOpenGeoFrame();
void acuCloseGeoFrame();

/* Thank god for mazo! Mazo is a combined 2D/3D hoopajoop from Tom */
void acuOpenMazoFrame();
void acuCloseMazoFrame();
/* Gets the current contents of the mazo image buffer */
GLubyte *acuGetMazoImage();
/* acuSetMazoImage is deprecated - please don't use for now */
void acuSetMazoImage(GLubyte *newBuffer);

/* DOWN WITH SCRSAVE! Grabs the contents of the screen
 * and writes them to an image file. 
 *
 * You can make jpeg, raw, or ppm format grabs by using:
 * acuSetInteger(ACU_SCREEN_GRAB_FORMAT, ACU_FILE_FORMAT_JPEG)
 * acuSetInteger(ACU_SCREEN_GRAB_FORMAT, ACU_FILE_FORMAT_RAW)
 * acuSetInteger(ACU_SCREEN_GRAB_FORMAT, ACU_FILE_FORMAT_PPM)
 * acuSetInteger(ACU_SCREEN_GRAB_FORMAT, ACU_FILE_FORMAT_TIFF)
 *
 * Both ppm and raw files are lossless. ppm is more useful when
 * you plan to use mediaconvert or dmconvert (which cannot take
 * raw files as input, because they have not width/height info). 
 *
 * On machines that support jpeg (currently only sgi) the
 * default file format is jpeg. On other machines, the default
 * is a raw file (width*height*3 in size, pixels RGBRGBRGB)
 *
 * When using JPEG, the compression quality can be controlled
 * by using acuSetInteger(ACU_SCREEN_GRAB_QUALITY, quality)
 * quality is a number between 0 and 100. Default is 100.
 */
void acuScreenGrab(char *filename);

/* Used internally by acu methods */
void acuDebug(acuEnum level, char *message);
void acuDebugString(acuEnum severity);

/* Use these to tweak acu parameters */
GLint acuGetInteger(acuEnum pname);
void acuGetIntegerv(acuEnum pname, GLint *params);
void acuSetInteger(acuEnum pname, GLint param);
void acuSetIntegerv(acuEnum pname, GLint *params);

GLfloat acuGetFloat(acuEnum pname);
void acuGetFloatv(acuEnum pname, GLfloat *params);
void acuSetFloat(acuEnum pname, GLfloat param);
void acuSetFloatv(acuEnum pname, GLfloat *params);

GLboolean acuGetBoolean(acuEnum pname);
void acuGetBooleanv(acuEnum pname, GLboolean *params);
void acuSetBoolean(acuEnum pname, GLboolean param);
void acuSetBooleanv(acuEnum pname, GLboolean *params);


/******************* misc.c *******************/

extern GLint acuTimeStep;

/* Set colors using HSB color space instead of RGB.
 * (converts the color and calls glColor4f for you)
 * h, s, and b should be between 0.0 and 1.0
 * Note that this function does the color conversion
 * each time it's called, so if you're using it a lot,
 * you should instead consider using acuHsbToRgb and 
 * store the returned values to use with glColor4f.
 */
void acuColorHsb(float h, float s, float b, float alpha);

/* Convert colors between hsb and rgb. Values should be
 * between 0.0 and 1.0 for conversion 
 */
void acuHsbToRgb(GLfloat *hsb, GLfloat *rgb);
void acuRgbToHsb(GLfloat *rgb, GLfloat *hsb);

/* Gets the current time in milliseconds.
 *
 * This function can be slowed down using
 * acuSetInteger(ACU_TIME_STEP, n);
 * It will cause time to pass n times slower.
 * So if n=2, time returned by acuCurrentTimeMillis
 * will go by twice as slowly. If you're capturing
 * screens, set this number to ~1000 or however many
 * milliseconds it's taking to grab each frame, and the
 * time-based things in your app will remain happy.
 */
GLuint acuCurrentTimeMillis();

/* Returns a random float between -1 and 1 */
GLfloat acuRandomf();

/* Returns a random unsigned float between 0 and 1 */
/* Tom says the random number f should be such that 0 <= f < 1 */
GLfloat acuRandomuf();

/* Returns a random integer (cross platform) */
GLint acuRandomui();

/* Does linear interpolation between a and b for a step size t */
GLfloat acuLerpf(GLfloat t, GLfloat a, GLfloat b);

/* Just like acuLerpf, but squared to make a nice S-curve */
GLfloat acuSerpf(GLfloat t, GLfloat a, GLfloat b);

/* Used internally, reads 4 bytes from a file and does the
 * appropriate endian-swapping based on what platform you're
 * using. This is used by the text routines.
 */
int acuReadInt(FILE *fp);

/* Two experimental functions, these may go away!
 *
 * Recomponent changes the number of components in an
 * array from 3 to 4 (RGB -> RGBA) or 4 to 3 (RGBA->RGB).
 * 
 * Resize will modify the size of the array, similar to
 * changing the "canvas size" in Photoshop.
 *
 * background is the value to set all background values to.
 *
 * THESE ARE NOT OPTIMIZED! THEY ARE NOT VERY FAST!
 * THESE MAY GO AWAY BUT ARE SORT OF USEFUL!
 */
unsigned char* acuRecomponentArray2D(unsigned char *data, 
				     int width, int height,
				     int inComponents, int outComponents,
				     unsigned char background);

unsigned char* acuResizeArray2D(unsigned char *data, 
				int inWidth, int inHeight,
				int outWidth, int outHeight,
				int components,
				unsigned char background);

/* These functions perform a wholesale read (or write) of
 * a binary file. This can be useful because it's annoying
 * code to write over and over again. *count returns the
 * size of the data actually read (by acuReadRawFile).
 *
 * For instance, you can read a raw stream of bits to use 
 * as an image. It's recommended that you just use RGB or 
 * RGBA data. If you need to resize these things or add 
 * an alpha channel use acuResizeArray2D and
 * acuRecomponentArray2D.
 *
 * The following opens a raw, 32x32 pixel, RGB format file, 
 * and adds an alpha channel to the data, set to 168:
 *
 * unsigned char *data, *newbuf;
 * int count = 0;
 * data = (unsigned char*) acuReadRawFile("face.raw", &count);
 * newbuf = acuRecomponentArray(data, 32, 32, 3, 4, 168);
 * free(data);
 */
void* acuReadRawFile(char *filename, int *count);

void acuWriteRawFile(char *filename, void *data, int count);


/* Writes an uncompressed TIFF file for use with photoduck
 * or your favorite image editing application.
 * Works the same way as acuWriteJpegFile, see example there.
 *
 * The code is adapted from Image/J
 * see http://rsb.info.nih.gov/ij/ for more information
 */
void acuWriteTiffFile(char *filename, unsigned char *data, 
                      int width, int height);


/******************* jpeg.c *******************/ 

/* Reads the contents of a jpeg file into an array.
 * An array of unsigned chars is allocated by the 
 * function and returned. The width and height are 
 * returned in *width and *height. Data is always 
 * assumed to be in RGB format.
 *
 * For example:
 * int width, height;
 * unsigned char *data;
 * data = acuReadJpegFile("potato.jpg", &width, &height);
 *
 * The image can then be manipulated in memory, or
 * drawn using glDrawPixels or something like acuTexRectf.
 */
unsigned char* acuReadJpegFile(char *filename,
                               int *width, int *height);

/* Write a JPEG file to disk. Data should be in RGB format,
 * (meaning an array of bytes that go RGBRGBRGBRGB..)
 * quality is a number between 0 and 100
 */
void acuWriteJpegFile(char *filename, unsigned char *data, 
                      int width, int height, int quality);


/******************* text.c *******************/

extern boolean acuFontNormalize;
extern boolean acuTextInited;

/* you never have to call this, please don't */
void acuTextInit();

/* To use a font, do the following:
 * int myfont = acuLoadFont("/acg/data/font/bitmaps/Univers55.48");
 * if (myfont != ACU_ERROR) {
 *   acuSetFont(myfont);
 * }
 * Then in your draw loop, something like this:
 * acuDrawString("potato", 0.0, 0.0);
 * To change the font, use acuSetFont().
 *
 * To find out if a font has already been loaded, use 
 * acuFindFont, which will return the font number or 
 * ACU_ERROR if the font doesn't exist yet.
 *
 * Because fonts are 1.0 units tall, Mazo and 2D apps will
 * also need a glScale(48, 48, 1) before acuDrawString.
 * Otherwise, the font is 1 pixel tall. For 3D apps, you
 * should be ok, but it will probably need some tweaking.
 *
 * It's not actually recommended to use anything but 0.0 
 * for the x and y values because that can really mess with 
 * things -- for instance, if you do the scale mentioned
 * above, then a drawstring at some coordinate.. phew! 
 * Instead, call glTranslate, then glScale, then acuDrawString,
 * if you need all those things.
 */
int acuLoadFont(char *fontname);
void acuSetFont(int index);

/* Advanced features, you probably won't need these */
void acuUnloadFont(int index);
int acuFindFont(char *fontname);
void* acuGetFont(int index);

/* Draw characters and strings to the screen */
void acuDrawChar(char c, GLfloat x, GLfloat y);
void acuDrawString(char *c, GLfloat x, GLfloat y);

/* Back off, not yet implemented */
void acuGetCharMetrics(acuEnum pname, char *c, GLfloat *metrics);
float acuGetCharMetric(acuEnum pname, char c);


/******************* geometry.c *******************/

extern GLUtriangulatorObj *acuTesselator;

/* Draw a polygon, and put it through the tesselator.
 * Unlike standard GL, this method handles both concave
 * and convex polygons.
 * (now fully tested and working, with help from creas)
 */
void acuPolygon(GLint count, GLfloat *vertices);

/* Used internally, no need to mess with these */
void acuPolygonOpen();
void acuPolygonClose();

/* Quick way to draw a textured rectangle.
 * Position of the rectangle is x1, y1, x2, y2.
 * image is just a byte array of what to show, format is
 * GL_RGB or GL_RGBA or any of the other texture formats.
 * components is 3 for RGB and 4 for RGBA (with alpha).
 * texWidth and texHeight are the width and height of the
 * texture image. maxU and maxV are the maximum u and v
 * coordinates of the texture image. Since texture sizes
 * must be powers of two, this is how you get rid of the 
 * extra that you don't need. (i.e. if the width of your 
 * image is 54, and the tex size is 64, you maximum U
 * would be 54.0/64.0).
 *
 * int width, height;
 * unsigned char *image = 
 *   acuReadJpegFile(filename, &width, &height);
 * if (image == NULL) exit(1);
 * float aspect = (float)width / (float)height;
 *
 * // find the closest power of 2 to use for the texture
 * int twidth = (int) pow(2, ceil(log(width) / log(2)));
 * int theight = (int) pow(2, ceil(log(height) / log(2)));
 *    
 * float maxu = (float)width / (float)twidth;
 * float maxv = (float)height / (float)theight;
 *    
 * // need to resize the array so that it fits the new texture
 * // size (whose width and height are both a power of two
 * // this is not very fast! don't do this often!
 * unsigned char *timage =
 *   acuResizeArray2D(image, width, height, 
 *                    twidth, theight, 3, 0xff);
 * glColor3f(1.0, 1.0, 1.0);
 * acuTexRectf(-0.5, -(1.0/aspect)/2.0, 0.5, (1.0/aspect)/2.0, 
 *             timage, GL_RGB, 3, twidth, theight, maxu, maxv);
 *
 * free(image);
 * free(timage);
 *
 *
 * NOTE! This draws a textured rectangle, so any color
 * you had set before drawing will be applied to the image.
 * Most likely you should call glColor3f(1, 1, 1) to set
 * the color back to white before calling this, unless you 
 * know what you're doing.
 */
void acuTexRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2,
		 unsigned char *image, GLenum format, GLint components,
		 GLsizei texWidth, GLsizei texHeight,
		 GLfloat maxU, GLfloat maxV);

/* Does the same thing as above, but draws a texture
 * that already has a 'name' i.e. it's had glBindTexture
 * applied to it. This makes it really speedy.
 */
void acuNamedTexRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2,
		      GLint name, GLfloat maxU, GLfloat maxV);

/* Convenience function, draw a two-dimensional line */
void acuLine2f(float x1, float y1, float x2, float y2);

/* Draw multiple, connected two-dimensional lines */
void acuLine2fv(int count, float *x, float *y);

/* Guess what this does */
void acuLine3f(float x1, float y1, float z1, float x2, float y2, float z2);

/* Extra credit: figure this one out */
void acuLine3fv(int count, float *x, float *y, float *z);


/******************* video.c *******************/

/* Useful get/set operations for video.
 *
 * The following will automatically mirror the video image:
 * acuSetBoolean(ACU_VIDEO_MIRROR_IMAGE, TRUE);
 *
 * If you want the video to be drawn into an array that's
 * a different size from the width/height of the video image,
 * use the following:
 * acuSetInteger(ACU_VIDEO_ARRAY_WIDTH, arrayWidth);
 * acuSetInteger(ACU_VIDEO_ARRAY_HEIGHT, arrayHeight);
 * For example, this would be useful if you wanted to draw
 * video into a texture, because the texture dimensions
 * must be a power of 2. 
 */

extern boolean acuVideoOpened;
extern int acuVideoWidth;
extern int acuVideoHeight;
extern int acuVideoArrayWidth;
extern int acuVideoArrayHeight;
extern boolean acuVideoMirrorImage;

extern boolean acuVideoProxyRepeating;
extern int acuVideoProxyCount;
extern int acuVideoProxyRawWidth;
extern int acuVideoProxyRawHeight;

/* Warm up the video, Marge. We've got company coming over. 
 *
 * // a simple video example:
 * acuOpenVideo();
 * videoWidth = 640;
 * videoHeight = 480;
 * // ask for a size, but the values get re-set to the correct size
 * acuRequestVideoSize(&videoWidth, &videoHeight);
 * // allocate an RGB buffer for it
 * int count = videoWidth * videoHeight * 3;
 * unsigned char *buffer = new unsigned char[count];
 *
 * void draw() {
 *   acuGetVideoFrame(buffer);
 *   // do something with the buffer here
 * }
 */
void acuOpenVideo();

/* Leftovers and cold cuts? Not again.. 
 * 
 * The video proxy provides acu developer community program 
 * members with the bonus functionality of reading a set of
 * jpeg files in as if they were actual video image being
 * displayed by the camera.
 *
 * Pass in a filename template, similar to what you might use
 * with printf or sprintf, such as "/tmp/frame-%03d.jpg"
 * (that would open files names frame-000.jpg, frame-001.jpg, etc.)
 * Make sure the first frame should be numbered 0!
 *
 * The first time a proxy file is used, acu will search the
 * directory for the highest numbered image. On our abyssmal
 * NFS setup, this runs very slowly. To make things speedy,
 * you might try using:
 * acuSetInteger(ACU_VIDEO_PROXY_COUNT, 1147);
 * The developer who used this line of code had frames 
 * numbered 0000 to 1146. This line has to go *before* 
 * acuOpenVideoProxy is called, otherwise it won't work.
 *
 * To make a series of jpeg files from a quicktime movie, use:
 * dmconvert -f jfif -p video frame-###.jpg blah.mov frame-###.jpg
 * This makes a bunch of files named frame-000.jpg, and so on.
 *
 * Be careful about asking for what you want because you just
 * might get it. When using a video proxy, acuRequestVideoSize
 * will set the video to exactly the size you ask for, without
 * preserving aspect ratio, the way that sgi video might. 
 * This is a good thing, not a bad thing, but something you 
 * might want to be aware of in case you were lazy about the
 * exact size that you wanted for acuRequestVideoSize.
 */

void acuOpenVideoProxy(char *filename);

/* Request or ask the machine for a particular size for 
 * your video image. Pass in a pointer to your width and height,
 * and it will return the actual numbers using the same variable.
 */
void acuRequestVideoSize(GLint *width, GLint *height);

/* Call this to get each frame. You're in charge of allocating
 * enough memory for the buffer, which will be width*height*3.
 */
void acuGetVideoFrame(unsigned char *buffer);

/* Call this at the end of your application */
void acuCloseVideo();


/*********** a few useful function definitions ***********/

/* some constants stolen from barnes' code */

#define PI       3.14159265358979323846
#define TWO_PI   6.28318530717958647693
#define FOUR_PI 12.56637061435917295385
#define HALF_PI  1.57079632679489661923

#define DEG_TO_RAD (PI/180.0)
#define RAD_TO_DEG (180.0/PI)

#ifndef MIN
#define MIN(x,y) (((x) < (y)) ? (x) : (y))
#endif

#ifndef MAX
#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#endif

#ifndef ABS
#define ABS(x) (((x) < 0) ? -(x) : (x))
#endif

#ifndef ROUND
#define ROUND(a) ((int)((a) + 0.5))
#endif

#ifdef __cplusplus
}
#endif
#endif /* ACU_H */



/* things not yet completed 
 *
 * this has more to do with 'thinking out loud' than 
 * 'things ben will be implementing within the next month or seven'.
 */

/*
  // get only
  ACU_SERIAL_CTS = 300, // boolean clear-to-send
  ACU_SERIAL_DCD, // boolean data-carrier-detect
  ACU_SERIAL_DSR, // boolean data set ready
  ACU_SERIAL_RI, // boolean ring indicator
  
  ACU_SERIAL_DTR, // data terminal ready, boolean set true/false
  ACU_SERIAL_RTS, // request to send, boolean set true/false
  
  ACU_SERIAL_FLOW_CONTROL,
  ACU_SERIAL_SOFTWARE_CONTROL, // can be or'ed together
  ACU_SERIAL_HARDWARE_CONTROL, 

  ACU_SERIAL_DATA_BITS, // 7 or 8, default is 8
  ACU_SERIAL_STOP_BITS, // 1 or 2, default is 1
  ACU_SERIAL_DATA_RATE, // default is 19,200 (?)
  ACU_SERIAL_PARITY, // 0 is no (default), 1 is odd, 2 is even

  ACU_SERIAL_NO_PARITY = 0,
  ACU_SERIAL_ODD_PARITY = 1,
  ACU_SERIAL_EVEN_PARITY = 2,

  ACU_LINE_CAP_BUTT = 400,
  ACU_LINE_CAP_ROUND,
  ACU_LINE_CAP_SQUARE,
  ACU_LINE_JOIN_BEVEL,
  ACU_LINE_JOIN_MITER,
  ACU_LINE_JOIN_ROUND,

  ACU_MIDI_NOTE_ON = 500,
  ACU_MIDI_NOTE_OFF,
  ACU_MIDI_PROGRAM_CHANGE
  */


/** NETWORK **/

/* COMING SOON
// listens on a port for connections, returns index
// dropped connection posts a serverReceive event with 0 length data
int acuOpenNetServer(int port);
int acuNetServerListen();
void acuNetServerSend(unsigned char *data, int length);
int acuNetServerReceive(unsigned char *data, int length);
void acuCloseNetServer(int index);

int acuOpenNetClient(char *hostaddr, int port);
void acuNetClientSend(int index, unsigned char *data, int length);
int acuNetClientReceive(unsigned char *data, int length);
void acuCloseNetClient(int index);
*/


/** SERIAL **/

/* COMING SOON
// needs work, what are the correct arguments here?
// serial1, serial2, serial3, serial4
// com1, com2, com3, com4
// modem, printer
int acuOpenSerial(int port);
void acuSerialSend(int index, unsigned char *data, int length);
int acuSerialReceive(int port, unsigned char *data, int length, boolean block);
void acuCloseSerial();
*/


/** MIDI, MUSIC, SOUND **/

/* COMING SOON
void acuOpenMidi();
//void acuMidiSetProgram(int channel, int program);
//void acuMidiNoteOn(int channel, int note, int velocity);
//void acuMidiNoteOff(int channel, int note, int velocity);
//void acuMidiReceive(int count, byte *data);
void acuMidiSend(int channel, int command, int value);
void acuMidiReceive(int channel, int *command, int *value);
void acuCloseMidi();

void acuOpenSound();
int acuLoadSound(char *filename);
void acuSoundPlay(int channel, int index, int pitch, int duration);
void acuSoundStop(int channel);
void acuCloseSound();
*/

/*
void acuSetLineAttributes(int thickness, int cap, int join);
void acuEllipsef(float cx, float cy, float width, float height);
*/
