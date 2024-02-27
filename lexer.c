// declarations
/*
kya zaroorat hai declarations ki
likh le
zarurat padegi
baad mie likh loonga
ok
how do i follow you?
abe declarations pehle likh le
*/
// include statements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexerDef.h"

#define BUFFER_SIZE 4096
typedef struct twinBuffer
{
    char *buffer1; // Declare buffer1 as a pointer
    char *buffer2;

} twinBuffer;
twinBuffer *buffer;

int fwdptr = 0;

char *currentBuffer(twinBuffer *buffer)
{
    if (bufferChoice == true)
    {
        return buffer->buffer1;
    }
    return buffer->buffer2;
}
TokenName *getNextToken(FILE *ptr)
{
    if (ptr == NULL)
    {
        return NULL;
    }
    else
    {
        if (feof(ptr))
        {
            fclose(ptr);
            return NULL;
        }
    }
    Token *token = (Token *)malloc(sizeof(Token));
    if (currentBuffer(buffer)[fwdptr] == '\0')
    {
        fwdptr = 0;
        ptr = getStream(ptr);
        if (ptr == NULL)
        {
            return NULL;
        }
    }
}
bool bufferChoice;

FILE *getStream(FILE *fp)
{
    if (bufferChoice == true)
    {
        memset(buffer->buffer1, '\0', BUFFER_SIZE + 1);
    }
    else
    {
        memset(buffer->buffer2, '\0', BUFFER_SIZE + 1);
    }
    if (feof(fp))
    {
        fclose(fp);
        bufferChoice = !bufferChoice;
        return NULL;
    }
    else
    {
        if (bufferChoice == true)
        {
            bufferChoice = !bufferChoice;
            if (fread(buffer->buffer1, sizeof(char), BUFFER_SIZE, fp) > 0)
            {
                buffer->buffer1[BUFFER_SIZE] = '\0';

                return fp;
            }
            else
            {
                fclose(fp);
                return NULL;
            }
        }
        else
        {
            bufferChoice = !bufferChoice;

            if (fread(buffer->buffer2, sizeof(char), BUFFER_SIZE, fp) > 0)
            {
                buffer->buffer2[BUFFER_SIZE] = '\0';

                return fp;
            }
            else
            {
                fclose(fp);
                return NULL;
            }
        }
    }
}

int main()
{
    // Allocate memory for buffers
    buffer->buffer1 = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char)); // true
    if (buffer->buffer1 == NULL)
    {
        fprintf(stderr, "Memory allocation failed for buffer1\n");
        return 1; // Exit with failure status
    }
    buffer->buffer1 = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char)); // false
    if (buffer->buffer2 == NULL)
    {
        fprintf(stderr, "Memory allocation failed for buffer1\n");
        return 1; // Exit with failure status
    }
    memset(buffer->buffer1, '\0', BUFFER_SIZE + 1);
    memset(buffer->buffer1, '\0', BUFFER_SIZE + 1);

    FILE *filePtr;
    filePtr = fopen("testCaseFile.txt", "r");
    if (filePtr == NULL)
    {
        printf("Error opening the file.\n");
        return 1; // Return 1 to indicate failure
    }
    filePtr = getStream(filePtr);

    fclose(filePtr);

    // Don't forget to free dynamically allocated memory when done using it

    return 0;
}
