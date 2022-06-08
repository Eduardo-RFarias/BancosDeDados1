#include "utils.h"

FILE *appendOrCreateFileForWriting(char *fileName)
{
    FILE *file;

    file = fopen(fileName, "ab");

    if (file != NULL)
    {
        return file;
    }

    file = fopen(fileName, "wb");

    if (file != NULL)
    {
        return file;
    }

    printf("Error opening file!\n");
    exit(1);
}

FILE *openFileForReading(char *fileName)
{
    FILE *file;

    file = fopen(fileName, "rb");

    if (file != NULL)
    {
        return file;
    }

    printf("Error opening file!\n");
    exit(1);
}

FILE *openFileOrCreateForReading(char *fileName)
{
    FILE *file;

    file = fopen(fileName, "rb");

    if (file != NULL)
    {
        return file;
    }

    file = fopen(fileName, "wb");

    if (file == NULL)
    {
        printf("Error creating file!\n");
        exit(1);
    }

    fclose(file);

    file = fopen(fileName, "rb");

    if (file != NULL)
    {
        return file;
    }

    printf("Error opening file!\n");
    exit(1);
}

FILE *overrideOrCreateFileForWriting(char *fileName)
{
    FILE *file;

    file = fopen(fileName, "wb");

    if (file != NULL)
    {
        return file;
    }

    printf("Error opening file!\n");
    exit(1);
}

void clearTerminal()
{
#if defined(_linux) || defined(unix) || defined(APPLE_)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

void readString(char *destiny, int MAXSIZE)
{
    fgets(destiny, MAXSIZE, stdin);
    destiny[strlen(destiny) - 1] = '\0';
}