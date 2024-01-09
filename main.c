#include "main.h"
#include "ui.h"
#include "data.h"

//-----------------------------------------------------------------

int SizeofRemaining;

//-----------------------------------------------------------------

void main() {
    int SizeOfPartition=-1;            //新建之空間大小
    char *ptr_Partition;               //空間指標
    char oper[2][10];                  //輸入轉換為操作及目的檔案名稱

    //-------------------------------------------------------------

    ptr_Partition=UI_SelectFunc_Init(&SizeOfPartition); //空間初始化
    SizeofRemaining=SizeOfPartition;
    UI_Help();
    
    //-------------------------------------------------------------
    tDataHead *head=Create_Init_DataHead("root");    //資料節點管理
    tDataPath *root=Create_Init_DataPath(head);      //路徑管理
    tDataPath *curr_Path=root;                       //當前路徑
    
    //-------------------------------------------------------------

    while(1){
        strcpy(oper[0],"\0");                            //清空
        strcpy(oper[1],"\0");
        UI_SelectFunc_Oper(oper,root,curr_Path);         //選擇操作

        if(!strcmp("ls",oper[0])){                       //ls
            OPER_ls(curr_Path->Head);
        }else if(!strcmp("cd",oper[0])){
            int FoR;                                     //切換路徑至上層或下層
            FoR=OPER_cd(oper[1],root,curr_Path);
            if(FoR==1){
                curr_Path = curr_Path->next;             //下層=>路徑往下走
            }else if(FoR==0){
                tDataPath *temp=curr_Path;               //上層=>路徑往上走
                curr_Path = curr_Path->prev;
                free(temp);                              //並釋放掉DataPath空間
            }
        }else if(!strcmp("rm",oper[0])){                 //rm
            OPER_rm(curr_Path->Head,oper[1]);
        }else if(!strcmp("mkdir",oper[0])){              //mkdir
            OPER_mkdir(curr_Path->Head,oper[1]);
        }else if(!strcmp("rmdir",oper[0])){              //rmdir
            OPER_rmdir(curr_Path->Head,oper[1]);
        }else if(!strcmp("put",oper[0])){                //put
            OPER_put(curr_Path->Head,oper[1]);   
        }else if(!strcmp("get",oper[0])){                //get
            OPER_get(curr_Path->Head, oper[1]);  
        }else if(!strcmp("cat",oper[0])){                //cat
            OPER_cat(curr_Path->Head, oper[1]);
        }else if(!strcmp("status",oper[0])){             //status
            UI_status(SizeOfPartition);  
        }else if(!strcmp("help",oper[0])){               //help
            UI_Help();
        }else if(!strcmp("exit",oper[0])){               //exit
            OPER_SaveDump(head);
        }else{
            printf("no such operation \n");
        }
    } 
}