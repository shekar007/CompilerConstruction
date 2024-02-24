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

#define BUFFER_SIZE 4096
typedef struct twinBuffer
{
    char *buffer1; // Declare buffer1 as a pointer
    char *buffer2;
} twinBuffer;
char *buffer1; // Declare buffer1 as a pointer
char *buffer2;
void removeComments(char *testcaseFile, char *cleanFile)
{
    int n = sizeof(testcaseFile) / sizeof(testcaseFile[0]);
    bool falg = false;
    for (int i = 0; i < n; i++)
    {
    }
};

bool bufferChoice;

FILE *getStream(FILE *fp)
{
    if (bufferChoice == true)
    {
        memset(buffer1, '\0', BUFFER_SIZE + 1);
    }
    else
    {
        memset(buffer2, '\0', BUFFER_SIZE + 1);
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
            if (fread(buffer1, sizeof(char), BUFFER_SIZE, fp) > 0)
            {
                buffer1[BUFFER_SIZE] = '\0';

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

            if (fread(buffer2, sizeof(char), BUFFER_SIZE, fp) > 0)
            {
                buffer2[BUFFER_SIZE] = '\0';

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

Token *getNextToken(twinBuffer B)
{
}

int main()
{
    // Allocate memory for buffers
    buffer1 = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char)); // true
    if (buffer1 == NULL)
    {
        fprintf(stderr, "Memory allocation failed for buffer1\n");
        return 1; // Exit with failure status
    }
    buffer2 = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char)); // false
    if (buffer2 == NULL)
    {
        fprintf(stderr, "Memory allocation failed for buffer1\n");
        return 1; // Exit with failure status
    }
    memset(buffer1, '\0', BUFFER_SIZE + 1);
    memset(buffer2, '\0', BUFFER_SIZE + 1);

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
    free(buffer1);
    free(buffer2);

    return 0;
}
