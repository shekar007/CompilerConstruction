#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "lexerDef.h"

//@aaradhya create struct for grammar and write computeFirstAndFollowSets function
//@aadit struct for parse table and write createParseTable function

typedef union
{
    TokenName terminal;
    nonTerminal nonterminal;
} symbolType;

typedef struct symbolNode
{
    symbolType type;
    struct symbolNode *next;
} SymbolNode;

typedef struct symbolList
{

    SymbolNode *head;
    int length;
} SymbolList;

typedef struct rule
{
    nonTerminal nonterminal;
    SymbolList *symbols;
    Rule *next;
    int ruleNo;
} Rule;
typedef struct rules
{
    Rule *head;
    int length;
} Rules;
typedef struct grammar
{
    int noOfRules;
    Rules **rules;
} Grammar;
typedef enum
{
    program,
    mainFunction,
    otherFunctions,
    function,
    input_par,
    output_par,
    parameter_list,
    data_type,
    primitiveDatatype,
    constructedDatatype,
    remaining_list,
    stmts,
    typeDefinitions,
    typeDefinition,
    fieldDefinitions,
    fieldDefinition,
    moreFields,
    declarations,
    declaration,
    global_or_not,
    otherStmts,
    stmt,
    assignmentStmt,
    singleOrRecId,
    funCallStmt,
    outputParameters,
    inputParameters,
    iterativeStmt,
    conditionalStmt,
    ioStmt,
    arithmeticExpression,
    operators, // operator changed to operators
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

typedef struct ffSingleNode
{
    nonTerminal *name;     // name of non terminal this struct stores data of
    TokenName **firstSet;  // list of token names in first set
    TokenName **followSet; // list of token names in follow set
    ffSingleNode *next;    // storing address of next node in linked list
} ffSingleNode;

// firstAndFollow is implemented as a hash table with the key being the name of the non-terminal.
// Conflict (hashing to same value) is resolved using linked list.
typedef struct firstAndFollow
{
    int no_slots;
    ffSingleNode **sets;
} firstAndFollow;

typedef struct Table
{
};