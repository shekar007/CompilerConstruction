#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
char *CharToString(char c)
{
    char *str = (char *)malloc(2 * sizeof(char));
    str[0] = c;
    str[1] = '\0';
    return str;
}

void removeComments(char *testcaseFile, char *cleanFile)
{
    int n = strlen(testcaseFile);
    bool flag = true;
    for (int i = 0; i < n; i++)
    {
        if (flag)
        {
            if (testcaseFile[i] == '%')
            {
                flag = false;
            }
            else
            {
                strcat(cleanFile, CharToString(testcaseFile[i]));
            }
        }
        else
        {
            if (testcaseFile[i] == '\n' || testcaseFile[i] == '\0')
            {
                strcat(cleanFile, CharToString(testcaseFile[i]));
                flag = true;
            }
        }
    }
}
#include <stdio.h>
#include <stdlib.h>

char *readFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(1);
    }

    // Find out the file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file contents
    char *buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    // Read the file into the buffer
    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead != fileSize)
    {
        fprintf(stderr, "Error reading file\n");
        exit(1);
    }
    buffer[bytesRead] = '\0'; // Null-terminate the string

    fclose(file);

    return buffer;
}

int main()
{
    const char *filename = "testCaseFile.txt"; // Change this to your file's name

    char *fileContent = readFile(filename);
    char *file2 = (char *)malloc(sizeof(fileContent));
    // Print the contents
    printf("File contents:\n%s\n", fileContent);
    removeComments(fileContent, file2);
    printf("File contents:\n%s\n", file2);

    // Don't forget to free the memory
    free(fileContent);

    return 0;
}
