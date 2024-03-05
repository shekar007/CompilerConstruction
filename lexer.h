#ifndef LEXER_H
#define LEXER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexerDef.h"
void initializations();
FILE *getStream(FILE *fp);
void printToken(Token *t);
Token *getNextToken(FILE *fileptr);
void printToken(Token *t)
#endif
