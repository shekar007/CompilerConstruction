#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "symbolTableDef.h"

int hashFunction(char* value, int no_entries){
    int hash = 0;

    while(*value != '\0'){
        char c = *value++;
        hash = hash*15 + c - '0';
    }

    return hash%no_entries;
}

//last node in each list is always empty(check by next is NULL)
symTable * createEmptyTable(int no_lists){

    symTable * lookupTable = (symTable*) malloc(sizeof(symTable));

    lookupTable->no_lists = no_lists;

    lookupTable->headList = (symNode**) malloc(sizeof(symNode*)*no_lists);
    for(int i = 0; i<no_lists; i++){
        lookupTable->headList[i] = (symNode*) malloc(sizeof(symNode));
        lookupTable->headList[i]->next = NULL;
    }

    return lookupTable;

}

void addSymbol(symTable * lookupTable, char * tokenName, tokenType type, char * lexeme, int rowNumber){

    int list_no = hashFunction(lexeme, lookupTable->no_lists);

    symNode * temp = (symNode*) malloc(sizeof(symNode));
    
    temp->lexeme = lexeme;
    temp->rowNumber = rowNumber;
    temp->tokenName = tokenName;
    temp->type = type;
    
    temp->next = lookupTable->headList[list_no];
    lookupTable->headList[list_no] = temp;

}

nodeInfo * getInfo(symTable * lookupTable, char * lexeme){

    int list_no = hashFunction(lexeme, lookupTable->no_lists);

    symNode * temp = lookupTable->headList[list_no];

    nodeInfo * info = (nodeInfo*) malloc(sizeof(nodeInfo));
    info->is_present = false;

    while(temp->next!=NULL && !(info->is_present)){
        if(strcmp(lexeme, temp->lexeme)==0){
            info->is_present = true;
            info->node = temp;
        }

        temp = temp->next;
    }

    return info;
}