#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "lexer.h"
#include "lexerDef.h"
#include "parser.h"
#include "parserDef.h"

#define LINE_SIZE 200 * sizeof(char)
#define LINE_SIZE 200 * sizeof(char)

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    stack->top = NULL;
    return stack;
}
int isEmpty(Stack *stack)
{
    return (stack->top == NULL);
}
void push(Stack *stack, TreeNode *element)
{
    stackNode *newNode = (stackNode *)malloc(sizeof(stackNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->stackEle = element;
    newNode->next = stack->top;
    stack->top = newNode;
}
TreeNode *pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack underflow\n");
        exit(1);
    }
    stackNode *temp = stack->top;
    TreeNode *data = temp->stackEle;
    stack->top = temp->next;
    free(temp);
    return data;
}
TreeNode *top(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty\n");
        exit(1);
    }
    return stack->top->stackEle;
}

TreeNode *createParseTree(Token **tokenArray, Grammar *grammar, Table *T, int tokenArrayLength)
{
    // pass length of tokenarray and variable = tokenArrayLength
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->isTerminal = 0;
    root->element = NULL;
    Stack *stack = createStack();
    push(stack, program);
    root->element = program;
    int tokenptr = 0;
    int stringptr = 0;

    while (!isEmpty(stack))
    {
        if (tokenptr >= tokenArrayLength)
        {
            return NULL;
        }
        // first step me kya hoga
        TreeNode *n = pop(stack);

        childElement *headptr = n->headChild;
        /*
        change in parse tree when popping
        */
        Rule *r = T->table[n->element->non_terminal][tokenArray[tokenptr]->name];
        SymbolList *ruleList = r->product;
        SymbolNode *ptr = ruleList->tail;
        while (ptr != NULL)
        {
            TreeNode *ele;
            allocTreeNode(ele);
            // memory for ele
            if (ptr->isTerm)
            {
                ele->isTerminal = 1;
            }
            else
            {
                ele->isTerminal = 0;
            }
            ele->noChild = 0;
            ele->headChild = NULL;
            ele->element = ptr;
            push(stack, ele);
            n->noChild++;

            if (headptr == NULL)
            {
                headptr = ele;
                headptr = headptr->next;
            }
            else
            {
                headptr->next = ele;
                headptr = headptr->next;
            }
            ptr = ptr->prev;
            if (root->element == NULL)
            {
                root->headChild = n;
                root->noChild = 1;
            }
        }

        while (top(stack) == tokenArray[tokenptr] || top(stack) == EPSILON)
        {
            pop(stack);
            tokenptr++;
        }

        // if it is non-terminal
        // int noRules = grammar->rules[n->element->non_terminal]->numVariableProductions;
    }
    if (tokenptr == tokenArrayLength)
    {
        return root->headChild;
        // successfully parsed
    }
    else
    {
        return NULL;
    }
    // stack has been pushed and tree has been initialised
}
void allocTreeNode(TreeNode *root)
{
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->element = NULL;
    root->noChild = 0;
    root->isTerminal = 0;
    root->headChild = NULL;
    return root;
}
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
    else if (strcmp(str, "term") == 0)
    {
        return term;
    }
    else if (strcmp(str, "expPrime") == 0)
    {
        return expPrime;
    }
    else if (strcmp(str, "termPrime") == 0)
    {
        return termPrime;
    }
    else if (strcmp(str, "factor") == 0)
    {
        return factor;
    }
    else if (strcmp(str, "highPrecedenceOperators") == 0)
    {
        return highPrecedenceOperators;
    }
    else if (strcmp(str, "lowPrecedenceOperators") == 0)
    {
        return lowPrecedenceOperators;
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
    const char *non_terminals[] = {"program", "mainFunction", "otherFunctions", "function", "input_par", "output_par", "parameter_list", "dataType", "primitiveDatatype", "constructedDatatype", "remaining_list", "stmts", "typeDefinitions", "typeDefinition", "fieldDefinitions", "fieldDefinition", "moreFields", "declarations", "declaration", "global_or_not", "otherStmts", "stmt", "assignmentStmt", "singleOrRecId", "funCallStmt", "outputParameters", "inputParameters", "iterativeStmt", "conditionalStmt", "ioStmt", "arithmeticExpression", "operator", "booleanExpression", "var", "logicalOp", "relationalOp", "returnStmt", "optionalReturn", "idList", "more_ids", "definetypestmt", "A"};

    Rules **R = G->rules;
    for (int i = 0; i < NO_OF_NONTERMINALS; i++)
    {
        Rule *cur_rule = G->rules[i]->rulePtr;
        while (cur_rule != NULL)
        {
            printf("NT:%s--->", non_terminals[i]);
            SymbolList *list = cur_rule->product;
            SymbolNode *temp = list->head;
            while (temp != NULL)
            {
                if (temp->isTerm)
                {
                    printf("%s ", terminals[temp->type.terminal]);
                }
                else
                {
                    printf("%s ", non_terminals[temp->type.non_terminal]);
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
    }
}

// doesn't work like sets, has duplicate values
void appendNodeSet(TokenList *L, TokenListNode *node)
{
    if (L->tail == NULL)
    {
        L->tail = node;
        L->head = node;
        // L->head->next = L->tail;
        L->setSize = 1;
        // L->is_present[node->name] = true;
    }
    else
    {
        L->tail->next = node;
        L->tail = L->tail->next;
        L->setSize += 1;
    }
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
        {
            set2_head = set2_head->next;
            continue;
        }
        if (!isNodeInSet(set1, set2_head))
        {
            appendNodeSet(set1, set2_head);
        }
        set2_head = set2_head->next;
    }
    resetTailSet(set1);
}

// O(n) searching? should be O(1). convert enum nonTerminal to int directly and use as index shi aise hi use krle wtf
ffSingleNode *returnFFSingleNode(FirstAndFollow *F, nonTerminal V)
{
    return F->table[(int)V];
}
// hash table ki tarah karna hai kya?
// lamba padhega but bahut
void computeFirst(Grammar *G, FirstAndFollow *F, nonTerminal V, ffSingleNode *node)
{
    if (node->firstSet->computed)
    {
        return;
    }
    Rules *V_productions = G->rules[(int)V];
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
                ffSingleNode *node2 = returnFFSingleNode(F, temp->type.non_terminal);
                TokenList *set2 = node2->firstSet;
                computeFirst(G, F, temp->type.non_terminal, node2);
                addSets(L, set2, false);
                if (!isNodeInSet(set2, createTokenNode(EPSILON)))
                    break;
            }

            temp = temp->next;
        }
        if (j == S->productionLength)
        {
            appendNodeSet(L, createTokenNode(EPSILON));
        }
        V_production = V_production->next;
    }
    node->firstSet->computed = true;
    return;
}

