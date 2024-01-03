#include "main.h"
#include "ui.h"
#include "data.h"

//---------------------------------------------------------------------

int SizeofRemaining=0;

//---------------------------------------------------------------------

void main() {
    int SizeOfPartition=-1;           //空間大小
    char *ptr_Partition;              //空間指標
    char oper[2][10];                 //輸入command轉換運算及引數
    
    tDataPath *root=Create_Init_DataPath();   //路徑暫存
    tDataPath *curr_Path=root;
    tDataHead *head=Create_Init_DataHead();   //dump管理

    //------------------------------------------------------------------

    ptr_Partition=UI_SelectFunc_Init(&SizeOfPartition);      //空間初始化
    SizeofRemaining=SizeOfPartition;
    UI_Help();
    
    //------------------------------------------------------------------
    

    while(1){
        UI_SelectFunc_Oper(oper,root,curr_Path);
        // printf("0:<%s>\n",oper[0]);
        // printf("1:<%s>\n",oper[1]);
        // printf("0:%d\n",!strcmp("ls",oper[0]));

        if(!strcmp("ls",oper[0])){
            OPER_ls(head);
        }else if(!strcmp("cd",oper[0])){
            printf("==cd\n");
        }else if(!strcmp("rm",oper[0])){
            printf("==rm\n");
        }else if(!strcmp("mkdir",oper[0])){
            OPER_mkdir(head,oper[1]);
        }else if(!strcmp("rmdir",oper[0])){
            printf("==rmdir\n");
        }else if(!strcmp("put",oper[0])){
            OPER_put(head,oper[1]);
        }else if(!strcmp("get",oper[0])){
            printf("==get\n");
        }else if(!strcmp("cat",oper[0])){
            OPER_cat(head, oper[1]);
        }else if(!strcmp("status",oper[0])){
            printf("==status\n");
        }else if(!strcmp("help",oper[0])){
            UI_Help();
        }else if(!strcmp("exit",oper[0])){
            printf("==exit\n");
        }else{
            printf("no such operation \n");
        }
        // printf("\nSizeofRemaining: %d\n",SizeofRemaining);
    } 
 
}