#ifndef LEXER_H
#define LEXER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexerDef.h"

FILE *getStream(FILE *fp);
TokenName *getNextToken(FILE *fileptr);
#endif