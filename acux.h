#include "acu.h"
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>


float acuxFrameRate();

void acuxNumberedFilename(char *dest, char *tmpl, int *num);

void acuxReadToEOL(FILE *fp);
void acuxReadSpace(FILE *fp);
void acuxReadWord(FILE *fp, char *word);
float acuxReadFloat(FILE *fp);

