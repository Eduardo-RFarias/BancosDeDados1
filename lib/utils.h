#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define TRUE 1
#define FALSE 0

FILE *appendOrCreateFileForWriting(char *fileName);

FILE *openFileForReading(char *fileName);

FILE *openFileOrCreateForReading(char *fileName);

FILE *overrideOrCreateFileForWriting(char *fileName);

void clearTerminal();

void readString(char *destiny, int MAXSIZE);

#endif