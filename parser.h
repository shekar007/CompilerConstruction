#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "lexerDef.h"
#include "parserDef.h"

firstAndFollow *computeFirstAndFollowSets(Grammar G);
void createParseTable(firstAndFollow F, Table T);
parseTree *parseInputSourceCode(char *testcaseFile, Table T);
void printParseTree(parseTree *PT, char *outfile);