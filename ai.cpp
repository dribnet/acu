#include "ai.h"


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

  float bgColor[3];
  acuGetFloatv(ACU_WINDOW_BG_COLOR, bgColor);
  aiFillColorRGB(bgColor[0], bgColor[1], bgColor[2]);
  aiBeginLock();
  aiFilledRectangleMacro(0, 0, (float)screenDim[0], 
			 (float)screenDim[1]);
  aiEndLock();
}


void aiEnd() {
  fprintf(afp, "%%%%PageTrailer%s", AI_EOL);
  fprintf(afp, "%%%%Trailer%s", AI_EOL);
  fprintf(afp, "_E end%s", AI_EOL);
  fprintf(afp, "%%%%EOF%s", AI_EOL);

  //fwrite(aiFooterData, 1, aiFooterLength, afp);
  fclose(afp);
  afp = NULL;
  aiCapture = FALSE;
}


void aiFillColorRGB(float r, float g, float b) {
  fprintf(afp, "%1.2f %1.2f %1.2f %1.2f k%s", 
	  1.0-r, 1.0-g, 1.0-b, 0.0, AI_EOL);
}

void aiStrokeColorRGB(float r, float g, float b) {
  fprintf(afp, "%1.2f %1.2f %1.2f %1.2f K%s", 
	  1.0-r, 1.0-g, 1.0-b, 0.0, AI_EOL);
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

void aiLineWidth(float width) {
  // 0.25 w = setlinewidth
  fprintf(afp, "%4.4f w%s", AI_EOL);
}

void aiBeginLine() {
}

void aiMoveTo(float x, float y) {
  fprintf(afp, "%4.4f %4.4f m%s", x, y, AI_EOL);
}

// L and l seem to do same thing
void aiLineTo(float x, float y) {
  fprintf(afp, "%4.4f %4.4f l%s", x, y, AI_EOL);
}

void aiEndLine() {
  // B - fill and stroke line
  // S - stroke line
  fprintf(afp, "S%s", AI_EOL);
}


void aiLineMacro(float x1, float y1, float x2, float y2) {
  aiBeginLine();
  aiMoveTo(x1, y1);
  aiLineTo(x2, y2);
  aiEndLine();
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
