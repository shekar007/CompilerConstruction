#ifndef PARSERDEF_H
#define PARSERDEF_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "lexerDef.h"
#include "definitions.h"
//@shekar git pe daal dena incase ur laptop goes down
//@aaradhya create struct for grammar and write computeFirstAndFollowSets function
//@aadit struct for parse table and write createParseTable function
// enum,union -> camelcase
// struct -> pascalca //bol
// Grammar->rules->rule->symbolList->symbolNode linked list is required cuz we need to add symbols
// union symbolType;
// struct symbolNode;
// struct symbolList;
// struct rule;
typedef enum
{
    program,
    mainFunction,
    otherFunctions,
    function,
    input_par,
    output_par,
    parameter_list,
    dataType,
    primitiveDatatype,
    constructedDatatype,
    remaining_list,
    stmts,
    typeDefinitions,
    actualOrRedefined,
    typeDefinition,
    fieldDefinitions,
    fieldDefinition,
    fieldType,
    moreFields,
    declarations,
    declaration,
    global_or_not,
    otherStmts,
    stmt,
    assignmentStmt,
    singleOrRecId,
    option_single_constructed,
    oneExpansion,
    moreExpansions,
    funCallStmt,
    outputParameters,
    inputParameters,
    iterativeStmt,
    conditionalStmt,
    elsePart,
    ioStmt,
    arithmeticExpression,
    expPrime,
    term,
    termPrime,
    factor,
    highPrecedenceOperators,
    lowPrecedenceOperators,
    booleanExpression,
    var,
    logicalOp,
    relationalOp,
    returnStmt,
    optionalReturn,
    idList,
    more_ids,
    definetypestmt,
    A
} nonTerminal;

typedef union
{
    TokenName terminal;
    nonTerminal non_terminal;
} symbolType;

typedef struct symbolNode
{
    symbolType type;
    struct symbolNode *next;
    struct symbolNode *prev; // modify prev
    bool isTerm;
} SymbolNode;

typedef struct symbolList
{
    SymbolNode *head;
    SymbolNode *tail;
    int productionLength;
} SymbolList;

typedef struct rule
{
    nonTerminal non_terminal; // functions to be modified @aarads21
    SymbolList *product;
    struct rule *next;
    struct rule *prev; // add previous to this
    int ruleNo;
} Rule;
typedef struct rules
{
    Rule *rulePtr;
    int numVariableProductions;
} Rules;
typedef struct grammar
{
    int numOfRules;
    Rules **rules;
} Grammar;

typedef struct tokenListNode
{
    TokenName name;
    struct tokenListNode *next;
} TokenListNode;
typedef struct tokenList
{
    int setSize;
    TokenListNode *head;
    TokenListNode *tail;
    bool containsEps; //added containsEps, no need to add EPSILON token
    bool computed;
    // bool is_present[59];
} TokenList;
typedef struct ffSingleNode
{
    nonTerminal name;          // name of non terminal this struct stores data of
    TokenList *firstSet;       // list of token names in first set
    TokenList *followSet;      // list of token names in follow set
    struct ffSingleNode *next; // storing address of next node in linked list
    bool firstComputed;
    bool followComputed;
    bool inFollow;
} ffSingleNode;

// firstAndFollow is implemented as a hash table with the key being the name of the non-terminal.
// Conflict (hashing to same value) is resolved using linked list.
// Changing name to firstAndFollowSets to match specifications
typedef struct firstAndFollow
{
    ffSingleNode **table;
} FirstAndFollow;

typedef struct table // parse table
{
    int numOfNonTerminals;
    int numTerminals;

    Rule *table[NO_OF_NONTERMINALS][NO_OF_TERMINALS + 1];
    bool check[NO_OF_NONTERMINALS][NO_OF_TERMINALS + 1];

} Table;

typedef struct TreeNode TreeNode;
typedef struct childElement childElement;

struct childElement
{
    TreeNode *element;
    childElement *next;
};

struct TreeNode
{
    symbolType element;
    childElement *headChild;
    int isTerminal;
    int noChild;

};


typedef struct stackNode
{
    TreeNode *stackEle;
    struct stackNode *next;
} stackNode;
typedef struct Stack
{
    stackNode *top;
} Stack;

#endif