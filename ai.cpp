#include "ai.h"


/*
  THIS IS HIGHLY UNSUPPORTED CODE THAT CHANGES ALL THE TIME
  ben fry 99.12.19

  why did i do this AI_EOL thing instead of just using \r\n?
*/


boolean aiCapture = FALSE;
static char AI_EOL[] = { 13, 10, 0 };
//static char aiFilenameTemplate[] = "illusfart-%03d.ai";
//int aiCount = -1;
FILE *aifp;


void aiBegin(char *filename) {
  /*
  char filename[32];
  if (aiCount == -1) {
    acuxNumberedFilename(filename, aiFilenameTemplate, &aiCount);
  } else {
    sprintf(filename, aiFilenameTemplate, aiCount++);
  }
  */
  aifp = fopen(filename, "wb");

  int screenDim[2];
  acuGetIntegerv(ACU_WINDOW_SIZE, screenDim);

  fprintf(aifp, "%%!PS-Adobe-2.0 %s", AI_EOL);
  fprintf(aifp, "%%%%Creator:Adobe Illustrator(TM) 1.1%s", AI_EOL);
  //fprintf(aifp, "%%%%For: (Glen Nupert) (Zemo\(r\) Handbuzzers)%s", AI_EOL);
  //fprintf(aifp, "%%%%Title: (oneline-1.0.ai)%s", AI_EOL);
  //fprintf(aifp, "%%%%CreationDate: (7/26/99) (8:25 PM)%s", AI_EOL);
  //fprintf(aifp, "%%%%DocumentProcessColors: Black%s", AI_EOL);
  //fprintf(aifp, "%%%%DocumentProcSets: Adobe_Illustrator_1.1 0 0%s", AI_EOL);
  //fprintf(aifp, "%%%%DocumentSuppliedProcSets: Adobe_Illustrator_1.1 0 0%s", AI_EOL);
  fprintf(aifp, "%%%%BoundingBox:%d %d %d %d%s", 
	  0, 0, screenDim[0], screenDim[1], AI_EOL);
  //fprintf(aifp, "%%%%TemplateBox:%d %d %d %d%s", 
  //  0, 0, screenDim[0], screenDim[1], AI_EOL);
  //fprintf(aifp, "%%%%TileBox:%d %d %d %d%s", 
  //  0, 0, screenDim[0], screenDim[1], AI_EOL);

  //fprintf(aifp, "%%%%ColorUsage: Black&White%s", AI_EOL);
  //fprintf(aifp, "%%%%TemplateBox:306 396 306 396%s", AI_EOL);
  //fprintf(aifp, "%%%%TileBox: 30 31 582 759%s", AI_EOL);
  //fprintf(aifp, "%%%%DocumentPreview: None%s", AI_EOL);
  fprintf(aifp, "%%%%EndComments%s", AI_EOL);
  fprintf(aifp, "%%%%EndProlog%s", AI_EOL);
  fprintf(aifp, "%%%%BeginSetup%s", AI_EOL);
  fprintf(aifp, "Adobe_Illustrator_1.1 begin%s", AI_EOL);
  fprintf(aifp, "n%s", AI_EOL);
  fprintf(aifp, "%%%%EndSetup%s", AI_EOL);

  // k = cmyk fill color
  //fprintf(aifp, "0 0 0 0 k%s", AI_EOL);  
  // K = cmyk stroke color
  //fprintf(aifp, "0 0 0 1 K%s", AI_EOL);  
  // i = setflat
  fprintf(aifp, "0 i%s", AI_EOL);  
  // 0 J = setlinecap
  // 0 j = setlinejoin
  // 0.25 w = setlinewidth
  // 4 M = setmiterlimit
  // []0 d = setdash
  fprintf(aifp, "0 J 0 j 0.25 w 4 M []0 d%s", AI_EOL);

  aiCapture = TRUE;
}


void aiEnd() {
  fprintf(aifp, "%%%%PageTrailer%s", AI_EOL);
  fprintf(aifp, "%%%%Trailer%s", AI_EOL);
  fprintf(aifp, "_E end%s", AI_EOL);
  fprintf(aifp, "%%%%EOF%s", AI_EOL);

  //fwrite(aiFooterData, 1, aiFooterLength, aifp);
  fflush(aifp);
  fclose(aifp);
  aifp = NULL;
  aiCapture = FALSE;
}


void aiScreenShapeMacro() {
  int screenDim[2];
  acuGetIntegerv(ACU_WINDOW_SIZE, screenDim);
  float bgColor[3];
  acuGetFloatv(ACU_WINDOW_BG_COLOR, bgColor);
  aiFillColorRGB(bgColor[0], bgColor[1], bgColor[2]);
  aiBeginLock();
  aiFilledRectangleMacro(0, 0, (float)screenDim[0], 
			 (float)screenDim[1]);
  aiEndLock();
}


void aiFillColorRGB(float r, float g, float b) {
  fprintf(aifp, "%1.2f %1.2f %1.2f %1.2f k%s", 
	  1.0-r, 1.0-g, 1.0-b, 0.0, AI_EOL);
}

