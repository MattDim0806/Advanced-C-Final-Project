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
    
    tDataHead *head=Create_Init_DataHead("root");   //dump管理
    tDataPath *root=Create_Init_DataPath(head);   //路徑暫存
    tDataPath *curr_Path=root;
    
    //------------------------------------------------------------------

    ptr_Partition=UI_SelectFunc_Init(&SizeOfPartition);      //空間初始化
    SizeofRemaining=SizeOfPartition;
    UI_Help();
    
    //------------------------------------------------------------------
    

    while(1){
        strcpy(oper[0],"\0");
        strcpy(oper[1],"\0");
        UI_SelectFunc_Oper(oper,root,curr_Path);

        // printf("0:<%s>\n",oper[0]);
        // printf("1:<%s>\n",oper[1]);
        // printf("0:%d\n",!strcmp("ls",oper[0]));

        if(!strcmp("ls",oper[0])){
            OPER_ls(curr_Path->Head);
        }else if(!strcmp("cd",oper[0])){
            int FoR;
            // printf("h:%p,hn:%p,c:%p\n",head,head->next,curr_Path);
            FoR=OPER_cd(oper[1],root,curr_Path);
            printf("For:%d\n",FoR);
            if(FoR==1){
                curr_Path = curr_Path->next;
            }else if(FoR==0){
                tDataPath *temp=curr_Path;
                curr_Path = curr_Path->prev;
                free(temp);
            }
            // printf("h:%p,hn:%p,c:%p\n",head,head->next,curr_Path);
        }else if(!strcmp("rm",oper[0])){
            printf("==rm\n");
        }else if(!strcmp("mkdir",oper[0])){
            OPER_mkdir(curr_Path->Head,oper[1]);
        }else if(!strcmp("rmdir",oper[0])){
            printf("==rmdir\n");
        }else if(!strcmp("put",oper[0])){
            OPER_put(curr_Path->Head,oper[1]);
        }else if(!strcmp("get",oper[0])){
            printf("==get\n");
        }else if(!strcmp("cat",oper[0])){
            OPER_cat(curr_Path->Head, oper[1]);
        }else if(!strcmp("status",oper[0])){
            printf("==status\n");
        }else if(!strcmp("help",oper[0])){
            UI_Help();
        }else if(!strcmp("exit",oper[0])){
            printf("==exit\n");
        }else{
            printf("no such operation \n");
        }
        printf("\nSizeofRemaining: %d\n",SizeofRemaining);
        printf("\nHead: %s\n",head->Name);
        printf("\nHead: %s\n",curr_Path->Head->Name);
    } 
 
}