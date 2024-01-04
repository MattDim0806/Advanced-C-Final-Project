#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <sys/stat.h>

//----------------------------------------------------------------------------------

#include "data.h"

//----------------------------------------------------------------------------------

extern int SizeofRemaining;

//----------------------------------------------------------------------------------

tDataPath* Create_Init_DataPath(tDataHead *head) {
    tDataPath* root = (tDataPath*)malloc(sizeof(tDataPath));
    strcpy(root->folder,"root");
    root->next = NULL;
    root->prev = NULL;
    root->Head=head;

    return root;
}

tDataHead* Create_Init_DataHead(char Name[]) {
    tDataHead* head = (tDataHead*)malloc(sizeof(tDataHead));
    strcpy(head->Name,Name);
    head->next = NULL;

    SizeofRemaining -= sizeof(tDataHead);
    return head;
}

void Add_DataPath(tDataPath* curr_Path,char target[],tDataHead *head) {
    tDataPath* new_path = (tDataPath*)malloc(sizeof(tDataPath));

    strcpy(new_path->folder,target);
    curr_Path->next = new_path;
    new_path->prev = curr_Path;
    new_path->Head=head;
}

void Del_DataPath(tDataPath *curr_Path){
    curr_Path->prev->next=NULL;
}

void OPER_LoadDump() {     //Load ().dump
    FILE* fp;
    char LoadFile[15];

    printf("Load Flie Name:");
    scanf("%s", LoadFile);

    fp = fopen(LoadFile, "r+");
    if (fp == NULL) {
        printf("failed to open the file.\n");
    }
    else {
        printf("Load Success.\n");
    }
}

void OPER_ls(tDataHead* head) {
    if (head->next == NULL) {
        printf("\n");
        return;
    }
    tDataTree* temp = head->next;

    while (temp != NULL) {
        if (temp->folder == 1) {
            printf("\x1B[0;34m""%s ", temp->FileName);
        }
        else {
            printf("\x1B[0m""%s ", temp->FileName);
        }

        if (temp->Right == NULL) {
            break;
        }
        temp = temp->Right;
    }
    printf("\n");
}

int OPER_cd(char target[],tDataPath *root,tDataPath *curr_Path){
    int exit=0;
    tDataTree *temp;
    tDataHead *head=curr_Path->Head;

    
    if(!strcmp(target,"..")){             //回上層
        if(!strcmp(head->Name,"root")){   //已在root
            printf("already in the root\n");
        }else{
            Del_DataPath(curr_Path);
            return 0;                     //0表示路徑往上走
        }
    }else{                                //往下層
        if (head->next != NULL) {
            temp = head->next;
            while(1){
                if((!strcmp(temp->FileName,target)) && temp->folder==1){   //尋找子目錄 
                    exit=1;
                    break;
                }
                if(temp->Right!=NULL){                                     //非空，繼續搜尋
                    temp=temp->Right;
                }else{
                    break;
                }
            }
        }
        if(exit==1){                                             //存在子目錄
            Add_DataPath(curr_Path,temp->FileName,temp->Left);   //添加路徑               
            return 1;                                            //1表示路徑往下走
        }
    }
    printf("Folder does not exist !\n");
    return -1;
}

void OPER_mkdir(tDataHead *head,char target[]){
    tDataTree* new = (tDataTree*)malloc(sizeof(tDataTree));
    SizeofRemaining -= sizeof(tDataTree);

    strcpy(new->FileName, target);
    new->content = NULL;
    new->folder = 1;
    new->Left = Create_Init_DataHead(target); 
    
    new->Right = NULL;
    new->size = 0;

    if (head->next == NULL) {
        new->parent = NULL;
        head->next = new;
    }
    else {
        tDataTree* temp = head->next;

        while ((temp->Right) != NULL) {
            temp = temp->Right;
        }
        new->parent = temp;
        temp->Right = new;
    }
}

void OPER_put(tDataHead* head, char target[]) {
    int size;
    char* content;
    struct stat st;
    FILE* fp;

    fp = fopen(target, "rb");
    if (fp == NULL) {
        printf("failed to open file '%s'\n", target);
        return;
    }

    stat(target, &st);
    size = st.st_size;

    if (SizeofRemaining < size) {
        printf("Not enough remaining space !\n");
        return;
    }

    content = (char*)malloc(size);
    SizeofRemaining -= sizeof(tDataTree);

    fread(content, 1, size, fp);
    fclose(fp);

    // -----------------------------------------------------
 
    tDataTree* new = (tDataTree*)malloc(sizeof(tDataTree));
    SizeofRemaining -= sizeof(tDataTree);    //結構大小

    strcpy(new->FileName, target);
    new->content = content;
    new->folder = 0;
    new->Left = NULL;
    new->Right = NULL;
    new->size = size;
    SizeofRemaining -= size;                 //內容大小

    if (head->next == NULL) {
        new->parent = NULL; 
        head->next = new;
    }
    else {
        tDataTree* temp = head->next;

        while ((temp->Right) != NULL) {
            temp = temp->Right;
        }
        new->parent=temp;
        temp->Right = new;
    }

    // printf("new'' name:%s,f:%d,l:%p,r:%p,p:%p,size:%d\n",new->FileName,new->folder,new->Left,new->Right,new->parent,new->size);
    // printf("head' name:%s,f:%d,l:%p,r:%p,p:%p,size:%d\n",head->FileName,head->folder,head->Left,head->Right,head->parent,head->size);
}

void OPER_get(tDataHead* head, char target[]) {
    int exit=0;
    tDataTree *temp;

    if (head->next != NULL) {
        temp = head->next;

        while(temp!=NULL)
        {
            if(!strcmp(temp->FileName,target)){
                exit=1;
                break;
            }
            if(temp->Right!=NULL){                                     //非空，繼續搜尋
                temp=temp->Right;
            }else{
                break;
            }
        }
    }
    if(exit==1){
        char* content=temp->content;
        char FileName[20]="Dump\\";
        
        strcat(FileName, target);
        CreateDirectory("Dump", NULL);
        FILE *fp = fopen(FileName, "wb");
        fwrite(content,sizeof(char),temp->size,fp);
        fclose(fp);
    }else{
        printf("File does not exist !\n");
        return;
    }
}

void OPER_cat(tDataHead* head, char target[]) {
    int exit=0;
    tDataTree *temp;

    if (head->next != NULL) {
        temp = head->next;

        while(temp!=NULL)
        {
            if(!strcmp(temp->FileName,target)){
                exit=1;
                break;
            }
            if(temp->Right!=NULL){                                     //非空，繼續搜尋
                temp=temp->Right;
            }else{
                break;
            }
        }
    }
    if(exit==1){
        char* content=temp->content;
        for (int count = 0; count < temp->size; count++) {
            printf("%c", content[count]);
        }
        printf("\n");
    }else{
        printf("File does not exist !\n");
        return;
    }
}