void aiStrokeColorRGB(float r, float g, float b) {
  fprintf(aifp, "%1.2f %1.2f %1.2f %1.2f K%s", 
	  1.0-r, 1.0-g, 1.0-b, 0.0, AI_EOL);
}

float hsb[3], rgb[3];
void aiStrokeColorHSB(float h, float s, float b) {
  hsb[0] = h; hsb[1] = s; hsb[2] = b;
  acuHsbToRgb(hsb, rgb);
  aiStrokeColorRGB(rgb[0], rgb[1], rgb[2]);
}

void aiStrokeColorHSBA(float h, float s, float b, float a) {
  hsb[0] = h; hsb[1] = s; hsb[2] = b;
  acuHsbToRgb(hsb, rgb);
  aiStrokeColorRGB(rgb[0]*a, rgb[1]*a, rgb[2]*a);
}

void aiStrokeColorGet() {
  float params[4];
  glGetFloatv(GL_CURRENT_COLOR, params);
  // alpha value is ignored.. that kinda sucks
  //aiStrokeColorRGB(params[0], params[1], params[2]);
  aiStrokeColorRGB(params[0] * params[3], 
		   params[1] * params[3], 
		   params[2] * params[3]);
}

void aiBeginGroup() {
  fprintf(aifp, "u%s", AI_EOL);
}

void aiEndGroup() {
  fprintf(aifp, "U%s", AI_EOL);
}

void aiBeginLock() {
  fprintf(aifp, "1 A%s", AI_EOL);
}

void aiEndLock() {
  fprintf(aifp, "0 A%s", AI_EOL);
}

void aiStrokeWidthGet() {
  float param[1];
  glGetFloatv(GL_LINE_WIDTH, param);
  aiStrokeWidth(param[0]);
}

void aiStrokeWidth(float width) {
  // 0.25 w = setlinewidth
  fprintf(aifp, "%4.4f w%s", width, AI_EOL);
}

void aiBeginPath() {
}

void aiMoveTo(float x, float y) {
  fprintf(aifp, "%4.4f %4.4f m%s", x, y, AI_EOL);
}

// L and l seem to do same thing
void aiLineTo(float x, float y) {
  fprintf(aifp, "%4.4f %4.4f l%s", x, y, AI_EOL);
}

void aiCurveTo(float x1, float y1, float x2, float y2, float x3, float y3) {
  fprintf(aifp, "%4.4f %4.4f %4.4f %4.4f %4.4f %4.4f c%s", 
	  x1, y1, x2, y2, x3, y3, AI_EOL);
}

void aiEndPath() {
  // B - fill and stroke line
  // S - stroke line
  fprintf(aifp, "S%s", AI_EOL);
}


void aiLineMacro(float x1, float y1, float x2, float y2) {
  aiBeginPath();
  aiMoveTo(x1, y1);
  aiLineTo(x2, y2);
  aiEndPath();
}


void aiFilledRectangleMacro(float x1, float y1, float x2, float y2) {
  aiMoveTo(x1, y1);
  aiLineTo(x2, y1);
  aiLineTo(x2, y2);
  aiLineTo(x1, y2);
  aiLineTo(x1, y1);
  // f - close and fill path
  fprintf(aifp, "f%s", AI_EOL);
}


float ctm[16];
void aiSetMatrix(float *matrix) {
  for (int i = 0; i < 16; i++) {
    ctm[i] = matrix[i];
  }
}

void aiSetMatrixGet() {
  //glGetFloatv(GL_PROJECTION_MATRIX, ctm);
  //acMatrix4f a; a.set(ctm);
  glGetFloatv(GL_MODELVIEW_MATRIX, ctm);
  //acMatrix4f b; b.set(ctm);
  //a.multiplyBy(&b);
  //a.get(ctm);
  
  /*
  for (int i = 0; i < 16; i++) {
    if ((i % 4) == 0) printf("\n");
    printf("%f ", ctm[i]);
  }
  printf("\n"); 
  */
}

/*
// pretends that the 'w' value for the input vector is 1.0
void Edge::transform3(float *in, float *out) {
  out[0] = m[0][0]*in[0] + m[0][1]*in[1] + m[0][2]*in[2] + m[0][3];
  out[1] = m[1][0]*in[0] + m[1][1]*in[1] + m[1][2]*in[2] + m[1][3];
  out[2] = m[2][0]*in[0] + m[2][1]*in[1] + m[2][2]*in[2] + m[2][3];
}
*/

void aiMoveTo3f(float x, float y, float z) {
  //float xx = ctm[0]*x + ctm[1]*y + ctm[2]*z + ctm[3];
  //float yy = ctm[4]*x + ctm[5]*y + ctm[6]*z + ctm[7];

  float xx = ctm[0]*x + ctm[4]*y + ctm[8]*z + ctm[12];
  float yy = ctm[1]*x + ctm[5]*y + ctm[9]*z + ctm[13];

  fprintf(aifp, "%4.4f %4.4f m%s", xx, yy, AI_EOL);
}

