#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "parser.h"
#include "lexer.h"
#include "lexerDef.h"

Grammar *allocGrammar()
{
    Grammar *G = (Grammar *)malloc(sizeof(Grammar));
    G->numOfRules = 0;
    G->rules = (Rules **)malloc(sizeof(Rules *) * NO_OF_NONTERMINALS);
    for (int i = 0; i < NO_OF_NONTERMINALS; i++)
    {
        G->rules[i] = (Rules *)malloc(sizeof(Rules));
        G->rules[i]->rulePtr = NULL;
        G->rules[i]->numVariableProductions = 0;
    }
    return G;
}
SymbolList *allocSymbolList()
{
    SymbolList *list = (SymbolList *)malloc(sizeof(SymbolList));
    list->productionLength = 0;
    list->head = NULL;
    list->tail = NULL;
}
void appendSymbolList(SymbolList *L, SymbolNode *node)
{
    if(L->head==NULL){
        L->head = node;
    }else{
        L->tail->next = node;
    }
    L->tail = node;
}

Rules *allocRules(int *ruleNo)
{
    Rule *newRule = (Rule *)malloc(sizeof(Rule));
    newRule->next = NULL;
    newRule->product = allocSymbolList();
    newRule->ruleNo = *ruleNo;
    *ruleNo++;
    return newRule;
}
// structure change kiya
// pooch raha hai ya bata raha
SymbolNode *allocSymbol(int enumIndex, bool isTerm)
{
    SymbolNode *S = (SymbolNode *)malloc(sizeof(SymbolNode));
    symbolType T;
    if (isTerm)
    {
        T.terminal = (TokenName)enumIndex;
    }
    else
    {
        T.non_terminal = (nonTerminal)enumIndex;
    }
    S->type = T;
    S->isTerm = isTerm;
    return S;
}
void appendRuleGrammar(Grammar *G, nonTerminal V, Rule *R)
{
    G->numOfRules++;
    G->rules[V]->numVariableProductions++;
    R->next = G->rules[V]->rulePtr = R;
    G->rules[V]->rulePtr = R;
}

TokenListNode *createTokenNode(TokenName name)
{
    TokenListNode *temp = (TokenListNode *)malloc(sizeof(TokenListNode));
    temp->name = name;
    temp->next = NULL;
    return temp;
}
TokenList *allocTokenList()
{
    TokenList *setPtr = (TokenList *)malloc(sizeof(TokenList));
    setPtr->setSize = 0;
    setPtr->head = NULL;
    setPtr->tail = NULL;
}
void allocSets(FirstAndFollow *F)
{
    F->table = (ffSingleNode **)malloc(NO_OF_NONTERMINALS * sizeof(ffSingleNode *));
    for (int i = 0; i < NO_OF_NONTERMINALS; i++)
    {
        F->table[i]->firstSet = allocTokenList();
        F->table[i]->followSet = allocTokenList();
    }
}
void appendNodeSet(TokenList *L, TokenListNode *node)
{
    L->tail->next = node;
    L->tail = L->tail->next;
}
void resetTailSet(TokenList *L)
{
    TokenListNode *temp = L->head;
    while (temp->next != NULL)
        temp = temp->next;
    L->tail = temp;
}
void deleteNodeSet(TokenList *L, TokenListNode *node)
{
    TokenListNode *temp = L->head, *prev = NULL;
    if (L->head == node)
    {
        L->head = temp->next;
    }
    else
    {
        while (temp != node)
        {
            temp = temp->next;
            prev = temp;
        }
        prev->next = temp->next;
    }
    free(temp);
    resetTailSet(L);
}
bool isNodeInSet(TokenList *L, TokenListNode *node)
{
    TokenListNode *temp = L->head;
    while (temp != node && temp != NULL)
    {
        temp = temp->next;
    }
    if (temp == node)
        return true;
    return false;
}

void addSets(TokenList *set1, TokenList *set2, bool isFollowSet)
{
    TokenListNode *set2_head = set2->head;
    while (set2_head != NULL)
    {
        if (set2_head->name == EPSILON && isFollowSet)
            continue;
        if (!isNodeInSet(set1, set2_head))
        {
            appendNodeSet(set1, set2_head);
        }
        set2_head = set2_head->next;
    }
    resetTailSet(set1);
}
ffSingleNode *findFFSymbolNode(FirstAndFollow *F, nonTerminal V){
    for(int i = 0; i < NO_OF_NONTERMINALS; i++){
        if(F->table[i]->name==V) {
            return F->table[i];
        }
    }

}
// hash table ki tarah karna hai kya?
// lamba padhega but bahut

void computeFirst(Grammar *G, FirstAndFollow *F, nonTerminal V, ffSingleNode *node)
{
    Rules *V_productions = G->rules[V];
    Rule *V_production = V_productions->rulePtr; // pointer to first V production
    TokenList *L = node->firstSet;
    for (int i = 0; i < V_productions->numVariableProductions; i++)
    {
        SymbolList *S = V_production->product;
        SymbolNode *temp = S->head; // first symbol in symbolList
        for (int j = 0; j < S->productionLength; j++)
        {

            if (temp->isTerm)
            {
                appendNodeSet(L, createTokenNode(temp->type.terminal));
                break;
            }
            else
            {
                TokenList *set2 = findFFSymbolNode(F,temp->type.non_terminal)->firstSet;
                computeFirst(G, F, temp->type.non_terminal, node);
                addSets(L,set2,false);
                if(!isNodeInSet(set2,EPSILON))break;
            }
        }
        temp = temp->next;
    }
    return;
}


bool contains_eps(TokenList *T)
{
    TokenListNode *ln = T->head;

    for (int i = 0; i < T->setSize; i++)
    {
        if (ln->name == EPSILON)
        {
            return true;
        }
        ln = ln->next;
    }
}

TokenList *returnFirst(FirstAndFollow *F, Rule *R)
{

    TokenList *firstSet = (TokenList *)malloc(sizeof(TokenList));
    firstSet->setSize = 0;
    Symbol *curr = R->symbols->symbols;

    TokenListNode *prev = (TokenListNode *)malloc(sizeof(TokenListNode));
    firstSet->head = prev;

    while (true)
    {

        TokenListNode *temp = (TokenListNode *)malloc(sizeof(TokenListNode));

        if (curr->isTerm)
        {
            prev->next = temp;
            prev->name = curr->type.terminal;
            firstSet->setSize++;
            break;
        }

        else if (!curr->isTerm)
        {
            ffSingleNode *ff = F->table[curr->type.nonterminal];
            prev->next = ff->firstSet->head;
            firstSet->setSize += ff->firstSet->setSize;
        }
    }
}

// function required to read grammar from text file

void createParseTable(FirstAndFollow F, Grammar G, Table *T)
{
}
// parseDef mai kya red dikha raha. suggestions han ab done hone band ho gye uski vajah se
