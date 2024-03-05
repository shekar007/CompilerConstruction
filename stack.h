#ifndef STACK_H
#define STACK_H
#include "stackDef.h"
#include "parserDef.h"

Stack * allocStack();
void push(Stack * S, TreeNode * TN);
bool isEmpty(Stack* S);
TreeNode * top(Stack * S);
void pop(Stack * S);
#endif