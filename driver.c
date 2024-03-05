#include "compiler.h"
#include <time.h>

void printCommentFreeCode(FILE *codeFile)
{
    char *line = (char *)malloc(1024);
    char *ptr;
    char *printstr = (char *)malloc(1024);
    char first_char;
    while (fgets(line, 1024, codeFile) != NULL)
    {
        ptr = line;
        printstr = line;
        int indent_cnt = 0;
        while (*ptr == ' ')
        {
            indent_cnt++;
            ptr++;
        }
        if (*ptr == '%')
        {
            continue;
        }
        if (*ptr == '\n')
        {
            continue;
        }
        char *temp = printstr;
        sscanf(ptr, "%[^%\n]", printstr);
        char *indentstr = (char *)malloc(indent_cnt + 1);
        if (indent_cnt != 0)
        {
            printf("%s%s\n", indentstr, printstr);
        }
        else
        {
            printf("%s\n", printstr);
        }
    }
}
void printTokens(FILE *codeFile)
{
    int cur_lineno = -1;
    Token *temp = NULL;
    while ((temp = getNextToken(codeFile)) != NULL)
    {
        if (cur_lineno < temp->lineno)
        {
            printf("\nLine.%d", temp->lineno);
            cur_lineno = temp->lineno;
        }
        if(temp->name == TK_COMMENT){
            continue;
        }
        printf("\t%s %s\n", terminals[temp->name], temp->lexeme);
    }
}

int main()
{
    // if (argc != 3)
    // {
    //    printf("supply 2 files\n");
    //    return 0;
    // }
    
    int i;
    while (true)
    {
        printf("Enter 1, 2, 3 or 0(quit)\n");
        scanf(" %d", &i);
        FILE *codeFile = fopen("t3.txt", "r");
        FILE *parseTreeOutFile = fopen("parsetreeout.txt", "w");

        if (i == 0)
        {
            printf("exit\n");
            break;
        }
        if (i == 1)
        {
            printCommentFreeCode(codeFile);
        }
        if (i == 2)
        {
            initializations();
            printTokens(codeFile);
        }
        if (i == 3)
        {
            callParser(codeFile, parseTreeOutFile); // which indirectly calls lexer
        }
        if (i == 4)
        {
            clock_t start_time, end_time;
            double total_CPU_time, total_CPU_time_in_seconds;
            start_time = clock();
            callParser(codeFile, parseTreeOutFile);
            end_time = clock();
            total_CPU_time = (double)(end_time - start_time);
            total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;
            printf("total_CPU_time: %lf\n", total_CPU_time);
            printf("total_CPU_time_in_seconds: %lf\n", total_CPU_time_in_seconds);
        }

        fclose(codeFile);
        fclose(parseTreeOutFile);
    }
}