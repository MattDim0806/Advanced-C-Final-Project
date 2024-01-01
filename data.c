#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

//----------------------------------------------------------------------------------

#include "data.h"

//----------------------------------------------------------------------------------

void Init_DataPath(tDataPath* root){
    strcpy(root->folder,"root");
    root->next=NULL;
    root->prev=NULL;
}

void Add_DataPath(tDataPath *curr_Path){
    char i[5];
    tDataPath *new_path=(tDataPath*)malloc(sizeof(tDataPath));
    curr_Path->next=new_path;
    new_path->prev=curr_Path;
    curr_Path=curr_Path->next;
}

void OPER_LoadDump(){
    FILE *fp;
    char LoadFile[15];

    printf("Load Flie Name:");
    scanf("%s",LoadFile);
    
    fp = fopen(LoadFile, "r+");
    if (fp == NULL) {
        printf("failed to open the file.\n");
    }else{
        printf("Load Success.\n");
    }
}