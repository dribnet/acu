#include "acux.h"


////////////////////////////////////////////////////////////

// CURVES

float bezierBasis[4][4] = {
  { -1,  3, -3,  1},
  {  3, -6,  3,  0},
  { -3,  3,  0,  0},
  {  1,  0,  0,  0},
};

float catmullRomBasis[4][4] = {
    {-0.5f,  1.5f, -1.5f,  0.5f},
    { 1   , -2.5f,  2   , -0.5f},
    {-0.5f,  0   ,  0.5f,  0   },
    { 0   ,  1   ,  0   ,  0   }
};

float sixth = 1.0f / 6.0f;
float bezierToCatmullRom[4][4] = {
  {  0,     1,     0,      0     },
  { -sixth, 1,     sixth,  0     },
  {  0,     sixth, 1,     -sixth },
  {  0,     0,     1,      0     }
};
acMatrix4f bezierToCatmullRomMatrix(bezierToCatmullRom);

#define PRECISION 10
float fstep = 1.0 / (float)PRECISION;
float fstep2 = fstep*fstep;
float fstep3 = fstep2*fstep;
float forwardMatrix[4][4] = {
    {        0,        0,     0, 1 },
    {   fstep3,   fstep2, fstep, 0 },
    { 6*fstep3, 2*fstep2,     0, 0 },
    { 6*fstep3,        0,     0, 0 }
};

void multCatmullRom(float m[4][4], float g[4][2], float mg[4][2]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      mg[i][j] = 0;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 4; k++) {
	mg[i][j] = mg[i][j] + (m[i][k] * g[k][j]);
      }
    }
  }
}

void drawCatmullRom(int pointCount, float *xpoints, float *ypoints) {
  float geom[4][2];
  float plot[4][2];
  float mg[4][2];
  
  for (int i = 0; i < pointCount-3;) {
    for (int j = 0; j <4 ;j++) {
      geom[j][0] = xpoints[i+j];
      geom[j][1] = ypoints[i+j];
    }
    multCatmullRom(catmullRomBasis, geom, mg);
    i += 1;
    
    multCatmullRom(forwardMatrix, mg, plot);
    float startX = plot[0][0];
    float x = startX;
    float startY = plot[0][1];
    float y = startY;
    
    glBegin(GL_LINE_STRIP);
    glVertex3f(startX, startY, 0);
    if (aiCapture) {
      aiBeginLine();
      aiMoveTo(startX, startY);
    }
    
    // plot the curve using the forward difference method
    for (int j = 0; j < PRECISION; j++) {
      x += plot[1][0];
      plot[1][0] += plot[2][0];
      plot[2][0] += plot[3][0];
      y += plot[1][1];
      plot[1][1] += plot[2][1];
      plot[2][1] += plot[3][1];
      //g.drawLine((int)startX, (int)startY, (int)x, (int)y);
      glVertex3f(x, y, 0);
      if (aiCapture) aiLineTo(x, y);
      startX = x;
      startY = y;
    }
    glEnd();
    if (aiCapture) aiEndLine();
  }
}


void drawCatmullRomBezier(int pointCount, float *xpoints, float *ypoints) {
  float control[4][3];  // 4 points, 3 for xyz

  for (int i = 0; i < pointCount-4; i++) {
    float convIn[4], convOut[4];

    // transform the x points
    for (int m = 0; m < 4; m++)
      convIn[m] = xpoints[i+m];
    //transform4x4(bezierToCatmullRom, convIn, convOut);
    bezierToCatmullRomMatrix.transform4(convIn, convOut);
    for (int m = 0; m < 4; m++)
      control[m][0] = convOut[m];

    // transform the y points
    for (int m = 0; m < 4; m++)
      convIn[m] = ypoints[i+m];
    //transform4x4(bezierToCatmullRom, convIn, convOut);
    bezierToCatmullRomMatrix.transform4(convIn, convOut);
    for (int m = 0; m < 4; m++)
      control[m][1] = convOut[m];

    // zero the z points
    for (int m = 0; m < 4; m++)
      control[m][2] = 0;

    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &control[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 20; i++) {
      glEvalCoord1f((GLfloat) i/20.0);
    }
    glEnd();
  }
}


void drawBezier(int pointCount, float *xpoints, float *ypoints) {
  // hey ben, write this later when you want to take the time
  // the code is inside innocents3 -> edge.cpp -> Edge::drawBezier
}


////////////////////////////////////////////////////////////

// FRAME RATE

// can't be used with multiple apps
float acuxFPS = 10.0f;
long acuxLastTime = 0;
float acuxFrameRate() {
  long currentTime = acuCurrentTimeMillis();
  if (acuxLastTime != 0) {
    float elapsed = currentTime - acuxLastTime;
    acuxFPS = (acuxFPS * 0.9f) + ((1.0f / (elapsed / 1000.0f)) * 0.1f);
  }
  acuxLastTime = currentTime;
  return acuxFPS;
}


////////////////////////////////////////////////////////////

// FILE I/O

void acuxNumberedFilename(char *dest, char *tmpl, int *num) {
  int counter = 0;
  int fd = -1;
  do {
    if (fd != -1) { 
      close(fd);
      counter++;
    }
    sprintf(dest, tmpl, counter);
    printf("trying %s\n", dest);
  } while ((fd = open(dest, O_RDONLY)) != -1);
  sprintf(dest, tmpl, counter);
  *num = counter+1;
}


void acuxReadToEOL(FILE *fp) {
  char c;
  do { 
    c = getc(fp); 
  } while (c != '\n');
  do { 
    c = getc(fp); 
  } while (c == '\n');
  if (!feof(fp)) 
    ungetc(c, fp);
}


void acuxReadSpace(FILE *fp) {
  char c;
  do {
    c = getc( fp );
    //if (c=='#') { c = ' '; fread_to_eol(fp); }
    if (feof(fp)) return;
  } while (isspace(c));
  ungetc(c, fp);
}


void acuxReadWord(FILE *fp, char *word) {
  acuxReadSpace(fp);
  int test = fscanf(fp, "%s", word);
  if (test == EOF) word[0] = 0;
  else if (test != 1) {
    acuDebug(ACU_DEBUG_PROBLEM, "scanf returned something funny");
  }
}


float acuxReadFloat(FILE *fp) {
  char temp[16];
  acuxReadWord(fp, temp);
  return atof(temp);
}

/*
// not sure why you'd want this
  void screenGrabAss() {
    char path[256];
    char command[256];
    sprintf(path, "/mas/u/fry/extra/sketchc-slides/sketchc%03d.rgb", 
	    grabAssCount++);
    sprintf(command, "scrsave %s %d %d %d %d", path,
	    0, windowWidth, 0, windowHeight);
    printf("%s\n", command);
    system(command);
  }
*/
