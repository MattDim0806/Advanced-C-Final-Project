#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

//----------------------------------------------------------------------------------

#include "ui.h"
#include "data.h"

//----------------------------------------------------------------------------------

extern int SizeofRemaining;

//----------------------------------------------------------------------------------

tDataTree* UI_SelectFunc_Init(int *SizeOfPartition){
    int select;

    do{
        printf("options:\n");
        printf("  1.loads from file\n");
        printf("  2.create new partition in memory\n");
        scanf("%d",&select);                                              //選擇讀取Dump檔案或是新建一個空間

        if(select==1){                                                    //若是讀取檔案則呼叫副程式處理
            tDataTree *load=OPER_LoadDump(SizeOfPartition);
            getchar();
            return load;
        }else if(select==2){                                              //若為新增
            printf("Input size of a new partition (example 1024000):");
            scanf("%d",SizeOfPartition);                                  //讀取欲新增Partition大小
            getchar();
            printf("partition size = %d\n\n",*SizeOfPartition); 
            
            SizeofRemaining=(*SizeOfPartition-sizeof(int));               //更新至變數(保留int空間儲存大小)
            return NULL;
        }
    }while(!(select==1||select==2));                                      //僅有二選項
}

void UI_SelectFunc_Oper(char oper[][10],tDataPath *root,tDataPath *curr_Path){
    int i=0;
    char InputString[20]="";                                    //使用者之輸入
    tDataPath *temp=root;                                       //用於走訪
    
    //產生路徑
    printf("\x1B[0m""/");                                            
    while(curr_Path!=root && temp!=curr_Path){
        temp=temp->next;
        printf("%s/",temp->folder);                             //透過DataPath的root以及current輸出路徑
    }
    printf(" $ ");

    //讀取輸入轉換為運算及引數
    fgets(InputString, sizeof(InputString), stdin);
    char *token = strtok(InputString," ");                      //使用空格切割

    while (token != NULL) {                                     //切割&處理字符
        if(i<2){                                                //輸入"操作種類","目標檔案"
            if (token[strlen(token) - 1] == '\n') {
                token[strlen(token) - 1] = '\0';
            }
            strcpy(oper[i++],token);
        }
        token = strtok(NULL," ");
    }

    // printf("oper[0]:%s\n",oper[0]);
    // printf("oper[1]:%s\n",oper[1]);
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