SymbolNode *returnSymbolFromList(SymbolList *S, nonTerminal V)
{
    SymbolNode *temp = S->head;
    while (temp != NULL)
    {
        if (temp->type.non_terminal == V)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

//---------------------------------------------------------------------

void computeFollow(Grammar *G, FirstAndFollow *F, nonTerminal V)
{
    TokenList *followSet = F->table[(int)V]->followSet;
    for (int i = 0; i < NO_OF_NONTERMINALS; i++)
    {

        Rules *V_productions = G->rules[i];
        Rule *cur_rule = V_productions->rulePtr;
        while (cur_rule != NULL)
        {
            SymbolList *rhs = cur_rule->product;
            cur_rule = cur_rule->next;
            SymbolNode *V_rhs = returnSymbolFromList(rhs, V);
            if (V_rhs == NULL)
            {
                continue;
            }
            SymbolNode *V_temp = V_rhs->next;
            ffSingleNode *V_tempSingleNode = F->table[(int)V_temp->type.non_terminal];
            TokenList *V_tempFollowSet = V_tempSingleNode->followSet;
            TokenList *V_tempFirstSet = V_tempSingleNode->firstSet;
            if (V_temp == NULL)
            {
                if (!V_tempSingleNode->followComputed)
                {
                    computeFollow(G, F, V_temp->type.non_terminal);
                }
                addSets(followSet, V_tempFollowSet, false);
            }
            while (V_temp != NULL)
            {
                if (V_temp->isTerm)
                {
                    if (isNodeInSet(followSet, createTokenNode(V_temp->type.terminal)))
                        ;
                    break;
                }
                else
                {
                    addSets(followSet, V_tempFirstSet, false);
                }
                V_temp =
            }
        }
    }
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

TokenList *returnFirstOfVariable(FirstAndFollow *F, nonTerminal V)
{
    return returnFFSingleNode(F, V)->firstSet;
}
TokenList *returnFirst(FirstAndFollow *F, Rule *R)
{
    SymbolNode *temp = R->product->head;
    TokenList *rhsFirstSet = allocTokenList();
    ffSingleNode **sets = F->table;
    while (temp != NULL)
    {
        if (temp->isTerm)
        {
            appendNodeSet(rhsFirstSet, createTokenNode(temp->type.terminal));
            break;
        }
        addSets(rhsFirstSet, sets[(int)temp->type.non_terminal]->firstSet, true);
        ffSingleNode *tempNode = returnFFSingleNode(F, temp->type.non_terminal);
        TokenList *tempList = tempNode->firstSet;
        if (!isNodeInSet(tempList, createTokenNode(EPSILON)))
        {
            break;
        }
        temp = temp->next;
    }
    return rhsFirstSet;
}
// bc liveshare terminal c used to access chandus entire lap
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

    for (int i = 0; i < NO_OF_NONTERMINALS; i++)
    {

        Rule *rule = G->rules[i]->rulePtr;

        for (int j = 0; j < G->rules[i]->numVariableProductions; j++)
        {
            TokenList *first = returnFirst(F, rule);

            TokenListNode *head = first->head;
            for (int z = 0; z < first->setSize; z++)
            {
                if (head->name == EPSILON)
                {
                    TokenList *follow = F->table[i]->followSet;

                    TokenListNode *followHead = follow->head;

                    for (int k = 0; k < follow->setSize; k++)
                    {
                        if (T->check[i][(int)head->name])
                        {
                            printf("Eroor in generation of parse table, duplicate entries in %d, %d", i, z);
                        }
                        else
                        {
                            // what is epsRule ?
                            // parse table mei a rule A->epsilon may be added even if it is actually not there
                            // to uske liye sirf follow sets ke under nhi hota tha kya if it is actually there ?
                            // frm what i read, i guess the actual eps productions(if actually present) are placed under the corresponding terminals present in the follow set of the nonTerminal
                            // iss step ke liye kara hai maine ye, not sure if maine sahi kara ahi
                            // If First(α) contains ε (epsilon) as terminal, then find the Follow(A) and for each terminal in Follow(A), make entry A –>  ε in the table.
                            // Ye A->epsilon hai epsRule. The thing is, ye condition true hone ke liye A->epsilon might or might not exits in the language ha shi, A->BC
                            // B->eps
                            // C->eps
                            Rule *epsRule = allocRule(j, -1);
                            SymbolNode *epsNode = allocSymbol(EPSILON, true);
                            appendSymbolList(epsRule->product, epsNode);

                            // inke liye functions bane hai
                            // oh, kaunsa?
                            // allocR

                            T->table[i][z] = epsRule;
                            T->check[i][z] = true;
                        }

                        followHead = followHead->next;
                    }
                }
                else
                {
                    if (T->check[i][(int)head->name])
                    {
                        printf("Error in generation of parse table, duplicate entries in %d, %d", i, z);
                    }
                    else
                    {
                        T->table[i][z] = rule;
                        T->check[i][z] = true;
                    }
                }
                head = head->next;
            }

            rule = rule->next;
        }
    }
}

int main()
{

    const char *terminals[] = {"TK_ASSIGNOP", "TK_COMMENT", "TK_FIELDID", "TK_ID", "TK_NUM", "TK_RNUM", "TK_FUNID", "TK_RUID", "TK_WITH", "TK_PARAMETERS", "TK_END", "TK_WHILE", "TK_UNION", "TK_ENDUNION", "TK_DEFINETYPE", "TK_AS", "TK_TYPE", "TK_MAIN", "TK_GLOBAL", "TK_PARAMETER", "TK_LIST", "TK_SQL", "TK_SQR", "TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL", "TK_COMMA", "TK_SEM", "TK_COLON", "TK_DOT", "TK_ENDWHILE", "TK_OP", "TK_CL", "TK_IF", "TK_THEN", "TK_ENDIF", "TK_READ", "TK_WRITE", "TK_RETURN", "TK_PLUS", "TK_MINUS", "TK_MUL", "TK_DIV", "TK_CALL", "TK_RECORD", "TK_ENDRECORD", "TK_ELSE", "TK_AND", "TK_OR", "TK_NOT", "TK_LT", "TK_LE", "TK_EQ", "TK_GT", "TK_GE", "TK_NE", "EPSILON", "TK_ERROR"};
    const char *non_terminals[] = {"program", "mainFunction", "otherFunctions", "function", "input_par", "output_par", "parameter_list", "dataType", "primitiveDatatype", "constructedDatatype", "remaining_list", "stmts", "typeDefinitions", "typeDefinition", "fieldDefinitions", "fieldDefinition", "moreFields", "declarations", "declaration", "global_or_not", "otherStmts", "stmt", "assignmentStmt", "singleOrRecId", "funCallStmt", "outputParameters", "inputParameters", "iterativeStmt", "conditionalStmt", "ioStmt", "arithmeticExpression", "term", "expPrime", "termPrime", "factor", "highPrecedenceOperators", "lowPrecedenceOperators", "booleanExpression", "var", "logicalOp", "relationalOp", "returnStmt", "optionalReturn", "idList", "more_ids", "definetypestmt", "A"};

    FILE *fp = fopen("modified_grammar.txt", "r");
    if (fp == NULL)
    {
        printf("failed to open file\n");
    }
    Grammar *G = generateGrammar(fp);
    // printGrammar(G);

    FirstAndFollow *F = (FirstAndFollow *)malloc(sizeof(FirstAndFollow));
    // F->table[(int)arithmeticExpression];
    // return 0;

    allocSets(F);

    for (int i = 0; i < NO_OF_NONTERMINALS; i++)
    {

        nonTerminal V = i;

        computeFirst(G, F, V, F->table[i]);

        TokenList *firstSet = F->table[i]->firstSet;
        TokenListNode *head = firstSet->head;

        printf("First(%s) %d: ", non_terminals[(int)V], (int)V);
        for (int i = 0; i < firstSet->setSize; i++)
        {
            printf("%s, ", terminals[head->name]);
            head = head->next;
        }
        printf("\n");
    }
}
