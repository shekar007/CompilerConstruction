#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "parser.h"
#include "parserDef.h"
#include "lexer.h"
#include "lexerDef.h"
#define LINE_SIZE 200 * sizeof(char)
TokenName stringToTokenName(char *str)
{
    if (strcmp(str, "TK_ASSIGNOP") == 0)
    {
        return TK_ASSIGNOP;
    }
    else if (strcmp(str, "TK_COMMENT") == 0)
    {
        return TK_COMMENT;
    }
    else if (strcmp(str, "TK_FIELDID") == 0)
    {
        return TK_FIELDID;
    }
    else if (strcmp(str, "TK_ID") == 0)
    {
        return TK_ID;
    }
    else if (strcmp(str, "TK_NUM") == 0)
    {
        return TK_NUM;
    }
    else if (strcmp(str, "TK_RNUM") == 0)
    {
        return TK_RNUM;
    }
    else if (strcmp(str, "TK_FUNID") == 0)
    {
        return TK_FUNID;
    }
    else if (strcmp(str, "TK_RUID") == 0)
    {
        return TK_RUID;
    }
    else if (strcmp(str, "TK_WITH") == 0)
    {
        return TK_WITH;
    }
    else if (strcmp(str, "TK_PARAMETERS") == 0)
    {
        return TK_PARAMETERS;
    }
    else if (strcmp(str, "TK_END") == 0)
    {
        return TK_END;
    }
    else if (strcmp(str, "TK_WHILE") == 0)
    {
        return TK_WHILE;
    }
    else if (strcmp(str, "TK_UNION") == 0)
    {
        return TK_UNION;
    }
    else if (strcmp(str, "TK_ENDUNION") == 0)
    {
        return TK_ENDUNION;
    }
    else if (strcmp(str, "TK_DEFINETYPE") == 0)
    {
        return TK_DEFINETYPE;
    }
    else if (strcmp(str, "TK_AS") == 0)
    {
        return TK_AS;
    }
    else if (strcmp(str, "TK_TYPE") == 0)
    {
        return TK_TYPE;
    }
    else if (strcmp(str, "TK_MAIN") == 0)
    {
        return TK_MAIN;
    }
    else if (strcmp(str, "TK_GLOBAL") == 0)
    {
        return TK_GLOBAL;
    }
    else if (strcmp(str, "TK_PARAMETER") == 0)
    {
        return TK_PARAMETER;
    }
    else if (strcmp(str, "TK_LIST") == 0)
    {
        return TK_LIST;
    }
    else if (strcmp(str, "TK_SQL") == 0)
    {
        return TK_SQL;
    }
    else if (strcmp(str, "TK_SQR") == 0)
    {
        return TK_SQR;
    }
    else if (strcmp(str, "TK_INPUT") == 0)
    {
        return TK_INPUT;
    }
    else if (strcmp(str, "TK_OUTPUT") == 0)
    {
        return TK_OUTPUT;
    }
    else if (strcmp(str, "TK_INT") == 0)
    {
        return TK_INT;
    }
    else if (strcmp(str, "TK_REAL") == 0)
    {
        return TK_REAL;
    }
    else if (strcmp(str, "TK_COMMA") == 0)
    {
        return TK_COMMA;
    }
    else if (strcmp(str, "TK_SEM") == 0)
    {
        return TK_SEM;
    }
    else if (strcmp(str, "TK_COLON") == 0)
    {
        return TK_COLON;
    }
    else if (strcmp(str, "TK_DOT") == 0)
    {
        return TK_DOT;
    }
    else if (strcmp(str, "TK_ENDWHILE") == 0)
    {
        return TK_ENDWHILE;
    }
    else if (strcmp(str, "TK_OP") == 0)
    {
        return TK_OP;
    }
    else if (strcmp(str, "TK_CL") == 0)
    {
        return TK_CL;
    }
    else if (strcmp(str, "TK_IF") == 0)
    {
        return TK_IF;
    }
    else if (strcmp(str, "TK_THEN") == 0)
    {
        return TK_THEN;
    }
    else if (strcmp(str, "TK_ENDIF") == 0)
    {
        return TK_ENDIF;
    }
    else if (strcmp(str, "TK_READ") == 0)
    {
        return TK_READ;
    }
    else if (strcmp(str, "TK_WRITE") == 0)
    {
        return TK_WRITE;
    }
    else if (strcmp(str, "TK_RETURN") == 0)
    {
        return TK_RETURN;
    }
    else if (strcmp(str, "TK_PLUS") == 0)
    {
        return TK_PLUS;
    }
    else if (strcmp(str, "TK_MINUS") == 0)
    {
        return TK_MINUS;
    }
    else if (strcmp(str, "TK_MUL") == 0)
    {
        return TK_MUL;
    }
    else if (strcmp(str, "TK_DIV") == 0)
    {
        return TK_DIV;
    }
    else if (strcmp(str, "TK_CALL") == 0)
    {
        return TK_CALL;
    }
    else if (strcmp(str, "TK_RECORD") == 0)
    {
        return TK_RECORD;
    }
    else if (strcmp(str, "TK_ENDRECORD") == 0)
    {
        return TK_ENDRECORD;
    }
    else if (strcmp(str, "TK_ELSE") == 0)
    {
        return TK_ELSE;
    }
    else if (strcmp(str, "TK_AND") == 0)
    {
        return TK_AND;
    }
    else if (strcmp(str, "TK_OR") == 0)
    {
        return TK_OR;
    }
    else if (strcmp(str, "TK_NOT") == 0)
    {
        return TK_NOT;
    }
    else if (strcmp(str, "TK_LT") == 0)
    {
        return TK_LT;
    }
    else if (strcmp(str, "TK_LE") == 0)
    {
        return TK_LE;
    }
    else if (strcmp(str, "TK_EQ") == 0)
    {
        return TK_EQ;
    }
    else if (strcmp(str, "TK_GT") == 0)
    {
        return TK_GT;
    }
    else if (strcmp(str, "TK_GE") == 0)
    {
        return TK_GE;
    }
    else if (strcmp(str, "TK_NE") == 0)
    {
        return TK_NE;
    }
    else
    {
        return EPSILON; // Default value
    }
}
nonTerminal stringToNonTerminal(char *str)
{
    if (strcmp(str, "program") == 0)
    {
        return program;
    }
    else if (strcmp(str, "mainFunction") == 0)
    {
        return mainFunction;
    }
    else if (strcmp(str, "otherFunctions") == 0)
    {
        return otherFunctions;
    }
    else if (strcmp(str, "function") == 0)
    {
        return function;
    }
    else if (strcmp(str, "input_par") == 0)
    {
        return input_par;
    }
    else if (strcmp(str, "output_par") == 0)
    {
        return output_par;
    }
    else if (strcmp(str, "parameter_list") == 0)
    {
        return parameter_list;
    }
    else if (strcmp(str, "dataType") == 0)
    {
        return dataType;
    }
    else if (strcmp(str, "primitiveDatatype") == 0)
    {
        return primitiveDatatype;
    }
    else if (strcmp(str, "constructedDatatype") == 0)
    {
        return constructedDatatype;
    }
    else if (strcmp(str, "remaining_list") == 0)
    {
        return remaining_list;
    }
    else if (strcmp(str, "stmts") == 0)
    {
        return stmts;
    }
    else if (strcmp(str, "typeDefinitions") == 0)
    {
        return typeDefinitions;
    }
    else if (strcmp(str, "typeDefinition") == 0)
    {
        return typeDefinition;
    }
    else if (strcmp(str, "fieldDefinitions") == 0)
    {
        return fieldDefinitions;
    }
    else if (strcmp(str, "fieldDefinition") == 0)
    {
        return fieldDefinition;
    }
    else if (strcmp(str, "moreFields") == 0)
    {
        return moreFields;
    }
    else if (strcmp(str, "declarations") == 0)
    {
        return declarations;
    }
    else if (strcmp(str, "declaration") == 0)
    {
        return declaration;
    }
    else if (strcmp(str, "global_or_not") == 0)
    {
        return global_or_not;
    }
    else if (strcmp(str, "otherStmts") == 0)
    {
        return otherStmts;
    }
    else if (strcmp(str, "stmt") == 0)
    {
        return stmt;
    }
    else if (strcmp(str, "assignmentStmt") == 0)
    {
        return assignmentStmt;
    }
    else if (strcmp(str, "singleOrRecId") == 0)
    {
        return singleOrRecId;
    }
    else if (strcmp(str, "funCallStmt") == 0)
    {
        return funCallStmt;
    }
    else if (strcmp(str, "outputParameters") == 0)
    {
        return outputParameters;
    }
    else if (strcmp(str, "inputParameters") == 0)
    {
        return inputParameters;
    }
    else if (strcmp(str, "iterativeStmt") == 0)
    {
        return iterativeStmt;
    }
    else if (strcmp(str, "conditionalStmt") == 0)
    {
        return conditionalStmt;
    }
    else if (strcmp(str, "ioStmt") == 0)
    {
        return ioStmt;
    }
    else if (strcmp(str, "arithmeticExpression") == 0)
    {
        return arithmeticExpression;
    }
    else if (strcmp(str, "operators") == 0)
    {
        return operators;
    }
    else if (strcmp(str, "booleanExpression") == 0)
    {
        return booleanExpression;
    }
    else if (strcmp(str, "var") == 0)
    {
        return var;
    }
    else if (strcmp(str, "logicalOp") == 0)
    {
        return logicalOp;
    }
    else if (strcmp(str, "relationalOp") == 0)
    {
        return relationalOp;
    }
    else if (strcmp(str, "returnStmt") == 0)
    {
        return returnStmt;
    }
    else if (strcmp(str, "optionalReturn") == 0)
    {
        return optionalReturn;
    }
    else if (strcmp(str, "idList") == 0)
    {
        return idList;
    }
    else if (strcmp(str, "more_ids") == 0)
    {
        return more_ids;
    }
    else if (strcmp(str, "definetypestmt") == 0)
    {
        return definetypestmt;
    }
    else if (strcmp(str, "A") == 0)
    {
        return A;
    }
    else
    {
        return -1;
    }
}
Grammar *generateGrammar(FILE *fp)
{
    Grammar *G = allocGrammar();
    char *line = (char *)malloc(200 * sizeof(char));
    char *lhs = (char *)malloc(100 * sizeof(char));
    char *rhs = (char *)malloc(100 * sizeof(char));
    char *symbol = (char *)malloc(50 * sizeof(char));
    int chars_read = 0;
    while (fgets(line, 200 * sizeof(char), fp))
    {
        if (sscanf(line, " <%99[^>]> ", lhs) == 1)
        {
            nonTerminal V = stringToNonTerminal(lhs);
            Rules *V_productions = G->rules[(int)V];
            char *rhsPtr = line + strlen(lhs) + 2;
            while (*rhsPtr == ' ')
                rhsPtr++;
            rhsPtr += 4;
            while (*rhsPtr == ' ')
                rhsPtr++;
            while (sscanf(rhsPtr, " %99[^|\n] ", rhs) == 1)
            {

                int ruleNo = V_productions->numVariableProductions + 1;
                rhsPtr += strlen(rhs) + 1;
                Rule *newRule = allocRule(ruleNo);
                char *symPtr = rhs;
                while (sscanf(symPtr, " %50[^ ]", symbol) == 1)
                {
                    symPtr += strlen(symbol);
                    while (*symPtr == ' ')
                        symPtr++;
                    if (symbol[0] == '<')
                    {
                        char substr[50];
                        for (int i = 0; i < strlen(symbol); i++)
                        {
                            if (symbol[i + 1] == '>')
                            {
                                substr[i] = '\0';
                                break;
                            }
                            substr[i] = symbol[i + 1];
                        }
                        nonTerminal temp = stringToNonTerminal(substr);
                        appendSymbolList(newRule->product, allocSymbol(temp, false));
                        printf("N:%d\n", temp);
                    }
                    else
                    {
                        TokenName temp = stringToTokenName(symbol);
                        appendSymbolList(newRule->product, allocSymbol(temp, true));
                        printf("T:%d\n", temp);
                    }
                }
                appendRuleGrammar(G, V, newRule);
            }
        }
    }
    return G;
}
void printGrammar(Grammar *G)
{
    Rules **R = G->rules;
    for (int i = 0; i < NO_OF_NONTERMINALS; i++)
    {
        Rule *cur_rule = G->rules[i]->rulePtr;
        while(cur_rule!=NULL){
            printf("NT:%d--->",i);
            SymbolList *list = cur_rule->product;
            SymbolNode *temp = list->head;
            while(temp!=NULL){
                if(temp->isTerm){
                    printf("%d",temp->type.terminal);
                }else{
                    printf("%d",temp->type.non_terminal);
                }
                temp = temp->next;
            }
            cur_rule = cur_rule->next;
        }
    }
}
int main()
{
    FILE *fp = fopen("modified_grammar.txt", "r");
    if (fp == NULL)
    {
        printf("failed to open file\n");
    }
    Grammar *G = generateGrammar(fp);
    // printGrammar(G);
}
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
    if (L->head == NULL)
    {
        L->head = node;
    }
    else
    {
        L->tail->next = node;
    }
    L->tail = node;
}

