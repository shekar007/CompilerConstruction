#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "parser.h"
#include "parserDef.h"
#include "lexer.h"
#include "symbolTable.h"
#include "stack.h"
#include "stackDef.h"
#define LINE_SIZE 200 * sizeof(char)

const char *terminals[] = {"TK_ASSIGNOP", "TK_COMMENT", "TK_FIELDID", "TK_ID", "TK_NUM", "TK_RNUM", "TK_FUNID", "TK_RUID", "TK_WITH", "TK_PARAMETERS", "TK_END", "TK_WHILE", "TK_UNION", "TK_ENDUNION", "TK_DEFINETYPE", "TK_AS", "TK_TYPE", "TK_MAIN", "TK_GLOBAL", "TK_PARAMETER", "TK_LIST", "TK_SQL", "TK_SQR", "TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL", "TK_COMMA", "TK_SEM", "TK_COLON", "TK_DOT", "TK_ENDWHILE", "TK_OP", "TK_CL", "TK_IF", "TK_THEN", "TK_ENDIF", "TK_READ", "TK_WRITE", "TK_RETURN", "TK_PLUS", "TK_MINUS", "TK_MUL", "TK_DIV", "TK_CALL", "TK_RECORD", "TK_ENDRECORD", "TK_ELSE", "TK_AND", "TK_OR", "TK_NOT", "TK_LT", "TK_LE", "TK_EQ", "TK_GT", "TK_GE", "TK_NE", "EPSILON", "TK_ERROR", "DOLLAR", "SYN"};
const char *non_terminals[] = {"program", "mainFunction", "otherFunctions", "function", "input_par", "output_par", "parameter_list", "dataType", "primitiveDatatype", "constructedDatatype", "remaining_list", "stmts", "typeDefinitions", "actualOrRedefined", "typeDefinition", "fieldDefinitions", "fieldDefinition", "fieldType", "moreFields", "declarations", "declaration", "global_or_not", "otherStmts", "stmt", "assignmentStmt", "singleOrRecId", "option_single_constructed", "oneExpansion", "moreExpansions", "funCallStmt", "outputParameters", "inputParameters", "iterativeStmt", "conditionalStmt", "elsePart", "ioStmt", "arithmeticExpression", "expPrime", "term", "termPrime", "factor", "highPrecedenceOperators", "lowPrecedenceOperators", "booleanExpression", "var", "logicalOp", "relationalOp", "returnStmt", "optionalReturn", "idList", "more_ids", "definetypestmt", "A"};


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
        return program;
    else if (strcmp(str, "mainFunction") == 0)
        return mainFunction;
    else if (strcmp(str, "otherFunctions") == 0)
        return otherFunctions;
    else if (strcmp(str, "function") == 0)
        return function;
    else if (strcmp(str, "input_par") == 0)
        return input_par;
    else if (strcmp(str, "output_par") == 0)
        return output_par;
    else if (strcmp(str, "parameter_list") == 0)
        return parameter_list;
    else if (strcmp(str, "dataType") == 0)
        return dataType;
    else if (strcmp(str, "primitiveDatatype") == 0)
        return primitiveDatatype;
    else if (strcmp(str, "constructedDatatype") == 0)
        return constructedDatatype;
    else if (strcmp(str, "remaining_list") == 0)
        return remaining_list;
    else if (strcmp(str, "stmts") == 0)
        return stmts;
    else if (strcmp(str, "typeDefinitions") == 0)
        return typeDefinitions;
    else if (strcmp(str, "typeDefinition") == 0)
        return typeDefinition;
    else if (strcmp(str, "fieldDefinitions") == 0)
        return fieldDefinitions;
    else if (strcmp(str, "fieldDefinition") == 0)
        return fieldDefinition;
    else if (strcmp(str, "moreFields") == 0)
        return moreFields;
    else if (strcmp(str, "declarations") == 0)
        return declarations;
    else if (strcmp(str, "declaration") == 0)
        return declaration;
    else if (strcmp(str, "global_or_not") == 0)
        return global_or_not;
    else if (strcmp(str, "otherStmts") == 0)
        return otherStmts;
    else if (strcmp(str, "stmt") == 0)
        return stmt;
    else if (strcmp(str, "assignmentStmt") == 0)
        return assignmentStmt;
    else if (strcmp(str, "singleOrRecId") == 0)
        return singleOrRecId;
    else if (strcmp(str, "funCallStmt") == 0)
        return funCallStmt;
    else if (strcmp(str, "outputParameters") == 0)
        return outputParameters;
    else if (strcmp(str, "inputParameters") == 0)
        return inputParameters;
    else if (strcmp(str, "iterativeStmt") == 0)
        return iterativeStmt;
    else if (strcmp(str, "conditionalStmt") == 0)
        return conditionalStmt;
    else if (strcmp(str, "ioStmt") == 0)
        return ioStmt;
    else if (strcmp(str, "arithmeticExpression") == 0)
        return arithmeticExpression;
    else if (strcmp(str, "term") == 0)
        return term;
    else if (strcmp(str, "expPrime") == 0)
        return expPrime;
    else if (strcmp(str, "termPrime") == 0)
        return termPrime;
    else if (strcmp(str, "factor") == 0)
        return factor;
    else if (strcmp(str, "highPrecedenceOperators") == 0)
        return highPrecedenceOperators;
    else if (strcmp(str, "lowPrecedenceOperators") == 0)
        return lowPrecedenceOperators;
    else if (strcmp(str, "booleanExpression") == 0)
        return booleanExpression;
    else if (strcmp(str, "var") == 0)
        return var;
    else if (strcmp(str, "logicalOp") == 0)
        return logicalOp;
    else if (strcmp(str, "relationalOp") == 0)
        return relationalOp;
    else if (strcmp(str, "returnStmt") == 0)
        return returnStmt;
    else if (strcmp(str, "optionalReturn") == 0)
        return optionalReturn;
    else if (strcmp(str, "idList") == 0)
        return idList;
    else if (strcmp(str, "more_ids") == 0)
        return more_ids;
    else if (strcmp(str, "definetypestmt") == 0)
        return definetypestmt;
    else if (strcmp(str, "A") == 0)
        return A;
    else if (strcmp(str, "actualOrRedefined") == 0)
        return actualOrRedefined;
    else if (strcmp(str, "oneExpansion") == 0)
        return oneExpansion;
    else if (strcmp(str, "moreExpansions") == 0)
        return moreExpansions;
    else if (strcmp(str, "option_single_constructed") == 0)
        return option_single_constructed;
    else if (strcmp(str, "elsePart") == 0)
        return elsePart;
    else if (strcmp(str, "fieldType") == 0)
        return fieldType;
    else
    {
        return -1;
    }
}
Grammar *generateGrammar(FILE *fp)
{
    Grammar *G = allocGrammar();
    char *line = (char *)malloc(200 * sizeof(char)); // size of buffers might need to be increased
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
            rhsPtr += 4; // why
            while (*rhsPtr == ' ')
                rhsPtr++;
            while (sscanf(rhsPtr, " %99[^|\n]", rhs) == 1)
            {

                int ruleNo = V_productions->numVariableProductions + 1;
                rhsPtr += strlen(rhs);
                while (*rhsPtr == ' ')
                    rhsPtr++;
                rhsPtr++;
                while (*rhsPtr == ' ')
                    rhsPtr++;
                Rule *newRule = allocRule(V, ruleNo);
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
                        // printf("N:%d\n", temp);
                    }
                    else
                    {
                        TokenName temp = stringToTokenName(symbol);
                        appendSymbolList(newRule->product, allocSymbol(temp, true));
                        // printf("T:%d\n", temp);
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

    const char *terminals[] = {"TK_ASSIGNOP", "TK_COMMENT", "TK_FIELDID", "TK_ID", "TK_NUM", "TK_RNUM", "TK_FUNID", "TK_RUID", "TK_WITH", "TK_PARAMETERS", "TK_END", "TK_WHILE", "TK_UNION", "TK_ENDUNION", "TK_DEFINETYPE", "TK_AS", "TK_TYPE", "TK_MAIN", "TK_GLOBAL", "TK_PARAMETER", "TK_LIST", "TK_SQL", "TK_SQR", "TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL", "TK_COMMA", "TK_SEM", "TK_COLON", "TK_DOT", "TK_ENDWHILE", "TK_OP", "TK_CL", "TK_IF", "TK_THEN", "TK_ENDIF", "TK_READ", "TK_WRITE", "TK_RETURN", "TK_PLUS", "TK_MINUS", "TK_MUL", "TK_DIV", "TK_CALL", "TK_RECORD", "TK_ENDRECORD", "TK_ELSE", "TK_AND", "TK_OR", "TK_NOT", "TK_LT", "TK_LE", "TK_EQ", "TK_GT", "TK_GE", "TK_NE", "EPSILON", "TK_ERROR"};
    const char *non_terminals[] = {"program", "mainFunction", "otherFunctions", "function", "input_par", "output_par", "parameter_list", "dataType", "primitiveDatatype", "constructedDatatype", "remaining_list", "stmts", "typeDefinitions", "actualOrRedefined", "typeDefinition", "fieldDefinitions", "fieldDefinition", "fieldType", "moreFields", "declarations", "declaration", "global_or_not", "otherStmts", "stmt", "assignmentStmt", "singleOrRecId", "option_single_constructed", "oneExpansion", "moreExpansions", "funCallStmt", "outputParameters", "inputParameters", "iterativeStmt", "conditionalStmt", "elsePart", "ioStmt", "arithmeticExpression", "expPrime", "term", "termPrime", "factor", "highPrecedenceOperators", "lowPrecedenceOperators", "booleanExpression", "var", "logicalOp", "relationalOp", "returnStmt", "optionalReturn", "idList", "more_ids", "definetypestmt", "A"};
    Rules **R = G->rules;
    for (int i = 0; i < NO_OF_NONTERMINALS; i++)
    {
        Rule *cur_rule = G->rules[i]->rulePtr;
        while (cur_rule != NULL)
        {
            printf("NT:%d--->", i);
            SymbolList *list = cur_rule->product;
            SymbolNode *temp = list->head;
            while (temp != NULL)
            {
                if (temp->isTerm)
                {
                    printf("%d ", temp->type.terminal);
                }
                else
                {
                    printf("%d ", temp->type.non_terminal);
                }
                temp = temp->next;
            }
            printf("\n");
            cur_rule = cur_rule->next;
        }
    }
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
    return list;
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
    L->productionLength++;
}
Rule *allocRule(nonTerminal V, int ruleNo)
{
    Rule *newRule = (Rule *)malloc(sizeof(Rule));
    newRule->next = NULL;
    newRule->product = allocSymbolList();
    newRule->ruleNo = ruleNo;
    newRule->non_terminal = V;
    return newRule;
}
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
    // printf("Var:%d\n",V);
    Rule *temp = G->rules[(int)V]->rulePtr;
    if (temp == NULL)
    {
        G->rules[(int)V]->rulePtr = R;
    }
    else
    {
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = R;
    }
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
    setPtr->computed = false;
    setPtr->containsEps = false;
    // memset(setPtr->is_present, false, 59*sizeof(bool));
    return setPtr;
}
void allocSets(FirstAndFollow *F)
{
    F->table = (ffSingleNode **)malloc(NO_OF_NONTERMINALS * sizeof(ffSingleNode *));
    for (int i = 0; i < NO_OF_NONTERMINALS; i++)
    {
        F->table[i] = (ffSingleNode *)malloc(sizeof(ffSingleNode));
        F->table[i]->name = i;
        F->table[i]->firstSet = allocTokenList();
        F->table[i]->followSet = allocTokenList();
        F->table[i]->firstComputed = false;
        F->table[i]->followComputed = false;
        F->table[i]->inFollow = false;
    }
}
void appendNodeSet(TokenList *L, TokenListNode *node)
{

    TokenListNode *temp = (TokenListNode *)malloc(sizeof(TokenListNode));
    temp->name = node->name;
    temp->next = NULL;
    if (L->tail == NULL)
    {
        L->tail = temp;
        L->head = temp;
        // L->head->next = L->tail;
        L->setSize = 1;
        // L->is_present[node->name] = true;
    }
    else
    {
        L->tail->next = temp;
        L->tail = L->tail->next;
        L->setSize++;
    }
}
void resetTailSet(TokenList *L)
{
    TokenListNode *temp = L->head;
    while (temp != NULL && temp->next != NULL)
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
    while (temp != NULL)
    {
        if (temp->name == node->name)
        {
            return true;
        }
        temp = temp->next;
    }
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
ffSingleNode *returnFFSingleNode(FirstAndFollow *F, nonTerminal V)
{
    return F->table[(int)V];
}
void computeFirst(Grammar *G, FirstAndFollow *F, nonTerminal V)
{
    Rules *V_productions = G->rules[(int)V];
    Rule *V_production = V_productions->rulePtr; // pointer to first V production
    ffSingleNode *node = F->table[(int)V];
    TokenList *L = node->firstSet;
    for (int i = 0; i < V_productions->numVariableProductions; i++)
    {
        SymbolList *S = V_production->product;
        SymbolNode *temp = S->head; // first symbol in symbolList
        int j = 0;
        for (j = 0; j < S->productionLength; j++)
        {
            if (S->productionLength == 1 && temp->isTerm && temp->type.terminal == EPSILON)
            {
                L->containsEps = true;
                continue;
            }
            if (temp->isTerm)
            {
                appendNodeSet(L, createTokenNode(temp->type.terminal));
                break;
            }
            else
            {
                ffSingleNode *node2 = F->table[temp->type.non_terminal];
                TokenList *set2 = node2->firstSet;
                if (!node2->firstComputed)
                {
                    computeFirst(G, F, temp->type.non_terminal);
                }
                addSets(L, set2, false);
                if (!set2->containsEps)
                {
                    break;
                }
                else if (j == S->productionLength - 1)
                {
                    L->containsEps = true;
                }
            }
            temp = temp->next;
        }

        V_production = V_production->next;
    }
    node->firstComputed = true;
    return;
}
SymbolNode *returnSymbolFromList(SymbolList *S, nonTerminal V)
{
    SymbolNode *temp = S->head;
    while (temp != NULL)
    {
        if (temp->isTerm == false && temp->type.non_terminal == V)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
void computeFollow(Grammar *G, FirstAndFollow *F, nonTerminal V)
{
    F->table[(int)V]->inFollow = true;
    if (F->table[(int)V]->followComputed)
    {
        return;
    }
    ffSingleNode *V_singleNode = F->table[(int)V];
    TokenList *followSet = F->table[(int)V]->followSet;
    if (V_singleNode->followComputed)
        return;
    if (V_singleNode->name == program)
    {
        TokenListNode *temp = createTokenNode(DOLLAR);
        appendNodeSet(followSet, temp);
        //free(temp);
        F->table[(int)program]->followComputed = true;
        return;
    }
    // if(V==DOLLAR){
    //     addDOLLAR;
    // } // TO BE COMPLETED!

    for (int nt = 0; nt < NO_OF_NONTERMINALS; nt++)
    {
        Rules *nt_rules = G->rules[nt];
        Rule *cur_nt_rule = nt_rules->rulePtr;
        while (cur_nt_rule != NULL)
        {
            // printf("rule_no: %d\n", cur_nt_rule->ruleNo);
            computeFollowHelper(G, F, V, cur_nt_rule);
            cur_nt_rule = cur_nt_rule->next;
        }
    }
    F->table[(int)V]->followComputed = true;
    F->table[(int)V]->inFollow = false;
}
void computeFollowHelper(Grammar *G, FirstAndFollow *F, nonTerminal V, Rule *R)
{

    ffSingleNode *V_singleNode = F->table[(int)V];
    TokenList *followSet = F->table[(int)V]->followSet;
    SymbolList *sym_list = R->product;
    SymbolNode *V_sym_node = returnSymbolFromList(sym_list, V);
    if (V_sym_node == NULL)
        return;
    SymbolNode *temp_node = V_sym_node->next;
    if (temp_node == NULL)
    {
        // computeFollow(G, F, R->non_terminal);
        if (!F->table[R->non_terminal]->followComputed && !F->table[(int)R->non_terminal]->inFollow)
        {
            computeFollow(G, F, R->non_terminal);
        }
        TokenList *fs = F->table[R->non_terminal]->followSet;
        addSets(followSet, F->table[R->non_terminal]->followSet, false);
        return;
    }

    while (temp_node != NULL)
    {
        ffSingleNode *temp_node_ff = F->table[temp_node->type.non_terminal];
        TokenList *temp_node_first = temp_node_ff->firstSet;
        TokenList *temp_node_follow = temp_node_ff->followSet;
        if (temp_node->isTerm)
        {
            TokenListNode *temp = createTokenNode(temp_node->type.terminal);
            if (!isNodeInSet(followSet, temp))
            {
                appendNodeSet(followSet, temp);
            }
            else
            {
                free(temp);
            }
            return;
        }
        else
        {
            addSets(followSet, temp_node_first, false);
            if (!temp_node_first->containsEps)
            {
                return;
            }
            temp_node = temp_node->next;
        }
    }
    ffSingleNode *lhs = F->table[R->non_terminal];
    if (!lhs->followComputed)
    {
        computeFollow(G, F, lhs->name);
    }
    TokenList *lhs_follow = lhs->followSet;
    addSets(followSet, lhs_follow, false);
    return;
}

TokenList *returnFirstOfVariable(FirstAndFollow *F, nonTerminal V)
{
    return returnFFSingleNode(F, V)->firstSet;
}
TokenList *returnFirst(FirstAndFollow *F, Rule *R)
{
    SymbolNode *temp = R->product->head;
    TokenList *rhsFirstSet = allocTokenList();
    ffSingleNode **sets = F->table;

    bool epsFlag = true;
    while (temp != NULL)
    {
        if (temp->isTerm && temp->type.terminal == EPSILON)
        {
            rhsFirstSet->containsEps = true;
            temp = temp->next;
            continue;
        }
        if (temp->isTerm)
        {
            appendNodeSet(rhsFirstSet, createTokenNode(temp->type.terminal));
            epsFlag = false;
            break;
        }
        addSets(rhsFirstSet, F->table[(int)temp->type.non_terminal]->firstSet, true);
        ffSingleNode *tempNode = returnFFSingleNode(F, temp->type.non_terminal);
        TokenList *tempList = tempNode->firstSet;
        if (!tempList->containsEps)
        {
            epsFlag = false;
            break;
        }
        temp = temp->next;
    }

    if (epsFlag)
    {
        rhsFirstSet->containsEps = true;
    }
    return rhsFirstSet;
}
Table *allocParseTable()
{

    Table *T = (Table *)malloc(sizeof(Table));

    for (int i = 0; i < NO_OF_NONTERMINALS; i++)
    {
        for (int j = 0; j < NO_OF_TERMINALS; j++)
        {
            T->check[i][j] = false;
        }
    }
    return T;
}
void createParseTable(FirstAndFollow *F, Grammar *G, Table *T)
{
    Rules **allRules = G->rules;
    int noRules = G->numOfRules;

    Rule * synRule;
    synRule = allocRule(-1, -1);
    SymbolNode *synNode = allocSymbol(SYN, true);
    appendSymbolList(synRule->product, synNode);

    for (int i = 0; i < NO_OF_NONTERMINALS; i++)
    {

        Rule *rule = G->rules[i]->rulePtr;

        for (int j = 0; j < G->rules[i]->numVariableProductions; j++)
        {
            TokenList *first = returnFirst(F, rule);

            TokenListNode *head = first->head;
            for (int z = 0; z < first->setSize; z++)
            {

                if (T->check[i][(int)head->name])
                {
                    printf("Error in generation of parse table, duplicate entries in %d, %d \n", i, (int)head->name);
                }
                else
                {
                    T->table[i][(int)head->name] = rule;
                    T->check[i][(int)head->name] = true;
                }

                head = head->next;
            }

            if (first->containsEps)
            {
                TokenList *follow = F->table[i]->followSet;

                TokenListNode *followHead = follow->head;

                for (int k = 0; k < follow->setSize; k++)
                {

                    if (T->check[i][(int)followHead->name])
                    {
                        printf("Error in generation of parse table, duplicate entries in %d, %d \n", i, (int)followHead->name);
                    }
                    else
                    {
                        Rule *epsRule = allocRule(i, -1);
                        SymbolNode *epsNode = allocSymbol(EPSILON, true);
                        appendSymbolList(epsRule->product, epsNode);

                        // inke liye functions bane hai
                        // oh, kaunsa?
                        // allocR

                        T->table[i][(int)followHead->name] = epsRule;
                        T->check[i][(int)followHead->name] = true;
                    }

                    followHead = followHead->next;
                }
            }

            rule = rule->next;
        }

        //adding syn
        TokenList * followSet = F->table[i]->followSet;
        TokenListNode * head = followSet->head;

        for(int j = 0; j<followSet->setSize; j++){
            if(!T->check[i][head->name]){
                T->table[i][head->name] = synRule;
                T->check[i][head->name] = true;
            }
        }
    }
}
void printParseTable(Table *T)
{
    const char *terminals[] = {"TK_ASSIGNOP", "TK_COMMENT", "TK_FIELDID", "TK_ID", "TK_NUM", "TK_RNUM", "TK_FUNID", "TK_RUID", "TK_WITH", "TK_PARAMETERS", "TK_END", "TK_WHILE", "TK_UNION", "TK_ENDUNION", "TK_DEFINETYPE", "TK_AS", "TK_TYPE", "TK_MAIN", "TK_GLOBAL", "TK_PARAMETER", "TK_LIST", "TK_SQL", "TK_SQR", "TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL", "TK_COMMA", "TK_SEM", "TK_COLON", "TK_DOT", "TK_ENDWHILE", "TK_OP", "TK_CL", "TK_IF", "TK_THEN", "TK_ENDIF", "TK_READ", "TK_WRITE", "TK_RETURN", "TK_PLUS", "TK_MINUS", "TK_MUL", "TK_DIV", "TK_CALL", "TK_RECORD", "TK_ENDRECORD", "TK_ELSE", "TK_AND", "TK_OR", "TK_NOT", "TK_LT", "TK_LE", "TK_EQ", "TK_GT", "TK_GE", "TK_NE", "EPSILON", "TK_ERROR", "DOLLAR", "SYN"};
    const char *non_terminals[] = {"program", "mainFunction", "otherFunctions", "function", "input_par", "output_par", "parameter_list", "dataType", "primitiveDatatype", "constructedDatatype", "remaining_list", "stmts", "typeDefinitions", "actualOrRedefined", "typeDefinition", "fieldDefinitions", "fieldDefinition", "fieldType", "moreFields", "declarations", "declaration", "global_or_not", "otherStmts", "stmt", "assignmentStmt", "singleOrRecId", "option_single_constructed", "oneExpansion", "moreExpansions", "funCallStmt", "outputParameters", "inputParameters", "iterativeStmt", "conditionalStmt", "elsePart", "ioStmt", "arithmeticExpression", "expPrime", "term", "termPrime", "factor", "highPrecedenceOperators", "lowPrecedenceOperators", "booleanExpression", "var", "logicalOp", "relationalOp", "returnStmt", "optionalReturn", "idList", "more_ids", "definetypestmt", "A"};
    for (int i = 0; i < NO_OF_NONTERMINALS; i++)
    {
        for (int j = 0; j < NO_OF_TERMINALS; j++)
        {
            // printf("%s %s", non_terminals[i], terminals[j]);
            Rule *r = T->table[i][j];
            if (r)
            {
                printf("%s %s:   ", non_terminals[i], terminals[j]);
                if(r->product->head->isTerm && r->product->head->type.terminal==SYN){
                    printf("%s %s --> SYN\n", non_terminals[i], terminals[j]);
                    continue;
                }
                printf("%s --> ", non_terminals[r->non_terminal]);
                SymbolNode *n;
                n = r->product->head;
                while (n != NULL)
                {
                    if (n->isTerm)
                    {

                        printf("%s ", terminals[n->type.terminal]);
                    }
                    else
                    {
                        printf("%s ", non_terminals[n->type.non_terminal]);
                    }
                    // printf(" ");
                    n = n->next;
                }
                printf("\n");
            }
            else
            {
                // printf("NULL");
            }
        }
    }
}

Token *getNextTokenHelper(FILE *fileptr)
{
    Token *t;
    while (true)
    {
        t = getNextToken(fileptr);

        if(t==NULL){
            return NULL;
        }
        if (t->name == TK_ERROR)
        {
            continue;
        }
        else if (t->name == TK_COMMENT)
        {
            continue;
        }
        else
        {
            return t;
        }
    }
}

TreeNodeList * allocTreeNodeList(){
    TreeNodeList * temp = (TreeNodeList *) malloc(sizeof(TreeNodeList));
    temp->head = NULL;
    temp->size = 0;
    return temp;
}

void appendToChildren(TreeNode * parent, TreeNode * child){
    child->next = parent->childList->head;
    parent->childList->head = child;
}

//push symbols to stack and append to children of parent
void pushSymbols(Stack * S, SymbolList * set, TreeNode * parent){
    Stack * sTemp = (Stack *) malloc(sizeof(Stack));

    SymbolNode * temp = set->head;
    TreeNode * tn;
    for(int i = 0; i<set->productionLength; i++){
        tn = (TreeNode*) malloc(sizeof(TreeNode));
        tn->isTerm = temp->isTerm;
        tn->value = temp->type;
        push(sTemp, tn);
        temp = temp->next;
    }

    while(!isEmpty(sTemp)){
        TreeNode * tn = top(sTemp);
        tn->parentNode = parent;
        appendToChildren(parent, tn);
        pop(sTemp);
        push(S, tn);
    }

    free(sTemp);
}

TreeNode * createParseTree(FILE* fileptr, Grammar * G, Table * T){

    TreeNode * root = (TreeNode *) malloc(sizeof(TreeNode));

    root->next = NULL;
    root->value.non_terminal = program;
    root->isTerm = false;

    root->childList = allocTreeNodeList();

    Stack * S = (Stack *) malloc(sizeof(Stack));

    TreeNode * curr;
    push(S, root);

    Token* currToken = getNextTokenHelper(fileptr);
    while(!isEmpty(S)){
        if(!top(S)->isTerm){
            curr = top(S);
            pop(S);

            if(currToken==NULL){
                printf("EOF reached with non empty stack\n");
                return NULL;
            }
            curr->childList = allocTreeNodeList();
            Rule * nextRule = T->table[curr->value.non_terminal][currToken->name];

            while(nextRule==NULL){
                printf("Error: skipping token %s", currToken->lexeme);
                printToken(currToken);
                currToken = getNextTokenHelper(fileptr);
                if(currToken==NULL){
                    printf("EOF reached with non empty stack\n");
                    return NULL;
                }
                nextRule = T->table[curr->value.non_terminal][currToken->name];
            }

            if(nextRule->product->head->isTerm && nextRule->product->head->type.terminal==SYN){
                printf("Error: popping %d from stack, current token %s\n", curr->value.non_terminal, currToken->lexeme);
                printToken(currToken);
                continue;
            }

            curr->lineno = currToken->lineno;

            pushSymbols(S, nextRule->product, curr);
        }

        while(!isEmpty(S) && top(S)->isTerm){
            
            if(currToken==NULL){
                printf("EOF reached with non empty stack\n");
                return NULL;
            }

            if(top(S)->value.terminal==currToken->name){
                //printToken(currToken);

                top(S)->lexeme = currToken->lexeme;
                top(S)->lineno = currToken->lineno;
                if(currToken->isint){
                    top(S)->num.num = currToken->value->num;
                }
                else if(currToken->name == TK_RNUM){
                    top(S)->num.r_num = currToken->value->r_num;
                }
                currToken = getNextTokenHelper(fileptr);
                pop(S);
            }
            else if(top(S)->value.terminal == EPSILON){
                top(S)->lineno = currToken->lineno;
                pop(S);
            }
            else{
                printf("Error, popping %d froms stack, current lexeme is %s\n", top(S)->value.terminal, currToken->lexeme);
                printToken(currToken);
                pop(S);
            }
        }
    }

    if(currToken!=NULL){
        printf("End of stack but not eof\n");
    }
    else{
        printf("Parse tree generated\n");
    }

    return root;
}

void printParseTree(TreeNode * PT, FILE * fileptr, int * i){

    if(PT==NULL){
        return;
    }

    if(!PT->isTerm){
        printParseTree(PT->childList->head, fileptr, i);
    }

    fprintf(fileptr, "\n---------------------------------------------------------------------------------------\n");

    if(!PT->isTerm){
        fprintf(fileptr, "---  ");
    }
    else{
        fprintf(fileptr, "%s  ", PT->lexeme);
    }

    fprintf(fileptr, "Node no. %d  ", *i);
    fprintf(fileptr, "%d  ", PT->lineno);
    
    if(!PT->isTerm){
        fprintf(fileptr, "%s  ", non_terminals[PT->value.non_terminal]);
    }
    else{
        fprintf(fileptr, "%s  ", terminals[PT->value.terminal]);
    }

    if(PT->isTerm){
        if(PT->value.terminal == TK_NUM){
            fprintf(fileptr, "%d  ", PT->num.num);
        }
        else if(PT->value.non_terminal == TK_RNUM){
            fprintf(fileptr, "%f ", PT->num.r_num);
        }
    }

    if(!PT->isTerm && PT->value.non_terminal == program){
        fprintf(fileptr, "ROOT  ");
    }
    else{
        fprintf(fileptr, "%s  ", non_terminals[PT->parentNode->value.non_terminal]);
    }

    if(!PT->isTerm){
        fprintf(fileptr, "no  ");
        fprintf(fileptr, "%s ", non_terminals[PT->value.non_terminal]);
    }
    else{
        fprintf(fileptr, "yes  ");
    }
    fprintf(fileptr, "\n");
    (*i)++;

    if(!PT->isTerm){
        TreeNode * temp = PT->childList->head->next;

        while(temp!=NULL){
            printParseTree(temp, fileptr, i);
            temp = temp->next;
        }
    }
}


// int main()
// {

//     FILE *fp = fopen("modified_grammar.txt", "r");
//     if (fp == NULL)
//     {
//         printf("failed to open file\n");
//     }
//     Grammar *G = generateGrammar(fp);
//     // printGrammar(G);

//     printf("grammar generated\n");

//     FirstAndFollow *F = (FirstAndFollow *)malloc(sizeof(FirstAndFollow));
//     allocSets(F);

//     printf("start compute first\n");
//     for (int i = 0; i < NO_OF_NONTERMINALS; i++)
//     {
//         computeFirst(G, F, (nonTerminal)i);
//     }
//     printf("end of compute first\n");
//     for (int i = 0; i < NO_OF_NONTERMINALS; i++)
//     {
//         nonTerminal V = i;

//         // TokenList *followSet = F->table[i]->followSet;
//         // printf("start compute Follow\n");
//         // TokenListNode *head = followSet->head;

//         computeFollow(G, F, V);
//         continue;

//         TokenList *followSet = F->table[i]->followSet;
//         TokenListNode *head = followSet->head;
//         printf("Follow(%s) %d: ", non_terminals[(int)V], (int)V);
//         for (int i = 0; i < followSet->setSize; i++)
//         {
//             printf("%s, ", terminals[head->name]);
//             head = head->next;
//         }
//         printf("\n");
//     }
//     Table *T = allocParseTable();
//     createParseTable(F, G, T);
//     //printParseTable(T);

//     //---------------------
//     initializations();
//     FILE *fileptr = fopen("t2.txt", "r");
//     if (fileptr == NULL)
//     {
//         printf("Error in opening \n");
//         return 1;
//     }

//     TreeNode * root = createParseTree(fileptr, G, T);

//     FILE *file = fopen("example.txt", "w");
//     if (file == NULL) {
//         perror("Failed to open file");
//         return 1;
//     }

//     int i = 0;
//     printParseTree(root, file, &i);

//     fclose(fileptr);

//     return 0;
//     // Allocate memory for buffers
// }
