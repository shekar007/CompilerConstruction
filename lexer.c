// declarations
/*
kya zaroorat hai declarations ki
likh le
zarurat padegi
baad mie likh loonga
ok
how do i follow you?
abe declarations pehle likh le

and phone on kar apna
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
bool bufferChoice;

int fwdptr = 0;

char *currentBuffer(twinBuffer *buffer)
{
    if (bufferChoice == true)
    {
        return buffer->buffer1;
    }
    return buffer->buffer2;
}

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

FILE *refillBuffer(int *fwdptr, FILE *fileptr)
{

    if (currentBuffer(buffer)[*fwdptr] == '\0')
    {
        *fwdptr = 0;
        return getStream(fileptr);
    }

    else
    {
        return fileptr;
    }
}

TokenName *getNextToken(FILE *fileptr)
{
    if (fileptr == NULL)
    {
        return NULL;
    }
    else
    {
        if (feof(fileptr))
        {
            fclose(fileptr);
            return NULL;
        }
    }

    Token *token = (Token *)malloc(sizeof(Token));
    refillBuffer(&fwdptr, currentBuffer(buffer));

    int state = 0;
    char *lexeme = (char *)malloc(sizeof(char) * 50);
    memset(lexeme, '\0', 50);
    int lex_ptr = 0;
    char prev;

    while (true)
    {
        switch (state)
        {
        case 0:
        {
            // ab mai kya karu
            // case 1 se likhna start kar
            fileptr = refillBuffer(&fwdptr, fileptr);

            if (fileptr == NULL)
            {
                // state 60
                // print something and null;
                state = 60;
            }

            else if (currentBuffer(buffer)[fwdptr] == ' ' || currentBuffer(buffer)[fwdptr] == '\t')
            {
                state = 0;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '\n')
            {
                state = 0;
                fwdptr++;
                // line_number++;
            }

            else if (currentBuffer(buffer)[fwdptr] == ')')
            {
                state = 1;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == ',')
            {
                state = 2;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == ';')
            {
                state = 3;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == ']')
            {
                state = 4;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == ':')
            {
                state = 5;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '(')
            {
                state = 6;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '.')
            {
                state = 7;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '[')
            {
                state = 8;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '!')
            {
                state = 9;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '+')
            {
                state = 11;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '-')
            {
                state = 12;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '*')
            {
                state = 13;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '~')
            {
                state = 14;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '/')
            {
                state = 15;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '=')
            {
                state = 16;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '<')
            {
                state = 18;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '@')
            {
                state = 21;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '&')
            {
                state = 24;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '%')
            {
                state = 27;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '<')
            {
                state = 28;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '#')
            {
                state = 35;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] - '0' <= 9 && currentBuffer(buffer)[fwdptr] - '0' >= 0)
            {
                prev = currentBuffer(buffer)[fwdptr];
                state = 38;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '_')
            {
                state = 49;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == 'b' || currentBuffer(buffer)[fwdptr] == 'c' || currentBuffer(buffer)[fwdptr] == 'd')
            {
                prev = currentBuffer(buffer)[fwdptr];
                state = 53;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == 'a' || currentBuffer(buffer)[fwdptr] - 'a' <= 25 && currentBuffer(buffer)[fwdptr] - 'a' >= 4)
            {
                prev = currentBuffer(buffer)[fwdptr];
                state = 57;
                fwdptr++;
            }

            else
            {
                state = 60;
                fwdptr++;
            }
            break;
        }
        case 1:
        {

            lexeme[lex_ptr] = ')';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_CL;
            return token;
            break;
        }
        case 2:
        {
            lexeme[lex_ptr] = ',';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_COMMA;
            return token;
            break;
        }
        case 3:
        {
            lexeme[lex_ptr] = ';';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_SEM;
            return token;
            break;
        }
        case 4:
        {
            lexeme[lex_ptr] = ']';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_SQR;
            return token;
            break;
        }
        case 5:
        {
            lexeme[lex_ptr] = ':';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_COLON;
            return token;
            break;
        }
        case 6:
        {
            lexeme[lex_ptr] = '(';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_OP;
            return token;
            break;
        }
        case 7:
        {
            lexeme[lex_ptr] = ')';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_CL;
            return token;
            break;
        }
        case 8:
        {
            lexeme[lex_ptr] = '[';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_CL;
            return token;
            break;
        }
        case 9:
        {
            fileptr = refillBuffer(&fwdptr, fileptr);
            lexeme[lex_ptr] = '!';
            lex_ptr++;
            if (currentBuffer(buffer)[fwdptr] == '=')
            {
                state = 10;
                fwdptr++;
            }
            else
            {
                state = 60;
            }
            break;
        }
        case 10:
        {
            lexeme[lex_ptr] = '=';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_NE;
            return token;
        }
        case 11:
        {
            lexeme[lex_ptr] = '+';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_PLUS;
            return token;
        }
        case 12:
        {
            lexeme[lex_ptr] = '-';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_NE;
            return token;
        }
        case 13:
        {
            lexeme[lex_ptr] = '*';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_MUL;
            return token;
        }
        case 14:
        {
            lexeme[lex_ptr] = '~';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_NOT;
            return token;
        }
        case 15:
        {
            lexeme[lex_ptr] = '/';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_DIV;
            return token;
        }
        case 16:
        {
            fileptr = refillBuffer(&fwdptr, fileptr);

            lexeme[lex_ptr] = '=';
            lex_ptr++;
            if (currentBuffer(buffer)[fwdptr] == '=')
            {
                state = 17;
                lex_ptr++;
            }
            else
            {
                state = 60;
            }
            break;
        }
        case 17:
        {
            lexeme[lex_ptr] = '=';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_EQ;
            return token;
        }
        case 18:
        {
            fileptr = refillBuffer(&fwdptr, fileptr);
            lexeme[lex_ptr] = '>';
            lex_ptr++;
            if (currentBuffer(buffer)[fwdptr] == '=')
            {
                state = 20;
                fwdptr++;
            }
            else
            {
                state = 19;
            }
            break;
        }
        case 19:
        {
            token->lexeme = lexeme;
            token->name = TK_GT;
            return token;
        }
        case 20:
        {
            lexeme[lex_ptr] = '=';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_GE;
            return token;
        }
        case 21:
        {

            fileptr = refillBuffer(&fwdptr, fileptr);
            lexeme[lex_ptr] = '@';
            lex_ptr++;
            if (currentBuffer(buffer)[fwdptr] == '@')
            {
                state = 22;
                fwdptr++;
            }
            else
            {
                state = 60;
            }
            break;
        }
        case 22:
        {
            fileptr = refillBuffer(&fwdptr, fileptr);
            lexeme[lex_ptr] = '@';
            lex_ptr++;
            if (currentBuffer(buffer)[fwdptr] == '@')
            {
                state = 23;
                fwdptr++;
            }
            else
            {
                state = 60;
            }
            break;
        }
        case 23:
        {
            lexeme[lex_ptr] = '@';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_OR;
            return token;
        }
        case 24:
        {

            fileptr = refillBuffer(&fwdptr, fileptr);
            lexeme[lex_ptr] = '&';
            lex_ptr++;
            if (currentBuffer(buffer)[fwdptr] == '&')
            {
                state = 25;
                fwdptr++;
            }
            else
            {
                state = 60;
            }
            break;
        }
        case 25:
        {
            fileptr = refillBuffer(&fwdptr, fileptr);
            lexeme[lex_ptr] = '&';
            lex_ptr++;
            if (currentBuffer(buffer)[fwdptr] == '&')
            {
                state = 26;
                fwdptr++;
            }
            else
            {
                state = 60;
            }
            break;
        }
        case 26:
        {
            lexeme[lex_ptr] = '&';
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_AND;
            return token;
        }
        case 27:
        {
            if (currentBuffer(buffer)[fwdptr] == '\n')
                lexeme[lex_ptr] = '%';
            {
                token->lexeme = lexeme;
                token->name = TK_COMMENT;
                return token;
            }
            state = 27;
            fwdptr++;
        }

        case 28:
        {
            lexeme[lex_ptr] = '<';
            lex_ptr++;

            fileptr = refillBuffer(&fwdptr, fileptr);

            if (fileptr == NULL)
            {
                state = 60;
            }
            else if (currentBuffer(buffer)[fwdptr] == '-')
            {
                state = 30;
                fwdptr++;
            }

            else if (currentBuffer(buffer)[fwdptr] == '=')
            {
                state = 34;
                fwdptr++;
            }

            else
            {
                state = 29;
            }
        }

        case 29:
        {
            token->lexeme = lexeme;
            token->name = TK_LT;
            return token;
        }

        case 30:
        {
            lexeme[lex_ptr] = '-';
            lex_ptr++;

            fileptr = refillBuffer(&fwdptr, fileptr);

            if (fileptr == NULL)
            {
                state = 60;
            }

            else if (currentBuffer(buffer)[fwdptr] == '-')
            {
                state = 32;
                fwdptr++;
            }
            else
            {
                // implement (double) retraction
            }
        }

        case 31:
        {
            token->lexeme = lexeme;
            token->name = TK_LT;
            return token;
        }

        case 32:
        {
            lexeme[lex_ptr] = '-';
            lex_ptr++;

            fileptr = refillBuffer(&fwdptr, fileptr);

            if (fileptr == NULL)
            {
                state = 60;
            }

            else if (currentBuffer(buffer)[fwdptr] == '-')
            {
                state = 33;
                fwdptr++;
            }

            else
            {
                state = 60;
            }
            break;
        }

        case 33:
        {
            lexeme[lex_ptr] = '-';
            token->lexeme = lexeme;
            token->name = TK_ASSIGNOP;
            return token;
        }

        case 34:
        {
            lexeme[lex_ptr] = '=';
            token->lexeme = lexeme;
            token->name = TK_LE;
            return token;
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

    return 0;
}