Rule *allocRule(int ruleNo)
{
    Rule *newRule = (Rule *)malloc(sizeof(Rule));
    newRule->next = NULL;
    newRule->product = allocSymbolList();
    newRule->ruleNo = ruleNo;
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
    G->rules[(int)V]->numVariableProductions++;
    Rule *temp = G->rules[(int)V]->rulePtr;
    while(temp->next!=NULL)temp = temp->next;
    temp->next = R;
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

void addSets(TokenList *set1, TokenList *set2, bool addEpsilon)
{
    TokenListNode *set2_head = set2->head;
    while (set2_head != NULL)
    {
        if (set2_head->name == EPSILON && !addEpsilon)
            continue;
        if (!isNodeInSet(set1, set2_head))
        {
            appendNodeSet(set1, set2_head);
        }
        set2_head = set2_head->next;
    }
    resetTailSet(set1);
}
ffSingleNode *findFFSymbolNode(FirstAndFollow *F, nonTerminal V)
{
    for (int i = 0; i < NO_OF_NONTERMINALS; i++)
    {
        if (F->table[i]->name == V)
        {
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
        int j = 0;
        for (j = 0; j < S->productionLength; j++)
        {

            if (temp->isTerm)
            {
                appendNodeSet(L, createTokenNode(temp->type.terminal));
                break;
            }
            else
            {
                ffSingleNode *node2 = findFFSymbolNode(F, temp->type.non_terminal);
                TokenList *set2 = node2->firstSet;
                computeFirst(G, F, temp->type.non_terminal, node2);
                addSets(L, set2, false);
                if (!isNodeInSet(set2, createTokenNode(EPSILON)))
                    break;
            }
        }
        if (j == S->productionLength)
        {
            appendNodeSet(L, createTokenNode(EPSILON));
        }
        temp = temp->next;
    }
    return;
}
void computeFollow(Grammar *G, FirstAndFollow *F, nonTerminal V);

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

// TokenList *returnFirst(FirstAndFollow *F, Rule *R)
// {

//     TokenList *firstSet = (TokenList *)malloc(sizeof(TokenList));
//     firstSet->setSize = 0;
//     Symbol *curr = R->symbols->symbols;

//     TokenListNode *prev = (TokenListNode *)malloc(sizeof(TokenListNode));
//     firstSet->head = prev;

//     while (true)
//     {

//         TokenListNode *temp = (TokenListNode *)malloc(sizeof(TokenListNode));

//         if (curr->isTerm)
//         {
//             prev->next = temp;
//             prev->name = curr->type.terminal;
//             firstSet->setSize++;
//             break;
//         }

//         else if (!curr->isTerm)
//         {
//             ffSingleNode *ff = F->table[curr->type.nonterminal];
//             prev->next = ff->firstSet->head;
//             firstSet->setSize += ff->firstSet->setSize;
//         }
//     }
// }

// function required to read grammar from text file

// void createParseTable(FirstAndFollow F, Grammar G, Table *T)
// {
// }
// parseDef mai kya red dikha raha. suggestions han ab done hone band ho gye uski vajah se
