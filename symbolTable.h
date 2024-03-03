#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#ifndef __symbolTabledef_H_INCLUDED__
#define __symbolTabledef_H_INCLUDED__
#include "symbolTableDef.h"
#endif
#ifndef __lexerDef_H_INCLUDED__
#define __lexerDef_H_INCLUDED__
#include "lexerDef.h"
#endif

int hashFunction(char *value, int no_entries);
symTable *createEmptyTable(int no_lists);
void addSymbol(symTable *lookupTable, Token *t, int lineno);
void addKeywords(symTable *lookupTable);
nodeInfo *getInfo(symTable *lookupTable, char *lexeme);
