#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "lexerDef.h"
#include "parserDef.h"

FirstAndFollow *computeFirstAndFollowSets(Grammar G);
void createParseTable(FirstAndFollow F, Grammar G, Table T);
parseTree *parseInputSourceCode(char *testcaseFile, Table T);
void printParseTree(parseTree *PT, char *outfile);