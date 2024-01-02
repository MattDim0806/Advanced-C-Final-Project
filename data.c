#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

//----------------------------------------------------------------------------------

#include "data.h"

//----------------------------------------------------------------------------------

extern int SizeofRemaining;

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

void OPER_LoadDump(){     //Load ().dump
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

void OPER_put(tDataTree *head,char target[]){
    FILE *fp;
    char buffer[1000];
    int j=0;
    fp = fopen(target, "r+");
    if (fp == NULL) {
        printf("failed to open file '%s'\n",target);
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
        printf("'%d'",j++);
    }
    printf("\n");

    // tDataTree *temp=head;
    // tDataTree *new=(tDataTree*)malloc(sizeof(tDataTree));

    
}

void OPER_cat(tDataTree *head,char target[]){
    FILE *fp;
    char buffer[1000];

    /*
        tDtatTree裡去找
    */

    printf("\n");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    printf("\n");
}