// L and l seem to do same thing
void aiLineTo3f(float x, float y, float z) {
  //float xx = ctm[0]*x + ctm[1]*y + ctm[2]*z + ctm[3];
  //float yy = ctm[4]*x + ctm[5]*y + ctm[6]*z + ctm[7];

  float xx = ctm[0]*x + ctm[4]*y + ctm[8]*z + ctm[12];
  float yy = ctm[1]*x + ctm[5]*y + ctm[9]*z + ctm[13];

  fprintf(aifp, "%4.4f %4.4f l%s", xx, yy, AI_EOL);
}

/*
  /_Univers-BlackOblique 12 Tf

  (blackoblique) Tx 1 0 Tk

  # second time around
0 To
1 0 0 1 256.0259 253.666 0 Tp
TP
0 Tr
(second) Tx 1 0 Tk
(\r) TX 
TO

  # the minimum
0 To
1 0 0 1 256.0259 253.666 0 Tp
TP
0 Tr
/_Univers-BlackOblique 12 Tfb
(second) Tx 1 0 Tk
(\r) TX 
TO


  0 A
  0 To               # begin text object
  1 0 0 1 106.0259 595.9741 0 Tp   # begin text path
                     [1 0 106.0259]
                     [0 1 595.9741]  startpt=0
  TP                 # end text path (concats the above matrix)
  0 Tr               # set text render mode (to fill)
  0 O                # set overprint to false
  0 0 0 1 k          # cmyk fill color (black)
  0 i                # setflat     
  0 J 0 j 1 w 4 M []0 d  # usual line stuff
  %AI3_Note:         # a comment
  0 D                # polarized fill style
  /_Helvetica 12 Tf  # set the font to 12 point helvetica
  0 Ts               # text super script false
  100 Tz             # horizontal scaling 100%
  0 Tt               # user tracking 0
  1 TA               # pairwise kerning ON
  0 0 5 TC           # text character spacing (min=0, opt=0, max=5)
  100 100 200 TW     # word spacing (min=100, opt=100, max=200)
  0 0 0 Ti           # set indent (firststart=0, otherstart=0, stop=0)
  0 Ta               # set alignment left (0=left, 1=center, 2=right)
  0 Tq               # hanging quotes false
  0 0 Tl             # leading (leading=0, paragraphleading=0)
  0 Tc               # set computed character spacing (charspacing=0)
  0 Tw               # set computed word spacing (wordspacing=0)
  (b) Tx 1 20 Tk     # Tx=non justified text, 
  (la b) Tx 1 20 Tk  # Tk=auto kern (=1, where 0=manual, 1=auto) and kern (=20)
  (lah) Tx 1 0 Tk
  (\r) TX            # overflow text
  TO                 # end text object
*/

// sets font by using a semi-bogus call to make 
// a text object (usually a block of text)
void aiSetFont(char *fontFace, int fontSize) {
  fprintf(aifp, "0 To %s", AI_EOL);
  fprintf(aifp, "1 0 0 1 0 0 0 Tp %s", AI_EOL);
  fprintf(aifp, "TP %s", AI_EOL);
  fprintf(aifp, "/_%s %d Tf %s", fontFace, fontSize, AI_EOL);
  fprintf(aifp, "TO %s", AI_EOL);  
}

void aiDrawString(char *what, float x, float y) {
  fprintf(aifp, "0 To %s", AI_EOL);
  fprintf(aifp, "1 0 0 1 %4.4f %4.4f 0 Tp %s", x, y, AI_EOL);
  fprintf(aifp, "TP %s", AI_EOL);
  fprintf(aifp, "0 Tr %s", AI_EOL);
  fprintf(aifp, "1 Ta %s", AI_EOL);  // TEMPORARY align center
  fprintf(aifp, "(%s) Tx 1 0 Tk %s", what, AI_EOL);
  fprintf(aifp, "(\\r) TX %s", AI_EOL);
  fprintf(aifp, "TO %s", AI_EOL);
}

void aiDrawString3f(char *what, float x, float y, float z) {
  float xx = ctm[0]*x + ctm[4]*y + ctm[8]*z + ctm[12];
  float yy = ctm[1]*x + ctm[5]*y + ctm[9]*z + ctm[13];
  float zz = ctm[2]*x + ctm[6]*y + ctm[10]*z + ctm[14];
  //zz /= 30.0;
  zz /= 35.0;
  zz = ABS(zz);

  fprintf(aifp, "0 To %s", AI_EOL);
  fprintf(aifp, "%4.4f 0 0 %4.4f %4.4f %4.4f 0 Tp %s", 
	  zz, zz, xx, yy, AI_EOL);
	  //ctm[0], ctm[4], ctm[1], ctm[5], x, y, AI_EOL);
  fprintf(aifp, "TP %s", AI_EOL);
  fprintf(aifp, "0 Tr %s", AI_EOL);
  fprintf(aifp, "1 Ta %s", AI_EOL);  // TEMPORARY align center
  fprintf(aifp, "(%s) Tx 1 0 Tk %s", what, AI_EOL);
  fprintf(aifp, "(\\r) TX %s", AI_EOL);
  fprintf(aifp, "TO %s", AI_EOL);
}
