#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

//----------------------------------------------------------------------------------

#include "ui.h"

//----------------------------------------------------------------------------------

extern int SizeofRemaining;

//----------------------------------------------------------------------------------

char* UI_SelectFunc_Init(int *SizeOfPartition){
    int select;

    do{
        printf("options:\n");
        printf("  1.loads from file\n");
        printf("  2.create new partition in memory\n");
        scanf("%d",&select);

        if(select==1){
            OPER_LoadDump();
        }else if(select==2){
            printf("Input size of a new partition (example 1024000):");
            scanf("%d",SizeOfPartition);
            getchar();
            printf("partition size = %d\n\n",*SizeOfPartition);
            
            char *ptr_Partition=calloc(*SizeOfPartition,sizeof(char));
            if (ptr_Partition!=NULL){
                printf("Make new patition successful !\n");
                return ptr_Partition;
            }else{
                printf("Make new patition failed !\n");
            }
        }
    }while(!(select==1||select==2));
}

void UI_SelectFunc_Oper(char oper[][10],tDataPath *root,tDataPath *curr_Path){
    int i=0;
    char InputString[20]="";
    tDataPath *temp=root;
    
    //產生路徑
    printf("\x1B[0m""/");                                            
    while(curr_Path!=root && temp!=curr_Path){
        temp=temp->next;
        printf("%s/",temp->folder);
    }
    printf(" $ ");

    //讀取輸入轉換為運算及引數
    fgets(InputString, sizeof(InputString), stdin);
    char *token = strtok(InputString," ");           //使用空格切割

    while (token != NULL) {                          //切割&處理字符
        if(i<2){
            if (token[strlen(token) - 1] == '\n') {
                token[strlen(token) - 1] = '\0';
            }
            strcpy(oper[i++],token);
        }
        token = strtok(NULL," ");
    }
}

void UI_Help(void){
    printf("List of commands\n");
    printf("'ls' list directory\n");
    printf("'cd' change directory\n");
    printf("'rm' remove\n");
    printf("'mkdir' mack directory\n");
    printf("'rmdir' remove directory\n");
    printf("'put' put file into the space\n");
    printf("'get' get file from the space\n");
    printf("'cat' show content\n");
    printf("'status' show of the space\n");
    printf("'help'\n");
    printf("'exit' exit and store img'\n");
}

void UI_status(int SizeOfPartition){
    printf("Partition size:\t%d\n",SizeOfPartition);
    printf("free space:\t%d\n",SizeofRemaining);
}