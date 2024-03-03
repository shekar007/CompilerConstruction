#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "lexerDef.h"
#include "parserDef.h"

FirstAndFollow *computeFirstAndFollowSets(Grammar G);
Grammar *allocGrammar();
SymbolList *allocSymbolList();
TokenList *allocTokenList();
Rule *allocRule(nonTerminal V, int ruleNo);
SymbolNode *allocSymbol(int enumIndex, bool isTerm);
void allocSets(FirstAndFollow *F);
void appendRuleGrammar(Grammar *G, nonTerminal V, Rule *R);
void appendSymbolList(SymbolList *L, SymbolNode *node);
void appendNodeSet(TokenList *L, TokenListNode *node);
void deleteNodeSet(TokenList *L, TokenListNode *node);
bool isNodeInSet(TokenList *L, TokenListNode *node);
void resetTailSet(TokenList *L);
void addSets(TokenList *set1, TokenList *set2, bool isFollowSet);
ffSingleNode *findFFSymbolNode(FirstAndFollow *F, nonTerminal V);
TokenListNode *createTokenNode(TokenName name);
void computeFirst(Grammar *G, FirstAndFollow *F, nonTerminal V, ffSingleNode *node);
void createParseTable(FirstAndFollow F, Grammar G, Table T);
// parseTree *parseInputSourceCode(char *testcaseFile, Table T);
// void printParseTree(parseTree *PT, char *outfile);
#endif