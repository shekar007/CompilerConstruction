#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "stackDef.h"
#include "parserDef.h"

void push(Stack * S, TreeNode * tn){
    StackNode * sn = (StackNode *) malloc(sizeof(StackNode));
    sn->curr = tn;
    sn->next = S->top;
    S->top = sn;
    S->size++;
}

bool isEmpty(Stack *S){
    if(S->size==0){
        return true;
    }
    else{
        return false;
    }
}

TreeNode * top(Stack * S){
    if(!isEmpty(S)){
        return S->top->curr;
    }
    else{
        printf("Stack is empty\n");
        return NULL;
    }
}

void pop(Stack *S){
    StackNode * sn = S->top;
    S->top = S->top->next;
    S->size--;
    free(sn);
}