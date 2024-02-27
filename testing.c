#include <stdio.h>

int main()
{
    FILE *file;
    char ch;

    // Open the file in read mode
    file = fopen("example.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // Read characters until EOF is encountered
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\0')
        {
            printf("found 0 \n");
        }
        putchar(ch); // Print each character to the console
    }
    printf("%c \n", ch);
    if (ch == -1)
    {
        printf("it is -1");
    }
    else if (ch == '\0')
    {
        printf("second");
    }
    // get next token ke states se likh raha hoon mai

    // Close the file
    fclose(file);

    return 0;
}
