/*

1. double retraction handle karna hai
2. values of variables and numbers - done
3. buffer retraction case
4. variable length case - Done
5. add to symbol table using addSymbol function
6. restrict varibale length

*/
// include statements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexerDef.h"
#include "symbolTable.h"
#include "symbolTableDef.h"

#define BUFFER_SIZE 4096
typedef struct twinBuffer
{
    char *buffer1; // Declare buffer1 as a pointer
    char *buffer2;

} twinBuffer;
twinBuffer *buffer;
bool bufferChoice;
symTable *symbolTable;
int fwdptr = 0;
int varlength = 0;
int lineno = 0;
bool isnum(char c)
{
    if (c >= '0' && c <= '9')
    {
        return true;
    }
    return false;
}
bool isalphabet(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return true;
    }
    return false;
}
bool isIgnoreCaseAlphabet(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return true;
    }
    return false;
}
bool is2to7(char c)
{
    if ((c >= '2' && c <= '7'))
    {
        return true;
    }
    return false;
}
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
    varlength = 0;
    int errtype = 0;
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
                prev = '%';
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
                varlength++;
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

            lexeme[lex_ptr] = prev;
            lex_ptr++;
            token->name = TK_COMMENT;

            do
            {
                fwdptr++;
                char ch = currentBuffer(buffer)[fwdptr];
                if (ch == -1)
                {
                    token->lexeme = lexeme;
                    return token;
                }
                else if (ch == '\n')
                {
                    token->lexeme = lexeme;
                    lineno++;
                    return token;
                }
                else
                {
                    lexeme[lex_ptr] = ch;
                }
            } while (true);
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
        case 35:
        {

            fileptr = refillBuffer(&fwdptr, fileptr);

            lexeme[lex_ptr] = '#';
            lex_ptr++;
            char c = currentBuffer(buffer)[fwdptr];
            if (isalphabet(c))
            {
                prev = c;
                state = 36;
                fwdptr++;
            }
            else
            {
                state = 60;
            }
            break;
        }
        case 36:
        {
            lexeme[lex_ptr] = prev;
            lex_ptr++;
            fileptr = refillBuffer(&fwdptr, fileptr);

            char c = currentBuffer(buffer)[fwdptr];
            if (isalphabet(c))
            {
                state = 36;
                prev = c;
                fwdptr++;
            }
            else
            {
                state = 37;
                prev = c;
            }
            break;
        }
        case 37:
        {
            token->lexeme = lexeme;
            token->name = TK_RUID;
            nodeInfo *n = getInfo(symbolTable, lexeme);
            if (n->is_present)
            {
                token->name = n->node->tokentype;
                return token;
            }
            else
            {
                addSymbol(symbolTable, token, lineno);
                return token;
            }
        }
        case 38:
        {
            lexeme[lex_ptr] = prev;
            lex_ptr++;
            fileptr = refillBuffer(&fwdptr, fileptr);
            char c = currentBuffer(buffer)[fwdptr];
            if (isnum(c))
            {
                prev = c;
                fwdptr++;
                state = 38;
            }
            else if (c == '.')
            {
                state = 40;
                fwdptr++;
            }
            else
            {
                state = 39;
            }
            break;
        }
        case 39:
        {

            token->lexeme = lexeme;
            token->name = TK_NUM;
            token->value->num = atoi(lexeme);
            token->isint = 1;
            return token;
        }
        case 40:
        {
            lexeme[lex_ptr] = '.';
            lex_ptr++;
            fileptr = refillBuffer(&fwdptr, fileptr);
            char c = currentBuffer(buffer)[fwdptr];
            if (isnum(c))
            {
                prev = c;
                state = 42;
                fwdptr++;
            }
            else
            {
                // double retraction
            }
        }
        case 41:
        {
            // double retraction
            // note
        }
        case 42:
        {
            lexeme[lex_ptr] = prev;
            lex_ptr++;
            fileptr = refillBuffer(&fwdptr, fileptr);
            char c = currentBuffer(buffer)[fwdptr];
            if (isnum(c))
            {
                prev = c;
                state = 43;
                fwdptr++;
            }
            else
            {
                state = 60;
            }
            break;
        }
        case 43:
        {
            lexeme[lex_ptr] = prev;
            lex_ptr++;
            fileptr = refillBuffer(&fwdptr, fileptr);
            char c = currentBuffer(buffer)[fwdptr];
            if (c == 'E')
            {
                prev = c;
                state = 45;
                fwdptr++;
            }
            else
            {
                state = 44;
            }
            break;
        }
        case 44:
        {

            token->lexeme = lexeme;
            token->name = TK_RNUM;
            token->isint = 0;
            token->value->r_num = strtof(lexeme, NULL);
            token->isint = 0;
            return token;
            // note
        }
        case 45:
        {
            lexeme[lex_ptr] = 'E';
            lex_ptr++;
            fileptr = refillBuffer(&fwdptr, fileptr);
            char c = currentBuffer(buffer)[fwdptr];
            prev = c;

            if (c == '+' | c == '-')
            {
                state = 46;
                fwdptr++;
            }
            else if (isnum(c))
            {
                state = 47;
                fwdptr++;
            }
            else
            {
                state = 60;
            }
        }
        case 46:
        {
            lexeme[lex_ptr] = prev;
            lex_ptr++;
            fileptr = refillBuffer(&fwdptr, fileptr);
            char c = currentBuffer(buffer)[fwdptr];
            prev = c;
            if (isnum(c))
            {
                state = 47;
                fwdptr++;
            }
            else
            {
                state = 60;
            }
            break;
        }
        case 47:
        {
            lexeme[lex_ptr] = prev;
            lex_ptr++;
            fileptr = refillBuffer(&fwdptr, fileptr);
            char c = currentBuffer(buffer)[fwdptr];
            prev = c;
            if (isnum(c))
            {
                state = 48;
                fwdptr++;
            }
            else
            {
                state = 60;
            }
            break;
        }
        case 48:
        {
            lexeme[lex_ptr] = prev;
            token->lexeme = lexeme;
            token->name = TK_RNUM;
            token->isint = 0;
            token->value->r_num = strtof(lexeme, NULL);
            return token;
        }
        case 49:
        {
            lexeme[lex_ptr] = '_';
            lex_ptr++;
            fileptr = refillBuffer(&fwdptr, fileptr);
            char c = currentBuffer(buffer)[fwdptr];
            prev = c;
            // note
            if (isIgnoreCaseAlphabet(c))
            {
                state = 50;
                fwdptr++;
            }
            else
            {
                state = 60;
            }
            break;
        }
        case 50:
        {
            lexeme[lex_ptr] = prev;
            lex_ptr++;
            fileptr = refillBuffer(&fwdptr, fileptr);
            char c = currentBuffer(buffer)[fwdptr];
            prev = c;
            if (isIgnoreCaseAlphabet(c))
            {
                state = 50;
                fwdptr++;
            }
            else if (isnum(c))
            {
                state = 51;
                fwdptr++;
            }
            else
            {
                state = 52;
                fwdptr++;
            }
            break;
        }
        case 51:
        {
            lexeme[lex_ptr] = prev;
            lex_ptr++;
            fileptr = refillBuffer(&fwdptr, fileptr);
            char c = currentBuffer(buffer)[fwdptr];
            prev = c;
            if (isnum(c))
            {
                state = 51;
                fwdptr++;
            }
            else
            {
                state = 52;
                fwdptr++;
            }
            break;
        }
        case 52:
        {
            lexeme[lex_ptr] = prev;
            lex_ptr++;
            token->lexeme = lexeme;
            token->name = TK_FUNID;
            nodeInfo *n = getInfo(symbolTable, lexeme);
            if (n->is_present)
            {
                token->name = n->node->tokentype;
                return token;
            }
            else
            {
                addSymbol(symbolTable, token, lineno);
                return token;
            }
            return token;
        }
        case 53:
        {
            lexeme[lex_ptr] = prev;
            lex_ptr++;
            fileptr = refillBuffer(&fwdptr, fileptr);
            char c = currentBuffer(buffer)[fwdptr];
            prev = c;
            // note
            if (is2to7(c))
            {
                state = 54;
                varlength++;
                fwdptr++;
            }
            else if (isalphabet(c))
            {
                state = 57;
                varlength++;
                fwdptr++;
            }
            else
            {
                state = 60;
            }
            break;
        }
        case 54:
        {
            lexeme[lex_ptr] = prev;
            lex_ptr++;
            fileptr = refillBuffer(&fwdptr, fileptr);
            char c = currentBuffer(buffer)[fwdptr];
            prev = c;
            if (c == 'b' || c == 'c' || c == 'd')
            {
                state = 54;
                varlength++;
                fwdptr++;
            }
            else if (is2to7(c))
            {
                state = 55;
                varlength++;
                fwdptr++;
            }
            else
            {
                state = 56;
            }
            break;
        }
        case 55:
        {
            lexeme[lex_ptr] = prev;
            lex_ptr++;
            fileptr = refillBuffer(&fwdptr, fileptr);
            char c = currentBuffer(buffer)[fwdptr];
            prev = c;
            if (is2to7(c))
            {
                state = 55;
                fwdptr++;
            }
            else
            {
                state = 56;
            }
            break;
        }
        case 56:
        {
            token->lexeme = lexeme;
            token->name = TK_ID;
            if (varlength >= 2 && varlength <= 20)
            {
                nodeInfo *n = getInfo(symbolTable, lexeme);
                if (n->is_present)
                {
                    token->name = n->node->tokentype;
                    return token;
                }
                else
                {
                    addSymbol(symbolTable, token, lineno);
                    return token;
                }
                return token;
            }
            else
            {
                state = 60;
                errtype = 1;
            }
            break;
            // note
        }
        case 57:
        {
            lexeme[lex_ptr] = prev;
            lex_ptr++;
            fileptr = refillBuffer(&fwdptr, fileptr);
            char c = currentBuffer(buffer)[fwdptr];
            prev = c;
            if (isalphabet(c))
            {
                state = 57;
                fwdptr++;
            }
            else
            {
                state = 58;
                fwdptr++;
            }
            break;
        }
        case 58:
        {
            token->lexeme = lexeme;
            token->name = TK_FIELDID;
            nodeInfo *n = getInfo(symbolTable, lexeme);
            if (n->is_present)
            {
                token->name = n->node->tokentype;
                return token;
            }
            else
            {
                addSymbol(symbolTable, token, lineno);
                return token;
            }
        }
        case 59:
        {
            lineno++;
            state = 0;
            fwdptr++;
            break;
        }
        case 60:
        {

            printf("Error at lineno : %d\n", lineno);
            if (errtype == 0)
            {
                printf("\nThis is not a valid token : %s \n", lexeme);
            }
            else
            {
                printf("Variable length should be between 2 and 20.\n Length of variable '%s' is %d \n", lexeme, varlength);
            }
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

    return 0;
}
