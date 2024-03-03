#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexerDef.h"

FILE *getStream(FILE *fp);
Token *getNextToken(FILE *fileptr);
