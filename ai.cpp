#include "ai.h"


/*
  THIS IS HIGHLY UNSUPPORTED CODE THAT CHANGES ALL THE TIME
  ben fry 99.12.19
*/


boolean aiCapture = FALSE;
static char AI_EOL[] = { 13, 10, 0 };
//static char aiFilenameTemplate[] = "illusfart-%03d.ai";
//int aiCount = -1;
FILE *afp;


void aiBegin(char *filename) {
  /*
  char filename[32];
  if (aiCount == -1) {
    acuxNumberedFilename(filename, aiFilenameTemplate, &aiCount);
  } else {
    sprintf(filename, aiFilenameTemplate, aiCount++);
  }
  */
  afp = fopen(filename, "wb");

  int screenDim[2];
  acuGetIntegerv(ACU_WINDOW_SIZE, screenDim);

  fprintf(afp, "%%!PS-Adobe-2.0 %s", AI_EOL);
  fprintf(afp, "%%%%Creator:Adobe Illustrator(TM) 1.1%s", AI_EOL);
  //fprintf(afp, "%%%%For: (Glen Nupert) (Zemo\(r\) Handbuzzers)%s", AI_EOL);
  //fprintf(afp, "%%%%Title: (oneline-1.0.ai)%s", AI_EOL);
  //fprintf(afp, "%%%%CreationDate: (7/26/99) (8:25 PM)%s", AI_EOL);
  //fprintf(afp, "%%%%DocumentProcessColors: Black%s", AI_EOL);
  //fprintf(afp, "%%%%DocumentProcSets: Adobe_Illustrator_1.1 0 0%s", AI_EOL);
  //fprintf(afp, "%%%%DocumentSuppliedProcSets: Adobe_Illustrator_1.1 0 0%s", AI_EOL);
  fprintf(afp, "%%%%BoundingBox:%d %d %d %d%s", 
	  0, 0, screenDim[0], screenDim[1], AI_EOL);
  //fprintf(afp, "%%%%TemplateBox:%d %d %d %d%s", 
  //  0, 0, screenDim[0], screenDim[1], AI_EOL);
  //fprintf(afp, "%%%%TileBox:%d %d %d %d%s", 
  //  0, 0, screenDim[0], screenDim[1], AI_EOL);

  //fprintf(afp, "%%%%ColorUsage: Black&White%s", AI_EOL);
  //fprintf(afp, "%%%%TemplateBox:306 396 306 396%s", AI_EOL);
  //fprintf(afp, "%%%%TileBox: 30 31 582 759%s", AI_EOL);
  //fprintf(afp, "%%%%DocumentPreview: None%s", AI_EOL);
  fprintf(afp, "%%%%EndComments%s", AI_EOL);
  fprintf(afp, "%%%%EndProlog%s", AI_EOL);
  fprintf(afp, "%%%%BeginSetup%s", AI_EOL);
  fprintf(afp, "Adobe_Illustrator_1.1 begin%s", AI_EOL);
  fprintf(afp, "n%s", AI_EOL);
  fprintf(afp, "%%%%EndSetup%s", AI_EOL);

  // k = cmyk fill color
  //fprintf(afp, "0 0 0 0 k%s", AI_EOL);  
  // K = cmyk stroke color
  //fprintf(afp, "0 0 0 1 K%s", AI_EOL);  
  // i = setflat
  fprintf(afp, "0 i%s", AI_EOL);  
  // 0 J = setlinecap
  // 0 j = setlinejoin
  // 0.25 w = setlinewidth
  // 4 M = setmiterlimit
  // []0 d = setdash
  fprintf(afp, "0 J 0 j 0.25 w 4 M []0 d%s", AI_EOL);

  aiCapture = TRUE;
}


void aiEnd() {
  fprintf(afp, "%%%%PageTrailer%s", AI_EOL);
  fprintf(afp, "%%%%Trailer%s", AI_EOL);
  fprintf(afp, "_E end%s", AI_EOL);
  fprintf(afp, "%%%%EOF%s", AI_EOL);

  //fwrite(aiFooterData, 1, aiFooterLength, afp);
  fflush(afp);
  fclose(afp);
  afp = NULL;
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
  fprintf(afp, "%1.2f %1.2f %1.2f %1.2f k%s", 
	  1.0-r, 1.0-g, 1.0-b, 0.0, AI_EOL);
}

void aiStrokeColorRGB(float r, float g, float b) {
  fprintf(afp, "%1.2f %1.2f %1.2f %1.2f K%s", 
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
  fprintf(afp, "u%s", AI_EOL);
}

void aiEndGroup() {
  fprintf(afp, "U%s", AI_EOL);
}

void aiBeginLock() {
  fprintf(afp, "1 A%s", AI_EOL);
}

void aiEndLock() {
  fprintf(afp, "0 A%s", AI_EOL);
}

void aiStrokeWidthGet() {
  float param[1];
  glGetFloatv(GL_LINE_WIDTH, param);
  aiStrokeWidth(param[0]);
}

void aiStrokeWidth(float width) {
  // 0.25 w = setlinewidth
  fprintf(afp, "%4.4f w%s", width, AI_EOL);
}

void aiBeginPath() {
}

void aiMoveTo(float x, float y) {
  fprintf(afp, "%4.4f %4.4f m%s", x, y, AI_EOL);
}

// L and l seem to do same thing
void aiLineTo(float x, float y) {
  fprintf(afp, "%4.4f %4.4f l%s", x, y, AI_EOL);
}

void aiCurveTo(float x1, float y1, float x2, float y2, float x3, float y3) {
  fprintf(afp, "%4.4f %4.4f %4.4f %4.4f %4.4f %4.4f c%s", 
	  x1, y1, x2, y2, x3, y3, AI_EOL);
}

void aiEndPath() {
  // B - fill and stroke line
  // S - stroke line
  fprintf(afp, "S%s", AI_EOL);
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
  fprintf(afp, "f%s", AI_EOL);
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

  fprintf(afp, "%4.4f %4.4f m%s", xx, yy, AI_EOL);
}

// L and l seem to do same thing
void aiLineTo3f(float x, float y, float z) {
  //float xx = ctm[0]*x + ctm[1]*y + ctm[2]*z + ctm[3];
  //float yy = ctm[4]*x + ctm[5]*y + ctm[6]*z + ctm[7];

  float xx = ctm[0]*x + ctm[4]*y + ctm[8]*z + ctm[12];
  float yy = ctm[1]*x + ctm[5]*y + ctm[9]*z + ctm[13];

  fprintf(afp, "%4.4f %4.4f l%s", xx, yy, AI_EOL);
}

