#ifndef STACKDEF_H
#define STACKDEF_H

#include <stdlib.h>

#include "parserDef.h"

typedef struct StackNode StackNode;

struct StackNode{
    TreeNode * curr;
    StackNode * next;
};

typedef struct Stack{
    StackNode * top;
    int size;
} Stack;

#endif